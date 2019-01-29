#pragma warning (disable : 4996)

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <vector> 
#include <fstream>
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

	ifstream inFile;
	inFile.open("test.txt");
	string userInput, token;

	while (getline(inFile, userInput)){


		cout << "> ";
	
		

		//Retrieving the input from user and parsing it
		vector <string> parsedInput;
		
		stringstream check1(userInput);

		while (getline(check1, token,' '))
		{
			parsedInput.push_back(token);
			//cout << token << endl;
		}
		
		//tokenizing userinput
		
		//ANALYZING THE INPUT TO DETERINE WHICH COMMAND IT IS
		//parsedInput[0] is the COMMAND

		//defining a book 
		if (parsedInput[0] == "B") {
			book tempBook;

			try {
				if (parsedInput.size() < 3)
					throw invalid_argument("Book : Not correct input size.");
				if (parsedInput[1][1] == '-')
					throw invalid_argument("ISBN below 0");
				tempBook.isbn = parsedInput[1];
				for (int lcv = 2; lcv < parsedInput.size(); lcv++)
				{
				tempBook.title += parsedInput[lcv];

				}
			}
			catch (invalid_argument e) {
				cout << e.what() << endl;
			}
			bookList.push_back(tempBook);
		}
		else if (parsedInput[0] == "D")
		{
			bool found = false;
			try {
				if (parsedInput.size() < 4)
					throw invalid_argument(" Book characterstic : Not correct input size.");
				for (int lcv = 0; lcv < bookList.size(); lcv++) {
					if (parsedInput[1] == bookList[lcv].isbn)
					{
						found = true;
						if (parsedInput[2] == "A")
						{
							for (int lcv2 = 3; lcv2 < parsedInput.size(); lcv2++)
							{
								bookList[lcv].author += parsedInput[lcv2];
							}

						}
						else if (parsedInput[2] == "E")
						{
							if (stoi(parsedInput[3]) < 0)
								throw invalid_argument("Invalid edition");

							bookList[lcv].edition = parsedInput[3];
						}
						else if (parsedInput[2] == "D")
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
									courseList[lcv2].courseSections.push_back(tempSection);


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
										courseList[lcv2].courseSections.push_back(tempSection);

									}
								}
							}

						}

					}
				}
				if (!placementFound)
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
								cout << endl;
								cout << "-------------------------------------------------" << endl;
								cout << courseList[lcv].courseSections[lcv2].books[lcv3].title << endl;
								cout << "-------------------------------------------------" << endl;
								cout << endl;
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
		bool found = false;
		try {
			if (parsedInput.size() != 4)
				throw invalid_argument("Not correct input size.");
			for (int lcv = 0; lcv < courseList.size(); lcv++) {
				if (courseList[lcv].deptID == parsedInput[1] && courseList[lcv].courseNum == parsedInput[2])
				{
					for (int lcv2 = 0; lcv2 < courseList[lcv].courseSections.size(); lcv2++)
					{
						if (parsedInput[3] == courseList[lcv].courseSections[lcv2].sectionNum)
						{
							for (int lcv3 = 0; lcv3 < courseList[lcv].courseSections[lcv2].books.size(); lcv3++)
							{
								found = true;
								cout << endl;
								cout << "-------------------------------------------------" << endl;
								cout << courseList[lcv].courseSections[lcv2].books[lcv3].title << endl;
								cout << "-------------------------------------------------" << endl;
								cout << endl;
							}
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
		else if (parsedInput[0] == "GB")
		{
			bool found = false;
			try {
				if (parsedInput.size() != 2)
					throw invalid_argument("Not correct input size.");
				for (int lcv = 0; lcv < bookList.size(); lcv++)
				{
					if (parsedInput[1] == bookList[lcv].isbn)
					{
						found = true;
						cout << "Title: " << bookList[lcv].title << endl;
					}
				}
				if (!found)
					throw invalid_argument("Book/Course not found");
			}
			catch (invalid_argument e) {
				cout << e.what() << endl;
			}
		}
		else if (parsedInput[0] == "PB")
		{
		try {
			for (int lcv = 0; lcv < bookList.size(); lcv++)
			{
				cout << "Title: " << bookList[lcv].title << endl;
			}
		}
		catch (invalid_argument e) {
			cout << e.what() << endl;
		}

		}
		else if (parsedInput[0] == "PC")
		{

		try {
			for (int lcv = 0; lcv < courseList.size(); lcv++)
			{
				cout << "Title: " << courseList[lcv].name << endl;
			}
		}
		catch (invalid_argument e) {
			cout << e.what() << endl;
		}

		}
		else if (parsedInput[0] == "PY")
		{
			try {
				for (int lcv = 0; lcv < bookList.size(); lcv++)
				{
					if (!bookList[lcv].dateOfPublication.empty()) {
						int month = stoi(bookList[lcv].dateOfPublication.substr(0, 2));
						int year = stoi(bookList[lcv].dateOfPublication.substr(3, 7));
						int req_month = stoi(parsedInput[1].substr(0, 2));
						int req_year = stoi(parsedInput[1].substr(3, 7));
						if (year > req_year)
						{
							cout << " Title " << bookList[lcv].title << endl;
						}
						else if (year == req_year)
						{
							if (month >= req_month)
							{
								cout << " Title " << bookList[lcv].title << endl;

							}
						}
					}
				}
			}
			catch (invalid_argument e) {
				cout << e.what() << endl;
			}
		}
		else if (parsedInput[0] == "PD")
		{
			bool found = false;
			try {
				if (parsedInput.size() != 2)
					throw invalid_argument("Not correct input size.");
				for (int lcv = 0; lcv < courseList.size(); lcv++) {
					if (courseList[lcv].deptID == parsedInput[1])
					{
						found = true;
						for (int lcv2 = 0; lcv2 < courseList[lcv].courseSections.size(); lcv2++)
						{
							for (int lcv3 = 0; lcv3 < courseList[lcv].courseSections[lcv2].books.size(); lcv3++)
							{
								cout << endl;
								cout << courseList[lcv].deptID<<" " << courseList[lcv].courseSections[lcv2].sectionNum << endl;
								
								cout << endl;
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
		else if (parsedInput[0] == "PM")
		{
		}
		else {

		}
		
	}

	system("pause");
	
}
