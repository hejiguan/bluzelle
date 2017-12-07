#include <iostream>
#include <utility>
#include <thread>
#include <sstream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/lexical_cast.hpp>

#include "Raft.h"

static uint64_t s_transaction_id = 0;

Raft::Raft(boost::asio::io_service &ios, const NodeInfo &i)
        : ios_(ios),
          peers_(ios_),
          info_(i),
          storage_("./storage_" + info_.name_ + ".txt"),
          command_factory_(info_.state_, storage_),
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
    std::cout << "♥ ";

    if (crud_queue_.empty())
        {
        for (auto &p : peers_)
            {
            p.send_request(s_heartbeat_message);
            std::cout << ".";
            }
        }
    else
        {
        auto m = crud_queue_.front();
        for (auto &p : peers_)
            {
            //p.send_request(m.second);
            std::cout << ".";
            }
        crud_queue_.pop();
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
    auto pt = from_json_string(req);

    unique_ptr<Command> command = command_factory_.get_command(pt);
    if (info_.state_ == State::leader) // If I am leader CRUD commands need to be sent to followers.
        {
        ++ s_transaction_id;
        crud_queue_.push(std::make_pair<const string, const string>(
                boost::lexical_cast<string>(s_transaction_id), translate_message(req)));
        }

    string response;
    if (command != nullptr)
        response = to_json_string(command->operator()());
    else
        std::cout << "Unsupported command: '" << req << "'" << std::endl;
    return response;
}

boost::property_tree::ptree Raft::from_json_string(const string &s) const {
    std::stringstream ss;
    ss << s;

    boost::property_tree::ptree json;
    try
        {
        boost::property_tree::read_json(ss, json);
        }
    catch (boost::property_tree::json_parser_error &ex)
        {
        std::cout << "Raft::from_json_string() threw '" << ex.what() << "' parsing " << std::endl;
        std::cout << s << std::endl;
        }


    return json;
}

string Raft::to_json_string(boost::property_tree::ptree pt) const {
    try
        {
        std::stringstream ss;
        boost::property_tree::write_json(ss, pt);
        return ss.str();
        }
    catch (boost::property_tree::json_parser_error &ex)
        {
        std::cout << "Raft::to_json_string() threw '" << ex.what() << std::endl;
        }

    return string();
}

// From API to CRUD (from API<->leader to leader<->followers).
string Raft::translate_message(const string& s) const {
    auto m = s;
    size_t start_pos = m.find("bzn-api");
    if (start_pos != std::string::npos)
        {
        m.replace(start_pos, string("bzn-api").length(), "crud");
        }
    return s;
}

/*string Raft::handle_storage_request(const string& req) {
    auto m = from_json_string(req);
    if (m.get<string>("raft") != "append-entries")
        {
        return error_message(m, "Not a CRUD command. Ignored.");
        }

    if (m.get<string>("transaction-id").empty()) // All CRUD requests must come from leader and have signed transaction id.
        {
        return error_message(m, "CRUD requst is not originated from leader. Ignored");
        }

    auto data  = m.get_child("data.");

    string crud = data.get<string>("command");
    string k = data.get<string>("key");
    string v = data.get<string>("value");

    if (crud == "create")
        {
        storage_.create(k, v);
        return error_message(m, "ok");
        }
    else if (crud == "read")
        {
        v = storage_.read(k);
        if (v.empty())
            return error_message(m, "Value is missing");
        else
            {
            data.put("value", v);
            return to_json_string(m);
            }
        }
    else if (crud == "update")
        {
        storage_.update(k,v);
        return error_message(m, "ok");
        }
    else if (crud == "delete")
        {
        storage_.remove(k);
        return error_message(m, "ok");
        }

    return error_message(m, "Unsupported CRUD command");
}*/

/*string Raft::error_message(boost::property_tree::ptree& req, const string& error) {
    boost::property_tree::ptree msg;
    msg.put("raft", req.get<string>("raft"));
    msg.put("error", error);
    return to_json_string(msg);
}*/

