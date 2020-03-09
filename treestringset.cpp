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
#include <algorithm>

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

TreeStringSet::Iterator::Iterator(Node* current)
    : current_{current} {
    queue<Node*> pending_;
}

string& TreeStringSet::Iterator::operator*() const {
    string& currentValue = current_->value_;
    return currentValue;
}

TreeStringSet::Iterator& TreeStringSet::Iterator::operator++() {
    if (current_->left_ != nullptr) {
        pending_.push(current_->left_);
    }
    if (current_->right_ != nullptr) {
        pending_.push(current_->right_);
    }
    if (pending_.empty()) {
        // if this is the last element in the tree, make the iterator end()
        current_ = nullptr;
    } else {
        current_ = pending_.front();
        pending_.pop();
    }
    return *this;
}

bool TreeStringSet::Iterator::operator==(const TreeStringSet::Iterator& rhs)
                                                    const {
    // We assume two iterators come from the same tree
    return (current_ == rhs.current_);
}

bool TreeStringSet::Iterator::operator!=(const TreeStringSet::Iterator& rhs)
                                                    const {
    return !(*this == rhs);
}

TreeStringSet::iterator TreeStringSet::begin() const {
    return Iterator(root_);
}

TreeStringSet::iterator TreeStringSet::end() const {
    return Iterator();
}

TreeStringSet::Iterator::pointer TreeStringSet::Iterator::operator->() const {
  return &(**this);
}

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
        } else {  // type is RANDOMIZED
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
        ++root->size_;
    } else {
        insertAtLeafNode(root->right_, value);
        ++root->size_;
    }
}

void TreeStringSet::insertAtRoot(Node*& root, const string& value) {
    if (root == nullptr) {
        root = new Node{value};
    } else if (value < root->value_) {
        insertAtRoot(root->left_, value);
        ++root->size_;
        rotateRight(root);
    } else if (value > root->value_) {
        insertAtRoot(root->right_, value);
        ++root->size_;
        rotateLeft(root);
    }
}

void TreeStringSet::rotateRight(Node*& root) {
    Node* leftChild = root->left_;

    // Adjust leftChild size to include root and root's right child
    if (root->right_ != nullptr) {
        leftChild->size_ += 1 + root->right_->size_;
    } else {
        ++leftChild->size_;
    }

    // Adjust root size to lose leftChild and its left child
    if (leftChild->left_ != nullptr) {
        root->size_ -= leftChild->left_->size_;
    }
    --root->size_;

    // Then, rotate
    if (leftChild->right_ != nullptr) {
        root->left_ = leftChild->right_;
    } else {
        root->left_ = nullptr;
    }
    leftChild->right_ = root;
    root = leftChild;
}

void TreeStringSet::rotateLeft(Node*& root) {
    Node* rightChild = root->right_;

    // Adjust rightChild size to include root and root's left child
    if (root->left_ != nullptr) {
        rightChild->size_ += 1 + root->left_->size_;
    } else {
        ++rightChild->size_;
    }

    // Adjust root size to lose rightChild and its right child
    if (rightChild->right_ != nullptr) {
        root->size_ -= rightChild->right_->size_;
    }
    --root->size_;

    if (rightChild->left_ != nullptr) {
        root->right_ = rightChild->left_;
    } else {
        root->right_ = nullptr;
    }
    rightChild->left_ = root;

    root = rightChild;
}

void TreeStringSet::insertAtRandom(Node*& root, const string& value) {
    if (root == nullptr) {
        insertAtRoot(root, value);
    } else {
        size_t randNumber = rand.get(root->size_ + 1);
        if (randNumber == 0) {
            insertAtRoot(root, value);
        } else if (value < root->value_) {
            ++root->size_;
            insertAtRandom(root->left_, value);
        } else {
            ++root->size_;
            insertAtRandom(root->right_, value);
        }
    }
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

bool TreeStringSet::operator==(const TreeStringSet& rhs) const {
    if (size() != rhs.size()) {
        return false;
    } else {
        for (TreeStringSet::iterator it = rhs.begin(); it != rhs.end(); ++it) {
            if (!exists(*it)) {
                return false;
            }
        }
        return true;
    }
}

bool TreeStringSet::operator!=(const TreeStringSet& rhs) const {
    return !(*this == rhs);
}

int TreeStringSet::height() const {
    return heightHelper(root_);
}

int TreeStringSet::heightHelper(const Node* root) const {
    if (root == nullptr) {
        return -1;
    } else {
        int heightLeft = heightHelper(root->left_);
        int heightRight = heightHelper(root->right_);
        return 1 + max(heightLeft, heightRight);
    }
}

double TreeStringSet::averageDepth() const {
    if (size() == 0) {
        return 0;
    } else {
        return totalDepth(root_, 0) / size();
    }
}

int TreeStringSet::totalDepth(const Node* root, int level) const {
    if (root == nullptr) {
        return 0;
    } else {
        int nextLevel = level + 1;
        return level + totalDepth(root->left_, nextLevel)
                + totalDepth(root->right_, nextLevel);
    }
}

ostream& TreeStringSet::showStatistics(ostream& o) const {
    o << size();
    o << " nodes, height ";
    o << height();
    o << ", average depth ";
    o << averageDepth();
    o << endl;
    return o;
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


