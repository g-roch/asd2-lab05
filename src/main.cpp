/**
 * @file main.cpp
 * Labo5
 * @author Gabriel Roch
 * @author Gwendoline Dossegger
 * @author Jean-Luc Blanc
 *
 * Nous avons choisis la structure "unordered_set"
 * car elle possède un temps de recherche, insertion et suppression en O(1)
 * Pour changer de structure entre unordered_set et TST il suffit de mettre la define TST à true ou false
 */
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_set>
#include "TernarySearchTrie.h"

//définit si on utilise un TST ou une unordered_set, true = TST, false = unordered_set
#define TST true

using namespace std;

//
const string LETTRE_ALLOWED("abcdefghijklmnopqrstuvwxyz'");

/**
 * Converti le mot en minuscule et ne garde que les caractères alphabétique
 * et les apostrophes à l'intérieur du mot
 * @param str Chaine à néttoyer
 */
void cleanWord(string & str) {
    string newstr;
    for(char i : str) {
        if(isalpha(i) or i == '\'')
            newstr.push_back((char)(tolower(i)));
    }
    while(newstr.front() == '\'')
        newstr.erase(0, 1);
    while(newstr.back() == '\'')
        newstr.erase(newstr.size() - 1);
    swap(newstr, str);
}
/**
 *
 * @tparam T, type de conteneur
 * @param filename, fichier contenant le dictionnaire
 * @param dict, le dictionnaire
 */
template <typename T>
void loadDictionnary(const string & filename, T & dict) {
    ifstream ifs(filename);
    string str;
    while(ifs) {
        getline(ifs, str);
        cleanWord(str);
        dict.insert(str);
    }
}

/**
 *
 * @tparam F,
 * @param filename, fichier contenant le texte
 * @param fn, fonction à utiliser
 */
template <typename F>
void loadText(const string & filename, F fn) {
    ifstream ifs(filename);
    string str;
    while(ifs) {
        ifs >> str;
        cleanWord(str);
        if(str.size())
            fn(str);
    }
}

/**
 * @brief affiche les corrections valides pour les mots faux
 * @param noHypo
 * @param strCopy
 */
void displayCorr(int noHypo, const string & strCopy, ofstream & result)
{
    result << noHypo << ":" << strCopy << endl;
}

/**
 * @brief test les 4 hypothèses de correction d'un mot
 * @tparam T, type du conteneur
 * @param str, mot à corriger
 * @param dict, dictionnaire
 */
template <typename T>
void hypoCorrWords(const string & str, T dict, ofstream & result)
{
    result << '*' << str << endl;
    string strCopy;
    //hypothèse 1
    for(unsigned i = 0; i < str.size(); ++i)
    {
        strCopy = str;
        strCopy.erase(i, 1);
        if(dict.count(strCopy))
        {
            displayCorr(1, strCopy, result);
        }
    }
    //hypothèse 2
    for(unsigned i = 0; i <= str.size(); ++i) {
        strCopy = str;
        strCopy.insert(i, "-"); // caractère remplacer dans la boucle
        for(char c : LETTRE_ALLOWED) {
            strCopy[i] = c;
            if(dict.count(strCopy))
                displayCorr(2, strCopy, result);

        }
    }

    //hypothèse 3
    for(unsigned i = 0; i < str.size(); ++i)
    {
        strCopy = str;
        for(char c : LETTRE_ALLOWED) {
            strCopy[i] = c;
            if(dict.count(strCopy))
                displayCorr(3, strCopy, result);
        }
    }
    //hypothèse 4
    strCopy = str;
    for(unsigned i = 0; i < str.size()-1; ++i) {
        swap(strCopy[i], strCopy[i+1]);
        if(dict.count(strCopy))
            displayCorr(4, strCopy, result);
        swap(strCopy[i], strCopy[i+1]);
    }
}

/**
 * @brief lance la correction des erreurs
 * @tparam T, types de données dans le conteneur
 * @param str, chaine de caractère à corriger
 * @param dict, conteneur du dictionnaire
 */
template <typename T>
void corrError(const string & str, T dict, ofstream & result)
{
    hypoCorrWords(str, dict, result);
}


int main() {
#if TST
    TernarySearchTrie dict;
#else
    unordered_set<string> dict;
#endif

    // Le Dictionnaire est en UTF-8 mais puisque l'on garde uniquement les
    // caractères a-z et apostrophe (') on peut le traiter comme un fichier
    // ASCII sans aucun problème (ces 27 caractères sont codés de la même manière
    // en UTF-8 et en ASCII).

    //temps load dict début
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    loadDictionnary("data/dictionary.txt", dict);


    //temps load dict fin
    end = chrono::system_clock::now();

    long long loadDictTime = chrono::duration_cast<chrono::seconds> (end-start).count();

    //temps corr txt début
    chrono::time_point<chrono::system_clock> startCorr, endCorr;
    startCorr = chrono::system_clock::now();

    ofstream result;
    result.open("data/result.txt");

    loadText(
            "data/input_sh.txt",
            [& dict, & result] (const string & str) {
                /* traitement du mot (test s'il est dans le dictionnaire */
                if(!dict.count(str))
                {
                    corrError(str, dict, result);
                }
            }
            );

    result.close();


    //temps corr txt fin
    endCorr = chrono::system_clock::now();

    long long corrTxtTime = chrono::duration_cast<chrono::seconds> (endCorr-startCorr).count();

    cout << "temps load dict : " << loadDictTime << " seconde(s) " << endl;
    cout << "temps corr txt  : " << corrTxtTime  << " seconde(s) " << endl;


	return EXIT_SUCCESS;
}
