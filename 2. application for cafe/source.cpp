#include <iostream>
#include <fstream>
#include <string>
#include <regex>   	// -std=c++11 or -std=gnu++11
#include <cstdlib>	// atof, atoi
#include <ctime>
#include <map>
#include <utility> 	// pair
#include <vector>
#include <algorithm> 	// std::sort

// #define DIR_INFO_FILES "./info_files/"
// #define DIR_REPORTS_FILES "./reports/"

#define DIR_INFO_FILES ".\\info_files\\"
#define DIR_REPORTS_FILES ".\\reports\\"

using namespace std;

//############################################
// ХРАНЕНИЕ ДАННЫХ
//############################################

class UnitCategoryMenu {
	private:
		string name;
		double cost;
		double discountDishDay;
	public:
		UnitCategoryMenu () {}
		UnitCategoryMenu (string name, double cost, double discountDishDay) {
			this->name = name;
			this->cost = cost;
			this->discountDishDay = discountDishDay;
			}
		string getName () const { return name; }
		double getCost () const { return cost; }
		double getDiscountDishDay () const { return discountDishDay; }
	};

class CategoryMenu {
	private:
		string category;
		bool birthday;
		vector <UnitCategoryMenu> catalogDish;
	public:
		CategoryMenu () {}
		CategoryMenu (string category, bool birthday, const vector <string> &vline) {
			this->category = category;
			this->birthday = birthday;
			regex rgCatalogDish ("\\s*(.+?)\\s+=+\\s+(\\d+),{1}(\\d{2})\\s*(\\d*),?(\\d{0,2})%?");
			cmatch cmCatalogDish;
			string cost, discount;
			for (size_t i = 0, len = vline.size (); i != len; ++i) {
				if (!regex_search (vline[i].c_str (), cmCatalogDish, rgCatalogDish))
					continue;
				cost = cmCatalogDish[2]; cost += '.'; cost += cmCatalogDish[3];
				discount = cmCatalogDish[4]; discount += '.'; discount += cmCatalogDish[5];
				catalogDish.push_back (UnitCategoryMenu (cmCatalogDish[1], atof (cost.c_str ()), atof (discount.c_str ())));
				}
			}
	public:
		string getMenuCategory () const { return category; }
		bool getBirthdayMenu () const { return birthday; }
		int sizeMenuCatalogDish ()  const { return catalogDish.size(); }
		UnitCategoryMenu getMenuCatalogDish (int unit) const {
			if (unit < catalogDish.size() && unit >= 0)
				return catalogDish[unit];
			}
	public:
		void printMenu () const {
			cout << category;
			if (birthday == true)
				cout << " #именинник";
			cout << endl;
			for (size_t i = 0, len = catalogDish.size(); i != len; ++i)
				cout << "   " << catalogDish[i].getName() << ": " << catalogDish[i].getCost()
					 << " " << catalogDish[i].getDiscountDishDay() << "%" << endl;			
			}
	};

class Menu {
	private:
		vector <CategoryMenu> menu;
	public:
		void addNewMenuCategory (string category, bool birthday, const vector <string> &vline) {
			menu.push_back (CategoryMenu (category, birthday, vline));
			}
		void clearMenu () { menu.clear (); }
		int sizeMenu () const { return menu.size (); }
		const CategoryMenu &operator[] (int numberMenuCategory) const {
			if (numberMenuCategory < menu.size() && numberMenuCategory >= 0)
				return menu[numberMenuCategory];
			}
		int countMenuDishes () const { 
			int x = 0;
			for (size_t i = 0, len_i = menu.size (); i != len_i; ++i)
				for (size_t j = 0, len_j = menu[i].sizeMenuCatalogDish (); j != len_j; ++j, ++x);
			return x;
			 }
		UnitCategoryMenu getMenuDish (int unit) const {
			for (size_t i = 0, x = 0, len_i = menu.size (); i != len_i; ++i)
				for (size_t j = 0, len_j = menu[i].sizeMenuCatalogDish (); j != len_j; ++j, ++x)
					if (x == unit && unit >= 0)
						return menu[i].getMenuCatalogDish(j);
			}
		double getMenuPrice (string name) const {
			for (size_t i = 0, len_i = menu.size (); i != len_i; ++i)
				for (size_t j = 0, len_j = menu[i].sizeMenuCatalogDish (); j != len_j; ++j)
					if (menu[i].getMenuCatalogDish(j).getName() == name)
						return menu[i].getMenuCatalogDish(j).getCost();
			return 0;
			}
	};

class Discount;

class UnitOrder {
	private:
		string name;
		int number;
	public:
		UnitOrder () {}
		UnitOrder (string name, int number) {
			this->name = name;
			this->number = number;
			}
		string getName () const { return name; }
		int getNumber () const { return number; }
	};

