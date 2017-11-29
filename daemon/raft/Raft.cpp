#include "Raft.h"

Raft::Raft(const NodeInfo& info) : storage_("./storage_" + info.name_ + ".txt") {

}

void Raft::run() {
    // Read peers file
    // Wait for 1-10 seconds at random.
    // Do I have a leader to talk?

    // Leader is hardcoded: node with port ending with '0' is always a leader.

    if (info_.port_ % 10 == 0)// This node is leader. [todo] replace with actual leader election.
        info_.state_ == State::leader;
    else // I am not the leader, find out who is.
        {
        // Check if any connected node is a leader
        // reach out to all the rest of known nodes and ask them if one of them is a leader.
        // Two lists: known nodes and connected nodes (these have sessions)
        }

    // How CRUD works? Am I writing to any node and it sends it to leader or I can write to leader only.
    // All goes through leader. Leader receives log entry and writes it locally, its state is uncommited.
    // Then leader sends the entry to all followers and waits for confirmation. When confirmation received
    // from majority the state changed to 'committed'. Then leader notify followers that entry is committed.
 }

void Raft::start_leader_election() {
/*
 * If node haven't heard from leader it can start election.
 * Change state to State::candidate and request votes
*/
    // Election_Timeout -> time to wait before starting new election (become a candidate)
    // Random in 150-300 ms interval

    // After Eection_Timeout follower becomes candidate nd start election term, votes for itself and sends
    // Request_Vote messages to other nodes.
    // If node hasn't voted for itself or didn't reply to others node Request_Vote it votes "YES" otherwise "NO"
    // An resets election timeout (won't start new election).
    // When candidate received majority of votes it sets itself as leader.
    // The leader sends Append_Entry messages to followers in Heartbeat_Tieout intervals. Followers respond
    // If follower don't receive Append_Entry in time alotted new election term starts.
    // Handle Split_Vote
}

string Raft::handle_request(const string& req) {
    // [todo] command factory

    // Who_is_the_Leader
    // {"raft":"who_is_the_leader"} ->
    // {"raft":"who_is_the_leader", "leader":"192.168.1.1"} <-

    // {"raft":"request-vote"} ->
    // {"raft":"request-vote", "vote":"yes"} <-

    // {"raft":"append-entries", "data":{}} -> heartbeat
    // {"raft":"append-entries", "data":{"transaction-id":""}}

    // {"raft":"append-entries", "data":{"command":"create|read|update|delete" "key":"key", "value":"value", "transaction-id":"id-of-transaction"}} -> CRUD command, id of the transaction on leader node.
    // {"raft":"append-entries", "data":{"transaction-id":"id-of-transaction"}}

}


/*
 * command interface:
 * reqs are inbound and come from PeerServer
 * cmds are outbound and sent via PeerDialer
 * reqs can be of type "raft" only
 * cmds can be both "raft" and "crud"
 *
 * {"cmd|req":"raft|crud"}
 */