//
// Created by gwend on 10.01.2020.
//

#ifndef ASD2_LABO4_TERNARYSEARCHTRIE_H
#define ASD2_LABO4_TERNARYSEARCHTRIE_H

#include <string>

class TernarySearchTrie {
private:
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

    TernarySearchTrie();

    /**
     * Insert un nouvel élément dans la structure
     * @param key
     */
    void insert(const std::string & key);

private:
    /**
     *
     * @param x
     * @param key
     * @param val
     * @param d
     * @return Retourne le noeud x
     */
    Node * insert(Node* x, const std::string & key, int d);

public:
    /**
     * Compte le nombre de fois qu'un élément est présent dans la structure
     * (cette fonction est la pour que la signature soit similaire à std::set, mais
     * dans les faits elle ne fait que de tester si la valeur est présent ou non
     * dans la structure.
     * @param key Valeur recherchée
     * @return 1 ou 0
     */
    int count(const std::string & key) const;
private:
    int count(Node* x, const std::string &key, int d) const;
};

#endif //ASD2_LABO4_TERNARYSEARCHTRIE_H
