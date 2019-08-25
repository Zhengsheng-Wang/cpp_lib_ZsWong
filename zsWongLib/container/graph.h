#pragma once
#ifndef ZSWONGGRAPH
#define ZSWONGGRAPH

#include <map>
#include <set>

namespace zsWong{
    template <typename Node, typename Val> class DGraph{
        public:
        DGraph(const Node&);
        //directed graph
        std::map<Node, std::map<Node, Val>> m_map_memory;
        std::set<Node> m_set_alreadyin;
    };

    template <typename Node, typename Val> DGraph<Node, Val>::DGraph(const Node& _Node){
        std::map<Node, Val> _map_path;
        m_map_memory[_Node] = _map_path;
    }
}

#endif