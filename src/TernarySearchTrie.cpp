/**
 * @file TernarySearchTrie.cpp
 * Labo5
 * @author Gabriel Roch
 * @author Gwendoline Dossegger
 * @author Jean-Luc Blanc
 */

#include "TernarySearchTrie.h"

using namespace std;

TernarySearchTrie::TernarySearchTrie() {
    root = nullptr;
}

TernarySearchTrie::Node * TernarySearchTrie::insert(TernarySearchTrie::Node * x, const std::string &key, int position) {
        char c = key.at(position);
        // Si le noeud est vide
        if(x == nullptr)
        {
            x = new Node();
            x->c = c;
        }

        // Si le char du noeud > char paramètre
        if(c < x->c)
            x->left = insert(x->left, key, position);

        //Si le char du noeud < char paramètre
        else if(c > x->c)
            x->right = insert(x->right, key, position);

        //Si le char du noeud = char paramètre ET qu'il reste de char
        else if(position < key.length() - 1)
            x->mid = insert(x->mid, key, position + 1);

        else {
            x->exist = true;
            return restoreBalance(x);
        }

        return restoreBalance(x);
}

void TernarySearchTrie::insert(const std::string & key) {
    root = insert(root,key,0);
}

int TernarySearchTrie::count(const std::string &key) const {
    return count(root,key,0);
}

int TernarySearchTrie::count(TernarySearchTrie::Node * x, const std::string &key, int position) const {
    if(x == nullptr)
        return 0;
    char c = key.at(position);
    if(c < x->c)
        return count(x->left, key, position);
    else if(c > x->c)
        return count(x->right, key, position);
    else if(position < key.length() - 1)
        return count(x->mid, key, position + 1);
    else
        return x->exist;
}

TernarySearchTrie::Node *TernarySearchTrie::rotateLeft(TernarySearchTrie::Node *x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    updateNodeHeight(x);
    updateNodeHeight(y);
    return y;
}

TernarySearchTrie::Node *TernarySearchTrie::rotateRight(TernarySearchTrie::Node *x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    updateNodeHeight(x);
    updateNodeHeight(y);
    return y;
}

int TernarySearchTrie::height(TernarySearchTrie::Node *x) {
    if (x)
        return x->height;
    else
        return -1;
}

void TernarySearchTrie::updateNodeHeight(TernarySearchTrie::Node *x) {
    x->height = max(height(x->left), height(x->right)) + 1;
}

int TernarySearchTrie::balance(TernarySearchTrie::Node *x) {
    if (x)
        return height(x->right) - height(x->left);
    else
        return 0;
}

TernarySearchTrie::Node *TernarySearchTrie::restoreBalance(TernarySearchTrie::Node *x) {
    if(balance(x) < -1) // left < right-1
    {
        if (balance(x->right)>0)
            x->right = rotateRight( x->right );
        x = rotateLeft(x);
    }
    else if( balance(x) > 1) // left > right+1
    {
        if ( balance(x->left) < 0 )
            x->left = rotateLeft( x->left );
        x = rotateRight(x);
    }
    else updateNodeHeight(x);
    return x;/*
    if (balance(x) < -1) {
        if (balance(x->left) > 0)
            x->left = rotateLeft(x->left);
        x = rotateRight(x);
    } else if(balance(x) > 1) {
        if (balance(x->right) > 0)
            x->right = rotateRight(x->right);
        x = rotateLeft(x);
    } else {
        updateNodeHeight(x);
    }
    return x;*/
}


TernarySearchTrie::Node::Node() :
    exist(false),
    right(nullptr),
    mid(nullptr),
    left(nullptr),
    height(0)
{

}

