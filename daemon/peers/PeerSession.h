#ifndef BLUZELLE_PEERSESSION_H
#define BLUZELLE_PEERSESSION_H

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>

class PeerSession : public std::enable_shared_from_this<PeerSession> {
private:
    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_;
    boost::asio::io_service::strand strand_;
    boost::beast::multi_buffer buffer_;

public:
    explicit PeerSession(boost::asio::ip::tcp::socket socket);

    void run();

    void on_accept(boost::system::error_code ec);

    void do_read();

    void on_read(boost::system::error_code ec,
            std::size_t bytes_transferred);

    void on_write(boost::system::error_code ec,
                  std::size_t bytes_transferred);
};

#endif //BLUZELLE_PEERSESSION_H
