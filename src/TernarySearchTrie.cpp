
#include "TernarySearchTrie.h"

TernarySearchTrie::TernarySearchTrie() {
    root = new Node();
}

TernarySearchTrie::Node * TernarySearchTrie::insert(TernarySearchTrie::Node * x, const std::string &key, int d) {
        char c = key.at(d);
        // Si le noeud est vide
        if(x == nullptr) {
            x = new Node();
            x->c = c;
        }

        // Si le char du noeud > char paramètre
        if(c < x->c)
            x->left = insert(x->left, key, d);

        //Si le char du noeud < char paramètre
        else if(c > x->c)
            x->right = insert(x->right, key, d);

        //Si le char du noeud = char paramètre
        else if(d < key.length() - 1)
            x->mid = insert(x->mid, key, d+1);

        else
            x->exist = true;

        return x;
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
