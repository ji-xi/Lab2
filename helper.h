#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <vector>
#include <iterator>
#include <stdlib.h>
#include <functional>
#include <math.h>

#include "Decimal.h"
#include "date.h"

class  Customer {
public:

	std::string surname;
	std::string district;
	std::string address;
	std::string phone;
	int contract_number;
	Date begin_date;
	bool payment;
	dec::decimal<2> monthly_payment;
	Date date_of_pay;

	Customer(std::string _surname, std::string _district, std::string _address, std::string _phone,
		int _contract_number, Date _begin_date, bool _payment, dec::decimal<2> _monthly_payment, Date _date_of_pay) {
		surname = _surname;
		district = _district;
		address = _address;
		phone = _phone;
		contract_number = _contract_number;
		begin_date = _begin_date;
		payment = _payment;
		monthly_payment = _monthly_payment;
		date_of_pay = _date_of_pay;
	}

	Customer() {
		surname = "";
		district = "";
		address = "";
		phone = "";
		contract_number = 0;
		begin_date = Date();
		payment = true;
		monthly_payment = 0;
		date_of_pay = Date();
	}

	~Customer() {}
	bool operator==(const Customer& right) const {
		if ((this->surname == right.surname) && (this->district == right.district) &&
			(this->address == right.address) && (this->phone == right.phone) &&
			(this->contract_number == right.contract_number) && (this->monthly_payment == right.monthly_payment))
			return	true;
		else return false;
	}
};
bool check_monthly_payment(std::string price);

std::ostream& operator <<(std::ostream &os, const Customer &cust) {
	os << cust.surname + "\t" + 
		cust.district + "\t" + 
		cust.address + "\t" + 
		cust.phone + "\t" + 
		std::to_string(cust.contract_number) + "\t";
	os << cust.begin_date; os << "\t";
	if (cust.payment) { os << "+ \t"; } else { os << "- \t"; }
	os << dec::toString(cust.monthly_payment) + "\t";
	os << cust.date_of_pay; os << "\n";
	return os;
}

std::istream& operator>> (std::istream& is, Customer &cust) {
	std::string str1;
	std::string str2;

	is >> cust.surname;
	is >> cust.district;
	is >> cust.address;
	is >> cust.phone;
	is >> cust.contract_number;
	is >> str1;
	is >> str2;
	if (!(Date::str_to_date(str1 + " " + str2, cust.begin_date)))
		throw "Incorrect file";
	is >> str1; 
	if (str1 == "+") { cust.payment = true; }
	else if (str1 == "-") { cust.payment = false; }
		else throw "Incorrect file";
	dec::fromStream(is, cust.monthly_payment);
	if (!check_monthly_payment) throw "Incorrect file";
	is >> str1;
	is >> str2;
	if (!(Date::str_to_date(str1 + " " + str2, cust.date_of_pay)))
		throw "Incorrect file";
	return is;
}

//Predicats
class surname_pred {
protected:
	std::string str;
public:
	surname_pred(std::string s) {
		str = s;
	}
	bool virtual operator () (Customer cust) {
		return cust.surname == str;
	}
};

class district_pred {
protected:
	std::string str;
public:
	district_pred(std::string s) {
		str = s;
	}
	bool virtual operator () (Customer cust) {
		return cust.district == str;
	}
};

class begin_date_pred {
protected:
	Date date;
public:
	begin_date_pred(Date s) {
		date = s;
	}
	bool virtual operator () (Customer cust) {
		return cust.begin_date == date;
	}
};

class date_of_pay_pred {
protected:
	Date date;
public:
	date_of_pay_pred(Date s) {
		date = s;
	}
	bool virtual operator () (Customer cust) {
		return cust.date_of_pay == date;
	}
};

//Comparators
class surname_Òomp {
public:
	bool operator () (Customer cust1, Customer cust2) {
		return cust1.surname < cust2.surname;
	}
};

class district_comp {
public:
	bool virtual operator () (Customer cust1, Customer cust2) {
		return cust1.district < cust2.district;
	}
};

class begin_date_comp {
public:
	bool virtual operator () (Customer cust1, Customer cust2) {
		return cust1.begin_date < cust2.begin_date;
	}
};

class date_of_pay_comp {
public:
	bool virtual operator () (Customer cust1, Customer cust2) {
		return cust1.date_of_pay < cust2.date_of_pay;
	}
};

//Accomulators
class surname_acc {
protected:
	std::string str;
	std::vector<Customer>* v;
public:
	surname_acc(std::string s) {
		str = s;
		v = new std::vector<Customer>();
	}
	std::vector<Customer> get_set() {
		return *v;
	}
	void virtual operator () (Customer cust) {
		if (cust.surname == str)
			(*v).push_back(cust);
	}
};

