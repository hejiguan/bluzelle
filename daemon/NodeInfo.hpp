#ifndef BLUZELLE_NODEINFO_H
#define BLUZELLE_NODEINFO_H

#include <string>
#include<vector>

using std::string;
using std::vector;

class NodeInfo {
public:
    string ip_;
    ushort port_;

    string address_;
    bool is_leader;

    string name_;


    NodeInfo() {}


    static NodeInfo this_node() { return NodeInfo();}
};

#endif //BLUZELLE_NODEINFO_H
