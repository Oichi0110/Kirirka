#include "Header.h"
int production() {
	int choice;
	system("cls");
	do {
		cout << "[1] Ввод данных о производимой продукции" << endl;
		cout << "[2] Вывод данных за определенный период времени" << endl;
		cout << "[3] Вывод отсортированных данных по наименевонаию" << endl;
		cout << "[4] Просмотр количества произведенной продукции" << endl;
		cout << "[5] Вывод данных опрделенного заведующего цеха" << endl;
		cout << "[6] Вывод данных производства продукции по номеру цеха" << endl;
		cout << "[7] Выход" << endl;
		cout << "Ввод: ";
		string input;
		while (true) {
			getline(cin, input);
			if (input.find_first_not_of("0123456789") == string::npos) {
				choice = stoi(input);
				break;
			}
			else {
				cout << "Введите целое число(1-7): ";
			}
		}
		switch (choice)
		{
		case 1:
			DataProduction();
			break;
		case 2:
			OutProdData();
			break;
		case 3:
			SorNameProd();
			break;
		case 4:
			NumberProd();
			break;
		case 5:
			PrintShopManager();
			break;
		case 6:
			PrintInfoWorkShop();
			break;
		default:
			cout << "Введите корректное значение" << endl;
			break;
		}
	} while (choice != 7);
	return 0;
}


bool isLeapYear(int year) {
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool isValidDate(int day, int month, int year) {
	if (year < 1970 || year > 2050)
		return false;

	if (month < 1 || month > 12)
		return false;

	int daysInMonth = 31;

	if (month == 4 || month == 6 || month == 9 || month == 11)
		daysInMonth = 30;
	else if (month == 2) {
		if (isLeapYear(year))
			daysInMonth = 29;
		else
			daysInMonth = 28;
	}

	return (day >= 1 && day <= daysInMonth);
}

void inputDate(int& day, int& month, int& year) {
	string input;
	while (true) {
		cout << "Введите день (1-31): ";
		while (true) {
			getline(cin, input);
			if (input.find_first_not_of("0123456789") == string::npos) {
				day = stoi(input);
				break;
			}
			else {
				cout << "Введите целое число(1-31): ";
			}
		}
		cout << "Введите месяц (1-12): ";
		while (true) {
			getline(cin, input);
			if (input.find_first_not_of("0123456789") == string::npos) {
				month = stoi(input);
				break;
			}
			else {
				cout << "Введите целое число(1-12): ";
			}
		}
		cout << "Введите год (1970-2050): ";
		while (true) {
			getline(cin, input);
			if (input.find_first_not_of("0123456789") == string::npos) {
				year = stoi(input);
				break;
			}
			else {
				cout << "Введите целое число(1970-2050): ";
			}
		}
		if (isValidDate(day, month, year))
			break;
		cout << "Некорректная дата, повторите ввод.\n";
	}
}

bool isValidFullName(const string& fullName) {
	size_t firstSpacePos = fullName.find(' ');
	size_t lastSpacePos = fullName.find_last_of(' ');
	if (firstSpacePos != string::npos && firstSpacePos != 0 && lastSpacePos != fullName.length() - 1) {
		if (firstSpacePos != lastSpacePos) {
			return true;
		}
	}
	return false;
}

void DataProduction() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	Prodd Prod;
	string quantity, workshop;
	inputDate(Prod.day, Prod.month, Prod.year);
	Prod.data = to_string(Prod.day) + "." + to_string(Prod.month) + "." + to_string(Prod.year);
	cout << "Введите наименование продукции: ";
	while (true) {
		getline(cin, Prod.NameProd);
		bool validInput = true;
		for (char c : Prod.NameProd) {
			if (!isalpha(c) || !isascii(c)) {
				validInput = false;
				break;
			}
		}
		if (validInput) {
			break;
		}
		else {
			cout << "Некорректный ввод, повторите попытку: ";
		}
	}
	cout << "Введите количество произведенной продукции: ";
	while (true) {
		getline(cin, quantity);
		if (quantity.find_first_not_of("0123456789") == string::npos) {
			Prod.QuantityProd = stoi(quantity);
			break;
		}
		else {
			cout << "Введите коректное число: ";
		}
	}
	cout << "Введите ФИО заведующего цехам: "; cin.ignore();
	while (true) {
		getline(cin, Prod.FullName);
		if (isValidFullName(Prod.FullName))
			break;
		else
			cout << "Введите коректные данные: ";
	}
	cout << "Введите номер цеха: ";
	while (true) {
		getline(cin, workshop);
		if (workshop.find_first_not_of("0123456789") == string::npos) {
			Prod.NumberWorkshop = stoi(workshop);
			break;
		}
		else {
			cout << "Введите корректное число: ";
		}
	}
	file << Prod.data << "," << Prod.NameProd << "," << Prod.QuantityProd << "," << Prod.FullName << "," << Prod.NumberWorkshop << "\n";
	file.close();
}


