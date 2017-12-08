#include <boost/format.hpp>

#include "ApiReadCommand.h"

ApiReadCommand::ApiReadCommand(ApiCommandQueue& q, Storage& s, boost::property_tree::ptree pt)
        : queue_(q), storage_(s), pt_(std::move(pt)) {

}

boost::property_tree::ptree ApiReadCommand::operator()() {
    auto data  = pt_.get_child("data.");

    string key;
    if (data.count("key") > 0)
        key = data.get<string>("key");

    if (!key.empty())
        {
        string val = storage_.read(key); // Read from local storage, no need to send to followers.
        return result(val);
        }

    return error("key is missing");
}