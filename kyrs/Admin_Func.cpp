#include "Header.h"

void Admin_menu() {
	int choice=0;
	system("cls");
	do {
		cout << "Функционал администратора: " << endl;
		cout << "[1] Забанить пользователя" << endl;
		cout << "[2] Выдать админ права" << endl;
		cout << "[3] Удалить аккаунт пользователя" << endl;
		cout << "[4] Вывести статистику пользователей" << endl;
		cout << "[5] Вывести статистику администраторов" << endl;
		cout << "[6] Ввести/вывести данные о продукции" << endl;
		cout << "[7] Разблокировать пользователя" << endl;
		cout << "[8] Выход" << endl;
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
			BanUser();
			break;
		case 2:
			GrantAdmin();
			break;
		case 3:
			DeleteAccount();
			break;
		case 4:
			UserStats();
			break;
		case 5:
			AdmStats();
			break;
		case 6:
			production();
			break;
		case 7:
			unbanneduser();
			break;
		case 8:
			cout << "Закрытие программы" << endl;
			exit(0);
			break;
		default:
			cout << "Некоректное значение" << endl;
			break;
		}
	} while (choice != 8);
}

void BanUser() {
	fstream file("ban.txt", ios::in | ios::app | ios::out);
	ifstream RegFile("reg.txt");
	if (!file.is_open() && !RegFile.is_open()) {
		cout << "Ошибка. Файл не открывается." << endl;
		return;
	}
	string users, line, banUs, pass, role, user;
	bool User;
	do {
		cout << "Введите пользователя (вы не можете забанить Админа): ";
		while (true) {
			getline(cin, user);
			bool validInput = true;
			for (char c : user) {
				if (!isalnum(c) || !isascii(c)) {
					validInput = false;
					break;
				}
			}
			if (user.find(" ") == string::npos && validInput) {
				break;
			}
			else {
				cout << "Некоректный ввод, повторите попытку: ";
			}
		}
		file.clear();
		file.seekg(0, ios::beg);
		User = true;
		while (file >> banUs) {
			if (user == banUs) {
				cout << "Пользователь имеет бан" << endl;
				User = false;
				break;
			}
		}
	} while (!User);
	file.clear();
	file.seekg(0, ios::beg);
	bool foundUser = false;
	while (RegFile >> users >> pass >> role) {
		if (users == user) {
			foundUser = true;
			if (role != "Admin") {
				file << user << "\n";
				cout << "Данный пользователь получил бан" << endl;
				break;
			}
			else {
				cout << "Вы не можете забанить администратора" << endl;
				break;
			}
		}
	}
	if (!foundUser) {
		cout << "Пользователь не найден" << endl;
	}
	file.close();
	RegFile.close();
}

void DeleteAccount() {
	fstream banFile("ban.txt", ios::in | ios::out | ios::app);
	fstream outBan("outban.txt", ios::in | ios::out | ios::app);
	fstream inputfile("reg.txt", ios::in | ios::out | ios::app);
	fstream outputfile("Out.txt", ios::in | ios::out | ios::app);
	if (!inputfile.is_open() || !banFile.is_open())
	{
		cout << "Ошибка. Файл не открывается" << endl;
		return;
	}
	string line, user, userFile, banUser, banline, role;
	cout << "Введите пользователя: ";
	while (true) {
		getline(cin, user);
		bool validInput = true;
		for (char c : user) {
			if (!isalnum(c) || !isascii(c)) {
				validInput = false;
				break;
			}
		}
		if (user.find(" ") == string::npos && validInput) {
			break;
		}
		else {
			cout << "Некоректный ввод, повторите попытку: ";
		}
	}
	bool Delete = false;
	while (getline(inputfile, line)) {
		role = line.substr(line.find_last_of(" ")+1);
		userFile = line.substr(0, line.find(' '));
		if (userFile == user && !Delete && role != "Admin")
		{
			Delete = true;
			continue;
		}
		outputfile << line << "\n";
	}
	if (Delete)
	{
		bool ban = false;
		while (getline(banFile, banUser)) {
			if (user == banUser && !ban)
			{
				ban = true;
				continue;
			}
			outBan << banUser << "\n";
		}
		cout << "Аккаунт пользователя был успешно удален" << endl;
	}
	else
	cout << "Пользователь не найден" << endl;
	inputfile.close();
	outputfile.close();
	remove("reg.txt");
	rename("Out.txt", "reg.txt");
	banFile.close();
	outBan.close();
	remove("ban.txt");
	rename("outban.txt", "ban.txt");
}

