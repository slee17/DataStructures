/**
 * \file TreeSet-private.hpp
 *
 * \author Rachel Lee
 *
 * \brief Implements TreeSet<T>, a TreeSet class template
 *
 * \remark There is no include-guard for this file, because it is
 *         only #included by TreeSet.hpp, inside TreeSet.hpp's
 *         own include guard.
 */

#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
TreeSet<T>::TreeSet() :
    root_{nullptr}
{
    std::random_device rd;
    gen_ = mt19937{rd()};
}

template <class T>
TreeSet<T>::~TreeSet()
{
    deleteNode(root_);
}

template <class T>
void TreeSet<T>::deleteNode(Node*& here)
{
    if (here != nullptr) {
        deleteNode(here->left_);
        deleteNode(here->right_);
        delete here;
    }
}

template <class T>
size_t TreeSet<T>::size() const
{
    return sizeNode(root_);
}

template <class T>
int TreeSet<T>::height() const
{
    return heightNode(root_);
}

template <class T>
void TreeSet<T>::insert(const T& item)
{
    insertNode(item, root_);
}

template <class T>
void TreeSet<T>::insertNode(const T& item, Node*& here)
{
    if (gen_() % (sizeNode(here)+1) == 0)
        insertNodeAtRoot(here, item);
    else if (here->value_ < item) {
        ++(here->size_);
        insertNode(item, here->right_);
    } else {
        ++(here->size_);
        insertNode(item, here->left_);
    }
}

template <class T> 
void TreeSet<T>::insertNodeAtRoot(Node*& here, const T& value) 
{
    if (here == nullptr) {
        here = new Node(value, NULL, NULL, 1); 
    } else if (value < here->value_) {
        ++(here->size_);
        insertNodeAtRoot(here->left_, value); 
        rightRotate(here); 
    } else {
        ++(here->size_);
        insertNodeAtRoot(here->right_, value); 
        leftRotate(here); 
    }
}    

template <class T>
bool TreeSet<T>::exists(const T& item) const
{
    return nodeExists(item, root_);
}

template <class T>
bool TreeSet<T>::nodeExists(const T& item, const Node* here) const
{
    if (here == nullptr)
        return false;
    else if (item < here->value_)
        return nodeExists(item, here->left_);
    else if (here->value_ < item)
        return nodeExists(item, here->right_);
    else
        return true;

}

template <class T>
void TreeSet<T>::showStatistics(ostream& out) const
{
    out << "height " << height() << ", size " << size() << endl;
}

template <class T>
ostream& TreeSet<T>::print(ostream& out) const
{
    return nodePrint(out, root_);
}

template <class T>
ostream& TreeSet<T>::nodePrint(ostream& out, const Node* here) const
{
    if (here == nullptr)
        out << "-";
    else {
        out << "(";
        nodePrint(out, here->left_); 
        out << ", " << here->value_ << ", ";
        nodePrint(out, here->right_) << ")";
    }
    return out;
}

template <class T>
int TreeSet<T>::heightNode(Node* here) const
{
    if (here == nullptr)
        return -1;
    return 1 + max(heightNode(here->left_), heightNode(here->right_));
}

template <class T>
int TreeSet<T>::sizeNode(Node* here) const
{
    if (here == nullptr)
        return 0;
    return here->size_;
}

template <class T>
void TreeSet<T>::rightRotate(Node*& here)
{
    fixSizeRight(here);
    Node* b = here->left_;
    here->left_ = b->right_;
    b->right_ = here;
    here = b;
}

template <class T>
void TreeSet<T>::leftRotate(Node*& here)
{
    fixSizeLeft(here);
    Node* d = here->right_;
    here->right_ = d->left_;
    d->left_ = here;
    here = d;
}

template <class T>
void TreeSet<T>::fixSizeRight(Node*& here)
{
    size_t hereSize = sizeNode(here);
    here->size_ = sizeNode(here->right_) + sizeNode(here->left_->right_);
    here->left_->size_ = hereSize;
}

template <class T>
void TreeSet<T>::fixSizeLeft(Node*& here)
{
    size_t hereSize = sizeNode(here);
    here->size_ = sizeNode(here->left_) + sizeNode(here->right_->left_);
    here->right_->size_ = hereSize;
}

template <class T>
TreeSet<T>::Node::Node(const T& value, Node* left, Node* right, size_t size) :
    value_{value}, left_{left}, right_{right}, size_{size}
{
    // Nothing to do
}