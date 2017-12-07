#include "CrudCreateCommand.h"

CrudCreateCommand::CrudCreateCommand(Storage& s)
    : storage_(s) {

}

boost::property_tree::ptree CrudCreateCommand::operator()() {
    boost::property_tree::ptree result;
    return result;
}
