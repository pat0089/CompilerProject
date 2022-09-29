#include "SyntaxNode.hpp"

/// Default constructor, no children or parent and "None" type
SyntaxNode::SyntaxNode() : _childCount(0), _parent(nullptr), _children(nullptr), _stype(SyntaxType::None) { }

/// Type Constructor
/// \param stype type of syntax to set node to
SyntaxNode::SyntaxNode(SyntaxType stype) : _childCount(0), _parent(nullptr), _children(nullptr), _stype(stype) {}

/// Copy Constructor, copy the parent and make a new list of the same children
/// \param node node to copy
SyntaxNode::SyntaxNode(const SyntaxNode &node) : _childCount(node._childCount), _parent(node._parent), _stype(node._stype) {
    _children = new SyntaxNode* [_childCount];
    for (int i = 0; i < _childCount; i++) {
        _children[i] = node._children[i];
    }
}

/// Set the node's parent
/// \param parent node pointer to set as parent
void SyntaxNode::Parent(SyntaxNode *parent) {
    _parent = parent;
}

/// Copy over an entire array of children to the end of the node's current list
/// \param children Double pointer to array of child pointers
/// \param childCount Number of children in the array
void SyntaxNode::Add(SyntaxNode **children, int childCount) {
    //copy over child reference array
    auto ** oldChildren = new SyntaxNode* [_childCount];
    for (int i = 0; i < _childCount; i++) {
        oldChildren[i] = _children[i];
    }

    //delete and resize child reference array, but do not update count yet
    delete[] _children;
    _children = new SyntaxNode*[_childCount + childCount];

    //copy over all data into new child reference array
    for (int i = 0; i < _childCount + childCount; i++) {
        if (i < _childCount) {
            _children[i] = oldChildren[i];
        } else {
            _children[i] = children[i - _childCount];
        }
        //set child's parent to us
        _children[i]->Parent(this);
    }

    //update child count
    _childCount += childCount;
    delete[] oldChildren;
}

/// Adds a child pointer to the array of children pointers
/// \param child pointer to child to add
void SyntaxNode::Add(SyntaxNode * child) {
    //copy over child reference array
    auto oldChildren = new SyntaxNode* [_childCount];
    for (int i = 0; i < _childCount; i++) {
        oldChildren[i] = _children[i];
    }

    //delete and resize child reference array, but do not update count yet
    delete[] _children;
    _children = new SyntaxNode*[_childCount + 1];

    //copy over all data into new child reference array
    for (int i = 0; i < _childCount + 1; i++) {
        if (i < _childCount) {
            _children[i] = oldChildren[i];
        } else {
            _children[i] = child;
        }
    }

    //update child count
    _childCount++;
    delete[] oldChildren;

    //set child's parent to us
    child->Parent(this);
}

/// Removes a child at given index
/// \param i index of child to remove
void SyntaxNode::Remove(int i) {
    //copy over all old children besides the one at index i
    auto ** childrenCopy = new SyntaxNode* [_childCount - 1];
    int iterator = 0;
    for (int index = 0; index < _childCount; i++) {
        if (index == i) {
            continue;
        } else {
            childrenCopy[iterator] = _children[i];
            iterator++;
        }
    }

    //adjust child count and child reference array accordingly
    _childCount--;
    delete[] _children;
    _children = new SyntaxNode*[_childCount];

    //copy over data into new child reference array
    for (int j = 0; j < _childCount; j++) {
        _children[j] = childrenCopy[j];
    }
    delete[] childrenCopy;
}

/// Finds the index of a pointer to a child
/// \param child Pointer to child to find index of
/// \return index of child
int SyntaxNode::IndexOf(SyntaxNode *child) const {
    for (int i = 0; i < _childCount; i++) {
        if (_children[i] == child) return i;
    }
    return -1;
}

/// Finds the index of a child
/// \param child Reference to child
/// \return index of child
int SyntaxNode::IndexOf(const SyntaxNode &child) const {
    for (int i = 0; i < _childCount; i++) {
        if (*_children[i] == child) return i;
    }
    return -1;
}

/// Remove child
/// \param child Reference to child
void SyntaxNode::Remove(const SyntaxNode &child) {
    Remove(IndexOf(child));
}

/// Remove child
/// \param child Pointer to child
void SyntaxNode::Remove(SyntaxNode *child) {
    Remove(IndexOf(child));
}

/// Equality operator
/// \param node node to compare to
/// \return whether or not the syntax nodes are equivalent
bool SyntaxNode::operator==(const SyntaxNode &node) const {
    if (_childCount == node._childCount && _parent == node._parent) {
        for (int i = 0; i < _childCount; i++) {
            if (_children[i] != node._children[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

/// Indexing operator
/// \param i Index of child
/// \return pointer to i'th child
SyntaxNode * SyntaxNode::operator[](int i) {
    return _children[i];
}

/// Get a reference to the node's Parent
/// \return Reference to the node's Parent
SyntaxNode & SyntaxNode::Parent() const {
    return *_parent;
}

/// Stream output operator
/// \param os output stream
/// \param rhs syntax node reference to output
/// \return reference to output stream
/// Uses virtual PrettyPrint function to output correct syntax node type
std::ostream &operator<<(std::ostream &os, SyntaxNode &rhs) {
    os << rhs.PrettyPrint();
    return os;
}

/// Get the number of children
/// \return number of children
int SyntaxNode::ChildCount() const {
    return _childCount;
}

/// Get the syntax's type
/// \return type of syntax
SyntaxType SyntaxNode::Type() const {
    return _stype;
}

/// Get a pointer to the i'th child
/// \param i index of child
/// \return pointer to child
/// This function is usable by pointers to use the indexing operator which otherwise uses a reference
SyntaxNode *SyntaxNode::Child(int i) const {
    return i < _childCount ? _children[i] : nullptr;
}

/// Returns whether or not there exists a child that has the specified type
/// \param stype Type to check for
/// \return whether or not there is a child with the specified type
bool SyntaxNode::ContainsChildType(SyntaxType stype) const {
    for (int i = 0; i < _childCount; i++) {
        if (_children[i]->Type() == stype) return true;
    }
    return false;
}

/// Destructor, delete the children and then delete the child array (recursively)
SyntaxNode::~SyntaxNode() {
    while (_childCount > 0) {
        delete _children[_childCount - 1];
        _childCount--;
    }
    delete[] _children;
}
