#pragma warning (disable : 4996)
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector> 

using namespace std;

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
	string version;
	string forcedBook;

};

class sections {
public:
	string deptID;
	string courseNum;
	vector<book> books;
	string sectionNum;
};


class course {
public:
	string courseNum;
	string deptID;
	string name;
	vector<sections> courseSections;


};

vector<book> bookList;
vector<course> courseList;

int main(int argc, char * argv[]) {
	while (true) {
	

		cout << "> ";
		
		//Retrieving the input from user and parsing it
		vector <string> parsedInput;
		string userInput, token;
		getline(cin, userInput);

		//tokenizing userinput
		int end = 0;
		int start = 0;
		userInput = userInput.strip(
		while(end < userInput.size())
		{
			if(userInput[end] == ' ')
			{
				if (userInput.substr(start, end) != "") {
					parsedInput.push_back(userInput.substr(start, end));
				}
				start = end+1;
			}
			end = end + 1;
		}
		if (start != end - 1) {
			parsedInput.push_back(userInput.substr(start, end));
		}
		for (int lcv = 0; lcv < parsedInput.size(); lcv++)
		{
			cout << parsedInput[lcv] << endl;

		}
		//ANALYZING THE INPUT TO DETERINE WHICH COMMAND IT IS
		//parsedInput[0] is the COMMAND

		//defining a book 
		if (parsedInput[0] == "B"){
			book tempBook;
			
			try {
				if (parsedInput.size() != 3)
					throw invalid_argument("Not correct input size.");
				if (parsedInput[1][1] == '-')
					throw invalid_argument("ISBN below 0");
				tempBook.isbn = parsedInput[1];
				tempBook.title = parsedInput[2];
			}	
			catch(invalid_argument e){
				cout << e.what()<< endl;
			}
			bookList.push_back(tempBook);
			cout << bookList.size() << " ADDED TO BOOKLSIT" << endl;
		}
		else if (parsedInput[0] == "D")
		{
			bool found = false;
			try {
				if (parsedInput.size() != 4)
					throw invalid_argument("Not correct input size.");
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
				cout << e.what() << endl;
			}
		}
		else if (parsedInput[0] == "M")
		{
			bool found = false;
			try {
				if (parsedInput.size() != 4)
					throw invalid_argument("Not correct input size.");
				for (int lcv = 0; lcv < bookList.size(); lcv++) {
					if (parsedInput[1] == bookList[lcv].isbn)
					{
						found = true;
						bookList[lcv].cost = parsedInput[2];
						if (parsedInput[3] == "N" || parsedInput[3] == "U" 
							|| parsedInput[3] == "R" || parsedInput[3] == "E")
						{
							bookList[lcv].version = parsedInput[3];
						}
						else {
							throw invalid_argument("Not a proper version");
						}
					}
				}
				if (!found)
					throw invalid_argument("Book not found");
			}
			catch (invalid_argument e) {
				cout << e.what() << endl;
			}

		}
		else if (parsedInput[0] == "C")
		{
			try {
				//cout << parsedInput.size() << endl;
				if (parsedInput.size() < 4)
					throw invalid_argument("Not correct input size.");
				course tempCourse;
				tempCourse.deptID = parsedInput[1];
				tempCourse.courseNum = parsedInput[2];
				for (int lcv = 3; lcv < parsedInput.size(); lcv++) {
					tempCourse.name += parsedInput[lcv];
					tempCourse.name += " ";
				}
				courseList.push_back(tempCourse);
			}
			catch (invalid_argument e) {
				cout << e.what() << endl;
			}
			
		}
		else if (parsedInput[0] == "A")
		{
			bool placementFound = false;
			bool sectionNotFound = true;
			try {
				if (parsedInput.size() != 6)
					throw invalid_argument("Not correct input size.");

				for (int lcv = 0; lcv < bookList.size(); lcv++) {
					if (parsedInput[1] == bookList[lcv].isbn)
					{
						for (int lcv2 = 0; lcv2 < courseList.size(); lcv2++)
						{
							//cout << parsedInput[2]<<endl;
							//cout<<parsedInput[3] << endl;
							//cout << courseList[lcv2].deptID << endl;
							//cout << courseList[lcv2].courseNum << endl;

							if (parsedInput[2] == courseList[lcv2].deptID && parsedInput[3] == courseList[lcv2].courseNum) {
								placementFound = true;
								if (courseList[lcv2].courseSections.size() == 0) {
									sectionNotFound = false;
									sections tempSection;
									tempSection.sectionNum = parsedInput[4];
									tempSection.books.push_back(bookList[lcv]);
									tempSection.books[tempSection.books.size() - 1].forcedBook = parsedInput[5];

								}
								else {
									for (int lcv3 = 0; lcv3 < courseList[lcv2].courseSections.size(); lcv3++) {
										if (courseList[lcv2].courseSections[lcv3].sectionNum == parsedInput[4])
										{
											sectionNotFound = false;
											courseList[lcv2].courseSections[lcv3].books.push_back(bookList[lcv]);
											courseList[lcv2].courseSections[lcv3].books[courseList[lcv2].courseSections[lcv3].books.size() - 1].forcedBook = parsedInput[5];
										}
									}
									if (sectionNotFound) {
										sections tempSection;
										tempSection.sectionNum = parsedInput[4];
										tempSection.books.push_back(bookList[lcv]);
										tempSection.books[tempSection.books.size() - 1].forcedBook = parsedInput[5];
									}
								}
							}

						}
					
					}
				}
				if(!placementFound)
					throw invalid_argument("Book/Course not found");
			}
			catch (invalid_argument e) {
				cout << e.what() << endl;
			}
		}
		else if (parsedInput[0] == "GC")
		{
			bool found = false;
			try {
				if (parsedInput.size() != 3)
					throw invalid_argument("Not correct input size.");
				for (int lcv = 0; lcv < courseList.size(); lcv++) {
					if (courseList[lcv].deptID == parsedInput[1] && courseList[lcv].courseNum == parsedInput[2])
					{
						found = true;
						for (int lcv2 = 0; lcv2 < courseList[lcv].courseSections.size(); lcv2++)
						{
							for (int lcv3 = 0; lcv3 < courseList[lcv].courseSections[lcv2].books.size(); lcv3++)
							{
								cout << "-------------------------------------------------" << endl;
								cout << courseList[lcv].courseSections[lcv2].books[lcv3].title << endl;
								cout << "-------------------------------------------------" << endl;
							}
						}
					}
				}
				if (!found)
					throw invalid_argument("Book/Course not found");
			}
			catch (invalid_argument e) {
				cout << e.what() << endl;
			}
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
