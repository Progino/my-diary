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
	int mood = 0;
	string sport = "";
	int sportHours = 0;
	int fatigue = 0;
	string subject = "";
	int studyHours = 0;
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

void sport(int position) {
	if (days[position].sport != "") {
		cout << "You already registered sport for today" << endl;
		cout << "Do you want to modify it?(1.yes 2.no)" << endl;
		int sport = inputControl(1, 2);
		if (sport == 1) {
			cout << "What sport did you practice today?" << endl;
			cout << "previously " << days[position].sport << endl;
			cout << "Do you want to change it?(1.yes 2.no)" << endl;
			int change = inputControl(1, 2);
			if (change == 1) {
				cout << "insert the new sport for today" << endl;
				getline(cin, days[position].sport);
			}
			cout << "For how many hours did you practice " << days[position].sport << "?" << endl;
			cout << "Previously " << days[position].sportHours << " hours" << endl;
			days[position].sportHours = inputControl(0, 24);
			cout << "And how do you feel?" << endl;
			cout << "1. Energized" << endl;
			cout << "2. Tired (good fatigue)" << endl;
			cout << "3. Exhausted" << endl;
			cout << "Previously ";
			switch (days[position].fatigue) {
			case 1:
				cout << "Energized" << endl;
				break;
			case 2:
				cout << "Tired (good fatigue)" << endl;
				break;
			case 3:
				cout << "Exhausted" << endl;
				break;
			}
			days[position].fatigue = inputControl(1, 3);
			cout << "Sport tracker updated" << endl;
			cin.get();
			system("cls");
			return;
		}
		else if (sport == 2) {
			cout << "Sport unchanged. Press Enter to return to menu" << endl;
			cin.get();
			system("cls");
			return;
		}
	}
	cout << "what sport did you practice today?" << endl;
	getline(cin, days[position].sport);
	cout << "For how many hours did you practice " << days[position].sport <<"?" << endl;
	days[position].sportHours = inputControl(0, 24);
	cout << "And how do you feel" << endl;
	cout << "1. Energized" << endl;
	cout << "2. Tired (good fatigue)" << endl;
	cout << "3. Exhausted" << endl;
	days[position].fatigue = inputControl(1, 3);
	cout << "Sport tracker updated" << endl;
	cin.get();
	system("cls");
	return;
}

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
				cout << "no" << endl;
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
						cout << "Insert the new dream" << endl;
						getline(cin, days[position].dream);
					}
				}
				else if (days[position].dreamt == false) {
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
		getline(cin, days[position].dream);
	}
	cout << "Sleep tracker updated" << endl;
	cin.get();
	system("cls");
	return;
}

void mood(int position) {
	if (days[position].mood != 0) {
		cout << "You already registered your mood for today" << endl;
		cout << "Do you want to modify it?(1.yes 2.no)" << endl;
		int update = inputControl(1, 2);
		if (update == 1) {
			cout << "What was your mood today" << endl;
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
			days[position].mood = inputControl(1, 5);
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
	days[position].mood = inputControl(1, 5);
	cout << "Mood tracker updated" << endl;
	cin.get();
	system("cls");
	return;
}

void study(int position) {
	if (days[position].subject != ""){
		cout << "You already registered your study for today" << endl;
		cout << "Do you want to modify it?(1.yes 2.no)" << endl;
		int change = inputControl(1, 2);
		if (change == 1) {
			cout << "What subject did you study today?" << endl;
			cout << "Previously " << days[position].subject << endl;
			cout << "Do you want to change it?(1.yes 2.no)" << endl;
			int update = inputControl(1, 2);
			if (update == 1) {
				cout << "Insert the new subject:" << endl;
				getline(cin, days[position].subject);
			}
			cout << "How many hours did you study today?" << endl;
			days[position].studyHours = inputControl(0, 24);
			cout << "Study tracker updated" << endl;
			cin.get();
			system("cls");
			return;
		}
		else if (change == 2) {
			cout << "Subject unchanged. Press Enter to return to menu" << endl;
			cin.get();
			system("cls");
			return;
		}
	}
	cout << "What subject did you study today?" << endl;
	getline(cin, days[position].subject);
	cout << "How many hours did you study it?" << endl;
	days[position].studyHours = inputControl(0, 24);
	cout << "Study tracker updated" << endl;
	cin.get();
	system("cls");
	return;
}

int menu() {
	int choice;
	cout << "1. sport" << endl;
	cout << "2. Sleep" << endl;
	cout << "3. mood" << endl;
	cout << "4. study" << endl;
	cout << "5. objective" << endl;
	cout << "6. recap" << endl;
	cout << "7. exit" << endl;
	choice = inputControl(1, 7);
	return choice;
}

int main() {
	int position = currentDay();

	while (true) {
		int choice = menu();
		switch (choice) {
		case 1: {
			system("cls");
			sport(position);
			break;
		}
		case 2: {
			system("cls");
			sleep(position);
			break;
		}
		case 3: {
			system("cls");
			mood(position);
			break;
		}
		case 4: {
			system("cls");
			study(position);
			break;
		}
		case 5: {
			system("cls");
			//objective
			break;
		}
		case 6: {
			system("cls");
			//recap
			break;
		}
		case 7: {
			return 0;
		}
		}
	}
}