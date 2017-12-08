#include <boost/format.hpp>

#include "ApiReadCommand.h"

ApiReadCommand::ApiReadCommand(ApiCommandQueue& q, Storage& s, string k)
        : queue_(q), storage_(s), key_(std::move(k)) {

}

boost::property_tree::ptree ApiReadCommand::operator()() {
    auto val = storage_.read(key_);

    /*auto f =
            boost::format("{\"crud\":\"read\", \"transaction-id\":\"123\", \"data\":{key\":\"%s\"}}")
            % key_;
    queue_.push(std::make_pair("123", f.str()));*/

    return result(val);
}