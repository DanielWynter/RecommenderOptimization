//=================================================================================================================
/**
 *  Example of implementation of a class that defines a binary search tree.
 */
 //=================================================================================================================

#ifndef SET_HPP
#define SET_HPP

// Includes
#include <vector> // For std::vector
#include "AVLTree.hpp"  // For AVLTree and AVLNode

/**
 *  Class that defines a set, which is a collection of unique elements.
 */
template <typename T>
class Set {
public:

    /**
     *  Constructs an empty set
     */
    Set() = default;

    /**
     *  Class destructor.
     */
    ~Set() 
    {
        clear();
    }

    /**
     *  Clears the set.
     */
    void clear() 
    {
        tree_.clear();
    }

    /**
     *  Checks if the set is empty.
     *
     *  @return True if the set is empty, false otherwise.
     */
    bool empty() const 
    {
        return tree_.root() == nullptr;
    }

    /**
     *  Returns the number of elements in the set.
     *
     *  @return The number of elements in the set.
     */
    unsigned long long size() const 
    {
        return tree_.size();
    }

    /**
     *  Returns a vector with all the elements in the set.
     *
     *  @return A vector with all the elements in the set.
     */
    std::vector<T> elements() const 
    {        
        return tree_.inorder_traversal();
    }

    /**
     *  Adds a new element into the set.
     *
     *  @param element  The element to be added.
     */
    void add(const T& element)
    {
        tree_.insert(element);
    }

    /**
     *  Removes an element from the set.
     *
     *  @param element  The element to be removed.
     */
    void remove(const T& element) 
    {
        tree_.erase(element);
    }

    /**
     *  Checks if the set contains a given element.
     * 
     *  @param element  The element to be checked.
     *
     *  @return True if the element is in the set, false otherwise.
     */
    bool contains(const T& element) const 
    {
        return tree_.find(element) != nullptr;
    }

    /**
     *  Checks if the set is a subset of another set.
     *
     *  @param otherSet  The other set.
     *
     *  @return True if the set is a subset of the other set, false otherwise.
     */
    bool is_subset(const Set<T>& otherSet) const 
    {
        auto elementsThis = elements();
        for (const T& elem : elementsThis) {
            if (!otherSet.contains(elem))
                return false;
        }
        return true;
    }

    /**
     *  Checks if the set is a superset of another set.
     *
     *  @param otherSet  The other set.
     *
     *  @return True if the set is a superset of the other set, false otherwise.
     */
    bool is_superset(const Set<T>& otherSet) const 
    {
        return otherSet.is_subset(*this);
    }

private:
    
    AVLTree<T> tree_;   /**< The AVL tree that stores the elements of the set. */ 
};


/**
 *  Overloaded operator for the equality comparison of two sets.
 *
 *  @param lhs  The left-hand side set.
 *  @param rhs  The right-hand side set.
 *
 *  @return True if the sets are equal, false otherwise.
 */
template <typename T>
bool operator == (const Set<T>& lhs, const Set<T>& rhs)
{
    if (lhs.size() != rhs.size())
        return false;

    auto elementsLhs = lhs.elements();
    for (const T& elem : elementsLhs) {
        if (!rhs.contains(elem))
            return false;
    }
    return true;    
}

/**
 *  Performs the union of two sets.
 *
 *  @param lhs  The left-hand side set.
 *  @param rhs  The right-hand side set.
 *
 *  @return The union of the two sets.
 */
template <typename T>
Set<T> union_set(const Set<T>& lhs, const Set<T>& rhs)
{
    Set<T> result;
    for (const T& elem : lhs.elements())
        result.add(elem);
    for (const T& elem : rhs.elements())
        result.add(elem);
    return result;
}

/**
 *  Performs the intersection of two sets.
 *
 *  @param lhs  The left-hand side set.
 *  @param rhs  The right-hand side set.
 *
 *  @return The intersection of the two sets.
 */
template <typename T>
Set<T> intersection(const Set<T>& lhs, const Set<T>& rhs)
{
    Set<T> result;
    for (const T& elem : lhs.elements()) {
        if (rhs.contains(elem))
            result.add(elem);
    }
    return result;
}

/**
 *  Performs the difference of two sets.
 *
 *  @param lhs  The left-hand side set.
 *  @param rhs  The right-hand side set.
 *
 *  @return The difference of the two sets.
 */
template <typename T>
Set<T> difference(const Set<T>& lhs, const Set<T>& rhs)
{
    Set<T> result;
    for (const T& elem : lhs.elements()) {
        if (!rhs.contains(elem))
            result.add(elem);
    }
    return result;
}

/**
 *  Performs the symmetric difference of two sets.
 *
 *  @param lhs  The left-hand side set.
 *  @param rhs  The right-hand side set.
 *
 *  @return The symmetric difference of the two sets.
 */
template <typename T>
Set<T> symmetric_difference(const Set<T>& lhs, const Set<T>& rhs)
{
    Set<T> result = union_set(lhs, rhs);
    Set<T> intersection_set = intersection(lhs, rhs);
    for (const T& elem : intersection_set.elements()) {
        result.remove(elem);
    }
    return result;
}

#endif
//=================================================================================================================
//  END OF FILE
//=================================================================================================================