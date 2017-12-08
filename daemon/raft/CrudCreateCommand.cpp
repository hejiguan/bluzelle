#include "CrudCreateCommand.h"

CrudCreateCommand::CrudCreateCommand(Storage& s, string k, string v)
    : storage_(s), key_(std::move(k)), value_(std::move(v)) {

}

boost::property_tree::ptree CrudCreateCommand::operator()() {
    storage_.create(key_, value_);
    return success();
}
