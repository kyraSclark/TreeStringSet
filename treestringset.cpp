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

using namespace std;

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
    : value_{value}, left_{nullptr}, right_{nullptr}, size_{1} {
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

void TreeStringSet::insert(const string& value) {
    if (!exists(value)) {
        if (type_ == treetype::LEAF) {
            insertAtLeafNode(root_, value);
        } else if (type_ == treetype::ROOT) {
            insertAtRoot(root_, value);
        } else { // type is RANDOMIZED
            insertAtRandom(root_, value);
        }
        ++size_;
    }
}

void TreeStringSet::insertAtLeafNode(Node*& root, const string& value) {
    if (root == nullptr) {
        root = new Node{value};
    } else if (root->value_ > value) {
        insertAtLeafNode(root->left_, value);
        ++(*root).size_;
    } else {
        insertAtLeafNode(root->right_, value);
        ++(*root).size_;
    }
}

void TreeStringSet::insertAtRoot(Node*& root, const string& value) {
    //implement later!!
}

void TreeStringSet::insertAtRandom(Node*& root, const string& value) {
    //implement later!!
}

bool TreeStringSet::exists(const string& value) const {
    return existsHelper(root_, value);
}

bool TreeStringSet::existsHelper(Node* root, const string& value) const {
    if (root == nullptr) {
        return false;
    } else if (root->value_ == value) {
        return true;
    } else if (root->value_ < value) {
        return existsHelper(root->right_, value);
    } else {
        return existsHelper(root->left_, value);
    }
}

//--------------------------------------------
// Prints
//--------------------------------------------

ostream& TreeStringSet::print(ostream& o) const {
    if (size() == 0) {
        return o << "-";
    } else {
        o << size();
        o << ":(";
        if (root_->left_ == nullptr) {
            o << "-";
        } else {
            root_->left_->print(o);
        }
        o << ", ";
        o << root_->value_;
        o << ", ";
        if (root_->right_ == nullptr) {
            o << "-";
        } else {
            root_->right_->print(o);
        }
        o << ")";
        return o;
    }
}

ostream& TreeStringSet::Node::print(ostream& o) const {
    o << size_;
    o << ":(";
    if (left_ == nullptr) {
        o << "-";
    } else {
        left_->print(o);
    }
    o << ", ";
    o << value_;
    o << ", ";
    if (right_ == nullptr) {
        o << "-";
    } else {
        right_->print(o);
    }
    o << ")";
    return o;
}

ostream& operator<<(ostream& o, const TreeStringSet& t) {
    return t.print(o);
}


