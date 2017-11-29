#ifndef BLUZELLE_RAFT_H
#define BLUZELLE_RAFT_H

#include <string>

using std::string;

#include "PeerList.h"
#include "NodeInfo.hpp"
#include "Storage.h"
#include "PeerDialer.h"

enum class LogRecordStatus {
    unknown,
    uncomitted,
    committed,
};

class Raft {
private:
    PeerList peers_; // List of known peers, connected or not, some came from file some are just connected.
    PeerDialer dialer_; // Creates outbound connections.
    NodeInfo info_; // This node info.
    Storage storage_; // Where the RAFTs log is replicated.

public:
    Raft(const NodeInfo& info); // Node name, other params will be added.
    void run();
    void start_leader_election();

    string handle_request(const string& req);
};

#endif //BLUZELLE_RAFT_H
