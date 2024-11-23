#include <iostream>
#include <string>
using namespace std;

int getNumOfVowels(string s);
int getNumOfConsonants(string s);

int main() {
	string str;

	cout << "\nInserisci una stringa: ";
	getline(cin, str);

	for(int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);

	cout << "\nIl numero di vocali presenti nella stringa e': " << getNumOfVowels(str) << "\nQuello di consonanti e': " << getNumOfConsonants(str);

	return 0;
}

int getNumOfVowels(string str) {
	int vowels = 0;

	for(int i = 0; i < str.length(); i++)
		if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
			vowels ++;

	return vowels;
}

int getNumOfConsonants(string str) {
	int consonants = 0;

	for(int i = 0; i < str.length(); i++)
		if(str[i] != 'a' && str[i] != 'e' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u' && str[i] != ' ')
			consonants ++;

	return consonants;
}