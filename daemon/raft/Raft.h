#ifndef BLUZELLE_RAFT_H
#define BLUZELLE_RAFT_H

#include <string>
#include <thread>
#include <queue>
#include <utility>

using std::string;
using std::queue;
using std::pair;

#include <boost/property_tree/ptree.hpp>

#include "PeerList.h"
#include "NodeInfo.hpp"
#include "Storage.h"
#include "CommandFactory.h"
#include "ApiCommandQueue.h"


class Raft {
    const string s_heartbeat_message = "{\"raft\":\"beep\"}";

private:
    static const uint raft_default_heartbeat_interval_milliseconds = 5050; // 50 millisec.

    boost::asio::io_service& ios_;

    PeerList peers_; // List of known peers, connected or not, some came from file some are just connected.
    NodeInfo info_; // This node info.
    Storage storage_; // Where the RAFTs log is replicated.
    ApiCommandQueue peer_queue_; // Keeps data to be sent to peers.

    CommandFactory command_factory_;

    boost::asio::deadline_timer heartbeat_timer_;
    void heartbeat();

public:
    Raft(boost::asio::io_service& io,
         const NodeInfo& info); // Node name, other params will be added.

    void run();

    string handle_request(const string& req);
};

#endif //BLUZELLE_RAFT_H
