#ifndef BLUZELLE_APIREADCOMMAND_H_H
#define BLUZELLE_APIREADCOMMAND_H_H

#include "Command.hpp"
#include "ApiCommandQueue.h"
#include "Storage.h"

class ApiReadCommand : public Command {
public:
    ApiCommandQueue& queue_;
    Storage& storage_;
    string key_;

public:
    ApiReadCommand(ApiCommandQueue& q, Storage& s, string k);
    virtual boost::property_tree::ptree operator()();
};

#endif //BLUZELLE_APIREADCOMMAND_H_H