class district_acc {
protected:
	std::string str;
	std::vector<Customer>* v;
public:
	district_acc(std::string s) {
		str = s;
		v = new std::vector<Customer>();
	}
	std::vector<Customer> get_set() {
		return *v;
	}
	void virtual operator () (Customer cust) {
		if (cust.district == str)
			(*v).push_back(cust);
	}
};

class begin_date_acc {
protected:
	Date date;
	std::vector<Customer>* v;
public:
	begin_date_acc(Date d) {
		date = d;
		v = new std::vector<Customer>();
	}
	std::vector<Customer> get_set() {
		return *v;
	}
	void virtual operator () (Customer cust) {
		if (cust.begin_date == date)
			(*v).push_back(cust);
	}
};

class date_of_pay_acc {
protected:
	Date date;
	std::vector<Customer>* v;
public:
	date_of_pay_acc(Date d) {
		date = d;
		v = new std::vector<Customer>();
	}
	std::vector<Customer> get_set() {
		return *v;
	}
	void virtual operator () (Customer cust) {
		if (cust.date_of_pay == date)
			(*v).push_back(cust);
	}
};

template <class P>
class Abs—ontainer {
protected:
	std::vector<P> vect;
public:
	typedef std::_Vector_iterator<std::_Vector_val<std::_Simple_types<P>>> my_iterator;

	Abs—ontainer(int size) {
		vect = std::vector<P>(size);
	}

	Abs—ontainer() {
		vect = std::vector<P>();
	}

	~Abs—ontainer() {}

	bool add(P cust) {
		if (!find(cust))
		{
			vect.push_back(cust);
			return true;
		}
		else
			return false;
	}

	bool find(P cust, std::random_access_iterator_tag &it) {
		it = std::find(vect.begin(), vect.end(), cust);
		return it != vect.end()
	}
	
	bool find(P cust) {
		return std::find(vect.begin(), vect.end(), cust) != vect.end();
	}

	template<class Predicate>
	bool find_by(Predicate &pred, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<P>>> &it) {
		my_iterator tmpIt = std::find_if(vect.begin(), vect.end(), pred);
		if (tmpIt == vect.end())
			return false;
		it = tmpIt;
		return true;
	}

	template<class Comparator>
	bool find_by_binary(Comparator &comp, P &bibb, std::_Vector_iterator<std::_Vector_val<std::_Simple_types<P>>> &it) {
		if (vect.size() != 0){
			std::sort(vect.begin(), vect.end(), comp);
			my_iterator tmpIt = std::lower_bound(vect.begin(), vect.end(), bibb, comp);
			if (tmpIt == vect.end() && !comp(bibb, *tmpIt))
				return false;
			it = tmpIt;
			return true;
		}
		else return false;
	}

	template<class Accomulator>
	std::vector<P> find_subset_by(Accomulator acc) {
		std::for_each(vect.begin(), vect.end(), acc);
		return acc.get_set();
	}

	int size() { return vect.size(); }
	void clear() { vect.clear(); }
	void remove(my_iterator &it) { vect.erase(it); }
};

class —ontainer : public Abs—ontainer<Customer> {
public:

	—ontainer(std::vector<Customer> v) { vect = v; }

	—ontainer() { vect = std::vector<Customer>(); }

	bool find_by_surname(std::string sur, std::vector<Customer>::iterator &it) {
		return find_by(surname_pred(sur), it);
	}	
	
	bool find_by_district(std::string dist, std::vector<Customer>::iterator &it) {
		return find_by(district_pred(dist), it);
	}

	bool find_by_begin_date(Date date, std::vector<Customer>::iterator &it) {
		return find_by(begin_date_pred(date), it);
	}

	bool find_by_date_of_pay(Date date, std::vector<Customer>::iterator &it) {
		return find_by(date_of_pay_pred(date), it);
	}

	bool find_by_surname_b(std::string surname, std::vector<Customer>::iterator &it) {
		return find_by_binary(surname_Òomp(), Customer(surname, "", "", "", 0, Date(), false, dec::decimal_cast<2>(0), Date()), it) && it->surname == surname;
	}	
	
	bool find_by_district_b(std::string district, std::vector<Customer>::iterator &it) {
		return find_by_binary(district_comp(), Customer("", district, "", "", 0, Date(), false, dec::decimal_cast<2>(0), Date()), it) && it->district == district;
	}

