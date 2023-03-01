#include "SyntaxNode.hpp"

/// Default constructor, no children or parent and "None" type
SyntaxNode::SyntaxNode() : _parent(nullptr), _children(std::vector<SyntaxNode*>()), _stype(SyntaxType::None) {}

/// Type Constructor
/// \param stype type of syntax to set node to
SyntaxNode::SyntaxNode(SyntaxType stype) : _parent(nullptr), _children(std::vector<SyntaxNode*>()), _stype(stype) {}

/// Copy Constructor, copy the parent and make a new list of the same children
/// \param node node to copy
SyntaxNode::SyntaxNode(const SyntaxNode &node) : _parent(node._parent), _children(std::vector<SyntaxNode*>(node._children)), _stype(node._stype) {}

/// Set the node's parent
/// \param parent node pointer to set as parent
void SyntaxNode::Parent(SyntaxNode *parent) {
    _parent = parent;
}

/// Copy over an entire array of children to the end of the node's current list
/// \param children Double pointer to array of child pointers
/// \param childCount Number of children in the array
void SyntaxNode::Add(const std::vector<SyntaxNode *> & newChildren) {
    for (auto child : newChildren) {
        _children.push_back(child);
    }
}

/// Adds a child pointer to the array of children pointers
/// \param child pointer to child to add
void SyntaxNode::Add(SyntaxNode * child) {
    //prevent nasty segfaults
    if (child) {
        //add to child vector
        _children.push_back(child);

        //set child's parent to us
        child->Parent(this);
    }
}

/// Removes a child at given index
/// \param i index of child to remove
void SyntaxNode::Remove(int i) {
    auto childrenCopy = std::vector<SyntaxNode *>();
    //copy over all old children besides the one at index i
    for (int it = 0; it < _children.size(); it++) {
        if (i != it) childrenCopy.push_back(_children[it]);
    }
    //set the child vector to the temporary vector
    _children = childrenCopy;
}

/// Finds the index of a pointer to a child
/// \param child Pointer to child to find index of
/// \return index of child
int SyntaxNode::IndexOf(SyntaxNode *child) const {
    for (int i = 0; i < _children.size(); i++) {
        if (_children[i] == child) return i;
    }
    return -1;
}

/// Finds the index of a child
/// \param child Reference to child
/// \return index of child
int SyntaxNode::IndexOf(const SyntaxNode &child) const {
    for (int i = 0; i < _children.size(); i++) {
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
    return _parent == node._parent && _children == node._children && _stype == node._stype;
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
    return _children.size();
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
    return i < _children.size() ? _children[i] : nullptr;
}

/// Returns whether or not there exists a child that has the specified type
/// \param stype Type to check for
/// \return whether or not there is a child with the specified type
bool SyntaxNode::ContainsChildType(SyntaxType stype) const {
    for (auto child : _children) {
        if (child->Type() == stype) return true;
    }
    return false;
}

/// Destructor, delete the children and then delete the child array (recursively)
SyntaxNode::~SyntaxNode() {
    for (auto child : _children) {
        delete child;
    }
}
