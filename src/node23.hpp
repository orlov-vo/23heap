#pragma once
#ifndef NODE_23_HPP
#define NODE_23_HPP

#include <iostream>

template<typename T>
class Node23
{
    template<typename Y> friend class Heap23;
    template<typename Y> friend int merge_nodes(Node23<Y> **a, Node23<Y> **b);

public:
    Node23(int key, T value) :
        child(NULL),
        left(NULL),
        right(NULL),
        parent(NULL),
        partner(NULL),
        extra(false),
        dim(0),
        key_(key),
        value_(value)
    {
    }

    int priority() { return key_; }
    T value() { return value_; }

    void addChild(Node23<T> *node);
    void removeChild(Node23<T> *child);
    void replaceChild(Node23<T> *new_node);

    void print(std::ostream &out, unsigned level);

protected:
    void printPartners(std::ostream &out, unsigned level);

private:
    Node23 *parent;
    Node23 *child;
    Node23 *left;
    Node23 *right;
    Node23 *partner;

    bool extra;
    int dim;
    int key_;
    T value_;
};

template<typename T>
int merge_nodes(Node23<T> **a, Node23<T> **b)
{
    Node23<T> *tree, *next_tree, *other, *next_other;
    int c = 0;

    if ((*a)->priority() <= (*b)->priority()) {
        tree = (*a);
        other = (*b);
    } else {
        tree = (*b);
        other = (*a);
    }
    ++c;

    next_tree = tree->partner;
    next_other = other->partner;

    if (!next_tree) {
        if (next_other) {
            tree->addChild(other);
            tree->dim++;
            *a = NULL;
            *b = tree;
        } else {
            tree->partner = other;
            other->partner = tree;
            other->extra = true;

            *a = tree;
            *b = NULL;
        }
    } else if (!next_other) {
        tree->partner = NULL;
        other->partner = next_tree;
        next_tree->partner = other;

        if (other->priority() < next_tree->priority()) {
            tree->addChild(other);
        } else {
            next_tree->extra = false;
            other->extra = true;
            tree->addChild(next_tree);
        }

        ++(tree->dim);

        ++c;
        *a = NULL;
        *b = tree;
    } else {
        tree->partner = NULL;
        next_tree->partner = NULL;
        next_tree->extra = false;
        next_tree->left = next_tree->right = next_tree;
        next_tree->parent = NULL;

        tree->addChild(other);
        ++(tree->dim);

        *a = next_tree;
        *b = tree;
    }
    return c;
}

template<typename T>
void Node23<T>::addChild(Node23<T> *node)
{
    Node23<T> *left, *right;
    if ((left = child)) {
        right = left->right;
        node->left = left;
        node->right = right;
        right->left = node;
        left->right = node;
    } else {
        node->left = node->right = node;
    }
    child = node;
    node->parent = this;
}

template<typename T>
void Node23<T>::removeChild(Node23<T> *node)
{
    Node23<T> *left, *right;
    if (node->dim) {
        left = node->left;
        right = node->right;
        left->right = right;
        right->left = left;
        child = left;
    } else {
        child = NULL;
    }
}

template<typename T>
void Node23<T>::replaceChild(Node23<T> *new_node)
{
    Node23<T> *l, *r = right;

    if (r == this) {
        new_node->right = new_node->left = new_node;
    } else {
        l = left;
        l->right = new_node;
        r->left = new_node;
        new_node->left = l;
        new_node->right = r;
    }

    new_node->parent = parent;
    if (parent->child == this)
        parent->child = new_node;
}

template <typename T>
void Node23<T>::print(std::ostream &out, unsigned level)
{
    Node23<T> *x;
    bool is_started = false;
    for (x = this; !is_started || x != this; x = x->right) {
        if (!is_started)
            is_started = true;
        for (int i = 0; i < level; ++i) {
            out << "  ";
        }
        out << x->key_ << '[' << x->dim << ']' << '[' << x->extra << ']';
        if (x->partner != NULL && x->partner != x) {
            out << " | " << x->partner->key_ << '[' << x->partner->dim << ']' << '[' << x->partner->extra << ']';
        }
        out << std::endl;
        if (x->child != NULL) {
            x->child->print(out, level + 1);
        }
        if (x->partner != NULL && x->partner != x && x->partner->child != NULL) {
            x->partner->child->print(out, level + 1);
        }
    }
}

template <typename T>
void Node23<T>::printPartners(std::ostream &out, unsigned level)
{
    Node23<T> *x = partner;
    for (int i = 0; i < level; ++i) {
        out << "  ";
    }
    out << x->key_ << '[' << x->dim << ']' << '[' << x->extra << ']' << std::endl;
    if (x->child != NULL) {
        x->child->print(out, level + 1);
    }
}

#endif
