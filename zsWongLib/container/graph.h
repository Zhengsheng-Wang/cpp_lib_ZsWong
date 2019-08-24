#pragma once
#ifndef ZSWONGGRAPH
#define ZSWONGGRAPH

#include <map>
#include <set>

#include "List.h"

namespace zsWong{
    template <typename T> class Graph{
        std::map<T, zsWong::List<T>*> m_map_vertex;
    };
}

#endif