class Order {
	private:
		int numberOrder;
		string time;
		bool birthday;
		vector <UnitOrder> catalogDish;
		double totalCost;
		Discount *discountType;
	public:
		Order () {}
		Order (int numberOrder, string time, bool birthday, const vector <string> &vline, double totalCost) {
			this->numberOrder = numberOrder;
			this->time = time;
			this->birthday = birthday;
			regex rgCatalogDish ("\\s*(.+?)\\s+=+\\s+(\\d+)");
			cmatch cmCatalogDish;
			string number;
			for (size_t i = 0, len = vline.size (); i != len; ++i) {
				if (!regex_search (vline[i].c_str (), cmCatalogDish, rgCatalogDish))
					continue;
				number = cmCatalogDish[2];
				catalogDish.push_back (UnitOrder (cmCatalogDish[1], atoi (number.c_str ())));
				}
			this->totalCost = totalCost;
			discountType = NULL;
			}
//		~Order () {
//			if (discountType != NULL) {
//				delete discountType;
//				discountType = NULL;
//				}
//			}
		~Order ();
		void setDiscountType (Discount *type) { 
			if (discountType == NULL)
				discountType = type;
			else
				cout << "ERROR: DiscountType is not empty\n\n";
			}
	public:
		int getNumberOrder () const { return numberOrder; }
		string getTimeOrder () const { return time; }
		bool getBirthdayOrder () const { return birthday; }
		int sizeOrderCatalogDish () const { return catalogDish.size(); }
		UnitOrder getOrderCatalogDish (int unit) const {
			if (unit < catalogDish.size() && unit >= 0)
				return catalogDish[unit];
			}
		double getOrderTotalCost () const { return totalCost; }
		Discount *getDiscountType () const {
			if (discountType != NULL)
				return discountType; 
			else
				cout << "ERROR: DiscountType is not found\n\n";
				}
	public:
		double calculationCost (const Menu &menu) const {
			double sum = 0;
			for (size_t i = 0, len = catalogDish.size (); i != len; ++i)
				sum += menu.getMenuPrice (catalogDish[i].getName()) * catalogDish[i].getNumber();
			return sum;
			}
//		double colculationCostDiscount (const Menu &menu) const {
//			if (discountType != NULL)
//				return calculationCost(menu) - discountType->getTotalDiscount();
//			else
//				return calculationCost(menu);
//			}
//		double colculationPercentDiscount (const Menu &menu) const {
//			if (discountType != NULL)
//				return (calculationCost(menu) / 100) * discountType->getTotalDiscount();
//			else
//				return 0;
//			}
		double colculationCostDiscount (const Menu &menu) const;
		double colculationPercentDiscount (const Menu &menu) const;
	public:
		void printOrder () const {
			cout << "Номер заказа: " << numberOrder << endl;
			cout << "Время заказа: " << time << endl;
			cout << "Именинник: " << birthday << endl;
			cout << "Заказ: " << endl;
			for (size_t i = 0, len = catalogDish.size(); i != len; ++i)
				cout << "   " << catalogDish[i].getName() << ": " << catalogDish[i].getNumber() << endl;
			cout << "Сумма к оплате: " << totalCost << "\n\n";
			}
	};

class Orders {
	private:
		vector <Order> orders;
	public:
		void addNewOrder (int numberOrder, string time, bool birthday, const vector <string> &vline, double totalCost) {
			orders.push_back (Order (numberOrder, time, birthday, vline, totalCost));
			}
		void clearOrders () { orders.clear (); }
		int sizeOrders () const { return orders.size (); }
		const Order &operator[] (int numberVOrder) const {
			if (numberVOrder < orders.size() && numberVOrder >= 0)
				return orders[numberVOrder];
			}
		Order &operator[] (int numberVOrder) {
			if (numberVOrder < orders.size() && numberVOrder >= 0)
				return orders[numberVOrder];
			}
		int countOrderDishes () const { 
			int x = 0;
			for (size_t i = 0, len_i = orders.size (); i != len_i; ++i)
				for (size_t j = 0, len_j = orders[i].sizeOrderCatalogDish (); j != len_j; ++j, ++x);
			return x;
			}
		UnitOrder getOrderDish (int unit) const {
			for (size_t i = 0, x = 0, len_i = orders.size (); i != len_i; ++i)
				for (size_t j = 0, len_j = orders[i].sizeOrderCatalogDish (); j != len_j; ++j, ++x)
					if (x == unit && unit >= 0)
						return orders[i].getOrderCatalogDish(j);
			}
	};

//############################################
// ОБРАБОТКА ОШИБОК
//############################################
class Errors {
	private:
		string numberInMonth (int number) {
			switch (number) {
				case 1 :
					return "January";
				case 2 :
					return "February";
				case 3 :
					return "March";
				case 4 :
					return "April";
				case 5 :
					return "May";
				case 6 :
					return "June";
				case 7 :
					return "July";
				case 8 :
					return "August";
				case 9 :
					return "September";
				case 10 :
					return "October";
				case 11 :
					return "November";
				case 12 :
					return "December";
				}
			}
	public: //ФАЙЛ
		int errorFileNotFound (const ifstream &fin, string fname) { //наличие файла
			if (!fin) {
				cout << endl << "ERROR: File " << fname << " not found" << endl << endl;
				return 1;
				}
			else return 0;
			}
		int errorFileData (const string &sdata, string fname) { //наличие данных
			if (sdata.empty ()) {
				cout << endl << "ERROR: No data in the file " << fname << endl << endl;
				return 1;
				}
			else return 0;
			}
	public: //DATA
		void errorUnknownDish (const multimap <string, int> &kitchen, const Orders &orders, const Menu &menu, string date) { //неопознанные блюда
			for (multimap <string, int>::const_iterator it = kitchen.begin (); it != kitchen.end (); ++it)
				if (!menu.getMenuPrice (it->first))
					cout << endl << "ERROR: In kitchen-" << date << " unknown dish: " + it->first << endl << endl;
			for (size_t i = 0, len = orders.countOrderDishes (); i != len; ++i)
				if (!menu.getMenuPrice (orders.getOrderDish(i).getName()))
					cout << endl << "ERROR: In orders-" << date << " unknown dish: " + orders.getOrderDish(i).getName() << endl << endl;
			}
	public: //DATE
		int errorDate (int yyyy, int mm, int dd) {
			if (yyyy < 1) {
				cout << endl << "ERROR: Incorrect year : " << yyyy << endl << endl;
				return 1;
				}
			if (mm == 1 || mm == 3 || mm == 5 || mm == 7 || 
			mm == 8 || mm == 10 || mm == 12) { // 31 день
				if (dd > 31 || dd < 1) {
					cout << endl << "ERROR: Incorrect number of days in a month: " << numberInMonth(mm) << endl << endl;
					return 1;
					}
				}
			else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) { // 30 дней
				if (dd > 30 || dd < 1) {
					cout << endl << "ERROR: Incorrect number of days in a month: " << numberInMonth(mm) << endl << endl;
					return 1;
					}
				}
			else if (mm == 2) { // февраль
				if (yyyy % 4 == 0 && yyyy % 100 != 0 || yyyy % 400 == 0) { //високосный год
					if (dd > 29 || dd < 1) {
						cout << endl << "ERROR: Incorrect number of days in a month: " << numberInMonth(mm) << endl << endl;
						return 1;
						}
					}
				else { //не високосный год
					if (dd > 28 || dd < 1) {
						cout << endl << "ERROR: Incorrect number of days in a month: " << numberInMonth(mm) << endl << endl;
						return 1;
						}
					}
				}
			else {
				cout << endl << "ERROR: Incorrect number of months: " << mm << endl << endl;
				return 1;
				}
			return 0;
			}
	};

