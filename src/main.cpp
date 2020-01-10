
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "TernarySearchTrie.h"

#define TST true

using namespace std;

const string LETTRE_ALLOWED("abcdefghijklmnopqrstuvwxyz'");

/**
 * Converti le mot en minuscule et ne garde que les caractères alphabétique
 * et les apostrophes à l'intérieur du mot
 * @param str Chaine à néttoyer
 */
void cleanWord(string & str) {
    string newstr;
    for(size_t i = 0; i < str.size(); ++i) {
        if(isalpha(str[i]) or str[i] == '\'')
            newstr.push_back(tolower(str[i]));
    }
    while(newstr.front() == '\'')
        newstr.erase(0, 1);
    while(newstr.back() == '\'')
        newstr.erase(newstr.size() - 1);
    swap(newstr, str);
}
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

void displayCorr(int noHypo, const string & strCopy)
{
    cout << noHypo << ":" << strCopy << endl;
}

template <typename T>
void hypoCorrWords(const string & str, T dict)
{
    cout << '*' << str << endl;
    string strCopy;
    for(int i = 0; i < str.size(); ++i)
    {
        strCopy = str;
        strCopy.erase(i, 1);
        if(dict.count(strCopy))
        {
            displayCorr(1, strCopy);
        }
    }
    for(int i = 0; i <= str.size(); ++i) {
        strCopy = str;
        strCopy.insert(i, "-"); // caractère remplacer dans la boucle
        for(char c : LETTRE_ALLOWED) {
            strCopy[i] = c;
            if(dict.count(strCopy))
                displayCorr(2, strCopy);

        }
    }

    for(int i = 0; i < str.size(); ++i)
    {
        strCopy = str;
        for(char c : LETTRE_ALLOWED) {
            strCopy[i] = c;
            if(dict.count(strCopy))
                displayCorr(3, strCopy);
        }
    }
    strCopy = str;
    for(int i = 0; i < str.size()-1; ++i) {
        swap(strCopy[i], strCopy[i+1]);
        if(dict.count(strCopy))
            displayCorr(4, strCopy);
        swap(strCopy[i], strCopy[i+1]);
    }
}

template <typename T>
bool corrError(const string & str, T dict)
{
    hypoCorrWords(str, dict);

    //pseudo code correction d'erreur
        //test si supprimer lettre à pos de l'erreur marche, sinon false
        //test si insérer/modifier une possible lettre à la pos de l'erreur, sinon false
        //test d'inverser la lettre à pos avec la lettre à pos+1, si rien n'est trouvé alors false
    //si qqchose marche, alors renvoyer la liste des solutions possibles au user
    //si rien ne marche alors on ne propose aucune correction au user

}


int main(int argc, const char * argv[]) {
#if TST
    TernarySearchTrie dict;
#else
    set<string> dict;
#endif

    // Le Dictionnaire est en UTF-8 mais puisque l'on garde uniquement les
    // caractères a-z et apostrophe (') on peut le traiter comme un fichier
    // ASCII sans aucun problème (ces 27 caractères sont codés de la même manière
    // en UTF-8 et en ASCII).
    loadDictionnary("data/dictionary.txt", dict);

    loadText(
            "data/input_wikipedia.txt",
            [& dict] (const string & str) {
                /* traitement du mot (test s'il est dans le dictionnaire */
                if(!dict.count(str))
                {
                    corrError(str, dict);
                }
            }
            );

    //cout << "dict size : " << dict.size() << endl;


	return EXIT_SUCCESS;
}
