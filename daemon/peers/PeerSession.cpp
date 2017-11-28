#include "PeerSession.h"

//#include <boost/date_time/posix_time/posix_time.hpp>


void fail(boost::system::error_code ec, char const *what); /*{
    std::cerr << what << ": " << ec.message() << "\n";
}*/

PeerSession::PeerSession(boost::asio::ip::tcp::socket socket)
        : ws_(std::move(socket)), strand_(ws_.get_io_service()) {
}

void PeerSession::run() {
    ws_.async_accept(
            strand_.wrap(std::bind(
                    &PeerSession::on_accept,
                    shared_from_this(),
                    std::placeholders::_1)));
}

void PeerSession::on_accept(boost::system::error_code ec) {
    if (ec)
        return fail(ec, "accept");

    do_read();
}

void PeerSession::do_read() {
    ws_.async_read(
            buffer_,
            strand_.wrap(std::bind(
                    &PeerSession::on_read,
                    shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2)));
}

void PeerSession::on_read(
        boost::system::error_code ec,
        std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    // This indicates that the session was closed
    if (ec == boost::beast::websocket::error::closed)
        return;

    if (ec)
        fail(ec, "read");

    std::stringstream ss;
    ss << boost::beast::buffers(buffer_.data());

    std::string response = ss.str(); // Echo it back for now.

    ws_.async_write(
            boost::asio::buffer(response),
            std::bind(
                    &PeerSession::on_write,
                    shared_from_this(),
                    std::placeholders::_1,
                    std::placeholders::_2));
}

void PeerSession::on_write(
        boost::system::error_code ec,
        std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "write");

    buffer_.consume(buffer_.size());

    do_read();
}