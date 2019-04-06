//
//  map.h
//  Project 2
//
//  Created by Xin Huang on 1/25/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

// Map.h

#ifndef MAP_INCLUDED
#define MAP_INCLUDED

#include <string>

// using KeyType = std::string;
// using ValueType = double;

using KeyType = char;
using ValueType = int;

class Map
{
public:
    Map();                              // constructor
    Map(const Map& src);                // copy operator
    Map& operator=(const Map& other);   // assignment operator
    ~Map();                             // destructor
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    
private:
    struct m_Pair
    {
        KeyType m_key;
        ValueType m_value;
    };
    
    struct m_Node
    {
        m_Pair pair;
        
        m_Node* next;
        m_Node* previous;
    };
    
    int m_size;
    
    m_Node* head;
    m_Node* tail;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);

#endif // MAP_INCLUDED
