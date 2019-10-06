#include <iostream>

using namespace std;

//class to store to date
class date {
	int day, month, year;
public:
	date() {}
	date(int d, int m, int y) :day(d), month(m), year(y) {}
	bool check_date(int d, int m, int y);
	void input();
	int date_diff(date& x);
	void add_days(int x,date y);
	void display() {
		cout << day << "." << month << "." << year;
	}
};

//adds 'x' days in 'date y' and stores it
void date::add_days(int x,date y) {
	day = y.day + x;
	month = y.month, year = y.year;
	if (day > 30) {
		day -= 30;
		month++;
		if (month > 12) {
			year++;
		}
	}
}

//return difference between two dates
int date::date_diff(date& x) {
	int temp_d, temp_m, temp_y;
	temp_y = year - x.year;
	temp_m = month - x.month;
	temp_d = day - x.day;
	if (temp_y != 0) {
		temp_m = temp_m + (temp_y * 12);
	}
	if (temp_m != 0) {
		temp_d = temp_d + (temp_m * 30);
	}
	return temp_d;
}

//checks if given date is correct or not
bool date::check_date(int d, int m, int y) {
	//check if year is a leap year
	if (y % 4 == 0) {
		if (m == 2) {
			if (d <= 29 && d > 0)
				return true;
		}
	}
	else {
		if (m == 2) {
			if (d <= 28 && d > 0)
				return true;
		}
	}
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) {
		if (d <= 31 && d > 0)
			return true;
	}
	else if (m == 4 || m == 6 || m == 9 || m == 11) {
		if (d <= 30 && d > 0)
			return true;
	}
	return false;

}

//takes input for date
void date::input() {
	int d, m, y;
	char c1, c2;
	do {
		cin >> d >> c1 >> m >> c2 >> y;
		if (c1 != '\\' || c2 != '\\') {
			cout << "Format error" << endl;
		}
		if (!check_date(d, m, y)) {
			cout << "Error in reading date" << endl;
			cout << "Please Enter date again." << endl;
		}
		else {
			day = d, month = m, year = y;
			return;
		}
	} while (true);
}

//class to store all the variable of electricity bill
class electricity_bill {
	long int tel_no;
	int use_type, meter_no, bill_no, current_reading, previous_reading, reading_difference;
	double rate, advance_payable, previous_arrears, amount_payable;
	char name[25], address[60], email[30];
	date bill_date, due_date, current_reading_date, previous_reading_date;
public:
	electricity_bill() {}
	void input();
	void output();
	void calculate_bill();
	double present_bill();
	void get_rate();
};

//takes input for electricity bill
void electricity_bill::input() {
	cout << "Enter Name : ";
	cin >> name;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cout << "Enter Address : ";
	cin.getline(address,60);
	cout << "email : ";
	cin >> email;
	cout << "Enter Contact number : ";
	cin >> tel_no;

	cout << "Enter Meter number : ";
	cin >> meter_no;
	cout << "Enter use type (1-Domestic/2-Commercial) : ";
	cin >> use_type;

	cout << "Enter current reading date : ";
	current_reading_date.input();
	cout << "Enter current reading : ";
	cin >> current_reading;

	cout << "Enter previous reading date : ";
	previous_reading_date.input();
	cout << "Enter previous reading : ";
	cin >> previous_reading;

	cout << "Enter Bill date : ";
	bill_date.input();

	cout << "Enter previous arrears (if any else 0) : ";
	cin >> previous_arrears;

	cout << "Enter Advance Payable (if any else 0) : ";
	cin >> advance_payable;
}


//returns rate for 1 unit
void electricity_bill::get_rate() {
	if (reading_difference < 101)
		rate = 1.40;
	else if (reading_difference < 201)
		rate = 2.10;
	else if (reading_difference < 301)
		rate = 2.65;
	else if (reading_difference < 401)
		rate = 3.45;
	else
		rate = 4;
	if (use_type == 2) {
		if (reading_difference < 201)
			rate += 2;
		else if (reading_difference < 401)
			rate = 4.60;
		else
			rate = 5;
	}
}

//returns bill of current period
double electricity_bill::present_bill() {
	get_rate();
	double b = reading_difference * rate;
	return b;
}

//calculates total electicity bill
void electricity_bill::calculate_bill() {
	double A, B, C, D, E;
	A = previous_arrears;
	B = advance_payable;
	int dateDiff = current_reading_date.date_diff(previous_reading_date);
	C = (previous_arrears * 0.05 / 100) * dateDiff;
	D = present_bill();
	int a = A - B + C + D;
	E = A - B + C + D - a;
	cout << "A-Previous Arrear : " << A << endl;
	cout << "B-Advance Payable : " << B << endl;
	cout << "C-DPC till bill date : " << C << endl;
	cout << "D-Present total bill : " << D << endl;
	cout << "E-Rounding amount : " << -E << endl;
	cout << "Amount Payable : " << A - B + C + D - E << endl;
}

//Gives output for electricity bill
void electricity_bill::output() {
	cout << endl << endl;
	cout << "---------------Electricity Bill---------------" << endl;
	cout << "Name                  :   " << name << endl;
	cout << "Address               :   " << address << endl;
	cout << "Contact No.           :   " << tel_no << endl;
	cout << "Email                 :   " << email << endl;
	cout << "Meter number          :   " << meter_no << endl;
	cout << "______________________________________________";
	cout << endl << "Current reading date  :   ";
	current_reading_date.display();
	cout << endl << "Current reading       :   " << current_reading << endl;
	cout << "______________________________________________";
	cout << endl << "Previous reading date :   ";
	previous_reading_date.display();
	cout << endl << "Previous reading      :   " << previous_reading << endl;
	cout << "______________________________________________";
	reading_difference = current_reading - previous_reading;
	cout << endl << "Consumption           :   " << reading_difference << endl;
	cout << endl << "Bill Date             :   ";
	bill_date.display();
	due_date.add_days(14, bill_date);
	cout << endl << "Due Date              :   ";
	due_date.display();
	cout <<endl<< "______________________________________________";
	cout << endl << "Bill Summary : " << endl;
	calculate_bill();
	cout << "______________________________________________";

}

int main() {
	int opt;
	electricity_bill e;
	while (true) {
		cout << endl << "1.Enter Info";
		cout << endl << "2.Display bill";
		cout << endl << "3.Exit" << endl<<"> ";
		cin >> opt;
		switch (opt) {
		case 1:
			e.input();
			break;
		case 2:
			e.output();
			break;
		case 3:
			exit(0);
		default: 
			cout << "Error!!!" << endl << "Enter again";
		}
	}
}