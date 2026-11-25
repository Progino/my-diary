#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <limits>
using namespace std;

struct Day {
	int day = 0;
	int month = 0;
	int year = 0;
	string text = "";
	int hoursSlept = 0;
	bool dreamt = false;
	string dream = "";
	//other for other functions
};

vector <Day> days(366);

int inputControl(int min, int max) {
	int input;
	while (true) {
		cin >> input;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Insert a valid action" << endl;
			continue;
		}
		else if(input < min || input > max) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Insert a valid action" << endl;
			continue;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return input;
		}
	}
}

int currentDay() {
	time_t t = time(nullptr);
	tm currentTime;
	localtime_s(&currentTime,&t);

	int position = currentTime.tm_yday;

	days[position].day = currentTime.tm_mday;
	days[position].month = currentTime.tm_mon + 1;
	days[position].year = currentTime.tm_year + 1900;

	return position;
}

void diary() {
	
}
//To do
void sleep(int position) {
	if (days[position].hoursSlept != 0) {
		cout << "You already registered your sleep for today" << endl;
		cout << "Do you want to modify it?(1.yes 2.no)" << endl;
		int update = inputControl(1, 2);
		if (update == 1) {
			cout << "How many hours did you sleep?" << endl;
			cout << "previously " << days[position].hoursSlept << " hours" << endl;
			days[position].hoursSlept = inputControl(0,24);
			cout << "Did you dream?(1.yes 2.no)" << endl;
			cout << "previously ";
			if (days[position].dreamt) {
				cout << "yes" << endl;
			}
			else {
				cout << "no";
			}
			int dreamt = inputControl(1, 2);
			if (dreamt == 1) {
				cout << "Briefly describe your dream:" << endl;
				if (days[position].dreamt) {
					cout << "previously: " << endl;
					cout << days[position].dream << endl;
					days[position].dreamt = true;
					cout << "do you want to change it?(1.yes 2.no)" << endl;
					int newDream = inputControl(1, 2);
					if (newDream == 1) {
						getline(cin, days[position].dream);
					}
				}
				else if(days[position].dreamt == false) {
					days[position].dreamt = true;
					getline(cin, days[position].dream);
				}
			}
			else if (dreamt == 2) {
				days[position].dreamt = false;
				days[position].dream = "";
			}
			cout << "Sleep tracker updated" << endl;
			cin.get();
			system("cls");
			return;
		}
		else if (update == 2) {
			system("cls");
			return;
		}
	}
	cout << "How many hours did you sleep?" << endl;
	int hoursSlept = inputControl(0, 24);
	days[position].hoursSlept = hoursSlept;
	cout << "Did you dream?(1.yes 2.no)" << endl;
	int dreamt = inputControl(1, 2);
	if (dreamt == 1) {
		days[position].dreamt = true;
		cout << "Briefly describe your dream:" << endl;
		getline(cin , days[position].dream);
	}
	cout << "Sleep tracker updated" << endl;
	cin.get();
	system("cls");
	return;
}

int menu() {
	int choice;
	cout << "1. Diary" << endl;
	cout << "2. Sleep" << endl;
	cout << "3. mood" << endl;
	cout << "4. objective" << endl;
	cout << "5. recap" << endl;
	cout << "6. exit" << endl;
	choice = inputControl(1, 6);
	return choice;
}

int main() {
	int position = currentDay();

	while (true) {
		int choice = menu();
		switch (choice) {
		case 1: {
			//diary
			break;
		}
		case 2: {
			sleep(position);
			break;
		}
		case 3: {
			//mood
			break;
		}
		case 4: {
			//objective
			break;
		}
		case 5: {
			//recap
			break;
		}
		case 6: {
			return 0;
		}
		}
	}
}