#ifndef BLUZELLE_PEER_H
#define BLUZELLE_PEER_H

#include <memory>

using std::shared_ptr;

#include "NodeInfo.hpp"
#include "PeerSession.h"

class Peer {
public:
    NodeInfo info_; // This node info.
    shared_ptr<PeerSession> session_; // Corresponding session.

    Peer(NodeInfo i);

    string send_request(boost::asio::io_service& io, const string& req);
    string handle_response(const string& req);

    bool is_active();
    bool is_leader();
};

#endif //BLUZELLE_PEER_H
