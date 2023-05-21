#include "Header.h"

bool Register = false;
bool AvtUs = false;
bool AvtAd = false;

void menu() {
	setlocale(LC_ALL, "Rus");
	string user;
	int choice;
	do {
		cout << "Выберите действие:" << endl;
		cout << "[1] Регистрация." << endl;
		cout << "[2] Авторизация." << endl;
		cout << "[3] Выход." << endl;
		cout << "Введите номер: ";
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
			Registrate();
			break;
		case 2:
			Avtorizate();
			break;
		case 3:
			cout << "Закрытие программы.";
			break;
		default:
			cout << "Введите корректное число" << endl;
			break;
		}
	} while (!AvtUs && !AvtAd && choice != 3);
	if (AvtUs) {
		User_Func();
	}
	if (AvtAd) {
		Admin_menu();
	}
}

void Registrate() {
	setlocale(LC_ALL, "Rus");
	system("cls");
	bool Username = false;
	string name, pas, confpass, FUs;
	bool cpass = false;
	fstream file("reg.txt", ios::in | ios::out);
	if (!file.is_open()) {
		cout << "Ошибка. Файл не открывается." << endl;
		return;
	}
	do {
		cout << "Введите имя_пользователя(без пробелов и с англоязычными символами): ";
		while (true) {
			getline(cin, name);
			bool validInput = true;
			for (char c : name) {
				if (!isalnum(c) || !isascii(c)) {
					validInput = false;
					break;
				}
			}
			if (name.find(" ") == string::npos && validInput) {
				break;
			}
			else {
				cout << "Некоректный ввод, повторите попытку: ";
			}
		}
		Username = true;
		file.seekg(0, ios::beg);
		while (file >> FUs) {
			if (FUs == name) {
				cout << "Такой пользователь уже зарегистрирован" << endl;
				Username = false;
				break;
			}
		}
	} while (!Username);
	file.close();
	fstream file1("reg.txt", ios::in | ios::out | ios::app);
	cout << "Введите пароль(без пробелов и с англоязычными символами)): ";
	while (true) {
		getline(cin, pas);
		bool validInput = true;
		for (char c : pas) {
			if (!isalnum(c) || !isascii(c)) {
				validInput = false;
				break;
			}
		}
		if (pas.find(" ") == string::npos && validInput) {
			break;
		}
		else {
			cout << "Некоректный ввод, повторите попытку: ";
		}
	}
	cout << "Подтвердите пароль: ";
	do {
		while (true) {
			getline(cin, confpass);
			bool validInput = true;
			for (char c : confpass) {
				if (!isalnum(c) || !isascii(c)) {
					validInput = false;
					break;
				}
			}
			if (confpass.find(" ") == string::npos && validInput) {
				if (pas.compare(confpass) == 0) {
					cout << "Вы зарегестрировались!" << endl;
					cpass = true;
					Register = true;
				}
				else {
					cout << "Повторите попытку: ";
				}
				break;
			}
			else {
				cout << "Некоректный ввод, повторите попытку: ";
			}
		}
	} while (!cpass);
	file1 << name << " " << pas << " " << "User" << "\n";
	file1.close();
}

void Avtorizate() {
	system("cls");
	string FUs, Avname, Avpass, Avrole, pass, name, BUs;
	ifstream file("reg.txt");
	ifstream BanFile("ban.txt");
	if (!file.is_open() || !BanFile.is_open()) {
		cout << "Ошибка. Файл не открывается." << endl;
		return;
	}
	cout << "Введите имя_пользователя: ";
	while (true) {
		getline(cin, name);
		bool validInput = true;
		for (char c : name) {
			if (!isalnum(c) || !isascii(c)) {
				validInput = false;
				break;
			}
		}
		if (name.find(" ") == string::npos && validInput) {
			break;
		}
		else {
			cout << "Некоректный ввод, повторите попытку: ";
		}
	}
	bool Username = true;
	file.clear();
	file.seekg(0, ios::beg);
	while (file >> FUs) {
		if (FUs == name) {
			Username = false;
			break;
		}
	}
	bool Ban = false;
	while (BanFile >> BUs) {
		if (BUs == name) {
			Ban = true;
			break;
		}
	}
	if (Username || Ban) {
		cout << "Данный пользователь не зарегистрирован или находится в бане" << endl;
		cout << "0 - Авторизоваться заново\n1 - Вернуться в меню\nEnter: ";
		int choice=0;
		string input;
		while (true) {
			getline(cin, input);
			if (input.find_first_not_of("0123456789") == string::npos) {
				choice = stoi(input);
				if(choice>=0 && choice <=1)
					break;
			}
			else {
				cout << "Введите целое число(0-1): ";
			}
		}
		switch (choice)
		{
		case 0:
			Avtorizate();
			break;
		case 1:
			menu();
		default:
			break;
		}
	}
	cout << "Введите пароль: ";
	while (true) {
		getline(cin, pass);
		bool validInput = true;
		for (char c : pass) {
			if (!isalnum(c) || !isascii(c)) {
				validInput = false;
				break;
			}
		}
		if (pass.find(" ") == string::npos && validInput) {
			break;
		}
		else {
			cout << "Некоректный ввод, повторите попытку: ";
		}
	}
	file.clear();
	file.seekg(0, ios::beg);
	while (file >> Avname >> Avpass >> Avrole) {
		if (name == Avname)
		{
			if (pass == Avpass)
			{
				cout << "Вы авторизовались!!! Роль: " << Avrole << endl;
				if (Avrole == "Admin") {
					AvtAd = true;
					file.close();
					BanFile.close();
					Admin_menu();
				}
				else 
				{
					AvtUs = true;
					file.close();
					BanFile.close();
					User_Func();
				}
				file.close();
				BanFile.close();
				return;
			}
			else
			{
				cout << "Неверный пароль" << endl;
				cout << "0 - Авторизоваться заново\n1 - Вернуться в меню\nEnter: ";
				int choice = 0;
				string input;
				while (true) {
					getline(cin, input);
					if (input.find_first_not_of("0123456789") == string::npos) {
						choice = stoi(input);
						if (choice >= 0 && choice <= 1)
							break;
					}
					else {
						cout << "Введите целое число(0-1): ";
					}
				}
				switch (choice)
				{
				case 0:
					system("cls");
					Avtorizate();
					break;
				case 1:
					system("cls");
					menu();
				default:
					break;
				}
			}
		}
	}
	file.close();
	BanFile.close();
}