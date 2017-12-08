#ifndef BLUZELLE_COMMAND_H
#define BLUZELLE_COMMAND_H

#include "Storage.h"
#include <boost/property_tree/ptree.hpp>

class Command {
public:
    virtual boost::property_tree::ptree operator()() = 0;

    boost::property_tree::ptree success() {
        return error("success");
    }

    // Ieally result should look like:
    // {"bzn-result":"create", "transaction-id":"123", "data":{key":"key_one", "value":"value_one"}}
    boost::property_tree::ptree result(string res) {
        boost::property_tree::ptree pt;
        pt.put("result", res);
        return pt;
    }

    boost::property_tree::ptree error(string er) {
        boost::property_tree::ptree pt;
        pt.put("result", "command-here");
        pt.put("error", er);
        return pt;
    }
};

#endif //BLUZELLE_COMMAND_H
