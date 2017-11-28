#ifndef BLUZELLE_PEERSERVER_H
#define BLUZELLE_PEERSERVER_H

#include <string>

using std::string;

#include <boost/asio.hpp>

#include "PeerListener.h"

class PeerServer {
private:
    boost::asio::ip::address ip_address_;
    unsigned short port_;
    size_t threads_;

    bool running_ = false;

public:
    PeerServer(const string &ip_address,
               unsigned short port,
               unsigned short threads);

    void run();

    bool is_running() const;
};

#endif //BLUZELLE_PEERSERVER_H
