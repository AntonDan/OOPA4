#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <fstream>
#include "DS.h"
#include "Users.h"

using namespace std;

#pragma region Functions
void PrintSubForums(Forum *);

void PrintSystem(System * root) {
	oList<Forum> * forums;
	forums = root->GetForums();
	for (int i = 0; i < forums->GetLength(); ++i ) {
		PrintSubForums((*forums)[i]);
		cout << (*forums)[i]->GetTitle() << endl;
	}
}

void PrintSubForums(Forum * forum) {
	oList<Forum> * forums;
	forums = forum->GetForums();
	for (int i = 0; i < forums->GetLength(); ++i) {
		PrintSubForums((*forums)[i]);
		cout << (*forums)[i]->GetTitle() << endl;
	}
}
#pragma endregion

#pragma region main

int main(void) {

#pragma region creator
	System * sys = new System();

	ForumNavigator nav(sys);
	Forum * cForum = NULL;

	ifstream infile("C:/Users/Antonis/Desktop/file.txt");
	string line , name;

	int pamount = -1, camount = 0;
	int pos;

	cin >> line;
	pos = line.find(char(32), 0);
	name = line.substr(pos + 1);
	line = line.substr(0, pos);

	cout << pos << "!!" << endl;

	while (getline(infile,line)) {
		camount = count(line.begin(), line.end(), '.');
		if (camount > pamount) {
			nav.VisitForum(cForum);
		} else if (camount < pamount) {
			for (int i = 0; i < pamount - camount; ++i) {
				nav.Back();
			}
		}
		cForum = nav.CreateForum(line);
		pamount = camount;	
	}

	PrintSystem(sys);
	
	cin.clear();
	cin.sync();
	cin.get();
	return 0;
#pragma endregion

#pragma region navigator
	System mySystem;

	ForumNavigator navigator(&mySystem);
	Forum * forum = NULL;
	Thread * thread = NULL;
	int a, b;
	string s1, s2, s3;

	while (true) {
		cout <<
			"Forum Navigator and Actions Guide \n" <<
			"> Visit forum    | Syntax: 1 i     \n" <<
			"> Visit thread   | Syntax: 2 i     \n" <<
			"> Back           | Syntax: 3       \n" <<
			"> Print Current  | Syntax: 4       \n" <<
			"> Print Contents | Syntax: 5       \n" <<
			"> Print Content  | Syntax: 6 i     \n" <<
			"> Create Forum   | Syntax: 7 t     \n" <<
			"> Create Thread  | Syntax: 8 t u c \n" <<
			"> Create Post    | Syntax: 9 u c   \n" <<
			"> Delete Forum   | Syntax: 10 i    \n" <<
			"> Delete Thread  | Syntax: 11 i    \n" <<
			"> Delete Post    | Syntax: 12 i    \n" <<
			"> Exit           | Syntax: 0       \n" << 
			"Info: i = index , t = title , u = username , c = content \n" << endl;
		cout << "\n>";
		cin >> a;

		cin.clear();
		cin.sync();

		switch (a) {
		case 1:
			cout << "Enter index number: " << endl;
			cin >> b;
			navigator.VisitForum(b);
			break;
		case 2:
			cout << "Enter index number: " << endl;
			cin >> b;
			navigator.VisitThread(b);
			break;
		case 3:
			navigator.Back();
			break;
		case 4:
			navigator.PrintCurrent();
			break;
		case 5:
			navigator.PrintContents();
			break;
		case 6:
			cout << "Enter index number: " << endl;
			cin >> b;
			navigator.PrintContent(b);
			break;
		case 7:
			cout << "Enter forum title" << endl;
			getline(cin, s1);
			navigator.CreateForum(s1);
			break;
		case 8:
			cout << "Enter threads title , username and content of first post" << endl;
			getline(cin, s1); getline(cin, s2);	getline(cin, s3);
			navigator.CreateThread(s1, s2, s3);
			break;
		case 9: 
			cout << "Enter writer's username and content" << endl;
			getline(cin, s1);
			getline(cin, s2);
			navigator.CreatePost(s1, s2);
			break;
		case 10:
			cout << "Enter index number: " << endl;
			cin >> b;
			navigator.DeleteForum(b);
			break;
		case 11:
			cout << "Enter index number: " << endl;
			cin >> b;
			navigator.DeleteThread(b);
			break;
		case 12:
			cout << "Enter index number: " << endl;
			cin >> b;
			navigator.DeletePost(b);
			break;
		case 0:
			break;
		default:
			break;
		}
		if (a == 0) break;
		cout << "\n" << endl;
	}
	cout << "Exitting" << endl;

#pragma endregion

	cin.get();
	return 0;
}

#pragma endregion