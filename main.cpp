#pragma warning (disable : 4996)
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector> 

using namespace std;

class bookCourse {
public:
	string course;
	string section;
	string deptID;

};
class book {
public:
	string isbn;
	string title;
	string course;
	string characteristic;
	string cost;
	string dateOfPublication;
	string author;
	string edition;
};
int main(int argc, char * argv[]) {
	while (true) {
		vector<book> bookList;
		cout << "> ";

		//Retrieving the input from user and parsing it
		vector <string> parsedInput;
		string userInput, token;
		getline(cin, userInput);

		//tokenizing userinput
		int end = 0;
		int start = 0;
		while (end < userInput.size())
		{
			if (userInput[end] == ' ')
			{
				if (userInput.substr(start, end) != "") {
					parsedInput.push_back(userInput.substr(start, end));
				}
				start = end;
			}
			end = end + 1;
		}
		if (start != end - 1) {
			parsedInput.push_back(userInput.substr(start, end));
		}

		//ANALYZING THE INPUT TO DETERINE WHICH COMMAND IT IS
		//parsedInput[0] is the COMMAND

		//defining a book 
		if (parsedInput[0] == "B") {
			book tempBook;

			try {
				if (parsedInput.size() != 3)
					throw invalid_argument("Not proper inputss");
				if (stoi(parsedInput[1]) < 0)
					throw invalid_argument("ISBN below 0");
				tempBook.isbn = parsedInput[1];
				tempBook.title = parsedInput[2];
			}
			catch (invalid_argument e) {
				cout << "Invalid input! Please try again." << endl;
			}
			bookList.push_back(tempBook);
		}
		else if (parsedInput[0] == "D")
		{
			bool found = false;
			try {
				if (parsedInput.size() != 4)
					throw invalid_argument("Not proper inputss");
				for (int lcv = 0; lcv < bookList.size(); lcv++) {
					if (parsedInput[1] == bookList[lcv].isbn)
					{
						found = true;
						if (parsedInput[2] == "A")
						{
							bookList[lcv].author = parsedInput[3];
						}
						else if (parsedInput[2] == "E")
						{
							if (stoi(parsedInput[3]) < 0)
								throw invalid_argument("Invalid edition");

							bookList[lcv].edition = parsedInput[3];
						}
						else if (parsedInput[3] == "D")
						{
							bookList[lcv].dateOfPublication = parsedInput[3];
						}
						else {
							throw invalid_argument("Not proper arguments");
						}
					}
				}
				if (!found)
					throw invalid_argument("Book not found");
			}
			catch (invalid_argument e) {
				cout << "Invalid input! Please try again." << endl;
			}
		}
		else if (parsedInput[0] == "M")
		{
		}
		else if (parsedInput[0] == "C")
		{
		}
		else if (parsedInput[0] == "A")
		{
		}
		else if (parsedInput[0] == "GC")
		{
		}
		else if (parsedInput[0] == "GS")
		{
		}
		else if (parsedInput[0] == "GB")
		{
		}
		else if (parsedInput[0] == "PB")
		{
		}
		else if (parsedInput[0] == "PC")
		{
		}
		else if (parsedInput[0] == "PY")
		{
		}
		else if (parsedInput[0] == "PD")
		{
		}
		else if (parsedInput[0] == "PM")
		{
		}
		else {

		}

	}
	system("pause");
}
