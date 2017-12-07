#ifndef BLUZELLE_COMMANDPROCESSOR_H
#define BLUZELLE_COMMANDPROCESSOR_H

#include <memory>
using std::unique_ptr;

#include "NodeInfo.hpp"
#include "Storage.h"
#include "Command.hpp"


class CommandFactory {
public:
    State& state_;
    Storage& storage_;

    bool is_raft(const boost::property_tree::ptree& s) const;
    bool is_crud(const boost::property_tree::ptree& s) const;
    bool is_api(const boost::property_tree::ptree& s) const;

    unique_ptr<Command> make_raft_command(const boost::property_tree::ptree& s) const;
    unique_ptr<Command> make_crud_command(const boost::property_tree::ptree& s) const;
    unique_ptr<Command> make_api_command(const boost::property_tree::ptree& s) const;

public:
    CommandFactory(State& s, Storage& st);
    unique_ptr<Command> get_command(const boost::property_tree::ptree& pt) const;
};

#endif //BLUZELLE_COMMANDPROCESSOR_H
