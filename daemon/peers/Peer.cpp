#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lexical_cast.hpp>

#include "Peer.h"

using std::shared_ptr;

Peer::Peer(NodeInfo i) : info_(std::move(i)){

}

string Peer::send_request(boost::asio::io_service& io, const string& req) {
    auto session = session_.lock();

    if (session == nullptr) // Check if we don't have a session.
        {
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::socket socket(io);

        try
            {
            auto lookup = resolver.resolve({info_.host_, boost::lexical_cast<string>(info_.port_)});

            boost::asio::connect(socket, lookup);

            auto s = std::make_shared<PeerSession>(std::move(socket));; // Store it for future use.
            s->run();
            session_ = s;
            }
        catch (std::exception& ex)
            {
            std::cout << "Cannot connect to "
                      << info_.host_ << ":"
                      << boost::lexical_cast<string>(info_.port_) << " '"
                      << ex.what() << "'" << std::endl;
            }

        session = session_.lock();
        }

    if (session != nullptr) // Check again in case we just created a session.
        {
        session->write_async(req);
        }
}

string Peer::handle_response(const string& resp) {
    std::cout << "<<" << resp << std::endl;
}