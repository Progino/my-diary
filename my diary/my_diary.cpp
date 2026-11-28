#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
using namespace std;

struct Day {
	int day = 0;
	int month = 0;
	int year = 0;
	string sport = "";
	int sportHours = 0;
	int fatigue = 0;
	int hoursSlept = 0;
	bool dreamt = false;
	string dream = "";
	int mood = 0;
	string subject = "";
	int studyHours = 0;
};

struct Goal {
	bool done = false;
	string goal = "";
};

vector <Day> days(365);
vector <Goal> goals;
//maybe vector for years that include Day vectors

const string SPORT = "sport.txt";
const string SLEEP = "sleep.txt";
const string MOOD =  "mood.txt";
const string STUDY = "study.txt";

void loadSportFromFile() {
	ifstream file(SPORT);
	if (!file.is_open()) {
		cout << "Unable to open the file" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string dayS, sport, hoursS, fatigueS;
		if (getline(ss, dayS, ';') && getline(ss, sport, ';') && getline(ss, hoursS, ';') && getline(ss, fatigueS, ';')) {

			int d = stoi(dayS);
			if (d >= 0 && d < 365) {
				days[d].sport = sport;
				days[d].sportHours = stoi(hoursS);
				days[d].fatigue = stoi(fatigueS);
			}
		}
	}
	file.close();
}

void saveSportFromFile() {
	ofstream file(SPORT);
	if (!file.is_open()) {
		cout << "Unable to save the data" << endl;
		return;
	}
	for (int i = 0;i < 365;i++) {
		if (days[i].sport != "") {
			file << i << ";" << days[i].sport << ";" << days[i].sportHours << ";" << days[i].fatigue << ";"<<endl;

		}
	}
	file.close();
}

void loadSleepFromFile() {
	ifstream file(SLEEP);
	if (!file.is_open()) {
		cout << "Unable to open the file" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string dayS, hoursSlept, dreamt, dream;
		if (getline(ss, dayS, ';') && getline(ss, hoursSlept, ';') && getline(ss, dreamt, ';') && getline(ss, dream, ';')) {

			int d = stoi(dayS);
			if (d >= 0 && d < 365) {
				days[d].hoursSlept = stoi(hoursSlept);
				days[d].dreamt = stoi(dreamt);
				days[d].dream = dream;
			}
		}
	}
	file.close();
}

void saveSleepFromFile() {
	ofstream file(SLEEP);
	if (!file.is_open()) {
		cout << "Unable to save the data" << endl;
		return;
	}
	for (int i = 0;i < 365;i++) {
		if (days[i].hoursSlept != 0) {
			file << i << ";" << days[i].hoursSlept << ";" << days[i].dreamt << ";" << days[i].dream << ";"<< endl;
		}
	}
	file.close();
}

void loadMoodFromFile() {
	ifstream file(MOOD);
	if (!file.is_open()) {
		cout << "Unable to open the file" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string dayS, mood;
		if (getline(ss, dayS, ';') && getline(ss, mood, ';')) {

			int d = stoi(dayS);
			if (d >= 0 && d < 365) {
				days[d].mood = stoi(mood);
			}
		}
	}
	file.close();
}//mood

void saveMoodFromFile() {
	ofstream file(MOOD);
	if (!file.is_open()) {
		cout << "Unable to save the data" << endl;
		return;
	}
	for (int i = 0;i < 365;i++) {
		if (days[i].mood != 0) {
			file << i << ";" << days[i].mood << ";"<< endl;
		}
	}
	file.close();
}

void loadStudyFromFile() {
	ifstream file(STUDY);
	if (!file.is_open()) {
		cout << "Unable to open the file" << endl;
		return;
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string dayS, subject, studyHours;
		if (getline(ss, dayS, ';') && getline(ss, subject, ';') && getline(ss, studyHours, ';')) {

			int d = stoi(dayS);
			if (d >= 0 && d < 365) {
				days[d].subject = subject;
				days[d].studyHours = stoi(studyHours);
			}
		}
	}
	file.close();
}

void saveStudyFromFile() {
	ofstream file(STUDY);
	if (!file.is_open()) {
		cout << "Unable to save the data" << endl;
		return;
	}
	for (int i = 0;i < 365;i++) {
		if (days[i].subject != "") {
			file << i << ";" << days[i].subject << ";" << days[i].studyHours << ";"<< endl;
		}
	}
	file.close();
}

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
			saveSportFromFile();
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
	saveSportFromFile();
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
			saveSleepFromFile();
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
	saveSleepFromFile();
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
			saveMoodFromFile();
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
	saveMoodFromFile();
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
			saveStudyFromFile();
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
	saveStudyFromFile();
	cout << "Study tracker updated" << endl;
	cin.get();
	system("cls");
	return;
}

int getDay() {
	int day, month = 0;
	int finalDay = 0;
	int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	cout << "Insert the month: ";
	month = inputControl(1, 12);
	cout << "Insert the day: ";
	day = inputControl(1, monthDay[month - 1]);

	for (int i = 0;i < month - 1;i++) {
		finalDay += monthDay[i];
	}
	finalDay += day;
	finalDay--;
	return finalDay;
}

