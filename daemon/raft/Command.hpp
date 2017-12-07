#ifndef BLUZELLE_COMMAND_H
#define BLUZELLE_COMMAND_H

#include "Storage.h"
#include <boost/property_tree/ptree.hpp>

enum class CommandType {
    unknown,
    crud_create,
    crud_read,
    crud_update,
    crud_delete,
    raft_heartbeat,
    // raft_start_election
    // raft_...
};


class Command {
public:
    virtual boost::property_tree::ptree operator()() = 0;
};

#endif //BLUZELLE_COMMAND_H
