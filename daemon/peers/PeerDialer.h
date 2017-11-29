#ifndef BLUZELLE_PEERDIALER_H
#define BLUZELLE_PEERDIALER_H

#include <string>

using std::string;

class PeerDialer {
public:
    PeerDialer();

    string send_request(const string& req);
};

#endif //BLUZELLE_PEERDIALER_H
