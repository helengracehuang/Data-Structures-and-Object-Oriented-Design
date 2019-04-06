#ifndef MYHASH_INCLUDED
#define MYHASH_INCLUDED

// forward declaration hash functions
unsigned int hash(const std::string& s);
unsigned int hash(const int& i);
unsigned int hash(const char& c);

// ========================================== Map.h =========================================
template <typename KeyType, typename ValueType>
class Map
{
public:
    Map();               // Create an empty map (i.e., one with no key/value pairs).
    bool empty() const;  // Return true if the map is empty, otherwise false.
    int size() const;    // Return the number of key/value pairs in the map.
    bool insert(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    ValueType* get(const KeyType& key) const;
    void swap(Map<KeyType, ValueType>& other);
    void rehash(Map<KeyType, ValueType>*& hashTable, int& NBuckets);
    
    // Housekeeping functions
    ~Map();
    Map(const Map<KeyType, ValueType>& other);
    Map<KeyType, ValueType>& operator=(const Map<KeyType, ValueType>& rhs);
    
private:
    struct Node
    {
        KeyType   m_key;
        ValueType m_value;
        Node*     m_next;
        Node*     m_prev;
    };
    
    Node* m_head;
    int   m_size;
    
    Node* find(const KeyType& key) const;
    bool doInsertOrUpdate(const KeyType& key, const ValueType& value,
                          bool mayInsert, bool mayUpdate);
};

// =============== Inline implementations ===============
// size (useful)
template <typename KeyType, typename ValueType>
inline
int Map<KeyType, ValueType>::size() const
{
    return m_size;
}

// empty (useful)
template <typename KeyType, typename ValueType>
inline
bool Map<KeyType, ValueType>::empty() const
{
    return size() == 0;
}

// contains (useful)
template <typename KeyType, typename ValueType>
inline
bool Map<KeyType, ValueType>::contains(const KeyType& key) const
{
    return find(key) != m_head;
}

// insert (useful)
template <typename KeyType, typename ValueType>
inline
bool Map<KeyType, ValueType>::insert(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, false /* no update */);
}

// insert or update (useful)
template <typename KeyType, typename ValueType>
inline
bool Map<KeyType, ValueType>::insertOrUpdate(const KeyType& key, const ValueType& value)
{
    return doInsertOrUpdate(key, value, true /* insert */, true /* update */);
}

// =============== Out of line implementations ===============
// constructors & destructors (useful)
template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map()
: m_size(0)
{
    // create dummy node
    m_head = new Node;
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::~Map()
{
    // Delete the m_size non-dummy nodes plus the dummy node
    
    for (Node* p = m_head->m_prev ; m_size >= 0; m_size--)
    {
        Node* toBeDeleted = p;
        p = p->m_prev;
        delete toBeDeleted;
    }
}

template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(const Map<KeyType, ValueType>& other)
: m_size(other.m_size)
{
    // Create dummy node; don't initialize its pointers
    
    m_head = new Node;
    
    // Initialize prev to last node created
    
    Node* prev = m_head;
    
    // Copy each non-dummy node from the other list; each iteration will set
    // the m_next of the previous node copied
    
    for (Node* p = other.m_head->m_next ; p != other.m_head; p = p->m_next)
    {
        // Create a copy of the node p points to
        Node* pnew = new Node;
        pnew->m_key = p->m_key;
        pnew->m_value = p->m_value;
        
        // Connect the new node to the previous one
        pnew->m_prev = prev;
        prev->m_next = pnew;
        
        // Reset prev to last node created
        prev = pnew;
    }
    
    // Connect last node created to m_head
    m_head->m_prev = prev;
    prev->m_next = m_head;
}

// operator= (useful)
template <typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::operator=(const Map<KeyType, ValueType>& rhs)
{
    if (this != &rhs)
    {
        Map temp(rhs);
        swap(temp);
    }
    return *this;
}

// erase
template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::erase(const KeyType& key)
{
    Node* p = find(key);
    
    if (p == m_head)  // not found
        return false;
    
    // unlink the node from the list and destroy it
    
    p->m_prev->m_next = p->m_next;
    p->m_next->m_prev = p->m_prev;
    delete p;
    
    m_size--;
    return true;
}

// get, 1-parameter (useful)
template <typename KeyType, typename ValueType>
ValueType* Map<KeyType, ValueType>::get(const KeyType& key) const
{
    Node* p = find(key);
    if (p == m_head)  // not found
        return nullptr;
    return &(p->m_value);
}

// swap (useful)
template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::swap(Map<KeyType, ValueType>& other)
{
    // swap head pointers
    Node* tempHead = m_head;
    m_head = other.m_head;
    other.m_head = tempHead;
    
    // swap sizes
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
}

// find (useful)
template <typename KeyType, typename ValueType>
typename Map<KeyType, ValueType>::Node* Map<KeyType, ValueType>::find(const KeyType& key) const
{
    // Do a linear search through the list
    
    Node* p;
    for (p = m_head->m_next; p != m_head && p->m_key != key; p = p->m_next)
        ;
    return p;
}

// doInsertOrUpdate (useful)
template <typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::doInsertOrUpdate(const KeyType& key, const ValueType& value,
                                               bool mayInsert, bool mayUpdate)
{
    Node* p = find(key);
    
    if (p != m_head)  // found
    {
        if (mayUpdate)
            p->m_value = value;
        return false;
    }
    if (!mayInsert)  // not found, and not allowed to insert
        return false;
    
    // Create a new node
    p = new Node;
    p->m_key = key;
    p->m_value = value;
    
    // Insert new item at tail of list (arbitrary choice of position)
    //     Connect it to tail
    p->m_prev = m_head->m_prev;
    p->m_prev->m_next = p;
    
    //     Connect it to dummy node
    p->m_next = m_head;
    m_head->m_prev = p;
    
    m_size++;
    return true;
}

// rehash (very useful)
template <typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::rehash(Map<KeyType, ValueType>*& hashTable, int& NBuckets)
{
    int oldCapacity = NBuckets;
    NBuckets *= 2;
    
    // allocate new temp table
    Map<KeyType, ValueType>* newHashTable = new Map<KeyType, ValueType>[NBuckets];
    
    //fill in the new temp table with old info
    for (int i = 0; i < oldCapacity; i++)
    {
        Node* p = hashTable[i].m_head->m_next;
        while (p != hashTable[i].m_head)
        {
            // find the proper bucket
            unsigned int hash(const KeyType& k); // prototype
            newHashTable[hash(p->m_key) % NBuckets].insert(p->m_key, p->m_value);
            p = p->m_next;
        }
    }
    delete[] hashTable;
    hashTable = newHashTable;
}

// ========================================== MyHash.h =========================================
template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();   // O(B)
    void associate(const KeyType& key, const ValueType& value);   // O(1 or B)
    int getNumItems() const;   // O(1)
    double getLoadFactor() const;   // O(1)

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;   // O(1)

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)   // O(1)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
    // private member variables
    Map<KeyType, ValueType>* m_hashTable;
    
    int m_numItems;   // number of items currently stored in the hashTable
    int m_numBuckets;   // size of the m_hashTable array
    double m_maxLoadFactor;   // m_numItems / m_numBuckets
    
    // private functions
    unsigned int getBucketNumber(const KeyType& key) const;
    bool resize();   // If load factor is too big, resize the hashtable and return TRUE
};

