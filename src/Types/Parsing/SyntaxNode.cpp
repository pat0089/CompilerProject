#include "SyntaxNode.hpp"
#include <type_traits>
//default constructor, no children or parent
SyntaxNode::SyntaxNode() : _childCount(0), _parent(nullptr), _children(nullptr), _stype(SyntaxType::None) { }

SyntaxNode::SyntaxNode(SyntaxType stype) : _childCount(0), _parent(nullptr), _children(nullptr), _stype(stype) {}

//copy the parent of and make a new list of the same children as in astNode
SyntaxNode::SyntaxNode(const SyntaxNode &node) : _childCount(node._childCount), _parent(node._parent), _stype(node._stype) {
    _children = new SyntaxNode* [_childCount];
    for (int i = 0; i < _childCount; i++) {
        _children[i] = node._children[i];
    }
}

void SyntaxNode::Parent(SyntaxNode *parent) {
    _parent = parent;
}

//copy over an array of children
void SyntaxNode::Add(SyntaxNode **children, int childCount) {
    //copy over child reference array
    SyntaxNode ** oldChildren = new SyntaxNode* [_childCount];
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

void SyntaxNode::Remove(int i) {
    //copy over all old children besides the one at index i
    SyntaxNode ** childrenCopy = new SyntaxNode* [_childCount - 1];
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

int SyntaxNode::IndexOf(SyntaxNode *child) const {
    for (int i = 0; i < _childCount; i++) {
        if (_children[i] == child) return i;
    }
    return -1;
}

int SyntaxNode::IndexOf(const SyntaxNode &child) const {
    for (int i = 0; i < _childCount; i++) {
        if (*_children[i] == child) return i;
    }
    return -1;
}

void SyntaxNode::Remove(const SyntaxNode &child) {
    Remove(IndexOf(child));
}

void SyntaxNode::Remove(SyntaxNode *child) {
    Remove(IndexOf(child));
}

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

SyntaxNode * SyntaxNode::operator[](int i) {
    return _children[i];
}

SyntaxNode & SyntaxNode::Parent() const {
    return *_parent;
}

std::ostream &operator<<(std::ostream &os, SyntaxNode &rhs) {
    os << rhs.PrettyPrint();
    return os;
}

int SyntaxNode::ChildCount() const {
    return _childCount;
}

SyntaxType SyntaxNode::Type() const {
    return _stype;
}

SyntaxNode *SyntaxNode::Child(int i) const {
    return i < _childCount ? _children[i] : nullptr;
}

bool SyntaxNode::ContainsChildType(SyntaxType stype) const {
    for (int i = 0; i < _childCount; i++) {
        if (_children[i]->Type() == stype) return true;
    }
    return false;
}

SyntaxNode::~SyntaxNode() {
    while (_childCount > 0) {
        delete _children[_childCount - 1];
        _childCount--;
    }
    delete[] _children;
}
