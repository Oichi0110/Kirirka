#pragma once
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <Windows.h>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <chrono>
using namespace std;

struct Prodd {
	string NameProd;
	int NumberWorkshop;
	string data;
	int day, month, year;
	string FullName;
	int QuantityProd;
};

struct SortProd {
	int BegDay, BegMonth, BegYear, EndDay, EndMonth, EndYear;
};

struct Date {
	string line;
	int day, month, year;
};

struct SortName {
	string name, line;
};

struct Number {
	string line;
	int day, month, year, quantity;
};

struct SortFullName {
	string line;
	int day, month, year;
	string FullName;
};

void Registrate();
void Avtorizate();
void User_Func();
void Admin_menu();
void menu();
void BanUser();
void DeleteAccount();
void GrantAdmin();
bool compare(const Date&, const Date&);
void DataProduction();
void NumberAllTime();
void NumberCertainPeriod();
void NumberCertainProd();
void NumberProd();
bool NumQuan(const Number&, const Number&);
void OutProdData();
int production();
bool Sname(const SortName&, const SortName&);
void SorNameProd();
void Sorted(vector<Date>&);
void AdmStats();
void UserStats();
bool isLeapYear(int year);
bool isValidDate(int day, int month, int year);
void inputDate(int& day, int& month, int& year);
bool isValidFullName(const string& fullName);
void PrintShopManager();
bool compareFull(const SortFullName&, const SortFullName&);
void unbanneduser();
void PrintInfoWorkShop();