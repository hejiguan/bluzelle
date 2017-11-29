#ifndef BLUZELLE_NODE_H
#define BLUZELLE_NODE_H

#include <string>

using std::string;

#include "PeerServer.h"
#include "NodeInfo.hpp"
#include "MessageInfo.hpp"
#include "Raft.h"

class Node {
private:
    PeerServer server_; // Serves inbound connections.
    Raft raft_; // RAFT protocol state machine.

public:
    Node(const NodeInfo& i);

    void run();

    vector<NodeInfo> get_peers() const; // returns list of all known peers connected or not.
    vector<MessageInfo> get_messages() const; // returns list of messages sent by this node, since timestamp.
};

#endif //BLUZELLE_NODE_H
