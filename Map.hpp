//=================================================================================================================
/**
 *  Example of implementation of a class that defines a dictionary.
 */
 //=================================================================================================================

#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>     // For std::cout
#include <vector>       // For std::vector
#include <stdexcept>    // For std::out_of_range

#include "KeyValueAVLTree.hpp" // For KeyValueAVLTree and KeyValueNode

/**
 *  Class that defines a map, which is a collection of key-value pairs.
 */
template <typename Key, typename Value>
class Map
{
public:
    
    /**
     *  Constructs an empty map.
     */
    Map() = default;

    /**
     *  Class destructor.
     */
    ~Map() 
    {
        clear();
    }

    /**
     *  Checks if the map is empty.
     *
     *  @return True if the map is empty, false otherwise.
     */    
    bool empty() const
    {
        return tree_.root() == nullptr;
    }

    /**
     *  Returns the number of key-value pairs in the map.
     * 
     *  @return The number of key-value pairs in the map.
     */
    unsigned long long size() const
    {
        return tree_.size();
    }

    /**
     *  Returns a vector with all the key-value pairs in the map.
     *
     *  @return A vector with all the key-value pairs in the map.
     */
    std::vector<std::pair<Key, Value>> elements() const
    {
        return tree_.inorder_traversal();
    }

    /**
     *  Clears the map.
     */
    void clear() 
    {
        tree_.clear();
    }

    /**
     *  Inserts a key-value pair into the map.
     * 
     *  @param key The key of the pair.
     *  @param value The value of the pair.
     */
    void insert(const Key& key, const Value& value)
    {
        tree_.insert(key, value);
    }

    /**
     *  Erases a key-value pair from the map.
     *
     *  @param key The key of the pair.
     */
    void erase(const Key& key)
    {
        tree_.erase(key);
    }

    /**
     *  Checks if the map contains a key.
     *
     *  @param key The key to be checked.
     * 
     *  @return True if the map contains the key, false otherwise.
     */
    bool contains(const Key& key) const
    {
        return tree_.find(key) != nullptr;
    }

    /**
     *  Returns the value associated with a key.
     *
     *  @param key The key of the pair.
     *
     *  @return The value associated with the key.
     */
    const Value& at(const Key& key) const 
    {
        auto node = tree_.find(key);
        if (node == nullptr)
            throw std::out_of_range("Key not found in the map.");
        return node->value;
    }
    
    /**
     *  Returns the value associated with a key.
     *
     *  @param key The key of the pair.
     *
     *  @return The value associated with the key.
     */
    Value& at(const Key& key) 
    {
        auto node = tree_.find(key);
        if (node == nullptr)
            throw std::out_of_range("Key not found in the map.");
        return node->value;
    }
    
    /**
     *  Returns the value associated with a key.
     *
     *  @param key The key of the pair.
     *
     *  @return The value associated with the key.
     */
    Value& operator[](const Key& key) 
    {
        auto node = tree_.find(key);
        if (node == nullptr) {
            // If the key is not in the map, insert it with a default value.
            tree_.insert(key, Value());
            node = tree_.find(key);
        }
        return node->value;
    }

    /**
     *  Prints the map.
     */
    void print() const 
    {
        tree_.print_inorder();
    }

private:

    KeyValueAVLTree<Key, Value> tree_;  /**< The AVL tree that stores the elements of the set. */ 

};


#endif
//=================================================================================================================
//  END OF FILE
//=================================================================================================================