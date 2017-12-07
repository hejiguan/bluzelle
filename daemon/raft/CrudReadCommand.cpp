#include "CrudReadCommand.h"

CrudReadCommand::CrudReadCommand(Storage& s)
        : storage_(s) {

}

boost::property_tree::ptree CrudReadCommand::operator()() {
        boost::property_tree::ptree result;

        return result;
}