void OutProdData() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	string Other, line;
	int day, month, year;
	vector<Date> times;
	Date date;
	SortProd Sort;
	cout << "Введите начало интервала: ";
	inputDate(Sort.BegDay, Sort.BegMonth, Sort.BegYear);
	cout << "Введите конец интервала: ";
	inputDate(Sort.EndDay, Sort.EndMonth, Sort.EndYear);
	while (getline(file, line)) {
		day = stoi(line.substr(0, 2));
		month = stoi(line.substr(3, 2));
		year = stoi(line.substr(6, 4));
		if ((Sort.BegYear < year && Sort.EndYear > year) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth < month && Sort.EndMonth > month) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth == month && Sort.EndMonth == month && Sort.BegDay < day && Sort.EndDay > day)) {
			Other = line.substr(11);
			date = { Other, day, month, year };
			times.push_back(date);
		}
	}
	system("cls");
	file.close();
	Sorted(times);
}

void Sorted(vector<Date>& times) {
	string NameProd, quantity, Fullname, NumberWorkshop;
	sort(times.begin(), times.end(), compare);
	for (const auto& date : times) {
		cout << endl;
		size_t pos1 = date.line.find(",");
		size_t pos2 = date.line.find(",", pos1 + 1);
		size_t pos3 = date.line.find(",", pos2 + 1);
		NameProd = date.line.substr(0, pos1 - 1);
		quantity = date.line.substr(pos1 + 1, pos2 - pos1 - 1);
		Fullname = date.line.substr(pos2 + 1, pos3 - pos2 - 1);
		NumberWorkshop = date.line.substr(pos3 + 1);
		cout << "" << date.day << "." << date.month << "." << date.year << ": \n" << "Наименование продукции: " << NameProd << "\nКоличество произаеденной продукции: " << quantity << "\nФИО заведующего цехам:" << Fullname << "\nНомер цеха: " << NumberWorkshop << endl;
	}
}

bool compare(const Date& d1, const Date& d2)
{
	if (d1.year < d2.year)
		return true;
	if (d1.year == d2.year && d1.month < d2.month)
		return true;
	if (d1.year == d2.year && d1.month == d2.month &&
		d1.day < d2.day)
		return true;
	return false;
}

bool compareFull(const SortFullName& d1, const SortFullName& d2)
{
	if (d1.year < d2.year)
		return true;
	if (d1.year == d2.year && d1.month < d2.month)
		return true;
	if (d1.year == d2.year && d1.month == d2.month &&
		d1.day < d2.day)
		return true;
	return false;
}

bool Sname(const SortName& d1, const SortName& d2)
{
	string name1 = d1.name;
	string name2 = d2.name;
	transform(name1.begin(), name1.end(), name1.begin(), [](unsigned char c) { return tolower(c); });
	transform(name2.begin(), name2.end(), name2.begin(), [](unsigned char c) { return tolower(c); });
	return name1 < name2;
}

