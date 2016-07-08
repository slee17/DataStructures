/**
 * \file intlist.hpp
 * \authors Rachel Lee
 * \brief A singly-linked list of ints.
 */

#ifndef INTLIST_HPP_INCLUDED
#define INTLIST_HPP_INCLUDED 1

#include <iostream>
#include <cstddef>

/**
 * \class IntList
 *
 * \brief A linked list of many Element objects which hold \c ints.
 *
 * \details Class allocates memory dynamically; thus can't use C++'s
 *          defaults for copy constructor, assignment operator and
 *          destructor.
 */
class IntList {

private:
    // Forward declaration of private class.
    class Iterator;

public:

    /**
     * \brief The default constructor for the IntList.
     */
    IntList();

    /**
     * \brief The copy constructor for the IntList.
     */
    IntList(const IntList& orig);

    /**
     * \brief Overloads the assignment operator for the IntList.
     */
    IntList& operator=(const IntList& rhs);

    /**
     * \brief The destructor for the IntList.
     */
    ~IntList();

    /**
     * \brief Swap function for an IntList.  
     */
    void swap(IntList& rhs);

    /**
     * \brief Pushes a value onto the front of the list
     * \post Size increased by one, pointers adjusted appropriately.
     */
    void push_front(int pushee);    ///< Push onto head of list

    /**
     * \brief Pushes a value onto the end of the list.
     * \post Size increased by one, pointers adjusted appropriately.
     */
    void push_back(int pushee);     ///< Push onto tail of list
    
    /**
     * \brief Removes the first value from the list.
     * \post Size decreased by one, pointers adjusted appropriately.
     */
    int pop_front();                ///< Drop & return the head element

    /**
     * \brief Returns the number of integers in the list.
     */
    size_t size() const;            ///< Size of the list

    /**
     * \brief Returns whether there are no integers in the list.
     */
    bool empty() const;             ///< true if the list is empty
 
    /**
     * \brief Overloads the equality operator for IntLists.
     */
    bool operator==(const IntList& rhs) const;
    
    /**
     * \brief Overloads the inequality operator for IntLists.
     */
    bool operator!=(const IntList& rhs) const;
 
    // Allow clients to iterate over the contents of the list. 
    using iterator = Iterator; 

    /**
     * \brief Returns an iterator to the front of the list.
     */
    iterator begin() const; ///< An iterator that refers to the first element

    /**
     * \brief Returns a 'null' iterator.
     */
    iterator end() const;   ///< An invalid / "past-the-end" iterator

    /**
     * Insert a value after a given iterator
     *
     * \details The iterator cannot be end(), the list cannot be empty.
     */
    void insert_after(iterator where, int value);

private:
    /***
     * \struct Element
     *
     * \brief The list is stored as a linked list of Elements.
     *        The class is private so only IntList knows about it. 
     *        A constructor is provided for convenience.
     *
     * \details The Copy Constructor and Assignment operator are
     *          disabled.
     */
    struct Element {
        int value_;
        Element*  next_;

        Element(int value, Element* next);

        Element() = delete;
        Element(const Element&) = delete;
        Element& operator=(const Element&) = delete;
        ~Element() = default;  // If you don't like this, you can change it.
    };

    Element* back_;   ///< Current tail of list
    Element* front_;  ///< Current head of list
    size_t   size_;   ///< Current size of list

    /***
     * \class Iterator
     * \brief STL-style iterator for IntList.
     */
    class Iterator {
    public:
        // Definitions that are required for this class to be a well-behaved
        // STL-style iterator that moves forward through a collection of ints.
        using value_type = int;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        // Provide all the usual operations for a forward iterator

        /**
         * \brief Default constructors, assignment operators, and destructor.
         */
        Iterator() = default;
        Iterator(const Iterator&) = default;
        Iterator& operator=(const Iterator&) = default;
        ~Iterator() = default;

        /**
         * \brief Overloads the prefix increment operator.
         */
        Iterator& operator++();

        /**
         * \brief Overloads the dereference operator.
         */
        int& operator*() const;

        /**
         * \brief Overloads the (in)equality operators.
         */
        bool operator==(const Iterator& rhs) const;
        bool operator!=(const Iterator& rhs) const;

    private:
        friend class IntList;
        Iterator(Element* current);  ///< Friends create non-default iterators
        Element* current_;           ///< The current list node
    };

};

/// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(IntList& lhs, IntList& rhs);

#endif // INTLIST_HPP_INCLUDED
