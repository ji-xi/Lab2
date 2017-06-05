#include "stdafx.h"
#include "Date.h"
#include <fstream>
#include <iostream>
#include <vector>


std::vector<std::string> split(const std::string &text, char sep) {
	std::vector<std::string> tokens;
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != std::string::npos) {
		if (end != start) {
			tokens.push_back(text.substr(start, end - start));
		}
		start = end + 1;
	}
	if (end != start) {
		tokens.push_back(text.substr(start));
	}
	return tokens;
}

bool check_date(std::string date) {
	if (date == " ")
		return false;

	std::vector<std::string> tokens = split(date, ' ');
	std::vector<std::string> tokens2 = split(tokens[1], '/');
	std::vector<std::string> tokens1 = split(tokens[0], ':');
	if (tokens1.size() != 2 || tokens2.size() != 3) return false;
	try {
		int year = std::stoi(tokens2[2]);
		if (year < 1900 || year > 2017) return false;

		int month = std::stoi(tokens2[1]);
		if (month < 1 || month > 12) return false;

		int day = std::stoi(tokens2[0]);
		if (day < 1 || day > Date::max_day_number(year, month)) return false;

		int hour = std::stoi(tokens1[0]);
		if (hour < 0 || hour > 23) return false;

		int min = std::stoi(tokens1[1]);
		if (min < 0 || min > 59) return false;
	}
	catch (...) {
		return false;
	}
	return true;
}


Date::Date() {
	year = 1900;
	month = 1;
	day = 1;
	hour = 0;
	min = 0;
}

Date::Date(const Date & date) {
	year = date.year;
	month = date.month;
	day = date.day;
	hour = date.hour;
	min = date.min;
}

Date::Date(int min, int hour, int day, int month, int year) {
	int max_day;
	this->year = year;
	if ((month < 1) || (month > 12)) {
		throw std::out_of_range("Неправильно введен месяц (от 1 до 12)");
	}
	this->month = month;

	max_day = max_day_number(year, month);

	if ((day < 1) || (day > max_day)) {
		throw std::out_of_range("Неправильно введен день (от 1 до " + std::to_string(max_day) + ")");
	}
	this->day = day;

	if ((hour < 0) || (hour > 23)) {
		throw std::out_of_range("Неправильно введены часы (от 0 до 23)");
	}
	this->hour = hour;

	if ((min < 0) || (min > 59)) {
		throw std::out_of_range("Неправильно введены минуты (от 0 до 59)");
	}
	this->min = min;
}

std::string const Date::to_string() {
	return   std::to_string(hour) + ':' + std::to_string(min) +
		' ' + std::to_string(day) + '/' + std::to_string(month) + '/' + std::to_string(year);
}

std::string static to_string(Date date) {
	return   std::to_string(date.hour) + ':' + std::to_string(date.min) +
		' ' + std::to_string(date.day) + '/' + std::to_string(date.month) + '/' + std::to_string(date.year);
}

bool Date::str_to_date(std::string str, Date & date) {
	if (!check_date(str))
		return false;

	std::vector<std::string> tokens = split(str, ' ');
	std::vector<std::string> tokens1 = split(tokens[1], '/');
	std::vector<std::string> tokens2 = split(tokens[0], ':');

	try {
		date.min = std::stoi(tokens2[1]);
	}
	catch (std::exception e) {
		return false;
	}

	try {
		date.hour = std::stoi(tokens2[0]);
	}
	catch (std::exception e) {
		return false;
	}

	try {
		date.day = std::stoi(tokens1[0]);
	}
	catch (std::exception e) {
		return false;
	}

	try {
		date.month = std::stoi(tokens1[1]);
	}
	catch (std::exception e) {
		return false;
	}

	try {
		date.year = std::stoi(tokens1[2]);
	}
	catch (std::exception e) {
		return false;
	}

	return true;
}

int Date::max_day_number(int year, int month) {
	if ((month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) || (month == 10) || (month == 12)) {
		return 31;
	}
	else if (month == 2) {
		if ((((year % 4) == 0) && ((year % 100) != 0)) || ((year % 400) == 0)) {
			return 29;
		}
		else {
			return 28;
		}
	}
	else {
		return 30;
	}
}

bool Date::operator<(Date date) {
	if (year != date.year) {
		return year < date.year;
	}

	if (month != date.month) {
		return month < date.month;
	}

	if (day != date.day) {
		return day < date.day;
	}

	if (hour != date.hour) {
		return hour < date.hour;
	}

	if (min != date.min) {
		return min < date.min;
	}

	return false;
}

Date & Date::operator=(Date date) {
	year = date.year;
	month = date.month;
	day = date.day;
	hour = date.hour;
	min = date.min;
	return *this;
}

bool Date::operator==(Date date) {
	return (year == date.year) && (month == date.month) &&
		(day == date.day) && (hour == date.hour) && (min == date.min);
}

Date::~Date() {
}

std::ostream& operator<<(std::ostream& cout, Date date) {
	cout << date.to_string();
	return cout;
}

std::istream& operator>>(std::istream& cin, Date date) {
	std::string buf1;
	std::string buf2;
	bool ok = false;
	while (!ok)
	{
		cin >> buf1;
		cin >> buf2;
		ok = Date::str_to_date(buf1 + " " + buf2, date);
		if (!ok)
			std::cout << "Неправильная дата";
	}
	return cin;
}