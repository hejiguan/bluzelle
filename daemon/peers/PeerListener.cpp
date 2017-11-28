#include "PeerListener.h"
#include "PeerSession.h"

void fail(boost::system::error_code ec, char const *what); // In PeerSession.cpp

PeerListener::PeerListener(boost::asio::io_service &ios,
                           boost::asio::ip::tcp::endpoint endpoint)
        : acceptor_(ios), socket_(ios) {
    boost::system::error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec)
        {
        fail(ec, "open");
        return;
        }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if (ec)
        {
        fail(ec, "bind");
        return;
        }

    // Start listening for connections
    acceptor_.listen(
            boost::asio::socket_base::max_connections, ec);
    if (ec)
        {
        fail(ec, "listen");
        return;
        }
}

// Start accepting incoming connections
void PeerListener::run() {
    if (!acceptor_.is_open())
        return;
    do_accept();
}

void PeerListener::do_accept() {
    acceptor_.async_accept(
            socket_,
            std::bind(
                    &PeerListener::on_accept,
                    shared_from_this(),
                    std::placeholders::_1));
}

void PeerListener::on_accept(boost::system::error_code ec) {
    if (ec)
        {
        fail(ec, "accept");
        }
    else
        {
        // Create the session and run it
        auto s = std::make_shared<PeerSession>(std::move(socket_));
        s->run();
        //sessions_.push_back(s);
        }

    do_accept(); // Accept another connection
}