void SorNameProd() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	string name, line, str, data, quantity, FullName, NumberWorkshop;
	int day, month, year;
	vector<SortName> sortName;
	SortName sor;
	SortProd Sort;
	cout << "Введите начало интервала: ";
	inputDate(Sort.BegDay, Sort.BegMonth, Sort.BegYear);
	cout << "Введите конец интервала: ";
	inputDate(Sort.EndDay, Sort.EndMonth, Sort.EndYear);
	while (getline(file, line)) {
		day = stoi(line.substr(0, 2));
		month = stoi(line.substr(3, 2));
		year = stoi(line.substr(6, 4));
		if ((Sort.BegYear < year && Sort.EndYear > year) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth < month && Sort.EndMonth > month) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth == month && Sort.EndMonth == month && Sort.BegDay < day && Sort.EndDay > day)) {
			size_t pos1 = line.find(",");
			size_t pos2 = line.find(",", pos1 + 1);
			name = line.substr(pos1 + 1, pos2 - pos1 - 1);
			str = line.substr(0, pos1) + "," + line.substr(pos2 + 1);
			sor = { name, str };
			sortName.push_back(sor);
		}
	}
	system("cls");
	sort(sortName.begin(), sortName.end(), Sname);
	for (const auto& sor : sortName) {
		size_t pos1 = sor.line.find(",");
		size_t pos2 = sor.line.find(",", pos1 + 1);
		size_t pos3 = sor.line.find(",", pos2 + 1);
		data = sor.line.substr(0, pos1 - 1);
		quantity = sor.line.substr(pos1 + 1, pos2 - pos1 - 1);
		FullName = sor.line.substr(pos2 + 1, pos3 - pos2 - 1);
		NumberWorkshop = sor.line.substr(pos3 + 1);
		cout << "Наименование продукции: " << sor.name << endl;
		cout << "Информация о продукции: " << endl;
		cout << "Дата производтсва: " << data << "\nКоличество произведенной продуции: " << quantity << "\nФИО заведующего цехам: " << FullName << "\nНомер цеха: " << NumberWorkshop << endl << endl;
	}
	file.close();
}

void NumberProd() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	int choice = 0;
	cout << "[1] Вывод количество продукции, произведенной за все время" << endl;
	cout << "[2] Вывод количество продукции, произведенной за определенный период времени" << endl;
	cout << "[3] Выведите количество продуктов определенного продукта" << endl;
	cout << "Ввод: ";
	string input;
	while (true) {
		getline(cin, input);
		if (input.find_first_not_of("0123456789") == string::npos) {
			choice = stoi(input);
			break;
		}
		else {
			cout << "Введите целое число(1-3): ";
		}
	}
	switch (choice)
	{
	case 1:
		NumberAllTime();
		break;
	case 2:
		NumberCertainPeriod();
		break;
	case 3:
		NumberCertainProd();
		break;
	default:
		cout << "Введите корректное число" << endl;
		NumberProd();
		break;
	}
	file.close();
}

bool NumQuan(const Number& d1, const Number& d2)
{
	if (d1.year < d2.year)
		return true;
	if (d1.year == d2.year && d1.month < d2.month)
		return true;
	if (d1.year == d2.year && d1.month == d2.month &&
		d1.day < d2.day)
		return true;
	return false;
}

void NumberAllTime() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	Number date;
	vector<Number> times;
	string line, otherline;
	int day, month, year, quantity, sumQuantity = 0;
	while (getline(file, line))
	{
		size_t pos1 = line.find(",");
		size_t pos2 = line.find(",", pos1 + 1);
		size_t pos3 = line.find(",", pos2 + 1);
		otherline = line.substr(pos1 + 1, pos2 - pos1 - 1) + "," + line.substr(pos3 + 1);
		day = stoi(line.substr(0, 2));
		month = stoi(line.substr(3, 2));
		year = stoi(line.substr(6, 4));
		quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
		sumQuantity += quantity;
		date = { otherline, day, month, year, quantity };
		times.push_back(date);
	}
	sort(times.begin(), times.end(), NumQuan);
	cout << endl;
	cout << "Количество произведенной продукции: " << sumQuantity << "\nОтчетность" << endl;
	for (const auto& date : times) {
		cout << date.day << "." << date.month << "." << date.year << ": " << date.quantity << endl;
	}
	file.close();
}

