#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

//#define PATH "D:/VSCode/Workspace/Stazioni meteorologiche.txt"
#define PATH "C:/Users/mat.maspero/VSCode/Workspace/Stazioni meteorologiche.txt"

/*
	CLASSES
*/

class City {
	private:
	string __name;
	string __province;
	string __region;
	int __maxTemp;
	int __minTemp;
	int __moisture;

	public:
	City(string name, string province, string region, int maxTemperature = 0, int minTemperature = 0, int moisture = 0) {
		__name = name;
		__province = province;
		__region = region;
		__maxTemp = maxTemperature;
		__minTemp = minTemperature;
		__moisture = moisture;
	}
	
	void calculateMinTemp(int minRand = -20, int maxRand = 10) {
		__minTemp = minRand + rand() % (maxRand - minRand);
	}

	void calculateMaxTemp(int maxRand = 40) {
		__maxTemp = __minTemp + rand() % (maxRand - __minTemp);
	}

	void calculateMoisture() {
		__moisture = rand() % 100 + 1;
	}
};

class Station {
	private:
	string __id;
	vector<City> __cities;

	public:
	Station(string id) {
		__id = id;
	}

	void loadCitiesFromTxt(string path) {
		ifstream file(path);

		if(!file.is_open()) {
			cerr << "Apertura del file fallita.\n";
			return;
		}

		string line;
		string name;
		string province;
		string region;

		while(file >> line)
			name = line.substr(0, line.find(';'));
			province = line.substr(name.length(), line.find(';'));
			region = line.substr(name.length() + province.length(), line.length());

			__cities.push_back(City(name, province, region));
		
		file.close();
	}
};

/*
	Prototypes
*/

void loadDataFromTxt(vector<City> &cities);

/*
	MAIN
*/

int main() {
	srand(time(0));

	Station station("OurStation");
	station.loadCitiesFromTxt(PATH);

	return 0;
}

void loadDataFromTxt(vector<City> &cities) {
	ifstream file(PATH);

	if(!file.is_open()) {
		cerr << "Failed to open file.\n";
		return;
	}

	string name, province, region;


	while(file >> name >> province >> region)
		cities.push_back(
			City(
				name,
				province,
				region
			)
		);
	
	file.close();
}