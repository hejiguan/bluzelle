#include <boost/format.hpp>

#include "ApiCreateCommand.h"
#include "CrudCreateCommand.h"

ApiCreateCommand::ApiCreateCommand(ApiCommandQueue& q, Storage& s, string k, string v)
        : queue_(q), storage_(s), key_(std::move(k)), value_(std::move(v)) {

}

boost::property_tree::ptree ApiCreateCommand::operator()() {
    storage_.create(key_, value_);

    auto f =
            boost::format("{\"crud\":\"create\", \"transaction-id\":\"123\", \"data\":{key\":\"%s\", \"value\":\"%s\"}}")
            % key_ % value_;

    queue_.push(std::make_pair("123", f.str()));

    return success();
}