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

enum class LogRecordStatus {
    unknown,
    uncommitted,
    committed,
};

class Raft {
    const string s_heartbeat_message = "{\"raft\":\"beep\"}";

private:
    static const uint raft_default_heartbeat_interval_milliseconds = 1050; // 50 millisec.

    boost::asio::io_service& ios_;

    PeerList peers_; // List of known peers, connected or not, some came from file some are just connected.
    NodeInfo info_; // This node info.
    Storage storage_; // Where the RAFTs log is replicated.
    queue<pair<const string, const string>> crud_queue_;

    CommandFactory command_factory_;

    boost::asio::deadline_timer heartbeat_timer_;
    void heartbeat();

    boost::property_tree::ptree from_json_string(const string& s) const;
    string to_json_string(boost::property_tree::ptree j) const;

    string translate_message(const string& m) const;
public:
    Raft(boost::asio::io_service& io, const NodeInfo& info); // Node name, other params will be added.
    void run();
    string handle_request(const string& req);
};

#endif //BLUZELLE_RAFT_H
