/**
 * \file treeset.hpp
 *
 * \author Rachel Lee
 *
 * \brief Provides TreeSet<T>, a set class template, using tree tables
 */

#ifndef TREESET_HPP_INCLUDED
#define TREESET_HPP_INCLUDED 1

#include <cstddef>
#include <forward_list>
#include <random>

template <class T>
class TreeSet {
private:
    struct Node;

public:
    TreeSet(); ///< Default constructor

    ~TreeSet(); ///< Destructor
    
    TreeSet(const TreeSet& copy) = delete;
    
    TreeSet& operator=(const TreeSet& rhs) = delete;

    size_t size() const; ///< Number of items in the TreeSet.

    int height() const; ///< Returns height of the tree.

    /**
     * \brief Adds item to the TreeSet. 
     *
     * \note The function's behavior is undefined if the item has already been
     *       added to the tree.
     */
    void insert(const T&);
 
    /**
     * \brief Returns true if item is present in the TreeSet and
     *        false otherwise. 
     */
    bool exists(const T&) const;

    /**
     * Prints the number of elements, the height of the TreeSet.
     * \notes These values are meant to show whether the tree is
     *        relatively well-balanced.
     */
    void showStatistics(std::ostream& out) const;

    /**
     * Prints out a representation of the TreeSet.
     */
    std::ostream& print(std::ostream&) const;

private:
    Node* root_; ///< Top-level node of this tree.

    /**
     * \class Node
     * \brief Node for TreeSet.     
     */
    struct Node {
        Node() = delete;

        /**
         * Parameterized Constructor
         */
        Node(const T& value, Node* left, Node* right, size_t size);

        T value_; ///< Value stored in this node

        Node* left_; ///< Left subtree of this node
        Node* right_; ///< Right subtree of this node

        size_t size_; ///< Number of items in this node and its subtrees
    };

    /**
     * Helper function for getting the height of a tree.
     */
    int heightNode(Node* here) const;

    /**
     * Helper function for getting the size of a node.
     */
    int sizeNode(Node* here) const;

    void rightRotate(Node*& here); ///< Rotates here's subtree to the right.

    void leftRotate(Node*& here); ///< Rotates here's subtree to the left.

    /**
     * \brief Adds a node at here.
     *
     * \note Helper function for insert.
     *       The function's behavior is undefined if the item has already been
     *       added to the tree.
     */
    void insertNode(const T& value, Node*& here);

    /**
     * \brief Adds a node to the root of the (sub)tree.
     *
     * \note The function's behavior is undefined if the item has already been
     *       added to the tree.
     */
    void insertNodeAtRoot(Node*& here, const T& value);

    /**
     * Fixes the size of here and its left child.
     */
    void fixSizeRight(Node*& here);

    /**
     * Fixes the size of here and its right child.
     */
    void fixSizeLeft(Node*& here);

    /**
     * \brief Checks if item exists in the subtree whose root is here.
     *
     * \note Helper function for exists.
     */
    bool nodeExists(const T& item, const Node* here) const;

    /**
     * \brief Deletes here and its subtrees.
     *
     * \note Helper function for the destructor.
     */
    void deleteNode(Node*& here);

    /**
     * \brief Prints here and its subtrees.
     *
     * \note Helper function for print.
     */
    std::ostream& nodePrint(std::ostream&, const Node* here) const;

    /**
     * Number generator for getting values from real distribution.
     */
    std::mt19937 gen_;
};

#include "treeset-private.hpp"

#endif
