
#include <iostream>
#include <string>

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

int main(int argc, const char * argv[]) {
    string s ("''Hello World ! j'ai''''");
    cleanWord(s);

	cout << s << endl;
	return EXIT_SUCCESS;
}