//############################################
// ВВОД-ВЫВОД
//############################################
class InputFile {
	private:
		Errors error;
	private: // KITCHEN
		int inputFileKitchen (multimap <string, int> &kitchen, string date) {
			kitchen.clear ();
			date = "kitchen-" + date;
			date = DIR_INFO_FILES + date + ".txt";
			ifstream fin (date.c_str ());
			if (error.errorFileNotFound (fin, "kitchen"))
				return 1;
			string line, number;
			regex rgCatalogDish ("\\s*(.+?)\\s+=+\\s+(\\d+)");
			cmatch cmCatalogDish;
			while (getline (fin, line)) {
				if (!regex_search (line.c_str (), cmCatalogDish, rgCatalogDish))
					continue;
				number = cmCatalogDish[2];
				kitchen.insert (make_pair (cmCatalogDish[1], atoi (number.c_str ())));
				}
			fin.close ();
			if (error.errorFileData (number, "kitchen"))
				return 1;
			return 0;
			}
	private: //ORDERS
		int inputFileOrders (Orders &orders, string date) {
			orders.clearOrders ();
			date = "orders-" + date;
			date = DIR_INFO_FILES + date + ".txt";
			ifstream fin (date.c_str ());
			if (error.errorFileNotFound (fin, "orders")) return 1;
			bool bufBirthday = false;
			string line, bufNumberOrder, bufTotalCost, bufTime;
			vector <string> vline;
			regex rgOrder ("Заказ №(\\d+)\\s+(\\d{2}:{1}\\d{2})\\s*(.*)"), rgTotal ("итого: (\\d+),?(\\d{0,2})");
			cmatch match;
			while (getline (fin, line)) {
				if (regex_search (line.c_str (), match, rgOrder)) {
					bufTime = match[2];
					if (match[3] == "именинник")
						bufBirthday = true;
					bufNumberOrder = match[1];
					continue;
					}
				if (regex_search (line.c_str (), match, rgTotal)) {
					bufTotalCost = match[1]; bufTotalCost += '.'; bufTotalCost += match[2];
					orders.addNewOrder (atoi (bufNumberOrder.c_str ()), bufTime, bufBirthday, vline, atof (bufTotalCost.c_str ()));
					bufBirthday = false;
					vline.clear ();
					continue;
					}
				vline.push_back (line);
				}
			fin.close ();
			if (error.errorFileData (bufNumberOrder, "orders")) return 1;
			return 0;
			}
	private: //MENU
		int inputFileMenu (Menu &menu, string date) {
			menu.clearMenu ();
			date = "menu-" + date;
			date = DIR_INFO_FILES + date + ".txt";
			ifstream fin (date.c_str ());
			if (error.errorFileNotFound (fin, "menu")) { return 1; }
			bool bufBirthday = false;
			map <int, string> mCtgr;
			map <int, string>::iterator itMCtgr;
			map <string, int> hashtag;
			map <string, int>::iterator itHashtag;
			string line, bufCtgr, bufSubCtgr;
			vector <string> dishes;
			regex rgCatalogDish ("\\s*.+?\\s+=+\\s+\\d+"), rgCtgr ("(\\s*)(.+)"), rgHashtag ("(.+?)\\s+#+(.+)");
			cmatch cmCtgr, cmHashtag;
			while (getline (fin, line)) {
				if (!regex_search (line.c_str (), rgCatalogDish) && regex_search (line.c_str (), cmCtgr, rgCtgr)) {
/*3*/				if (dishes.size ()) {
						bufCtgr.clear ();
						for (itMCtgr = mCtgr.begin(); itMCtgr != mCtgr.end(); ++itMCtgr)
							bufCtgr += itMCtgr->second;
						menu.addNewMenuCategory (bufCtgr, bufBirthday, dishes);
						dishes.clear ();
						}
/*1*/				if (!dishes.size ()) {
						for (itHashtag = hashtag.begin(); itHashtag != hashtag.end(); ++itHashtag) //очищаем ненужные хештеги
							if (itHashtag->second >= cmCtgr[1].length())
								hashtag.erase (itHashtag);
						for (itMCtgr = mCtgr.begin(); itMCtgr != mCtgr.end(); ++itMCtgr) //очищаем ненужную вложенность
							if (itMCtgr->first > cmCtgr[1].length())
								mCtgr.erase (itMCtgr);
						bufSubCtgr = cmCtgr[2];
						if (regex_search (bufSubCtgr.c_str (), cmHashtag, rgHashtag)) { //отделить категорию от хештега
							bufSubCtgr = cmHashtag[1];
							hashtag[cmHashtag[2]] = cmCtgr[1].length();
							}
						mCtgr[cmCtgr[1].length()] = "[" + bufSubCtgr + "]";
						bufBirthday = false;
						for (itHashtag = hashtag.begin(); itHashtag != hashtag.end(); ++itHashtag)
							if (itHashtag->first == "именинник")
								bufBirthday = true;
						}
					}
/*2*/			else
					dishes.push_back (line);
				}
			if (error.errorFileData (bufSubCtgr, "menu")) { return 1; }
			else { menu.addNewMenuCategory ("[" + bufSubCtgr + "]", bufBirthday, dishes); }
			fin.close ();
			return 0;
			}
	public:
		InputFile (multimap <string, int> &kitchen, Orders &orders, Menu &menu, string date) {
			if (inputFileKitchen (kitchen, date) || inputFileOrders (orders, date) || inputFileMenu (menu, date))
				return;
			error.errorUnknownDish (kitchen, orders, menu, date);
			}
		InputFile (Menu &menu, string date) {
			if (inputFileMenu (menu, date))
				return;
			}
	};

