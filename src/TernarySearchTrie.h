/**
 * @file TernarySearchTrie.h
 * Labo5
 * @author Gabriel Roch
 * @author Gwendoline Dossegger
 * @author Jean-Luc Blanc
 */

#ifndef ASD2_LABO4_TERNARYSEARCHTRIE_H
#define ASD2_LABO4_TERNARYSEARCHTRIE_H

#include <string>

class TernarySearchTrie {
private:
    /**
     * Structure d'un noeud, contient un char, bool = si le mot existe et
     * une référence sur les sous-arbres gauche/droite/milieux
     */
    struct Node {
    public:
        bool exist;  // si le mot existe
        char c;      // char du noeud
        Node* right; // sous arbre avec des cles plus grandes
        Node* mid;   // sous arbres
        Node* left;  // sous arbre avec des cles plus petites

        int height; // hauteur de l'arbre

        Node();
    };

    /**
     * Noeud racine
     */
    Node* root;

public:
    /**
     * Cosntructeur par défaut
     */
    TernarySearchTrie();

    /**
     * Insert un nouvel élément dans la structure
     * @param key Mot a inséré
     */
    void insert(const std::string & key);

private:
    /**
     * Insertion position' un nouvel élément dans la structure
     * @param x Noeud où insérer l'élément
     * @param key Element a inséré (string)
     * @param position Index du du string
     * @return Retourne le noeud x
     */
    Node * insert(Node* x, const std::string & key, int position);

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

    /**
     * Compte le nombre de fois qu'un élément est présent dans la structure
     * (cette fonction est la pour que la signature soit similaire à std::set, mais
     * dans les faits elle ne fait que de tester si la valeur est présent ou non
     * dans la structure.
     * @param x Noeud
     * @param position index qui détermine la position dans le string
     * @param key Valeur recherchée
     * @return 1 ou 0
     */
    int count(Node* x, const std::string &key, int position) const;

private:
    Node* rotateLeft(Node* x);
    Node* rotateRight(Node* x);
    int height(Node* x);
    void updateNodeHeight(Node* x);
    int balance(Node* x);
    Node* restoreBalance(Node* x);

};

#endif //ASD2_LABO4_TERNARYSEARCHTRIE_H
