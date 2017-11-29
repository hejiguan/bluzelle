#ifndef BLUZELLE_NODEINFO_H
#define BLUZELLE_NODEINFO_H

#include <string>
#include<vector>

using std::string;
using std::vector;

#include "PeerSession.h"

enum class State {
    unknown,
    candidate,
    leader,
    follower,
};

class NodeInfo {
public:
    string ip_;
    ushort port_;

    string address_;
    State state_;

    string name_;
    string config_;

    std::weak_ptr<PeerSession> session_; // Corresponding session.s

    boost::posix_time::posix_time_system last_contacted_;

    NodeInfo(const string& ip,
             ushort port,
             const string& address,
             bool leader,
             const string& name)
    : ip_(ip), port_(port), address_(address), state_(State::unknown), name_(name) {}

    NodeInfo() {
        ip_ = "localhost";
        port_ = 58000;
        address_ = "0x0000000000000000000000000000000000000000";
        name_ = "this computer";
    }


    static NodeInfo this_node() { return NodeInfo();}
};

#endif //BLUZELLE_NODEINFO_H