void GrantAdmin() {
	ifstream banFile("ban.txt");
	fstream inputf("reg.txt", ios::in | ios::app | ios::out);
	fstream outf("out.txt", ios::in | ios::app | ios::out);
	if (!inputf.is_open() && !outf.is_open() && !banFile.is_open()) {
		cout << "Ошибка. Файл не открывается" << endl;
		return;
	}
	string line, role, user, users, newline, banUser; int last_pos = 0;
	cout << "Введите пользователя: ";
	while (true) {
		getline(cin, user);
		bool validInput = true;
		for (char c : user) {
			if (!isalnum(c) || !isascii(c)) {
				validInput = false;
				break;
			}
		}
		if (user.find(" ") == string::npos && validInput) {
			break;
		}
		else {
			cout << "Некоректный ввод, повторите попытку: ";
		}
	}
	while (banFile >> banUser) {
		if (user == banUser)
		{
			inputf.close();
			outf.close();
			banFile.close();
			remove("reg.txt");
			rename("out.txt", "reg.txt");
			cout << "Пользователь имеет бан!" << endl;
			return;
		}
	}
	bool NewAdm = false;
	while (getline(inputf, line)) {
		users = line.substr(0, line.find(" "));
		if (user == users && !NewAdm) {
			newline = line.substr(0, line.find_last_of(" ")) + " Admin";
			outf << newline << "\n";
			NewAdm = true;
			continue;
		}
		outf << line << "\n";
	}
	if (!NewAdm)
		cout << "Пользователь не найден" << endl;
	else
		cout << "Пользователь получил админ права" << endl;
	inputf.close();
	outf.close();
	banFile.close();
	remove("reg.txt");
	rename("out.txt", "reg.txt");
}

void UserStats() {
	system("cls");
	fstream file("reg.txt", ios::in | ios::out | ios::app);
	fstream banfile("ban.txt", ios::in | ios::out | ios::app);
	if (!file.is_open() || !banfile.is_open()) {
		cout << "Ошибка. Файл не открывается!" << endl;
		return;
	}
	string banus, user, role, pass;  bool userban;
	cout << "Пользователи зарегистрированные в программе:" << endl;
	while (file >> user >> pass >> role) {
		userban = false;
		if (role == "User") {
			banfile.clear();
			banfile.seekg(0, ios::beg);
			while (banfile >> banus) {
				if (banus == user) {
					cout << user << ": имеет бан" << endl;
					userban = true;
					break;
				}
			}
			if (!userban)
				cout << user << endl;
		}
	}
	file.close();
	banfile.close();
}

void AdmStats() {
	system("cls");
	fstream file("reg.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "Ошибка файл не открывается!" << endl;
		return;
	}
	string  user, role, pass;
	cout << "Администраторы зарегестрированные в программе:" << endl;
	while (file >> user >> pass >> role) {
		if (role == "Admin") {
			cout << user << endl;
		}
	}
	file.close();
}

void unbanneduser() {
	system("cls");
	fstream file("ban.txt", ios::in | ios::out | ios::app);
	fstream out("outban.txt", ios::in | ios::out | ios::app);
	if (!file.is_open()) {
		cout << "ошибка, файл не открывается!" << endl;
		return;
	}
	bool Ban = false;
	string user, banuser;
	cout << "введите пользователя, которого вы хотите разбанить: ";
	while (true) {
		getline(cin, user);
		bool validinput = true;
		for (char c : user) {
			if (!isalnum(c) || !isascii(c)) {
				validinput = false;
				break;
			}
		}
		if (user.find(" ") == string::npos && validinput) {
			break;
		}
		else {
			cout << "некоректный ввод, повторите попытку: ";
		}
	}
	while (file >> banuser) {
		if (banuser == user) {
			Ban = true;
			continue;
		}
		out << banuser << endl;
	}
	if (Ban)
		cout << "Пользователь разблокирован" << endl;
	else
		cout << "Пользователь не найден" << endl;
	file.close();
	out.close();
	remove("ban.txt");
	rename("outban.txt", "ban.txt");
}