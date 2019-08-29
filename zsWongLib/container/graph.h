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
        DGraph() = default;

        //add a vertex(start Node --->[edge Val] end Node)
        /*
            when we add a vertex to this graph, we also should specify the edge
            pointing to that vertex
        */
        bool add_vertex(const Node &, const Val &, const Node &);

        private:
        //add a edge(start Node --->[edge Val] end Node)
        void add_edge(const Node&, const Val&, const Node&);
        
        private:
        std::map<Node, std::map<Node, Val>> m_map_memory;
        std::set<Node> m_set_alreadyin;
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
    void DGraph<Node, Val>::add_edge(const Node &_Node_start, const Val &_Val_weight, const Node &_Node_end){
    }

    template <typename Node, typename Val> 
    bool DGraph<Node, Val>::add_vertex(const Node &_Node_start, const Val &_Val_weight, const Node &_Node_end){
        /*
        _Node_start refers the start vertex of this edge
        _Val_weight refers the weight of this edge
        _Node_end refers the end vertex of this edge
        */

        auto _it_start = m_map_memory.find(_Node_start);
        auto _it_end = m_map_memory.find(_Node_end);

        if(_it_start == m_map_memory.end()){
            //start vertex is not a start point already in this graph
            //Add a new edge with _Node_start as start Node to this DGraph
            m_map_memory[_Node_start] = std::map<Node, Val>(std::pair<Node, Val>(_Node_end, _Val_weight));

            if(_it_end == m_map_memory.end()){
                /*
                    end vertex is not a start point already in this graph,
                    so edge adding fails
                */
               return false;
            }
            else{
                //end vertex is a start point already in this graph
                m_map_memory.insert(std::pair<Node, std::map<Node, Val>>(
                    _Node_start, std::map<Node, Val>({std::pair<Node, Val>(_Node_end, _Val_weight)})
                ));
            }
        }
        else{
            if((*_it_start).second.find(_Node_end) != (*_it_start).second.end()){
                //if this edge is already existing 
                return false;
            }
            else{
                //add this edge
                (*_it_start).second[_Node_end] = _Val_weight;//add the edge(_Node_start ---> _Val_weight ---> _Node_end)
            }

        }
    }
}

#endif