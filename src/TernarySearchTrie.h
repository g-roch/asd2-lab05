//
// Created by gwend on 10.01.2020.
//

#ifndef ASD2_LABO4_TERNARYSEARCHTRIE_H
#define ASD2_LABO4_TERNARYSEARCHTRIE_H

#include <string>

class TernarySearchTrie {

    //
    // Noeud de l'arbre. contient une cle, une valeur, et les liens vers les
    // sous-arbres droit et gauche.
    //
    struct Node {
    public:
        bool exist;
        char c;
        Node* right; // sous arbre avec des cles plus grandes
        Node* mid;   // sous arbres
        Node* left;  // sous arbre avec des cles plus petites

    };

    //
    // Racine de l'arbre.
    //
    Node* root;

public:
    /**
     * Initialiser le root (pas sur)
     * @param key
     * @param val
     */
    void insert(std::string key){
        root = insert(root,key,0);
    }

private:
    /**
     *
     * @param x
     * @param key
     * @param val
     * @param d
     * @return Retourne le noeud x
     */
    Node* insert(Node* x, std::string key, int d){
        char c = key.at(d);
        //Si le noeud est vide
        if(x == nullptr) {
            x = new Node(); x->c = c;
        }

        //Si le char du noeud > char paramètre
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

public:

    int count(std::string key){
        return count(root,key,0);
    }
private:
    int count(Node* x, std::string key, int d){
        if(x == nullptr) return 0;
        char c = key.at(d);
        if(c < x->c)                   return count(x->left, key, d);
        else if(c > x->c)              return count(x->right, key, d);
        else if(d < key.length() - 1) return count(x->mid, key, d+1);
        else                          return x->exist;
    }
};

#endif //ASD2_LABO4_TERNARYSEARCHTRIE_H
