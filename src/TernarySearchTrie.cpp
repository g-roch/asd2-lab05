/**
 * @file TernarySearchTrie.cpp
 * Labo5
 * @author Gabriel Roch
 * @author Gwendoline Dossegger
 * @author Jean-Luc Blanc
 */

#include "TernarySearchTrie.h"

TernarySearchTrie::TernarySearchTrie() : root(nullptr) {
}

TernarySearchTrie::Node * TernarySearchTrie::insert(TernarySearchTrie::Node * x, const std::string &key, int d) {
        char c = key.at(d);
        // Si le noeud est vide
        if(x == nullptr) {
            x = new Node(c);
        }

        // Si le char du noeud > char paramètre
        if(c < x->c)
            x->left = insert(x->left, key, d);

        //Si le char du noeud < char paramètre
        else if(c > x->c)
            x->right = insert(x->right, key, d);

        //Si le char du noeud = char paramètre et qu'il reste des char
        else if(d < key.length() - 1)
            x->mid = insert(x->mid, key, d+1);

        else
            x->exist = true;

        return restoreBalance(x);
}

void TernarySearchTrie::insert(const std::string & key) {
    root = insert(root,key,0);
}

int TernarySearchTrie::count(const std::string &key) const {
    return count(root,key,0);
}

int TernarySearchTrie::count(TernarySearchTrie::Node * x, const std::string &key, int d) const {
    if(x == nullptr)
        return 0;
    char c = key.at(d);
    if(c < x->c)
        return count(x->left, key, d);
    else if(c > x->c)
        return count(x->right, key, d);
    else if(d < key.length() - 1)
        return count(x->mid, key, d+1);
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

void TernarySearchTrie::updateNodeHeight(TernarySearchTrie::Node *x) {
    x->nodeHeight = std::max(height(x->right),height(x->left)) + 1;
}

int TernarySearchTrie::balance(TernarySearchTrie::Node *x) {
    if(x==nullptr) return 0;
    return height(x->left) - height(x->right);
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
    return x;
}

int TernarySearchTrie::height(TernarySearchTrie::Node *x) {
    if ( x == nullptr )
        return -1;
    return x->nodeHeight;
}

TernarySearchTrie::Node::Node(char c) : exist(false), c(c), right(nullptr), mid(nullptr), left(nullptr), nodeHeight(0) {

}
