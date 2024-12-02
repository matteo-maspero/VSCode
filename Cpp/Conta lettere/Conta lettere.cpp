#include <iostream>
#include <string>
using namespace std;

void conta_vocali_e_consonanti(string str, int* vocali, int* consonanti);

int main() {
	string str;

	cout << "\nInserire una stringa: (massimo 100 caratteri)";
	do
		getline(cin, str);
	while(str.length() > 100);
	
	int vocali, consonanti;
	conta_vocali_e_consonanti(str, &vocali, &consonanti);

	cout << "\nVocali: " << vocali << "\nConsonanti: " << consonanti << endl;

	return 0;
}

void conta_vocali_e_consonanti(string str, int* vocali, int* consonanti) {
	char current;
	*vocali = 0;
	*consonanti = 0;

	for(int i = 0; i < str.length(); i ++) {
		current = tolower(str[i]);

		if(current < 'a' || current > 'z')
			continue;

		if(current == 'a' || current == 'e' || current == 'i' || current == 'o' || current == 'u')
			(*vocali) ++;
		else
			(*consonanti) ++;
	}
}