/**
 * \file hashset-private.hpp
 *
 * \author Rachel Lee
 *
 * \brief Implements HashSet<T>, a hash-table class template
 *
 * \remark There is no include-guard for this file, because it is
 *         only #included by hashset.hpp, inside hashset.hpp's
 *         own include guard.
 */

#include <string>
#include <iostream>
#include <forward_list>
#include <iterator>

template <class T>
HashSet<T>::~HashSet()
{
    for(size_t i = 0; i < numBuckets_; i++) {
        delete table_[i];
    }
    delete [] table_;
}

template <class T>
size_t HashSet<T>::size() const
{
    return size_;
}

template <class T>
void HashSet<T>::insert(const T &item)
{
    ++size_;
    ++collisions_;

    size_t hashed = myhash(item);
    size_t bucket = hashed % buckets();

    auto& chain = table_[bucket];

    // If the bucket is empty
    if (!chain) {
        chain = new std::forward_list<T>;
        --collisions_;
    }
    
    chain->push_front(item);

    size_t chainSize = std::distance(chain->begin(), chain->end());

    if(chainSize > maximalChainSize_)
        maximalChainSize_ = chainSize;

    if (overloaded()) {
        resize();
    }
}

template <class T>
bool HashSet<T>::overloaded() const
{
    return double(size_)/double(numBuckets_) >= LOAD_FACTOR;
}

template <class T>
bool HashSet<T>::exists(const T &item) const
{
    size_t hashed = myhash(item);
    size_t bucket = hashed % buckets();

    auto& chain = table_[bucket];

    if (chain == NULL) {
        return false;
    }

    for (auto i = chain->begin(); i != chain->end(); ++i) {
        if (*i == item) {
            return true;
        }
    }
    return false;
}

template <class T>
void HashSet<T>::resize() 
{
    maximalChainSize_ = 0;
    collisions_ = 0;
    size_ = 0;

    // Make a copy of the old table
    size_t oldSize = numBuckets_;
    std::forward_list<T>** oldTable = table_;

    // Resize the original table and initialize its elements to be null pointers
    numBuckets_ = 2 * oldSize;
    table_ = new std::forward_list<T>*[numBuckets_]();

    // Copy over the elements
    for(size_t i = 0; i < oldSize; ++i) {
        if(oldTable[i]) {
            insertWholeList(oldTable[i]);
        }
        delete oldTable[i];
    }
    delete[] oldTable;

    ++reallocations_;
}

template <class T>
void HashSet<T>::insertWholeList(std::forward_list<T>* list)
{
    for(auto i = list->begin(); i != list->end(); ++i) {
        insert(*i);
    }
}

template <class T>
size_t HashSet<T>::buckets() const
{
    return numBuckets_;
}

template <class T>
size_t HashSet<T>::reallocations() const
{
    return reallocations_;
}

template <class T>
size_t HashSet<T>::collisions() const
{
    return collisions_;
}

template <class T>
size_t HashSet<T>::maximal() const
{
    return maximalChainSize_;
}