// =============== Inline implementations ===============
// getNumItems
template <typename KeyType, typename ValueType>
inline
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_numItems;
}

// getLoadFactor
template <typename KeyType, typename ValueType>
inline
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return double(m_numItems) / double(m_numBuckets);
}

// =============== Out of line implementations ===============
// public functions
// constructor & destructor
template <typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::MyHash(double maxLoadFactor)
: m_numItems(0), m_numBuckets(100)
{
    // check max load factor
    if (maxLoadFactor >= 2.0)
        m_maxLoadFactor = 2.0;
    else if (maxLoadFactor <= 0.5)
        m_maxLoadFactor = 0.5;
    
    // dynamically allocate a new hash table
    m_hashTable = new Map<KeyType, ValueType>[100];
}

template <typename KeyType, typename ValueType>
MyHash<KeyType, ValueType>::~MyHash()
{
    // for (int i = 0; i < m_numBuckets; i ++)
    delete[] m_hashTable;
}

// reset
template <typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    // for (int i = 0; i < m_numBuckets; i ++)
    delete[] m_hashTable;
    m_hashTable = new Map<KeyType, ValueType>[100];
    m_numItems = 0;
    m_numBuckets = 100;
}

// associate
template <typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
    unsigned int bucket = getBucketNumber(key);
    if (m_hashTable[bucket].insertOrUpdate(key, value))
    {
        m_numItems ++;   // increment # of items if inserted, DON't increment if updated
        resize();   // resize the hash table if necessary
    }
}

// find
template <typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    // ValueType* value = nullptr;
    unsigned int bucket = getBucketNumber(key);
    if (m_hashTable[bucket].contains(key))
        return m_hashTable[bucket].get(key);
    return nullptr;
}

// private functions
// getBucketNumber
template <typename KeyType, typename ValueType>
unsigned int MyHash<KeyType, ValueType>::getBucketNumber(const KeyType& key) const
{
    unsigned int hash(const KeyType& k); // prototype
    unsigned int h = hash(key);
    unsigned int bucketNumber = h % m_numBuckets;
    
    return bucketNumber;
}

// resize
template <typename KeyType, typename ValueType>
bool MyHash<KeyType, ValueType>::resize()   // Check load factor, if too big, resize the hashtable
{
    if (getLoadFactor() > m_maxLoadFactor)
    {
        m_hashTable->rehash(m_hashTable, m_numBuckets);
        return true;
    }
    return false;
}

#endif // MYHASH_INCLUDED
