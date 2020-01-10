
#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

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

void loadDictionnary(const string & filename, set<string> & dict) {
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

int main(int argc, const char * argv[]) {
    set<string> dict;

    // Le Dictionnaire est en UTF-8 mais puisque l'on garde uniquement les
    // caractères a-z et apostrophe (') on peut le traiter comme un fichier
    // ASCII sans aucun problème (ces 27 caractères sont codés de la même manière
    // en UTF-8 et en ASCII).
    loadDictionnary("data/dictionary.txt", dict);

    loadText(
            "data/input_sh.txt",
            [] (string str) { /* traitement du mot (test s'il est dans le dictionnaire */ }
            );

    cout << "dict size : " << dict.size() << endl;
	return EXIT_SUCCESS;
}