	bool find_by_begin_date_b(Date date, std::vector<Customer>::iterator &it) {
		return find_by_binary(begin_date_comp(), Customer("", "", "", "", 0, date, false, dec::decimal_cast<2>(0), Date()), it) && it->begin_date == date;
	}

	bool find_by_date_of_pay_b(Date date, std::vector<Customer>::iterator &it) {
		return find_by_binary(date_of_pay_comp(), Customer("", "", "", "", 0, Date(), false, dec::decimal_cast<2>(0), date), it) && it->date_of_pay == date;
	}

	—ontainer find_subset_by_surname(std::string s) {
		return —ontainer(find_subset_by(surname_acc(s)));
	}

	—ontainer find_subset_by_district(std::string s) {
		return —ontainer(find_subset_by(district_acc(s)));
	}

	—ontainer find_subset_by_begin_date(Date d) {
		return —ontainer(find_subset_by(begin_date_acc(d)));
	}

	—ontainer find_subset_by_date_of_pay(Date d) {
		return —ontainer(find_subset_by(date_of_pay_acc(d)));
	}

	void file_input(std::fstream& fin) {
		if (fin.is_open()) {
			std::istream_iterator<Customer> is(fin);
			vect.clear();
			if (fin.eof()) return;
			Customer cust = *is++;
			while (!fin.eof()) {
				add(cust); 
				cust = *is++;
			}
			if (cust.surname != "") add(cust);
			fin.close();
		}
		else throw "File not found";
	}

	void file_output(std::fstream& fout) {
		if (fout.is_open()) 
			 {
			copy(vect.begin(), vect.end(), std::ostream_iterator<Customer>(fout, "\n"));
			fout.close();
		}
		else throw "File not found";
	}

	void output(std::ostream_iterator<Customer> os) {
		copy(vect.begin(), vect.end(), os);
	}
};

//Helpers
bool p_m(std::string str) {
	while (true) {
		std::string c;
		std::cout << str + " ";
		std::cin >> c;
		if (c == "skip") throw 's';
		if (c == "exit") throw "exit";
		if (c == "+") return(true);
		else
			if (c == "-") return(false);
			else std::cout << "Invalid command, try again (+/-)\n";
	}
}

int input_int(std::string message = "", int min = 0, int max = 10000) {
	std::string str;
	int res;
	while (true) {
		std::cout << message;
		try {
			std::cin >> str;
			if (str == "skip") throw 's';
			if (str == "exit") throw "exit";
			res = std::stoi(str);
			while (res < min || res > max) {
				std::cout << "Error (value < " << min << " or value > " << max << "), try again:";
				std::cin >> str;
				if (str == "exit") throw "exit";
				res = std::stoi(str);
			}
			return res;
		}
		catch (std::exception &e) {
			std::cout << "Invalid number \n" << std::endl;
		}
	}
}

Date input_date(std::string message = "Input date in format hh:mm dd/mm/yyyy : ") {
	Date date = Date();
	std::string buf1;
	std::string buf2;
	bool ok = false;
	while (!ok) {
		std::cout << message;
		std::cin >> buf1;
		if (buf1 == "skip") throw 's';
		if (buf1 == "exit") throw "exit";
		std::cin >> buf2;
		ok = Date::str_to_date(buf1 + " " + buf2, date);
		if (!ok)
			std::cout << "Invalid date\n";
	}
	return date;
}

bool check_monthly_payment(std::string price) {
	size_t i = 0;
	while ((i < price.length()) && ((price[i] == ' ') || (price[i] == '	'))) { ++i; }
	if (i >= price.length()) { return false; }

	switch (price[i]) {
	case '-': { return false; }
	case '+': { ++i; break; }
	default: { break; }
	}

	size_t j = i;
	bool result = j < price.length();
	int dot_number = 0;
	while ((j < price.length()) && (result)) {
		if (price[j] == '.') {
			++dot_number;
		}
		result = ((price[j] >= '0') && (price[j] <= '9')) || ((price[j] == '.') && (dot_number <= 1));
		++j;
	}
	while ((j < price.length()) && ((price[j] == ' ') || (price[j] == '	'))) { ++j; } // .1
	return (j == price.length()) && (result);
}

dec::decimal<2> input_monthly_payment(std::string message = "Input monthly payment: ", bool isAdd = true) {
	std::string tmp;
	dec::decimal<2> res;
	std::cout << message;
	bool ok = false;
	while (!ok) {
		std::cin >> tmp;
		if (tmp == "skip") throw 's';
		if (tmp == "exit") throw "exit";
		ok = check_monthly_payment(tmp);
		if (!ok) std::cout << "Invalid monthly payment, try again\n";
	}
	dec::fromString(tmp, res);
	return res;
}

