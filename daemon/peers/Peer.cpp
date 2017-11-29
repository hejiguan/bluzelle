#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "Peer.h"

using std::shared_ptr;

string Peer::send_request(boost::asio::io_service& io, const string& req) {
    auto session = session_.lock();
    if (session != nullptr) // Peer already connected and has a running session.
        {
        // [todo] Implement async_wrote()
        //session->write_asinc(req);
        }
    else  //Peer is not conected, create a session.
        {
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::socket socket(io);

        auto lookup = resolver.resolve({"", ""/*info_.host_.c_str(), info_.port_*/});

        boost::asio::connect(socket, lookup);

        auto s = std::make_shared<PeerSession>(std::move(socket));
        session_ = s; // Store it for future use.
        s->run();
        }
}