void NumberCertainPeriod() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается" << endl;
		return;
	}
	Number date;
	vector<Number> times;
	string line, otherline;
	SortProd Sort;
	int day, month, year, quantity, sumQuantity = 0;
	cout << "Введите начало интервала: ";
	inputDate(Sort.BegDay, Sort.BegMonth, Sort.BegYear);
	cout << "Введите конец интервала: ";
	inputDate(Sort.EndDay, Sort.EndMonth, Sort.EndYear);
	while (getline(file, line))
	{
		day = stoi(line.substr(0, 2));
		month = stoi(line.substr(3, 2));
		year = stoi(line.substr(6, 4));
		if ((Sort.BegYear < year && Sort.EndYear > year) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth < month && Sort.EndMonth > month) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth == month && Sort.EndMonth == month && Sort.BegDay < day && Sort.EndDay > day)) {
			size_t pos1 = line.find(",");
			size_t pos2 = line.find(",", pos1 + 1);
			size_t pos3 = line.find(",", pos2 + 1);
			otherline = line.substr(pos1 + 1, pos2 - pos1 - 1) + "," + line.substr(pos3 + 1);
			quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
			sumQuantity += quantity;
			date = { otherline, day, month, year, quantity };
			times.push_back(date);
		}
	}
	sort(times.begin(), times.end(), NumQuan);
	cout << endl;
	cout << "Суммарное количество произведенной продукции: " << sumQuantity << "\nОтчетность: " << endl;
	for (const auto& date : times) {
		cout << date.day << "." << date.month << "." << date.year << ": " << date.quantity << endl;
	}
	file.close();
}

void NumberCertainProd() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	Number date;
	vector<Number> times;
	string line, otherline, name, nameProd;
	int day, month, year, quantity, sumQuantity = 0;
	cout << "Введите наименование продукции: ";
	getline(cin, name);
	while (getline(file, line))
	{
		size_t pos1 = line.find(",");
		size_t pos2 = line.find(",", pos1 + 1);
		nameProd = line.substr(pos1 + 1, pos2 - pos1 - 1);
		if (nameProd == name) {
			day = stoi(line.substr(0, 2));
			month = stoi(line.substr(3, 2));
			year = stoi(line.substr(6, 4));
			size_t pos3 = line.find(",", pos2 + 1);
			otherline = line.substr(pos1 + 1, pos2 - pos1 - 1) + "," + line.substr(pos3 + 1);
			quantity = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
			sumQuantity += quantity;
			date = { otherline, day, month, year, quantity };
			times.push_back(date);
		}
	}
	sort(times.begin(), times.end(), NumQuan);
	cout << endl;
	cout << "Суммарное количество произведенной продукции: " << sumQuantity << "\nОтчетность: " << endl;
	for (const auto& date : times) {
		cout << date.day << "." << date.month << "." << date.year << ": " << date.quantity << endl;
	}
	file.close();
}

