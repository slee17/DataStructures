/*
 * \file intlist.cpp
 * \authors Rachel Lee
 * \brief Implemenation of IntList, a linked list of ints, and its private classes.
 */

#include "intlist.hpp"

#include <cstddef>
#include <cassert>

using namespace std;

IntList::IntList() : back_{nullptr}, front_{nullptr}, size_{0} {
}

IntList::IntList(const IntList& orig) :
    back_{nullptr}, front_{nullptr}, size_{0} {
    // Iterate over the given list and copy the values
    // This works because push_back makes a copy instead of using a reference
    for (iterator b = orig.begin(); b != orig.end(); ++b)  {
        push_back(*b);
    }
}

IntList::~IntList()
{
    // May be more efficient to simply delete the values without returning them,
    // although the difference should be negligible
    while(!empty())
        pop_front();
}

void IntList::swap(IntList& rhs)
{
    using std::swap;

    swap(back_, rhs.back_);
    swap(front_, rhs.front_);
    swap(size_, rhs.size_);
}


void swap(IntList& lhs, IntList& rhs)
{
    lhs.swap(rhs);
}


IntList& IntList::operator=(const IntList& rhs)
{
    // Implemented idiomatically for C++, using "the swap trick"
    IntList copy = rhs;
    swap(copy);
    return *this;
}


size_t IntList::size() const
{
    return size_;
}

bool IntList::empty() const
{
    return size_ == 0;
}


bool IntList::operator==(const IntList& rhs) const
{
    // Cheap check
    if (size_ != rhs.size_)
        return false;
    
    // Have to compare element by element otherwise
    else {
        iterator a = begin();
        for (iterator b = rhs.begin(); b != rhs.end(); ++b) {
            // Bail early as soon as we find a difference
            if (*b != *a)
                return false;
            ++a;
        }
        return true;
    }
}

bool IntList::operator!=(const IntList& rhs) const
{
    // Idiomatic code: leverage == to implement !=
    return !operator==(rhs);
}


void IntList::push_front(int pushee)
{
    // Create a new Element that has the current front_ as its next_, then
    // repoint front_ to our new Element
    front_ = new Element{pushee, front_};
    ++size_;

    // Handle the edge case where we push onto an empty list
    if (size_ == 1)
        back_ = front_;
}


int IntList::pop_front()
{
    assert(!empty());

    // Get our value before we delete the Element
    int value = front_->value_;

    // Repoint everything as necessary
    Element* first = front_;
    front_ = first->next_;
    --size_;
    delete first;
    return value;
}


void IntList::push_back(int pushee)
{
    // The new Element is the last node in the list, it doesn't need a next_
    Element* last = new Element{pushee, nullptr};
    // Our more common case, a non-empty list
    if (!empty()) {
        back_->next_ = last;
    } else { // The edge case of an empty list
        front_ = last;
    }
    back_ = last;
    ++size_;
}


void IntList::insert_after(iterator where, int value)
{
    // Make a new Element and point it to the next value
    Element* inserted = new Element{value, where.current_->next_};
    // Repoint the current Element to the new element
    where.current_->next_ = inserted;
    ++size_;
}


IntList::iterator IntList::begin() const
{
    // Iterator to the first element
    return Iterator{front_};
}


IntList::iterator IntList::end() const
{
    // Iterator to an invalid element; if we have an iterator whose current_
    // value is this then we've gone past the end of the list
    return Iterator{nullptr};
}

// --------------------------------------
// Implementation of IntList::Element
// --------------------------------------

IntList::Element::Element(int value, Element* next)
    : value_{value}, next_{next}
{
    // Nothing else to do
}

// --------------------------------------
// Implementation of IntList::Iterator
// --------------------------------------

IntList::Iterator::Iterator(Element* current)
    : current_{current}
{
    // Nothing else to do
}


IntList::Iterator& IntList::Iterator::operator++()
{
    // Move the pointer along, then return a reference to the current instance
    current_ = current_->next_;
    return *this;
}


int& IntList::Iterator::operator*() const
{
    // Return a reference to the current value
    return current_->value_;
}

bool IntList::Iterator::operator==(const Iterator& rhs) const
{
    return (rhs.current_ == current_);
}


bool IntList::Iterator::operator!=(const Iterator& rhs) const
{
    // Idiomatic code: leverage == to implement !=
    return !(*this == rhs);
}
