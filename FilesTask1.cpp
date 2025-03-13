/*
Задача 1.
Напишете програма, която получава от командния ред два параметъра - първият е команда - едно от: -c, -C , -w, -l, -L, -s или -h. Вторият е име на файл.
Програмата трябва да анализира подадения файл в текстов тежим според командата и да изведе информация съответно за:
-c -> Брой на символите във файла (всички символи).
-C -> Брой на не-празните символи във файла - символи с код по-голям от 32 и по-малък от 127.
-w -> Брой на думите във файла. Думите се разделят с произволен брой празни символи.
-l -> Брой на редовете във файла.
-L -> Брой на не-празните редове във файла. Те трябва да съдържат поне един символ (без значение какъв).
-s -> Извежда статистика за файла. Тя включва всяка от горните метрики, но също и колко процента от общия брой символи е срещането на всеки непразен символ.
-h -> Извежда помощно съобщение на екрана (help message). Не използва втория параметър.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void Menu();
int CountAllSymbols(ifstream& file);
int CountNonEmptySymbols(ifstream& file);
int CountWords(ifstream& file);
int CountAllLines(ifstream& file);
int CountNonEmptyLines(ifstream& file);
void Statistics(ifstream& file);

int main()
{
	string option;
	string fileName;

	Menu();
	cin >> option;

	if (option == "-h") {
		cout << "\nThis program counts the number of symbols, number of non-empty symbols, words, lines and non-empty lines in a file\n";
		return 1;
	}

	cin.ignore();
	cout << "Enter the file name that you want to work with: ";
	getline(cin, fileName);

	ifstream readingFile(fileName);

	if (!readingFile) {
		cerr << "\nNo such file exist!\n";
		return 1;
	}

	if (option == "-c") {
		size_t numSymbols = CountAllSymbols(readingFile);
		cout << "\nNumber of symbols in the file is: " << numSymbols << "\n";
	}
	else if (option == "-C") {
		cout << "\nNumber of non-empty symbols in the file is: " << CountNonEmptySymbols(readingFile) << "\n";
	}
	else if (option == "-w") {
		cout << "\nNumber of words in the file is: " << CountWords(readingFile);
	}
	else if (option == "-l") {
		cout << "\nNumber of lines in the file is: " << CountAllLines(readingFile);
	}
	else if (option == "-L") {
		cout << "\nNumber of non-empty lines in the file is: " << CountNonEmptyLines(readingFile);
	}
	else if (option == "-s") {
		Statistics(readingFile);
	}
	else {
		cout << "\nInvalid option!\n";
	}

	readingFile.close();

}

void Menu() {
	cout << "Choose an option\n";
	cout << "-------------------\n";
	cout << "-c   - This will print the number of all symbols in the file\n";
	cout << "-C   - This will print the number of non-emply symbols in the file\n";
	cout << "-w   - This will print the number of all words in the file\n";
	cout << "-l   - This will print the number of all lines in the file\n";
	cout << "-L   - This will print the number of all non-empty lines in the file\n";
	cout << "-s   - All of the above\n";
	cout << "-h   - Help\n\n";

}

//Checks all symbols in the file
int CountAllSymbols(ifstream& file) {
	int symbols = 0;
	char ch;

		while (file.get(ch)){
			symbols++;
		}



	return symbols;
}

//Checks only non-empty symbols
int CountNonEmptySymbols(ifstream& file) {
	int nonEmptySymbols = 0;
	int ascii = 0;
	char ch;


	while (file.get(ch)) {
		if (ch > 32 && ch < 127)
			nonEmptySymbols++;
	}

	return nonEmptySymbols;
}

//Checks number of words in the file
int CountWords(ifstream& file) {
	int words = 0;
	char ch;
	bool isWord = true;

	while (file.get(ch)) {
		if (((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) && isWord) {
			words++;
			isWord = false;
		}
		else if (ch == ' ' || ch == '!' || ch == ',' || ch == '\n' || ch == '.' || ch == '?') {
			isWord = true;
		}

	}

	return words;
}

//Check number of all lines in the file
int CountAllLines(ifstream& file) {
	int lines = 0;
	string text;

	while (getline(file, text)) {
		lines++;
	}

	return lines;
}

//Checks the non-empty lines in the file
int CountNonEmptyLines(ifstream& file) {
	int lines = 0;
	string text;

	while (getline(file, text)) {
		if (text.empty()) {
			continue;
		}
		lines++;
	}

	return lines;
}

//Prints all of the above mentioned info
void Statistics(ifstream& file) {
	file.clear();
	file.seekg(0);
	int allSymbols = CountAllSymbols(file);

	file.clear();
	file.seekg(0);
	int nonEmptySymbols = CountNonEmptySymbols(file);
	double percentage = ((double)nonEmptySymbols / allSymbols) * 100;

	file.clear();
	file.seekg(0);
	cout << "All symbols in the file: " << CountAllSymbols(file) << "\n";

	file.clear();
	file.seekg(0);
	cout << "All non-empty symbols in the file: " << CountNonEmptySymbols(file) << '\n';

	file.clear();
	file.seekg(0);
	cout << "All words in the file: " << CountWords(file) << "\n";

	file.clear();
	file.seekg(0);
	cout << "All lines in the file: " << CountAllLines(file) << "\n";

	file.clear();
	file.seekg(0);
	cout << "All non-empty lines in the file: " << CountNonEmptyLines(file) << "\n";
	cout << fixed << setprecision(2);
	cout << "Part of non-empty symbols in the file(in percentages): " << percentage << "%\n";
}



