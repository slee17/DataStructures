/**
 * \file hashset.hpp
 *
 * \author Rachel Lee
 *
 * \brief Provides HashSet<T>, a set class template, using hash tables
 */

#ifndef HASHSET_HPP_INCLUDED
#define HASHSET_HPP_INCLUDED 1


// Header files that are needed to typecheck the class declaration
#include <cstddef>
#include <forward_list>


// Templated interfaces (e.g., the HashSet class declarations)
template <class T>
class HashSet {

public:
    HashSet() = default; ///< Default constructor

    ~HashSet(); ///< Destructor
    
    HashSet(const HashSet& copy) = delete;
    
    HashSet& operator=(const HashSet& rhs) = delete;

    size_t size() const; ///< Number of items in the hash table

    /**
     * \brief Adds item to the hash table. 
     *
     * \note The function's behavior is undefined if the item has already been
     *       added to the table.
     */
    void insert(const T &item);

    /**
     * \brief Returns true if item is present in the hash table and
     *        false otherwise. 
     */
    bool exists(const T &item) const;

    /**
     * \brief Returns the number of buckets in the hash table.
     */
    size_t buckets() const;

    /**
     * \brief Returns the number of times the hash table has resized itself.
     */
    size_t reallocations() const;

    /**
     * \brief Returns the number of times an insert into the current hash table
     *        representation has found a non-empty bucket.
     */
    size_t collisions() const;

    /**
     * \brief Returns the length of the longest chain discovered so far in the
     *        current hash table representation.
     */
    size_t maximal() const;

private:
    const static int LOAD_FACTOR = 4; 

    size_t size_ = 0;
    size_t numBuckets_ = 1;
    size_t reallocations_ = 0;
    size_t collisions_ = 0;
    size_t maximalChainSize_ = 0;
    
    void resize();

    void insertWholeList(std::forward_list<T>* list);

    bool overloaded() const;

    std::forward_list<T>** table_ = new std::forward_list<T>*[numBuckets_]();
};

#include "hashset-private.hpp"

#endif