class OutputFile {
	public:
		OutputFile (const vector <string> &input, string fileName) {
			fileName = DIR_REPORTS_FILES + fileName + ".txt";
			ofstream fout (fileName.c_str());
			for (size_t i = 0, len = input.size(); i != len; ++i)
				fout << input[i] << endl;
			fout.close ();
			}
	};

//############################################
// ДАТА
//############################################
class Date {
	private:
		string date;
	private:
		Errors error;
	private:
		void dateIntInString (int yyyy, int mm, int dd) {
			stringstream str;
			str << yyyy;
			if (mm < 10) 
				str << 0 << mm;
			else 
				str << mm;
			if (dd < 10) 
				str << 0 << dd;
			else 
				str << dd;
			str >> date;
			}
		int dateStringInInt (int &yyyy, int &mm, int &dd, string date) {
			if (!date.size())
				return 1;
			yyyy = atoi (date.substr(0, 4).c_str());
			mm = atoi (date.substr(4, 2).c_str());
			dd = atoi (date.substr(6, 2).c_str());
			if (error.errorDate (yyyy, mm, dd))
				return 1;
			return 0;
			}
	public:
		const Date operator++ () {
			int yyyy, mm, dd;
			dateStringInInt (yyyy, mm, dd, date);
			if (mm == 1 || mm == 3 || mm == 5 || mm == 7 || 
			mm == 8 || mm == 10 || mm == 12) // 31 день
				if (dd == 31)
					if (mm == 12) {
						++yyyy;
						mm = 1;
						dd = 1;
						}
					else {
						++mm;
						dd = 1;
						}
				else ++dd;
			else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) // 30 дней
				if (dd == 30) {
						++mm;
						dd = 1;
						}
				else ++dd;
			else if (mm == 2) // февраль
				if (yyyy % 4 == 0 && yyyy % 100 != 0 || yyyy % 400 == 0) //високосный год
					if (dd == 29) {
						++mm;
						dd = 1;
						}
					else ++dd;
				else //не високосный год
					if (dd == 28) {
						++mm;
						dd = 1;
						}
					else ++dd;
			dateIntInString (yyyy, mm, dd);
			return *this;
			}
	public:
		void inputDateFromString () {
			int yyyy, mm, dd;
			while (1) {
				cout << "Введите год: ";
				cin >> yyyy;
				cout << "Введите месяц (номер): ";
				cin >> mm;
				cout << "Введите день: ";
				cin >> dd;
				if (!(error.errorDate (yyyy, mm, dd))) {
					dateIntInString (yyyy, mm, dd);
					return;
					}
				}
			}
		void currentDate () { //текущая дата
			time_t t = time (NULL);
			tm *st = localtime(&t);
			dateIntInString (st->tm_year + 1900, st->tm_mon + 1, st->tm_mday);
			}
		int dateWeekAgo (string currentDate) { //дата 6 дней назад
			int yyyy, mm, dd;
			if (dateStringInInt (yyyy, mm, dd, currentDate))
				return 1;
			for (int i = 6; i != 0; --i) {
				if (dd == 1) {
					if (mm == 1) {
						--yyyy;
						mm = 12;
						}
					else --mm;
					if (mm == 1 || mm == 3 || mm == 5 || mm == 7 || 
					mm == 8 || mm == 10 || mm == 12) // 31 день
						dd = 31;
					else if (mm == 4 || mm == 6 || mm == 9 || mm == 11) // 30 дней
						dd = 30;
					else if (mm == 2) // февраль
						if (yyyy % 4 == 0 && yyyy % 100 != 0 || yyyy % 400 == 0) //високосный год
							dd = 29;
						else dd = 28; //не високосный год
					}
				else --dd;
				}
			dateIntInString (yyyy, mm, dd);
			return 0;
			}
		int compareDates (string currentDate) { //если date >= currentDate возвращает 1, иначе 0; -1 - если ошибка даты
			int yyyy1, mm1, dd1, 
				yyyy2, mm2, dd2;
			if (dateStringInInt (yyyy1, mm1, dd1, date) || dateStringInInt (yyyy2, mm2, dd2, currentDate)) 
				return -1;
			if (yyyy1 > yyyy2)
				return 1;
			if (yyyy1 == yyyy2) {
				if (mm1 > mm2)
					return 1;
				if (mm1 == mm2)
					if (dd1 >= dd2)
						return 1;
				}
			return 0;
			}
	public:
		string getDate () const { return date; }
	};

