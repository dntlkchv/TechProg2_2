#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <sstream>

using namespace std;

string* priority;
string* other;
int prioritySize = 0;
int otherSize = 0;

void addPriority(string str) {
	string* newList = new string[prioritySize + 1];

	for (int i = 0; i < prioritySize; i++) {
		newList[i] = priority[i];
	}

	newList[prioritySize++] = str;

	delete[]priority;
	priority = newList;
}

void addOther(string str) {
	string* newList = new string[otherSize + 1];

	for (int i = 0; i < otherSize; i++) {
		newList[i] = other[i];
	}

	newList[otherSize++] = str;

	delete[]other;
	other = newList;
}

bool isLetter(char c) {
	return c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z';
}

int main()
{

	ifstream fin("F1.txt");

	if (!fin.is_open()) {
		cout << "Can`t open file!";
		return 0;
	}

	char c;
	int words = 0;
	int letters = 0;
	bool valid = false;

	stringstream stream;

	while (!fin.eof()) {
		c = fin.get();
		stream << c; //запись символа в строковый поток

		if (c == '.' || c == '!' || c == '?' ) {

			if (valid || words == 0 && letters == 1) {
				addPriority(stream.str());
			}
			else {
				addOther(stream.str());
			}

			stream = stringstream();

			words = 0;
			letters = 0;
			valid = false;
			continue;
		}

		if (isLetter(c)) {
			letters++;
		}
		else {
			if (words == 0 && letters == 0)  // если встретился разделитель, а букв в предложении не было до этого, игнорируем его. 
			{
				stream.seekp(-1, stream.cur); // забираем назад этот символ
				continue;
			}

			if (words == 0 && letters == 1) {
				valid = true;
			}
			words++;
			letters = 0;
		}
	}


	for (int i = 0; i < prioritySize; i++)
	{
		cout << priority[i] << endl;
	}

	for (int i = 0; i < otherSize; i++)
	{
		cout << other[i] << endl;
	}

	fin.close();

	return 0;
}

