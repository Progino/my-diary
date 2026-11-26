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
	int mood;
	//other for other functions
};

vector <Day> days(366);
//maybe vector for years that include Day vectors

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

void diary(int position) {
	
}
//To do
void sleep(int position) {
	system("cls");
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
			cout << "Sleep unchanged. Press Enter to return to menu" << endl;
			cin.get();
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

void mood(int position) {
	system("cls");
	if (days[position].mood != 0) {
		cout << "You already registered your mood for today" << endl;
		cout << "Do you want to modify it?(1.yes 2.no)" << endl;
		int update = inputControl(1, 2);
		if (update == 1) {
			cout << "What was tour mood today" << endl;
			cout << "1. euphoric" << endl;
			cout << "2. happy" << endl;
			cout << "3. good" << endl;
			cout << "4. meh" << endl;
			cout << "5. down" << endl;
			cout << "previously ";
			switch (days[position].mood) {
			case 1: 
				cout << "euphoric" << endl;
				break;
			case 2:
				cout << "happy" << endl;
				break;
			case 3:
				cout << "good" << endl;
				break;
			case 4:
				cout << "meh" << endl;
				break;
			case 5:
				cout << "down" << endl;
				break;
			}
			int mood = inputControl(1, 5);
			switch (mood) {
			case 1: {
				days[position].mood = 1;
				break;
			}
			case 2: {
				days[position].mood = 2;
				break;
			}
			case 3: {
				days[position].mood = 3;
				break;
			}
			case 4: {
				days[position].mood = 4;
				break;
			}
			case 5: {
				days[position].mood = 5;
				break;
			}
			}
			cout << "mood tracker updated" << endl;
			cin.get();
			system("cls");
			return;
		}
		else if (update == 2) {
			cout << "Mood unchanged. Press Enter to return to menu" << endl;
			cin.get();
			system("cls");
			return;
		}

	}
	cout << "What was your mood today?" << endl;
	cout << "1. euphoric" << endl;
	cout << "2. happy" << endl;
	cout << "3. good" << endl;
	cout << "4. meh" << endl;
	cout << "5. down" << endl;
	int mood = inputControl(1, 5);
	switch (mood) {
	case 1: {
		days[position].mood = 1;
		break;
	}
	case 2: {
		days[position].mood = 2;
		break;
	}
	case 3: {
		days[position].mood = 3;
		break;
	}
	case 4: {
		days[position].mood = 4;
		break;
	}
	case 5: {
		days[position].mood = 5;
		break;
	}
	}
	cout << "Mood tracker updated" << endl;
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
			mood(position);
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