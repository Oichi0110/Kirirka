#include "Header.h"

void User_Func(){
	int choice = 0;
	system("cls");
	do {
		cout << "Функционал Пользователя: " << endl;
		cout << "[1] Ввод данных о производимой продукции" << endl;
		cout << "[2] Вывод данных за определенный период времени" << endl;
		cout << "[3] Вывод отсортированных данных по наименевонаию" << endl;
		cout << "[4] Просмотр количества произведенной продукции" << endl;
		cout << "[5] Вывод данных определенного заведующего цехам" << endl;
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
				cout << "Введите целое число(1-6): ";
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
		case 7:
			cout << "Закрытие программы" << endl;
			exit(0);
			break;
		default:
			cout << "Введите корректное значение" << endl;
			break;
		}
	} while (choice != 7);
} 