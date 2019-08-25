#pragma once
#ifndef ZSWONGSORT
#define ZSWONGSORT

#include <random>
#include <map>
#include <set>
#include "../container/list.h"

namespace zsWong{
	template <typename L, typename T> L sortQuick(const L& _li_ori){
		if(_li_ori.getLength() < 2){
			//there is no need in sorting array containing 0 or 1 element
			return _li_ori;
		}
		else{
			L _li_left, _li_right;    //liLeft receives the elements smaller than pivot element, liRight receives the greater or equal

			//use random library to generate random pivot index
			static std::default_random_engine s_e;
			static std::uniform_int_distribution<int> s_u(0, _li_ori.getLength() - 1);

			int _int_pivot = s_u(s_e) % (_li_ori.getLength() - 1);  //privot index
			T _T_pivot = _li_ori.get(_int_pivot);  //privot element

			for(int i = 0; i != _li_ori.getLength(); ++i){
				//split the elements in _li_Ori into two seperate list according to pivot element
				if(i != _int_pivot){
					T _T_tmp = _li_ori.get(i);
					if(_T_tmp > _T_pivot){
						_li_right.push(_T_tmp);
					}
					else{
						_li_left.push(_T_tmp);
					}
				}
			}

			//we sort _li_left and _li_right, and make them a result list together with _T_pivot
			return sortQuick<L, T>(_li_left).push(_T_pivot).append(sortQuick<L, T>(_li_right));
		}
	}

	//Dijkstra algorithm find shortest path in DAG
	template <typename Node, typename Val, typename Graph, typename List>  
	List find_shortestPath_Dijkstra(const Graph& _graph){
	}
}

#endif // !ZSWONGSORT
