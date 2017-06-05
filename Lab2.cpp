// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "helper.h"

// Харченко Евгения Андреевна
// 13 - Список абонентов кабельной сети состоит из структур с полями: фамилия, район, адрес, телефон, 
// номер договора, дата заключения договора, оплата установки, абонентская плата помесячно, дата 
// последнего платежа. Поиск по фамилии, району, дате заключения договора, дате последнего платежа. 

void print_menu() {
	std::cout << "________________________________________________________" << std::endl;
	std::cout << "Menu:" << std::endl;
	std::cout << " 1. Input" << std::endl;
	std::cout << " 2. Output" << std::endl;
	std::cout << " 3. Find" << std::endl;
	std::cout << " 4. Add" << std::endl;
	std::cout << " 5. Subset" << std::endl;
	std::cout << " 0. Exit" << std::endl;
	std::cout << "________________________________________________________" << std::endl;
}

void print_console_file_menu() {
	std::cout << "-------------------------------" << std::endl;
	std::cout << " 1. Console" << std::endl;
	std::cout << " 2. File" << std::endl;
	std::cout << " 0. Cancel" << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

void print_find_menu() {
	std::cout << "-------------------------------" << std::endl;
	std::cout << " 1. By surname" << std::endl;
	std::cout << " 2. By district" << std::endl;
	std::cout << " 3. By date of contract" << std::endl;
	std::cout << " 4. By date of last payment" << std::endl;
	std::cout << " 0. Cancel" << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

void print_search_menu() {
	std::cout << "-------------------------------" << std::endl;
	std::cout << " 1. Simple search" << std::endl;
	std::cout << " 2. Binary search" << std::endl;
	std::cout << " 0. Cancel" << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

void print_action_menu() {
	std::cout << "-------------------------------" << std::endl;
	std::cout << " 1. Print" << std::endl;
	std::cout << " 2. Change" << std::endl;
	std::cout << " 3. Delete" << std::endl;
	std::cout << " 0. Exit" << std::endl;
	std::cout << "-------------------------------" << std::endl;
}

std::string input_file_name() {
	std::string name;
	std::cout << "Input file name(without extension): " << std::endl;
	std::getline(std::cin, name);
	std::getline(std::cin, name);
	if (name == "") name = "testfile";
	return name + ".txt";
}

int main() {
	Сontainer cont = Сontainer();
	Сontainer sub = Сontainer();
	std::string str;
	int n;
	bool binarSearch;
	bool found = false;
	std::string FName;
	std::_Vector_iterator<std::_Vector_val<std::_Simple_types<Customer>>> it;

	while (true) {
		print_menu();
		n = input_int("Enter the command: ", 0, 5);
		switch (n) {
		case 1://INPUT
			print_console_file_menu();
			n = input_int("Enter the command: ", 0, 2);
			switch (n) {
			case 1://Console
				console_input(cont);
				break;
			case 2://File
				try {
					FName = input_file_name();
					cont.file_input(std::fstream(FName, std::ios::in));
				}
				catch (const char* str) { std::cout << str << std::endl; }
				break;
			case 0: break;
			}
			break;

		case 2://OUTPUT
			print_console_file_menu();
			n = input_int("Enter the command:", 0, 2);
			switch (n) {
			case 1://Console
				console_output(cont);
				break;
			case 2://File
				try {
				FName = input_file_name();
				cont.file_output(std::fstream(FName, std::ios::out));
				}
				catch (const char* str) { std::cout << str << std::endl; }
				break;
			case 0: break;
			}
			break;

		case 3://FIND
			print_search_menu();
			n = input_int("Enter the command: ", 0, 2);
			if (n == 0) break;
			switch (n) {
			case 1://Simple
				binarSearch = false;
				break;
			case 2://Binary
				binarSearch = true;
				break;
			}
			print_find_menu();
			n = input_int("Enter the command: ", 0, 4);
			bool ok;
			switch (n) {
			case 1: //Surname
				std::cout << "Surname: ";
				std::cin >> str;
				if (binarSearch)
					found = cont.find_by_surname_b(str, it);
				else
					found = cont.find_by_surname(str, it);
				break;
			case 2: //District
				std::cout << "District: ";
				std::cin >> str;
				if (binarSearch)
					found = cont.find_by_district_b(str, it);
				else
					found = cont.find_by_district(str, it);
				break;

			case 3://Begin date
				if (binarSearch) {
					ok = false;
					while (!ok) {
						try { found = cont.find_by_begin_date_b(input_date(), it); ok = true; }
						catch (char) { std::cout << "You can't skip this: "; }
					}
				}
				else {
					ok = false;
					while (!ok) {
						try { found = cont.find_by_begin_date(input_date(), it); ok = true; }
						catch (char) { std::cout << "You can't skip this: "; }
					}
				}
				break;
			case 4://Date of pay
				if (binarSearch) {
					ok = false;
					while (!ok) {
						try { found = cont.find_by_date_of_pay_b(input_date(), it); ok = true; }
						catch (char) { std::cout << "You can't skip this: "; }
					}
				}
				else {
					ok = false;
					while (!ok) {
						try { found = cont.find_by_date_of_pay(input_date(), it); ok = true; }
						catch (char) { std::cout << "You can't skip this: "; }
					}
				}
				break;
			case 0: break;
			}
			if (found) {
				while (true) {
					std::cout << "\n Record found \n";
					print_action_menu();
					n = input_int("Enter the command: ", 0, 3);
					if (n == 0) break;
					switch (n) {
					case 1: //Console
						std::cout << *(it);
						break;
					case 2: //Change
						try {
							*it = input_customer(*it);
							break;
						}
						catch (const char* str) { break; }
					case 3: //Delete
						cont.remove(it);
						break;
					}
					if (n == 3) break;
				}
			}
			else
				std::cout << "Record not found \n";
			break;

		case 4://ADD
			try { cont.add(input_customer()); }
			catch (const char*) {}
			break;

		case 5://SUBSET
			print_find_menu();
			n = input_int("Enter the command: ", 1, 4);
			switch (n) {
			case 1://Surname
				std::cout << "Surname: ";
				std::cin >> str;
				sub = cont.find_subset_by_surname(str);
				break;
			case 2://District
				std::cout << "District: ";
				std::cin >> str;
				sub = cont.find_subset_by_district(str);
				break;
			case 3://Begin date
				std::cout << "Enter begin date in format(mm:hh  dd/mm/yyyy): ";
				ok = false;
				while (!ok) {
					try { sub = cont.find_subset_by_begin_date(input_date()); ok = true; }
					catch (char) { std::cout << "You can't skip this: "; }
				}
				break;
			case 4://Date of pay
				std::cout << "Enter date of pay in format(mm:hh  dd/mm/yyyy): ";
				ok = false;
				while (!ok) {
					try { sub = cont.find_subset_by_date_of_pay(input_date()); ok = true; }
					catch (char) { std::cout << "You can't skip this: "; }
				}
				break;
			}
			if (sub.size() == 0) {
				std::cout << "Subset is empty" << std::endl;
				break;
			}
			else { std::cout << std::endl << sub.size() << " records found" << std::endl; }
			print_console_file_menu();
			n = input_int("Enter the command: ", 0, 2);
			switch (n) {
			case 1://Console
				console_output(sub);
				break;
			case 2://File
				FName = input_file_name();
				sub.file_output(std::fstream(FName, std::ios::out));
				break;
			case 0: break;
			}
			break;

		case 0://EXIT
			return 0;
		}
	}
}

