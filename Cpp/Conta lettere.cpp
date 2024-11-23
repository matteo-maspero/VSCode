#include <iostream>
#include <string>
using namespace std;

int getNumOfVowels(string s);

int main() {
	string str;

	cout << "\nInserisci una stringa: ";
	getline(cin, str);

	for(int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);

	int vowels = getNumOfVowels(str);
	cout << "\nIl numero di vocali presenti nella stringa e': " << vowels << "\nQuello di consonanti e': " << str.length() - vowels;

	return 0;
}

int getNumOfVowels(string str) {
	int vowels = 0;

	for(int i = 0; i < str.length(); i++)
		if(str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
			vowels ++;

	return vowels;
}