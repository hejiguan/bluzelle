#include "CommandFactory.h"

#include "RaftHeartbeatCommand.h"
#include "CrudCreateCommand.h"
#include "CrudReadCommand.h"

CommandFactory::CommandFactory(State& s, Storage& st)
    : state_(s), storage_(st) {

}


unique_ptr<Command> CommandFactory::get_command(const boost::property_tree::ptree& pt) const {
    if (is_raft(pt))
        return make_raft_command(pt);

    if (is_crud(pt))
        return make_crud_command(pt);

    if (is_api(pt))
        return make_api_command(pt);

    // Unsuported command.
    return nullptr;
}

// {"raft":"beep"} // This is a heartbeat command.
bool CommandFactory::is_raft(const boost::property_tree::ptree& pt) const {
    return pt.count("raft") > 0;
}

// CRUD commands go from leader to followers. I.e they are log replication commands.
// {"crud":"create", "transaction-id":"123", "data":{key":"key_one", "value":"value_one"}}
bool CommandFactory::is_crud(const boost::property_tree::ptree& pt) const {
    return pt.count("crud") > 0;
}

// API commands go from API to leader. Same format as CRUD.
// In future we can change either API or CRUD command format so better keep them separate.
// {"bzn-api":"create", "transaction-id":"123", "data":{key":"key_one", "value":"value_one"}}
bool CommandFactory::is_api(const boost::property_tree::ptree& pt) const {
    return pt.count("bzn-api") > 0;
}

unique_ptr<Command> CommandFactory::make_raft_command(const boost::property_tree::ptree& pt) const {
    auto cmd = pt.get<string>("raft");
    if (cmd == "beep")
        return std::make_unique<RaftHeartbeatCommand>();

    return nullptr;
}

unique_ptr<Command> CommandFactory::make_crud_command(const boost::property_tree::ptree& pt) const {
    auto cmd = pt.get<string>("crud");

    if (cmd == "create")
        return std::make_unique<CrudCreateCommand>(storage_);

    if (cmd == "read")
        return std::make_unique<CrudReadCommand>(storage_);

    return nullptr;
}

unique_ptr<Command> CommandFactory::make_api_command(const boost::property_tree::ptree& pt) const {
    auto cmd = pt.get<string>("bzn-api");

    if (cmd == "create")
        return std::make_unique<CrudCreateCommand>(storage_);

    if (cmd == "read")
        return std::make_unique<CrudReadCommand>(storage_);

    return nullptr;
}