#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/lexical_cast.hpp>

#include <boost/beast/websocket.hpp>

#include "Peer.h"

using std::shared_ptr;

Peer::Peer(NodeInfo i) : info_(std::move(i)){

}

string Peer::send_request(boost::asio::io_service& ios, const string& req) {
    if (session_ == nullptr) // Check if we don't have a session.
        {
        boost::asio::ip::tcp::resolver resolver(ios);
        boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{ios};

        try
            {
            // Resolve, connect, handshake.
            auto lookup = resolver.resolve({info_.host_, boost::lexical_cast<string>(info_.port_)});
            boost::asio::connect(ws.next_layer(), lookup);
            ws.handshake(info_.host_, "/");

            session_ = std::make_shared<PeerSession>(std::move(ws.next_layer())); // Store it for future use.
            }
        catch (std::exception& ex)
            {
            std::cout << "Cannot connect to "
                      << info_.host_ << ":"
                      << boost::lexical_cast<string>(info_.port_) << " '"
                      << ex.what() << "'" << std::endl;
            }
        }

    if (session_ != nullptr) // Check again in case we just created a session.
        {
        session_->write_async(req);
        }
}

string Peer::handle_response(const string& resp) {
    std::cout << "<<" << resp << std::endl;
}