//############################################
// Discounts
//############################################
class Discount {
	public:
		virtual string getNameDiscountType (void) const = 0;
		virtual void calculationTotalDiscount (const Menu &menu, const Order &order) = 0;
		virtual double getTotalDiscount (void) const = 0;
	};

class DiscountDishDay : public Discount {
	private:
		string name;
		double totalDiscount;
	public:
		DiscountDishDay () : name ("Блюдо дня"), totalDiscount (0) {}
		string getNameDiscountType () const { return name; }
		void calculationTotalDiscount (const Menu &menu, const Order &order) {
			for (size_t i = 0, len_i = menu.countMenuDishes (); i != len_i; ++i)
				for (size_t j = 0, len_j = order.sizeOrderCatalogDish (); j != len_j; ++j)
					if (menu.getMenuDish(i).getName() == order.getOrderCatalogDish(j).getName())
						totalDiscount += order.getOrderCatalogDish(j).getNumber()
						* (menu.getMenuDish(i).getCost() * (menu.getMenuDish(i).getDiscountDishDay() / 100));
			}
		double getTotalDiscount () const { return totalDiscount; }
	};

class DiscountEvening : public Discount {
	private:
		string name;
		double totalDiscount;
	private:
		string time;
		double discount;
	public:
		DiscountEvening () : name ("Вечерняя"), totalDiscount (0), time ("21:00"), discount (10) {}
		DiscountEvening (string time, double discount) : name ("Вечерняя"), totalDiscount (0) {
			this->time = time;
			this->discount = discount;
			}
		string getNameDiscountType () const { return name; }
		void calculationTotalDiscount (const Menu &menu, const Order &order) {
			if (order.getTimeOrder () > time)
				totalDiscount = order.calculationCost(menu) * (discount / 100);
			}
		double getTotalDiscount () const { return totalDiscount; }
	};

class DiscountBirthday : public Discount {
	private:
		string name;
		double totalDiscount;
	private:
		double discount;
	public:
		DiscountBirthday () : name ("Именинник"), totalDiscount (0), discount (20) {}
		DiscountBirthday (double discount) : name ("Именинник"), totalDiscount (0) {
			this->discount = discount;
			}
		string getNameDiscountType () const { return name; }
		void calculationTotalDiscount (const Menu &menu, const Order &order) {
			if (!order.getBirthdayOrder ())
				return;
			for (size_t i = 0, len_i = menu.sizeMenu (); i != len_i; ++i)
				for (size_t j = 0, len_j = menu[i].sizeMenuCatalogDish (); j != len_j; ++j)
					if (menu[i].getBirthdayMenu())
						for (size_t k = 0, len_k = order.sizeOrderCatalogDish (); k != len_k; ++k)
							if (menu[i].getMenuCatalogDish(j).getName() == order.getOrderCatalogDish(k).getName())
								totalDiscount += order.getOrderCatalogDish(k).getNumber()
								* (menu[i].getMenuCatalogDish(j).getCost() * (discount / 100));
			}
		double getTotalDiscount () const { return totalDiscount; }
	};

class DiscountBigOrder : public Discount {
	private:
		string name;
		double totalDiscount;
	private:
		map <double, double> costAndDiscount;
	public:
		DiscountBigOrder () : name ("Большой заказ"), totalDiscount (0) {
			costAndDiscount[1500] = 5;
			costAndDiscount[2500] = 6;
			costAndDiscount[5000] = 8;
			}
		DiscountBigOrder (const map <double, double> &catalogCostAndDiscount) : name ("Большой заказ"), totalDiscount (0) {
			costAndDiscount[1500] = 5;
			costAndDiscount[2500] = 6;
			costAndDiscount[5000] = 8;
			for (map <double, double>::const_iterator it = catalogCostAndDiscount.begin (); it != catalogCostAndDiscount.end (); ++it)
				costAndDiscount[it->first] = it->second;
			}
		string getNameDiscountType () const { return name; }
		void calculationTotalDiscount (const Menu &menu, const Order &order) {
			for (map <double, double>::reverse_iterator it = costAndDiscount.rbegin (); it != costAndDiscount.rend (); ++it)
				if (it->first < order.calculationCost(menu)) {
					totalDiscount = order.calculationCost(menu) * (it->second / 100);
					break;
					}
			}
		double getTotalDiscount () const { return totalDiscount; }
	};

class DiscountPointersCompare { //функциональный объект
	public:
		bool operator () (const Discount* const &i, const Discount* const &j) {
			return (i->getTotalDiscount() <= j->getTotalDiscount());
			}
	};

//############################################
// Ввод Discounts в Order
//############################################
class InputDiscountOrders {
	public:
		InputDiscountOrders (Orders &orders, Menu &menu) {
			for (size_t i = 0, len_i = orders.sizeOrders (); i != len_i; ++i) {
				vector <Discount*> vDiscount;
				vDiscount.push_back (new DiscountDishDay);
				vDiscount.push_back (new DiscountEvening);
				vDiscount.push_back (new DiscountBirthday);
				vDiscount.push_back (new DiscountBigOrder);
			/*	vDiscount.push_back (new "New Discount Type");	*/
				for (size_t j = 0, len_j = vDiscount.size (); j != len_j; ++j)
					vDiscount[j]->calculationTotalDiscount(menu, orders[i]);
				sort (vDiscount.begin (), vDiscount.end(), DiscountPointersCompare());
				orders[i].setDiscountType (*vDiscount.rbegin());
				for (vector <Discount*>::reverse_iterator it = vDiscount.rbegin() + 1; it != vDiscount.rend (); ++it)
					delete *it;
				}
			}
	};