string getDate(int finalDay) {
	int day, month = 0;
	int monthDay[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int p = 0;
	for (int i = 0;p <= finalDay;i++) {
		month++;
		p += monthDay[i];
	}

	int dayD = 0;
	for (int i = 0; i < month-1 ;i++) {
		dayD += monthDay[i];
	}
	day = finalDay - dayD;
	day++;

	return to_string(day) + "/" + to_string(month);
}
//make that you can continue to choose an option as many time you want
//add saving files
void objective() {
	while (true) {
		cout << "1. add goal" << endl;
		cout << "2. see goals" << endl;
		cout << "3. check off goal" << endl;
		cout << "4. exit" << endl;
		int goal = inputControl(1, 4);
		switch (goal) {
		case 1: {
			Goal newGoal;
			cout << "What's your goal:" << endl;
			getline(cin, newGoal.goal);
			goals.push_back(newGoal);
			cout << endl << "Goal added succesfully" << endl;
			cout << "(Press enter)" << endl;
			cin.get();
			system("cls");
			break;
		}
		case 2: {
			cout << "GOALS" << endl << endl;
			if (goals.empty()) {
				cout << "Add a goal first" << endl;
				cout <<endl<< "(Press enter)" << endl;
				cin.get();
				system("cls");
				break;
			}
			for (size_t i = 0;i < goals.size();i++) {
				cout << "[] " << goals[i].goal << endl;
			}
			cout <<endl<< "(Press enter)" << endl;
			cin.get();
			system("cls");
			break;
		}
		case 3: {
			if (goals.empty()) {
				cout << "Add a goal first" << endl;
				cout << endl <<  "(Press enter)" << endl;
				cin.get();
				system("cls");
				break;
			}
			cout << "What goal did you complete?" << endl;
			for (size_t i = 0;i < goals.size();i++) {
				cout << i + 1 << "[]" << goals[i].goal << endl;;
			}
			int check = inputControl(1, goals.size());

			goals.erase(goals.begin() + check - 1);
			cout << "Goal comleted succesfully" << endl;
			cout << "(Press enter)" << endl;
			cin.get();
			system("cls");
			break;
		}
		case 4: {
			return;
		}
		}
	}

}

void recap() {
	cout << "What date do you want to see?" << endl<<endl;
	int day = getDay();
	while (true) {
		system("cls");
		cout << "What do you want to see?" << endl;
		cout << "1. Sport" << endl;
		cout << "2. Sleep" << endl;
		cout << "3. Mood" << endl;
		cout << "4. study" << endl;
		cout << "5. return to menu" << endl;
		int choice = inputControl(1, 5);
		switch (choice) {
		case 1: {
			cout << getDate(day) << endl << endl;
			if (days[day].sport == "") {
				cout << "You didn't practice any spport that day" << endl;
				cout << "Press enter to return" << endl;
				cin.get();
				system("cls");
				break;
			}
			cout << "sport:   " << days[day].sport << endl;
			cout << "hours:   " << days[day].sportHours << endl;
			cout << "fatigue: ";
			switch (days[day].fatigue) {
			case 1: {
				cout << "Energized" << endl;
				break;
			}
			case 2: {
				cout << "Tired (good fatigue)" << endl;
				break;
			}
			case 3: {
				cout << "Exhausted" << endl;
				break;
			}
			}
			cout <<endl<< "Press enter to return" << endl;
			cin.get();
			system("cls");
			break;
		}
		case 2: {
			cout << getDate(day) << endl << endl;
			if (days[day].hoursSlept == 0) {
				cout << "You didn't sleep that night" << endl;
				cout << "Press enter to return" << endl;
				cin.get();
				system("cls");
				break;
			}
			cout << "Hours: " << days[day].hoursSlept << endl;
			if (days[day].dreamt) {
				cout << "dream: " << days[day].dream << endl;
			}
			cout <<endl<< "Press enter to return" << endl;
			cin.get();
			system("cls");
			break;
		}
		case 3: {
			cout << getDate(day) << endl << endl;
			if (days[day].mood == 0) {
				cout << "You didn't registered your mood that day" << endl;
				cout << "Press enter to return" << endl;
				cin.get();
				system("cls");
				break;
			}
			cout << "mood: ";
			switch (days[day].mood) {
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
			cout <<endl<< "Press enter to return" << endl;
			cin.get();
			system("cls");
			break;
		}
		case 4: {
			cout << getDate(day) << endl << endl;
			if (days[day].subject == "") {
				cout << "You didn't registered your study that day" << endl;
				cout << "Press enter to return" << endl;
				cin.get();
				system("cls");
				break;
			}
			cout << "Subject: " << days[day].subject << endl;
			cout << "Hours  : " << days[day].studyHours << endl;
			cout << endl << "Press enter to return" << endl;
			cin.get();
			system("cls");
			break;
		}
		case 5:
			system("cls");
			return;
		}
	}
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
	int goals = 0;
	loadSportFromFile();
	loadSleepFromFile();
	loadMoodFromFile();
	loadStudyFromFile();
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
			objective();
			break;
		}
		case 6: {
			system("cls");
			recap();
			break;
		}
		case 7: {
			return 0;
		}
		}
	}
}