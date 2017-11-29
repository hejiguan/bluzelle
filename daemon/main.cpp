 // TODO: move this to the correct module

#include <iostream>
#include <boost/thread.hpp>


#include "CommandLineOptions.h"
#include "Node.h"


int main(int argc, char *argv[]) {
    CommandLineOptions options;

    if (!options.parse(argc, argv))
        {
        std::cout << options.get_last_error() << std::endl;
        return 1;
        }

    string address = options.get_address();
    if (!CommandLineOptions::is_valid_ethereum_address(address))
        {
        std::cout << address << " is not a valid Ethereum address." << std::endl;
        return 1;
        }

    uint port = options.get_port();
    if (!CommandLineOptions::is_valid_port(port))
        {
        std::cout << port << " is not a valid port. Please pick a port in 49152 - 65535 range" << std::endl;
        return 1;
        }

    std::cout << "Running node: " << options.get_address() << std::endl
              << "     on port: " << options.get_port() << std::endl
              << " config path: " << options.get_config() << std::endl;


    NodeInfo info = NodeInfo::this_node();
    info.port_ = port;
    info.address_ = address;
    info.config_ = options.get_config();
    info.name_ = "Node_running_on_port_" + boost::lexical_cast<string>(port);

    Node this_node(info);
    try
        {
        this_node.run();
        }
    catch (std::exception& ex)
        {
        std::cout << ex.what() << std::endl;
        return 1;
        }


    return 0;
}