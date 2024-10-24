#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class LiterallyJustToaster
{
public:
	virtual const string toStr() = 0;
	friend ostream& operator<< (ostream& os, LiterallyJustToaster& bread)
	{
		os << bread.toStr();
		return os;
	}
};

class Snap : public LiterallyJustToaster
{
public:
	string studentID;
	string studentName;
	Snap(string id = 0, string name = "", string address = "", string phone = 0)
	{
		studentID = id;
		studentName = name;
		studentAddress = address;
		studentPhone = phone;
	}
	const string toStr()
	{
		return "snap(" + studentID + "," + studentName + "," + studentAddress + "," + studentPhone + ")";
	}
	const string betterToStr()
	{
		return studentName + ", " + studentID + ", " + studentAddress + ", " + studentPhone;
	}
private:
	string studentAddress;
	string studentPhone;
};

class Csg : public LiterallyJustToaster
{
public:
	string courseName;
	string studentID;
	string studentGrade;
	Csg(string course = "", string id = 0, string grade = "")
	{
		courseName = course;
		studentID = id;
		studentGrade = grade;
	}
	const string toStr()
	{
		return "csg(" + courseName + "," + studentID + "," + studentGrade + ")";
	}
};

class Cdh : public LiterallyJustToaster
{
public:
	string courseName;
	string courseDay;
	string courseTime;
	Cdh(string course = "", string day = "", string time = "")
	{
		courseName = course;
		courseDay = day;
		courseTime = time;
	}
	const string toStr()
	{
		return "cdh(" + courseName + "," + courseDay + "," + courseTime + ")";
	}
};

class Cr : public LiterallyJustToaster
{
public:
	string courseName;
	string courseRoom;
	Cr(string course = "", string room = "")
	{
		courseName = course;
		courseRoom = room;
	}
	const string toStr()
	{
		return "cr(" + courseName + "," + courseRoom + ")";
	}
};

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		cerr << "Enter arguments for input and output files";
		return 1;
	}
	cout << "Input file: " << argv[1] << endl;
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile)
	{
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream outFile;
	outFile.open(argv[2]);
	if (!outFile)
	{
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	vector<Snap> snap;
	vector<Csg> csg;
	vector<Cdh> cdh;
	vector<Cr> cr;
	outFile << "Input Strings:" << endl;;
	for (string currentLine; getline(inFile, currentLine);)
	{
		string originalLine = currentLine;
		if ("snap(" == currentLine.substr(0, 5))
		{
			string snapID = currentLine.substr(5, currentLine.find(',') - 5);
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string snapName = currentLine.substr(0, currentLine.find(','));
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string snapAddress = currentLine.substr(0, currentLine.find(','));
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string snapPhone = currentLine.substr(0, currentLine.find(')'));
			snap.push_back(Snap(snapID, snapName, snapAddress, snapPhone));
		}
		else if ("csg(" == currentLine.substr(0, 4))
		{
			string csgCourse = currentLine.substr(4, currentLine.find(',') - 4);
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string csgID = currentLine.substr(0, currentLine.find(','));
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string csgGrade = currentLine.substr(0, currentLine.find(')'));
			csg.push_back(Csg(csgCourse, csgID, csgGrade));
		}
		else if ("cdh(" == currentLine.substr(0, 4))
		{
			string cdhCourse = currentLine.substr(4, currentLine.find(',') - 4);
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string cdhDay = currentLine.substr(0, currentLine.find(','));
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string cdhTime = currentLine.substr(0, currentLine.find(')'));
			cdh.push_back(Cdh(cdhCourse, cdhDay, cdhTime));
		}
		else if ("cr(" == currentLine.substr(0, 3))
		{
			string crCourse = currentLine.substr(3, currentLine.find(',') - 3);
			currentLine = currentLine.substr(currentLine.find(',') + 1);
			string crRoom = currentLine.substr(0, currentLine.find(')'));
			cr.push_back(Cr(crCourse, crRoom));
		}
		else
		{
			outFile << "**Error: ";
		}
		outFile << originalLine << endl;
	};

	outFile << endl << "Vectors:" << endl;
	for (int i = 0; i < snap.size(); i++)
	{
		outFile << snap.at(i) << endl;
	}
	for (int i = 0; i < csg.size(); i++)
	{
		outFile << csg.at(i) << endl;
	}
	for (int i = 0; i < cdh.size(); i++)
	{
		outFile << cdh.at(i) << endl;
	}
	for (int i = 0; i < cr.size(); i++)
	{
		outFile << cr.at(i) << endl;
	}

	outFile << endl << "Course Grades:" << endl;
	for (int i = 0; i < csg.size(); i++)
	{
		outFile << csg.at(i).courseName << ", ";
		for (int j = 0; j < snap.size(); j++)
		{
			if (csg.at(i).studentID == snap.at(j).studentID)
			{
				outFile << snap.at(j).studentName << ", ";
			}
		}
		outFile << csg.at(i).studentGrade << endl;
	}

	outFile << endl << "Student Schedules:" << endl;
	for (int i = 0; i < snap.size(); i++)
	{
		outFile << snap.at(i).betterToStr() << endl;
		for (int j = 0; j < csg.size(); j++)
		{
			string classDays = "";
			string classTime = "";
			if (snap.at(i).studentID == csg.at(j).studentID)
			{
				for (int k = 0; k < cdh.size(); k++)
				{
					if (cdh.at(k).courseName == csg.at(j).courseName)
					{
						classDays.append(cdh.at(k).courseDay);
						classTime = cdh.at(k).courseTime;
					}
				}
				for (int k = 0; k < cr.size(); k++)
				{
					if (cr.at(k).courseName == csg.at(j).courseName)
					{
						outFile << "  " + cr.at(k).courseName + " " + classDays + " " + classTime + ", " + cr.at(k).courseRoom << endl;
					}
				}
			}
		}
		cout << endl;
	}
}