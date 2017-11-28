#ifndef BLUZELLE_PEER_H
#define BLUZELLE_PEER_H

#include "NodeInfo.hpp"

class Peer {
public:
    NodeInfo info_;

    bool is_active();
    bool is_leader();

};

#endif //BLUZELLE_PEER_H
