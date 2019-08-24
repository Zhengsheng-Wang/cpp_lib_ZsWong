#pragma once
#ifndef ZSWONGMAP
#define ZSWONGMAP

#include <cmath>
#include "list.h"

namespace zsWong
{
    template <typename K, typename V> class Map{
        /*
            Initial Map with m_ui_slots_num or it will be initialed with 10
        */
        public:
        //constructor with the number of slots
        Map(unsigned size = 10);
        public:
        unsigned calculate_hkey(const K&);  //calculate the hkey of the key of the input pair

        private:
        unsigned m_ui_elements_num = 0; //the maximum size of Map m_ui_maxsize
        unsigned m_ui_slots_num;   //slot number m_ui_size
        float m_f_a = 0.7;   //load factor m_f_a, which is m_ui_slots_num / m_ui_elements_num

        unsigned m_ui_w = sizeof(unsigned) * 8;  //calculate the half of machine bit size m_ui_w
        float m_f_A = (std::sqrt(5) - 1) / 2;  //calculate multiple hashing's efficience m_f_A
        unsigned m_ui_p = m_ui_w / 2;   //calculate multiple hashing's p m_uint_p
    };
    template <typename, typename> class Map_Node;
    template <typename K, typename V> bool operator==(const Map_Node<K, V>&, const Map_Node<K, V>&);
    template <typename K, typename V> class Map_Node{
        friend bool operator==<K, V>(const Map_Node&, const Map_Node&);

        Map_Node() = delete; //delete default constructor
        Map_Node(const K& _k, const V& _v){
            m_ptrK_key = new K(_k);
            m_ptrV_val = new V(_v);
        }
        ~Map_Node(){
            delete m_ptrK_key;
            delete m_ptrV_val;
        }

        const K* m_ptrK_key = nullptr;
        const V* m_ptrV_val = nullptr;
    };
    template <typename K, typename V> bool operator== (const Map_Node<K, V>& _left, const Map_Node<K, V>& _right){
        return *(_left.m_ptrK_key) == *(_right.m_ptrK_key);
    }

    template <typename K, typename V> Map<K, V>::Map(unsigned size): m_ui_slots_num(size){
    }
    template <typename K, typename V> unsigned Map<K, V>::calculate_hkey(const K& key){
        //hash the key to hkey
        unsigned _ui_addr = static_cast<unsigned>(&key);

        //multiply the address of key by 2^m_ui_w, equaling to left sifting m_ui_w bits;
        unsigned long long _ull_addr = _ui_addr << m_ui_w;
        //multiply t
        _ull_addr *= m_f_A;    
        _ull_addr <<= m_ui_w;
        _ull_addr >>= m_ui_w * 2 - m_ui_p;

        //get the final hkey _ui_key by model _ui_addr with m_ui_size
        unsigned _ui_key = _ull_addr % m_ui_slots_num; 
        return _ui_key;
    }
} // namespace namezswong


#endif