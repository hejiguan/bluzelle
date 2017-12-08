#ifndef BLUZELLE_APICREATECOMMAND_H
#define BLUZELLE_APICREATECOMMAND_H

#include "Command.hpp"
#include "ApiCommandQueue.h"
#include "Storage.h"

class ApiCreateCommand : public Command {
public:
    ApiCommandQueue queue_;
    Storage& storage_;

    string key_;
    string value_;

public:
    ApiCreateCommand(ApiCommandQueue& q, Storage& s, string k, string v);
    virtual boost::property_tree::ptree operator()();
};

#endif //BLUZELLE_APICREATECOMMAND_H