void PrintShopManager() {
	fstream file("Production.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	string FullName, line, FileName, otherline, nameprod, quantity, numberworshop;
	SortFullName date;
	vector <SortFullName> times;
	int day, month, year;
	cout << "Введите ФИО заведующего цехам: ";
	while (true) {
		getline(cin, FullName);
		if (isValidFullName(FullName))
			break;
		else
			cout << "Введите коректные данные: ";
	}
	while (getline(file, line))
	{
		size_t pos1 = line.find(",");
		size_t pos2 = line.find(",", pos1 + 1);
		size_t pos3 = line.find(",", pos2 + 1);
		size_t pos4 = line.find(",", pos3 + 1);
		FileName = line.substr(pos3 + 1, pos4 - pos3 - 1);
		if (FullName == FileName) {
			day = stoi(line.substr(0, 2));
			month = stoi(line.substr(3, 2));
			year = stoi(line.substr(6, 4));
			otherline = line.substr(pos1 + 1, pos4 - pos1 - 1) + "," + line.substr(pos4 + 1);
			date = { otherline, day, month, year, FullName };
			times.push_back(date);
		}
	}
	sort(times.begin(), times.end(), compareFull);
	cout << "ФИО: " << date.FullName << "\nОтчет:" << endl;
	for (const auto& date : times) {
		cout << endl;
		size_t pos1 = date.line.find(",");
		size_t pos2 = date.line.find(",", pos1 + 1);
		size_t pos3 = date.line.find(",", pos2 + 1);
		nameprod = date.line.substr(0, pos1 - 1);
		quantity = date.line.substr(pos1 + 1, pos2 - pos1 - 1);
		numberworshop = date.line.substr(pos3 + 1);
		cout << "" << date.day << "." << date.month << "." << date.year << ": \n" << "Наименование продукции: " << nameprod << "\nКоличество произаеденной продукции: " << quantity << "\nНомер цеха: " << numberworshop << endl;
	}
	file.close();
}

void PrintInfoWorkShop() {
	fstream Prod("Production.txt", ios::in | ios::out | ios::app);
	if (!Prod.is_open()) {
		cout << "Ошибка, файл не открывается!" << endl;
		return;
	}
	vector <SortName> WorkShop;
	SortName date;
	SortProd Sort;
	int day, month, year;
	string workshop, line, FileWorkShop, Name, OtherLine, Quantity, Times;
	cout << "Введите номер цеха: ";
	while (true) {
		getline(cin, workshop);
		if (workshop.find_first_not_of("0123456789") == string::npos) {
			break;
		}
		else {
			cout << "Введите корректное число: ";
		}
	}
	cout << "Введите начало интервала: ";
	inputDate(Sort.BegDay, Sort.BegMonth, Sort.BegYear);
	cout << "Введите конец интервала: ";
	inputDate(Sort.EndDay, Sort.EndMonth, Sort.EndYear);
	while (getline(Prod, line)) {
		day = stoi(line.substr(0, 2));
		month = stoi(line.substr(3, 2));
		year = stoi(line.substr(6, 4));
		size_t pos4 = line.find_last_of(",");
		FileWorkShop = line.substr(pos4 + 1);
		if (workshop.compare(FileWorkShop) == 0 && ((Sort.BegYear < year && Sort.EndYear > year) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth < month && Sort.EndMonth > month) || (Sort.BegYear == year && Sort.EndYear == year && Sort.BegMonth == month && Sort.EndMonth == month && Sort.BegDay < day && Sort.EndDay > day))) {
			size_t pos1 = line.find(",");
			size_t pos2 = line.find(",", pos1 + 1);
			size_t pos3 = line.find(",", pos2 + 1);
			Name = line.substr(pos1 + 1, pos2 - pos1 - 1);
			OtherLine = line.substr(0, pos1 - 1) + "," + line.substr(pos2+1);
			date = { Name, OtherLine };
			WorkShop.push_back(date);
		}
	}
	sort(WorkShop.begin(), WorkShop.end(), Sname);
	system("cls");
	cout << "Информация по цеху №" << workshop << ":" << endl;
	for (const auto& date : WorkShop) {
		cout << endl;
		size_t pos1 = date.line.find(",");
		size_t pos2 = date.line.find(",", pos1 + 1);
		Quantity = date.line.substr(pos1 + 1, pos2 - pos1 - 1);
		Times = date.line.substr(0, pos1 - 1);
		cout << "Наименование продукции: " << date.name << "\nКоличество произведенной продукции: " << Quantity << "\nДата производства: " << Times << endl;
	}
	Prod.close();
}