//(start)---------Order-----------------------
double Order::colculationCostDiscount (const Menu &menu) const {
	if (discountType != NULL)
		return calculationCost(menu) - discountType->getTotalDiscount();
	else
		return calculationCost(menu);
	}
double Order::colculationPercentDiscount (const Menu &menu) const {
	if (discountType != NULL)
		return (discountType->getTotalDiscount() * 100) / calculationCost(menu);
	else
		return 0;
	}
Order::~Order () {
	if (discountType != NULL) {
		delete discountType;
		discountType = NULL;
		}
	}
//(end)-----------Order----------------------

//############################################
// ОТЧЁТЫ
//############################################
class Report {
	public:
		virtual vector <string> getReport (void) const = 0;
	};

class ReportStolenDishes : Report {
	private:
		vector <pair <string, double>> stolenDishes;
	public:
		ReportStolenDishes () {}
		ReportStolenDishes (const multimap <string, int> &kitchen, const Orders &orders, Menu &menu) {
			for (size_t i = 0, len = menu.countMenuDishes (); i != len; ++i) {
				double kcount = 0, ocount = 0;
				for (multimap <string, int>::const_iterator it = kitchen.begin (); it != kitchen.end (); ++it) //подсчитали kitchen
					if (menu.getMenuDish(i).getName() == it->first)
						kcount += it->second;
				for (size_t j = 0, len = orders.countOrderDishes (); j != len; ++j) //подсчитали orders
					if (menu.getMenuDish(i).getName() == orders.getOrderDish(j).getName())
						ocount += orders.getOrderDish(j).getNumber();
				stolenDishes.push_back (make_pair (menu.getMenuDish(i).getName(), kcount - ocount));
				}
			double stolenRevenue = 0;
			for (size_t i = 0, len = stolenDishes.size (); i != len; ++i)
				stolenRevenue += menu.getMenuPrice (stolenDishes[i].first) * stolenDishes[i].second;
			stolenDishes.push_back (make_pair ("Stolen revenue", stolenRevenue));
			}
		const ReportStolenDishes &operator+= (const ReportStolenDishes &right) {
			if (this == &right)
				return *this;
			for (size_t i = 0, len_i = right.stolenDishes.size(); i != len_i; ++i) {
				bool flag = true;
				double buf = 0;
				for (size_t j = 0, len_j = this->stolenDishes.size(); j != len_j; ++j)
					if (right.stolenDishes[i].first == this->stolenDishes[j].first) {
						buf = right.stolenDishes[i].second + this->stolenDishes[j].second;
						this->stolenDishes.erase (this->stolenDishes.begin() + j);
						flag = false;
						this->stolenDishes.push_back (make_pair (right.stolenDishes[i].first, buf));
						break;
						}
				if (flag)
					this->stolenDishes.push_back (make_pair (right.stolenDishes[i].first, right.stolenDishes[i].second));
				}
			return *this;
			}
	public:
		vector <string> getReport () const {
			vector <string> sd;
			for (size_t i = 0, len = stolenDishes.size (); i != len; ++i) {
				stringstream str;
				string count;
				str << stolenDishes[i].second;
				str >> count;
				sd.push_back (stolenDishes[i].first + ": " + count);
				}
			return sd;
			}
	};

class ReportOrdersStatistics : Report {
	private:
		vector <pair <string, double>> ordersStat;
	private: //выручка
		double getReportTotalRevenue (const Orders &orders, const Menu &menu) const {
			double count = 0;
			for (size_t i = 0, len = orders.sizeOrders (); i != len; ++i)
				count += menu.getMenuPrice(orders.getOrderDish(i).getName()) * orders.getOrderDish(i).getNumber();
			return count;
			}
	private: //количество заказов
		int getReportOrdersCount (const Orders &orders) const {
			return orders[orders.sizeOrders() - 1].getNumberOrder();
			}
	private: //средняя сумма заказа
		double getAvgSumOrders (const Orders &orders) const {
			size_t i, len;
			double sum = 0;
			for (i = 0, len = orders.sizeOrders(); i != len; ++i)
				sum += orders[i].getOrderTotalCost();
			if (i != 0) sum /= i;
			return sum;
			}
	private: //количество заказанных блюд (detail: 1 - с детализацией, 0 - без деталицзации)
		void putCountOrdersDishes (const multimap <string, int> &kitchen, const Menu &menu, int detail) {
			for (size_t i = 0, len = menu.sizeMenu(); i != len; ++i) {
				double buf2 = 0;
				for (size_t j = 0, len = menu[i].sizeMenuCatalogDish(); j != len; ++j) {
					double buf = 0;
					for (multimap <string, int>::const_iterator it = kitchen.begin(); it != kitchen.end(); ++it)
						if (menu[i].getMenuCatalogDish(j).getName() == it->first)
							buf += it->second;
					if (detail)
						ordersStat.push_back (make_pair (menu[i].getMenuCatalogDish(j).getName(), buf)); // с детализацией
					buf2 += buf;
					}
				if (!detail)
					ordersStat.push_back (make_pair (menu[i].getMenuCategory(), buf2)); // без детализацией
				}
			}
	public:
		ReportOrdersStatistics () {}
		ReportOrdersStatistics (const multimap <string, int> &kitchen, const Orders &orders, const Menu &menu, int detail) {
			putCountOrdersDishes (kitchen, menu, detail);
			ordersStat.push_back (make_pair ("Total revenue", getReportTotalRevenue (orders, menu)));
			ordersStat.push_back (make_pair ("Orders count", getReportOrdersCount (orders)));
			ordersStat.push_back (make_pair ("Average sum orders", getAvgSumOrders (orders)));
			}
		const ReportOrdersStatistics &operator+= (const ReportOrdersStatistics &right) {
			if (this == &right)
				return *this;
			for (size_t i = 0, len_i = right.ordersStat.size(); i != len_i; ++i) {
				bool flag = true;
				double buf = 0;
				for (size_t j = 0, len_j = this->ordersStat.size(); j != len_j; ++j)
					if (right.ordersStat[i].first == this->ordersStat[j].first) {
						buf = right.ordersStat[i].second + this->ordersStat[j].second;
						if (right.ordersStat[i].first == "Average sum orders")
							buf /= 2;
						this->ordersStat.erase (this->ordersStat.begin() + j);
						flag = false;
						this->ordersStat.push_back (make_pair (right.ordersStat[i].first, buf));
						break;
						}
				if (flag)
					this->ordersStat.push_back (make_pair (right.ordersStat[i].first, right.ordersStat[i].second));
				}
			return *this;
			}
	public:
		vector <string> getReport () const {
			vector <string> os;
			for (size_t i = 0, len = ordersStat.size (); i != len; ++i) {
				stringstream str;
				string count;
				str << ordersStat[i].second;
				str >> count;
				os.push_back (ordersStat[i].first + ": " + count);
				}
			return os;
			}
	};

