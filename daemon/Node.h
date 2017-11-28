#ifndef BLUZELLE_NODE_H
#define BLUZELLE_NODE_H

#include <string>

using std::string;

#include "PeerServer.h"
#include "PeerList.h"
#include "NodeInfo.hpp"
#include "Storage.h"
#include "PeerDialer.h"
#include "Raft.h"

class Node {
private:
    PeerServer server_; // Serves inbound connections.
    PeerDialer dialer_; // Creates outbound connections.

    NodeInfo info_; // This node info.

    PeerList peers_; // List of known peers, connected or not, some came from file some are just connected.

    Storage storage_; // Where the RAFTs log is replicated.

    Raft raft_; // RAFT protocol state machine.

public:
    Node(const string& address, ushort port, const string& configpath);

    void run();
};

#endif //BLUZELLE_NODE_H
