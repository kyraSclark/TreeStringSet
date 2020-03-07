/**
 * \file treestringset.cpp
 * \authors Ellie and Kyra
 * \brief Implementation of TreeStringSet
 */

#include <cs70/randuint32.hpp>
#include <iostream>
#include <utility>
#include <string>
#include <queue>
#include "treestringset.hpp"

//--------------------------------------------
// TreeStringSet constructors and destructors
//--------------------------------------------

TreeStringSet::TreeStringSet(treetype type)
    : root_{nullptr}, type_{type}, size_{0} {
    RandUInt32 rand_;
}

TreeStringSet::TreeStringSet(treetype type, size_t seed)
    : root_{nullptr}, type_{type}, size_{0} {
    RandUInt32 rand_{seed};
}

TreeStringSet::~TreeStringSet() {
    delete root_;
}

//--------------------------------------------
// Node constructors and destructors
//--------------------------------------------

TreeStringSet::Node::Node(string value) 
    : value_{value}, left_{nullptr}, right{nullptr}, size_{1} {
    // Nothing else to do
}

TreeStringSet::Node::~Node() {
    if (left_ != nullptr) {
        delete left_;
    }
    if (right_ != nullptr) {
        delete right_;
    }
}

//--------------------------------------------
// Iterator constructors and destructors
//--------------------------------------------



//--------------------------------------------
// TreeStringSet Member Functions
//--------------------------------------------

size_t TreeStringSet::size() const {
    return size_;
}

bool TreeStringSet::consistent() const {
    return ((size() == 0) && (root_ == nullptr)) ||
            ((size() > 0) && (root_ != nullptr));
}

