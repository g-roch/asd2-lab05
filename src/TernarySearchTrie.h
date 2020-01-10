//
// Created by gwend on 10.01.2020.
//

#ifndef ASD2_LABO4_TERNARYSEARCHTRIE_H
#define ASD2_LABO4_TERNARYSEARCHTRIE_H

#include <string>

template <typename ValueType >
class TernarySearchTrie{

    //
    // Noeud de l'arbre. contient une cle, une valeur, et les liens vers les
    // sous-arbres droit et gauche.
    //
    struct Node {
    public:
        ValueType val;
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
    void put(std::string key, ValueType val){
        root = put(root,key,val,0);
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
    Node put(Node x, std::string key, ValueType val, int d){
        char c = key.at(d);
        //Si le noeud est vide
        if(x == nullptr) {x == new Node(); x.c = c;}

        //Si le char du noeud > char paramètre
        if(c < x.c)
            x.left = put(x.left,key,val,d);

       //Si le char du noeud < char paramètre
        else if(c > x.c)
            x.right = put(x.right, key, val,d);

        //Si le char du noeud = char paramètre
        else if(d < key.length() - 1)
            x.mid = put(x.mid, key, val, d+1);

        else
            x.val = val;

        return x;
    }

public:
    bool contains(std::string key){
        return get(key) != nullptr;
    }

    ValueType get(std::string key){
        Node x = get(root,key,0);
        if(x == nullptr) return nullptr;
        return x.val;
    }
private:
    Node get(Node x, std::string key, int d){
        if(x == nullptr) return nullptr;
        char c = key.at(d);
        if(c < x.c)                   return get(x.left, key, d);
        else if(c > x.c)              return get(x.right, key, d);
        else if(d < key.length() - 1) return get(x.mid, key, d+1);
        else                          return x;
    }
};

#endif //ASD2_LABO4_TERNARYSEARCHTRIE_H