class ReportTrendInPrices : Report {
	private:
		vector <string> trendInPrices;
	private:
		string doubleInString (double number) const {
			string buf;
			stringstream str;
			str << number;
			str >> buf;
			return buf;
			}
	private: //динамика цен в меню - изменение цены в абсолютной величине и в процентах
		void putTrendInPrices (const Menu &menuStart, const Menu &menuEnd) {
			double changedPrice, changePercent;
			for (size_t i = 0, len_i = menuStart.countMenuDishes(); i != len_i; ++i)
				for (size_t j = 0, len_j = menuEnd.countMenuDishes(); j != len_j; ++j)
					if (menuStart.getMenuDish(i).getName() == menuEnd.getMenuDish(j).getName()) {
						changedPrice = menuEnd.getMenuDish(j).getCost() - menuStart.getMenuDish(i).getCost();
						changePercent = (changedPrice / menuStart.getMenuDish(i).getCost()) * 100;
						if (changedPrice > 0)
							trendInPrices.push_back (menuEnd.getMenuDish(j).getName() + ": +" + 
							doubleInString(changedPrice) + " (+" + doubleInString(changePercent) + "%)");
						else
							trendInPrices.push_back (menuEnd.getMenuDish(j).getName() + ": " + 
							doubleInString(changedPrice) + " (" + doubleInString(changePercent) + "%)");
						}
			}
	private: //изъятые/добавленные блюда
		void putAddedRemovedDishes (const Menu &menuStart, const Menu &menuEnd) {
			for (size_t i = 0, len_i = menuStart.countMenuDishes(); i != len_i; ++i) {
				bool flag = true;
				for (size_t j = 0, len_j = menuEnd.countMenuDishes(); j != len_j; ++j)
					if (menuStart.getMenuDish(i).getName() == menuEnd.getMenuDish(j).getName())
						flag = false;
				if (flag) trendInPrices.push_back (menuStart.getMenuDish(i).getName() + " (REMOVED)");
				}
			for (size_t i = 0, len_i = menuEnd.countMenuDishes(); i != len_i; ++i) {
				bool flag = true;
				for (size_t j = 0, len_j = menuStart.countMenuDishes(); j != len_j; ++j)
					if (menuStart.getMenuDish(j).getName() == menuEnd.getMenuDish(i).getName())
						flag = false;
				if (flag) trendInPrices.push_back (menuEnd.getMenuDish(i).getName() + " (ADDED)");
				}
			}
	public:
		ReportTrendInPrices () {}
		ReportTrendInPrices (const Menu &menuStart, const Menu &menuEnd) {
			putTrendInPrices (menuStart, menuEnd);
			putAddedRemovedDishes (menuStart, menuEnd);
			}
	public:
		vector <string> getReport () const { return trendInPrices; }
	};

class ReportControlDiscount : Report {
	private:
		vector <string> controlDiscount;
	public:
		ReportControlDiscount () {}
		ReportControlDiscount (const Orders &orders, const Menu &menu, string date) {
			for (size_t i = 0, len_i = orders.sizeOrders (); i != len_i; ++i) {
				if (orders[i].colculationCostDiscount(menu) == orders[i].getOrderTotalCost())
					continue;
				stringstream str;
				string numberOrder, incorrectCost, correctCost, percentDiscount;
				str << orders[i].getNumberOrder();
				str >> numberOrder;
				str.str(""); str.clear();
				str << orders[i].getOrderTotalCost();
				str >> incorrectCost;
				str.str(""); str.clear();
				str << orders[i].colculationCostDiscount(menu);
				str >> correctCost;
				str.str(""); str.clear();
				str << orders[i].colculationPercentDiscount(menu);
				str >> percentDiscount;
				controlDiscount.push_back (date + " " + orders[i].getTimeOrder() + "\t\tЗаказ №" + numberOrder + "\t" + incorrectCost
				+ "\t\t" + correctCost + "\t\t" + percentDiscount + "% " + orders[i].getDiscountType()->getNameDiscountType());
				}
			}
		const ReportControlDiscount &operator+= (const ReportControlDiscount &right) {
			if (this == &right)
				return *this;
			for (size_t i = 0, len = right.controlDiscount.size(); i != len; ++i)
				this->controlDiscount.push_back (right.controlDiscount[i]);
			return *this;
			}
	public:
		vector <string> getReport () const { 
			vector <string> buf;
			buf.push_back("<Дата и время заказа> <номер заказа> <неверная сумма> <верная сумма> <размер и тип скидки>");
			for (vector <string>::const_iterator it = controlDiscount.begin (); it != controlDiscount.end (); ++it)
				buf.push_back (*it);
			return buf;
			}
	};