Customer input_customer() {
	std::string surname, district, address, phone;
	int contract_number;
	Date begin_date, date_of_pay;
	bool payment;
	dec::decimal<2> monthly_payment;
	std::cout << "-------------Customer------------" << std::endl;
	std::cout << "Surname: ";
	std::cin >> surname;
	if (surname == "exit") throw "exit";
	std::cout << "District: ";
	std::cin >> district;
	if (district == "exit") throw "exit";
	std::cout << "Address: ";
	std::cin >> address;
	if (address == "exit") throw "exit";
	std::cout << "Phone number: ";
	std::cin >> phone;
	if (phone == "exit") throw "exit";
	bool ok = false;
	while (!ok) {
		try { contract_number = input_int("Contract number: "); ok = true; }
		catch (char) { std::cout << "You can't skip this: "; }
	}
	ok = false;
	while (!ok) {
		try { begin_date = input_date("Date of contract: "); ok = true; }
		catch (char) { std::cout << "You can't skip this: "; }
	}
	ok = false;
	while (!ok) {
		try { payment = p_m("Installation paid? (+/-)"); ok = true; }
		catch (char) { std::cout << "You can't skip this: "; }
	}
	ok = false;
	while (!ok) {
		try { monthly_payment = input_monthly_payment("Monthly payment: "); ok = true; }
		catch (char) { std::cout << "You can't skip this: "; }
	}
	ok = false;
	while (!ok) {
		try { date_of_pay = input_date("Date of last payment: "); ok = true; }
		catch (char) { std::cout << "You can't skip this: "; }
	}
	std::cout << "----------------------------------" << std::endl;
	return Customer(surname, district, address, phone, contract_number, begin_date, payment, monthly_payment, date_of_pay);
}

Customer input_customer(Customer cust) {
	std::string surname, district, address, phone;
	int contract_number;
	Date begin_date, date_of_pay;
	bool payment;
	dec::decimal<2> monthly_payment;
	std::string str;

	std::cout << "-------------Customer------------" << std::endl;
	std::cout << "Surname(dafault : " + cust.surname + "): ";
	std::cin >> surname;
	if (surname == "skip") surname = cust.surname;
	if (surname == "exit") throw "exit";

	std::cout << "District(dafault : " + cust.district + "): ";
	std::cin >> district;
	if (district == "skip") district = cust.district;
	if (district == "exit") throw "exit";

	std::cout << "Address(dafault : " + cust.address + "): ";
	std::cin >> address;
	if (address == "skip") address = cust.address;
	if (address == "exit") throw "exit";

	std::cout << "Phone number(dafault : " + cust.phone + "): ";
	std::cin >> phone;
	if (phone == "skip") phone = cust.phone;
	if (phone == "exit") throw "exit";

	try { contract_number = input_int("Contract number(dafault : " + std::to_string(cust.contract_number) + "): "); }
	catch (char) { contract_number = cust.contract_number; }

	std::string cur_date = cust.begin_date.to_string();
	try { begin_date = input_date("Enter date of contract in format(mm:hh  dd/mm/yyyy)(default : " + cur_date + ")"); }
	catch (char) { begin_date = cust.begin_date; }

	try { payment = p_m("Installation paid? (+/-)"); }
	catch (char) { payment = cust.payment; }

	try { monthly_payment = input_monthly_payment("Monthly payment: "); }
	catch (char) { monthly_payment = cust.monthly_payment; }
	cur_date = cust.date_of_pay.to_string();

	try { date_of_pay = input_date("Enter date of last payment in format(mm:hh  dd/mm/yyyy)(default : " + cur_date + ")"); }
	catch (char) { date_of_pay = cust.date_of_pay; }	
	std::cout << "----------------------------------" << std::endl;
	return Customer(surname, district, address, phone, contract_number, begin_date, payment, monthly_payment, date_of_pay);
}

static void print_head() {
	std::cout << "Surname\t" << "Dist\t" << "Address\t" << "Phone\t" << "Contract\t" << "Date of contract:\t" << "Paid\t" << "Payment\t" << "Last payment\n";
}

void console_input(—ontainer& cont) {
	cont.clear();
	Customer cust;
	bool add = true;
	while (add) {
		try {
			cust = input_customer();
		}
		catch (const char* str) {
			return;
		}
		cont.add(cust);
		add = p_m("Add more? (+/-)");
	}
}

void console_output(—ontainer& cont) {
	if (cont.size() != 0) {
		print_head();
		cont.output(std::ostream_iterator<Customer>(std::cout, "\n"));
	}
	else {
		std::cout << "Empty \n";
	}
}