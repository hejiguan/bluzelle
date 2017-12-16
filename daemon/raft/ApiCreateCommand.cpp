#include <boost/format.hpp>

#include "ApiCreateCommand.h"
#include "JsonTools.h"

ApiCreateCommand::ApiCreateCommand(ApiCommandQueue& q, Storage& s, boost::property_tree::ptree pt)
        : queue_(q), storage_(s), pt_(pt) {

}

boost::property_tree::ptree ApiCreateCommand::operator()() {
    auto data  = pt_.get_child("data.");

    string key;
    if (data.count("key") > 0)
        key = data.get<string>("key");

    string val;
    if (data.count("value") > 0)
        val = data.get<string>("value");

    if (!key.empty())
        {
        // Store locally.
        storage_.create(key, val);

        // Translate BZN-API command to CRUD command.
        /*auto c = pt_.get<string>("bzn-api");
        pt_.erase("bzn-api");
        pt_.put("crud", c); // Doesn't work!
        */


        // {"bzn-api":"create", "transaction-id":"123", "data":{key":"key_one", "value":"value_one"}}
        // {"crud":"create", "transaction-id":"123", "data":{key":"key_one", "value":"value_one"}}
        string resp = pt_to_json_string(pt_);
        resp.replace(resp.find("bzn-api"), 7, "crud");

        queue_.push(std::make_pair<string,string>(
                pt_.get<string>("transaction-id"),
                std::move(resp)/*pt_to_json_string(pt_)*/));

        std::cout << "Queue size: " << queue_.size() << std::endl;

        return success();
        }


    return error("key is missing");
}