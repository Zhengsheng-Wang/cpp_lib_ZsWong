#pragma once
#ifndef ZSWONGGRAPH
#define ZSWONGGRAPH

#include <map>
#include <set>
#include <tuple>
#include <iostream>

namespace zsWong{
    template <typename Node, typename Val> class DGraph;
    template <typename Node, typename Val> std::ostream &operator<<(std::ostream &, const DGraph<Node, Val> &);
    template <typename Node, typename Val> class DGraph{
        //directed graph
        friend std::ostream &operator<< <Node, Val>(std::ostream &, const DGraph &);
        public:
        DGraph(const Node &);

        //add a vertex(start Node --->[edge Val] end Node)
        /*
            when we add a vertex to this graph, we also should specify the edge
            pointing to that vertex
        */
        DGraph & add_vertex(const Node &, const Val &, const Node &);

        private:
        //add a edge(start Node --->[edge Val] end Node)
        void add_edge(const Node&, const Val&, const Node&);
        
        private:
        std::map<Node, std::map<Node, Val>> m_map_memory;
    };
    //Define << operator. Output the inner hash table m_map_memory actually.
    /*
        Output  format: 
            vertex: 
            --->(value): vertex2
            vertex2:
            --->(value2): vertex3
            ...
            ...
            ...
    */
    template <typename Node, typename Val> 
    std::ostream &operator<<(std::ostream &_os, const DGraph<Node, Val> &_DGraph_graph){
        for(auto it_beg = _DGraph_graph.m_map_memory.cbegin(), it_end = _DGraph_graph.m_map_memory.cend();
        it_beg != it_end; ++it_beg){
            _os << (*it_beg).first << ": " << std::endl;

            for(auto it_beg2 = (*it_beg).second.cbegin(), it_end2 = (*it_beg).second.cend();
            it_beg2 != it_end2; ++it_beg2){
                _os << "--->" << "(" << (*it_beg2).second << "): " << (*it_beg2).first << std::endl;
            }
        }
        return _os;
    }

    template <typename Node, typename Val>
    DGraph<Node, Val>::DGraph(const Node &_Node){
        m_map_memory[_Node] = std::map<Node, Val>();
    }

    template <typename Node, typename Val> 
    DGraph<Node, Val> & DGraph<Node, Val>::add_vertex(const Node &_Node_start, const Val &_Val_weight, const Node &_Node_end){
        /*
        _Node_start refers the start vertex of this edge
        _Val_weight refers the weight of this edge
        _Node_end refers the end vertex of this edge
        */

        auto _it_start = m_map_memory.find(_Node_start);

        if(_it_start == m_map_memory.end()){
            //_Node_start is not a start point already in this graph
            //Add _Node_start and a new edge with _Node_start as start Node to this DGraph
            std::map<Node, Val> _map_tmp;
            _map_tmp[_Node_end] = _Val_weight;
            m_map_memory[_Node_start] = _map_tmp;
        }
        else{
            //_Node_start is in this DGraph
            //If _Node_end is not already associated with _Node_start, add it. Or do nothing.
            //The type of *(_it_start) is std::pair<Node, std::map<Node, Val>>
            //The type of _it_end is std::pair<Node, Val>
            auto _it_end = _it_start->second.find(_Node_end);

            if(_it_end == _it_start->second.end()){
                //If _Node_end is not a end vertex already associated with _Node_start, then add it
                _it_start->second[_Node_end] = _Val_weight;
            }
        }
        return *this;
    }
}

#endif