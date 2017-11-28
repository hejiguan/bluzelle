#include <iostream>

#include <boost/lexical_cast.hpp>

#include "Node.h"


Node::Node(const string &address,
           ushort port, const string &configpath)
        : server_("127.0.0.1", port, 1),
          storage_("./storage_" + boost::lexical_cast<string>(port) + ".txt") {
    //info_ = NodeInfo::this_node();
}

void Node::run() {
    server_.run(); // Start accepting connections.
    // Wait random amount of time 1-10 seconds.

    /* // load list of known nodes from file.
     * // Start RAFT
     * // Do we have a leader?
     * // Start election process.
     * //   Any takers: vote YES
     * //   Endorse itself, wait for votes to come, assume leader position.
     * */

    // PeerServer know about RAFT, RAFT doesn't know about PS.
    // Raft knows about PeerDialer.

    std::cout << "Press a key to stop" << std::endl;
    getchar();
    std::cout << "Stopping..." << std::endl;
}