//############################################
// ИНТЕРФЕЙС
//############################################

class UserInterface {
	private:
		int basicInterface (string reporttype) {
			int number;
			while (1) {
				cout << endl << "Получить отчёт " << reporttype << " за период: " << endl;
				cout << "1) За последний день (текущая дата)" << endl;
				cout << "2) За определенные сутки (дата задается пользователем)" << endl;
				cout << "3) За последнюю неделю (текущая дата и 6 предшествующих дней) с детализацией по дням" << endl;
				cout << "4) За заданный период (задаются даты начала и окончания) с детализацией по дням" << endl;
				cout << "0) Не получать отчёт" << endl;
				cout << "Номер выбранного отчёта: ";
				cin >> number;
				if (number >= 0 && number <= 4)
					return number;
				cout << endl << "ERROR: Incorrect number report" << endl;
				}
			}
		int interfaceTwoOptions (string name) {
			int number;
			while (1) {
				cout << endl << name << endl;
				cout << "1) Да" << endl;
				cout << "0) Нет" << endl;
				cout << "Номер выбранного варианта: ";
				cin >> number;
				if (number >= 0 && number <= 1)
					return number;
				cout << endl << "ERROR: Incorrect number" << endl;
				}
			}
		int basicInterfaceInput (Date &dateStart, Date &dateEnd, int number) {
			switch (number) {
				case 1 :
					dateStart.currentDate ();
					dateEnd = dateStart;
					return 1;
				case 2 :
					cout << endl;
					dateStart.inputDateFromString ();
					dateEnd = dateStart;
					return 2;
				case 3 :
					dateEnd.currentDate ();
					dateStart.dateWeekAgo (dateEnd.getDate());
					return 3;
				case 4 :
					while (1) {
						cout << endl << "Начиная c какой даты?" << endl;
						dateStart.inputDateFromString ();
						cout << endl << "Заканчивая какой датой?" << endl;
						dateEnd.inputDateFromString ();
						if (!dateStart.compareDates(dateEnd.getDate()))
							return 4;
						cout << endl << "ERROR: date-start >= date-end" << endl;
						}
				case 0 :
					return 0;
				}
			}
	public:
		UserInterface () {
			Date dstart, dend;
			if (basicInterfaceInput (dstart, dend, basicInterface ("об украденных блюдах"))) {
				ReportStolenDishes RSD;
				while (dstart.getDate() <= dend.getDate()) {
					multimap <string, int> kitchen;
					Orders orders;
					Menu menu;
					InputFile (kitchen, orders, menu, dstart.getDate());
					if (!kitchen.size() || !orders.sizeOrders() || !menu.sizeMenu()) return;
					RSD += ReportStolenDishes (kitchen, orders, menu);
					++dstart;
					}
				OutputFile (RSD.getReport(), "report_stolen_dishes");
				}
			if (basicInterfaceInput (dstart, dend, basicInterface ("по статистике заказов"))) {
				int detail = interfaceTwoOptions ("По отчёту о количестве заказанных блюд нужна детализация?");
				ReportOrdersStatistics ROS;
				while (dstart.getDate() <= dend.getDate()) {
					multimap <string, int> kitchen;
					Orders orders;
					Menu menu;
					InputFile (kitchen, orders, menu, dstart.getDate());
					if (!kitchen.size() || !orders.sizeOrders() || !menu.sizeMenu()) return;
					ROS += ReportOrdersStatistics (kitchen, orders, menu, detail);
					++dstart;
					}
				OutputFile (ROS.getReport(), "report_orders_statistics");
				}
			if (interfaceTwoOptions ("Получить отчёт по динамике цен в меню (в сравнении между двумя датами)?")) {
				basicInterfaceInput (dstart, dend, 4);
				Menu menuS, menuE;
				InputFile (menuS, dstart.getDate());
				InputFile (menuE, dend.getDate());
				if (!menuS.sizeMenu() || !menuE.sizeMenu()) return;
				ReportTrendInPrices RTiP (menuS, menuE);
				OutputFile (RTiP.getReport(), "report_trend_in_prices");
				}
			if (basicInterfaceInput (dstart, dend, basicInterface ("по контролю за расчетом скидок"))) {
				ReportControlDiscount RCD;
				while (dstart.getDate() <= dend.getDate()) {
					multimap <string, int> kitchen;
					Orders orders;
					Menu menu;
					InputFile (kitchen, orders, menu, dstart.getDate());
					InputDiscountOrders (orders, menu);
					if (!kitchen.size() || !orders.sizeOrders() || !menu.sizeMenu()) return;
					RCD += ReportControlDiscount (orders, menu, dstart.getDate());
					++dstart;
					}
				OutputFile (RCD.getReport(), "report_control_discount");
				}
			}
	};

int main (void) {
	setlocale (LC_ALL, "RUS");

	UserInterface ();

	system ("PAUSE");
	return 0;
	}
