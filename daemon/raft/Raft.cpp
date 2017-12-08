#include <iostream>
#include <utility>
#include <thread>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include "Raft.h"
#include "JsonTools.h"

static uint64_t s_transaction_id = 0;

Raft::Raft(boost::asio::io_service &ios, const NodeInfo &i)
        : ios_(ios),
          peers_(ios_),
          info_(i),
          storage_("./storage_" + info_.name_ + ".txt"),
          command_factory_(info_.state_, storage_, peer_queue_),
          heartbeat_timer_(ios_,
                           boost::posix_time::milliseconds(raft_default_heartbeat_interval_milliseconds)) {

}

void Raft::run() {
    // Leader is hardcoded: node with port ending with '0' is always a leader.
    if (info_.port_ % 10 == 0) // This node is leader. [todo] replace with actual leader election.
        {
        info_.state_ = State::leader;
        }
    else
        {
        info_.state_ = State::follower;
        }

    if (info_.state_ == State::leader)
        {
        std::cout << "\n\tI am leader" << std::endl;
        heartbeat_timer_.async_wait(
                boost::bind(&Raft::heartbeat,
                            this)); // start heartbeat.
        }
    else
        {
        std::cout << "\n\tI am follower" << std::endl;
        }

    // How CRUD works? Am I writing to any node and it sends it to leader or I can write to leader only.
    // All goes through leader. Leader receives log entry and writes it locally, its state is uncommited.
    // Then leader sends the entry to all followers and waits for confirmation. When confirmation received
    // from majority the state changed to 'committed'. Then leader notify followers that entry is committed.
}

//void Raft::start_leader_election() {
/*
 * If node haven't heard from leader it can start election.
 * Change state to State::candidate and request votes
*/
    // Election_Timeout -> time to wait before starting new election (become a candidate)
    // Random in 150-300 ms interval

    // After Election_Timeout follower becomes candidate and start election term, votes for itself and sends
    // Request_Vote messages to other nodes.
    // If node hasn't voted for itself or didn't reply to others node Request_Vote it votes "YES" otherwise "NO"
    // An resets election timeout (won't start new election).
    // When candidate received majority of votes it sets itself as leader.
    // The leader sends Append_Entry messages to followers in Heartbeat_Timeout intervals. Followers respond
    // If follower don't receive Append_Entry in time alotted new election term starts.
    // Handle Split_Vote
//}

void Raft::heartbeat() {
    if (peer_queue_.empty())
        {
        std::cout << "♥ ";
        for (auto &p : peers_)
            {
            p.send_request(s_heartbeat_message);
            std::cout << ".";
            }
        }
    else
        {
        std::cout << "❥ ";
        auto m = peer_queue_.front();
        for (auto &p : peers_)
            {
            p.send_request(m.second);
            std::cout << ".";
            }
        peer_queue_.pop();
        }
    std::cout << std::endl;

    // Re-arm timer.
    heartbeat_timer_.expires_at(
            heartbeat_timer_.expires_at() +
            boost::posix_time::milliseconds(raft_default_heartbeat_interval_milliseconds));
    heartbeat_timer_.async_wait(
            boost::bind(&Raft::heartbeat,
                        this));
}

string Raft::handle_request(const string &req) {
    auto pt = pt_from_json_string(req);

    unique_ptr<Command> command = command_factory_.get_command(pt);
    string response = pt_to_json_string(command->operator()());

    return response;
}



