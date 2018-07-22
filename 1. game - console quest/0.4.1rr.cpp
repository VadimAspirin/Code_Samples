#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <utility> 		// pair
#include <regex>   		// -std=c++11 or -std=gnu++11
#include <cstdlib>		// atoi

/*
#define DIR_ITEM_FILES "./item/"
#define DIR_MOB_FILES "./mobile_object/"
#define DIR_ROOM_FILES "./room/"
#define DIR_PLAYER_FILES "./player/"
#define DIR_MAP_FILES "./map/"
*/

#define DIR_ITEM_FILES ".\\item\\"
#define DIR_MOB_FILES ".\\mobile_object\\"
#define DIR_ROOM_FILES ".\\room\\"
#define DIR_PLAYER_FILES ".\\player\\"
#define DIR_MAP_FILES ".\\map\\"

using namespace std;

/********************************************
 *			 ХРАНЕНИЕ ДАННЫХ				*
 ********************************************/

class Item {
	private:
		string name;
		int weight;
		int lifeUp;
		int damage;
		size_t countUses;
		bool special;
	public:
		Item () {}
		Item (string name, int weight, int lifeUp, int damage, size_t countUses, bool special) {
			this->name = name;
			this->weight = weight;
			this->lifeUp = lifeUp;
			this->damage = damage;
			this->countUses = countUses;
			this->special = special;
			}
		void use () { --countUses; }
	public:
		string getName () const { return name; }
		int getWeight () const { return weight; }
		int getLifeUp () const { return lifeUp; }
		int getDamage () const { return damage; }
		size_t getCountUses () const { return countUses; }
		bool getSpecial () const { return special; }
	};

class MobileObject {
	private:
		string name;
		int healthPoints;
		int damage;
		int armor;
	public:
		MobileObject () {}
		MobileObject (string name, int damage, int armor) : healthPoints (100) {
			this->name = name;
			this->damage = damage;
			this->armor = armor;
			}
		void setHealthPoints (int healthPoints) {
			this->healthPoints = healthPoints;
			}
	public:
		string getName () const { return name; }
		int getHealthPoints () const { return healthPoints; }
		int getDamage () const { return damage; }
		int getArmor () const { return armor; }
	};

class Room {
	private:
		string name;
		string story;
		vector <Item*> *items;
		map <string, bool> keyItems;
		vector <MobileObject*> *mobs;
		vector <Room*> *rooms;
	public:
		Room () : items (NULL), mobs (NULL), rooms (NULL) {}
		Room (string name,
			  string story,
			  vector <Item*> *items,
			  const map <string, bool> &keyItems,
			  vector <MobileObject*> *mobs) {
			this->name = name;
			this->story = story;
			this->items = items;
			this->keyItems = keyItems;
			this->mobs = mobs;
			rooms = new vector <Room*>;
			}
		~Room () {
			if (items != NULL) { 
				for (vector <Item*>::iterator it = items->begin(); it != items->end(); ++it) {
					delete *it;
					*it = NULL;
					}
				items->clear();
				delete items;
				}
			if (mobs != NULL) {
				for (vector <MobileObject*>::iterator it = mobs->begin(); it != mobs->end(); ++it) {
					delete *it;
					*it = NULL;
					}
				mobs->clear();
				delete mobs;
				}
			if (rooms != NULL) {
				for (vector <Room*>::iterator it = rooms->begin(); it != rooms->end(); ++it)
					*it = NULL;
				rooms->clear();
				delete rooms;
				}
			}
		bool checkKeyItems (string name) {
			map <string, bool>::iterator it = keyItems.begin();
			if (it->first == name) {
				it->second = true;
				return true;
				}
			else
				return false;
			}
		void addRoom (Room *room) { rooms->push_back(room); }
	public:
		string getName () const { return name; }
		string getStory () const { return story; }
		vector <Item*> *get_ptrItems () const { return items; }
		vector <MobileObject*> *get_ptrMobs () const { return mobs; }
		vector <Room*> *get_ptrRooms () const { return rooms; }
		bool getCloseRoom () { 
			for (map <string, bool>::iterator it = keyItems.begin(); it != keyItems.end(); ++it)
				if(it->second == false)
					return true;
			return false;
			}
	};

class GameMap {
	private:
		Room *currentRoom;
		vector <Room*> rooms;
	public:
		GameMap () : currentRoom (NULL) {}
		GameMap (Room *currentRoom, const vector <Room*> &rooms) {
			this->currentRoom = currentRoom;
			this->rooms = rooms;
			}
		~GameMap () {
			if (currentRoom != NULL)
				currentRoom = NULL;
			if (rooms.size() != 0) {
				for (vector <Room*>::iterator it = rooms.begin(); it != rooms.end(); ++it) {
					delete *it;
					*it = NULL;
					}
				rooms.clear();
				}
			}
		void setCurrentRoom (Room *newCurrentRoom) { currentRoom = newCurrentRoom; }
	public:
		Room &getCurrentRoom () const { return *currentRoom; }
	};

class Player {
	private:
		string name;
		int healthPoints;
		size_t damage;
		size_t sizeInventory;
		vector <Item*> *items;
		int damageBonus; //в процентах
	public:
		Player () : name ("anonymous"), healthPoints (100), damage (20), sizeInventory (10), items (NULL), damageBonus(0) {}
		Player (string name, int healthPoints, size_t damage, size_t sizeInventory, int damageBonus) {
			this->name = name;
			this->healthPoints = healthPoints;
			this->damage = damage;
			this->sizeInventory = sizeInventory;
			this->damageBonus = damageBonus;
			items = new vector <Item*>;
			}
		~Player () {
			if (items != NULL) { 
				for (vector <Item*>::iterator it = items->begin(); it != items->end(); ++it) {
					delete *it;
					*it = NULL;
					}
				items->clear();
				delete items;
				}
			}
		void setHealthPoints (int healthPoints) {
			this->healthPoints = healthPoints;
			}
		void setSizeInventory (size_t size) { sizeInventory = size; }
		void addItem (Item *item) { items->push_back(item); }
	public:
		string getName () const { return name; }
		int getHealthPoints () const { return healthPoints; }
		size_t getDamage () const { return damage; }
		size_t getSizeInventory () const { return sizeInventory; }
		vector <Item*> *get_ptrItems () const { return items; }
		int getDamageBonus () const { return damageBonus; }
	};

/********************************************
 *			 		ВВОД					*
 ********************************************/

class InputGameObject {
	private:
		MobileObject *inputMobileObject (string fileName) {
			string buf = DIR_MOB_FILES + fileName + ".dat";
			map <int, string> mob;
			vector <string> rgPatterns = {"name:\\s*(.*)",
										  "damage:\\s*(.*)",
										  "armor:\\s*(.*)%{1}"};
			ifstream fin (buf.c_str ());
			if (!fin) {
				cout << "ОШИБКА: Файл " << fileName << " не существует\n\n";
				return NULL;
				}
			while (getline (fin, buf)) {
				for (size_t i = 0, len = rgPatterns.size(); i != len; ++i) {
					regex rg (rgPatterns[i]);
					cmatch match;
					if (regex_search (buf.c_str (), match, rg)) {
						mob[i] = match[1];
						break;
						}
					}
				}
			fin.close ();
			return new MobileObject (mob[0], atoi (mob[1].c_str ()), atoi (mob[2].c_str ()));
			}
	private:
		Room *inputRoom (string fileName) {
			string buf = DIR_ROOM_FILES + fileName + ".dat",
				   name, story;
			vector <Item*> *items = new vector <Item*>;
			map <string, bool> keyItems;
			vector <MobileObject*> *mobs = new vector <MobileObject*>;
			regex rgName ("name:\\s*(.*)"),
				  rgStory ("story:\\s*(.*)"),
				  rgItem ("item:\\s*(.*)"),
				  rgKeyItem ("keyItem:\\s*(.*)"),
				  rgMob ("mob:\\s*(.*)");
			cmatch match;
			ifstream fin (buf.c_str ());
			if (!fin) {
				cout << "ОШИБКА: Файл " << fileName << " не существует\n\n";
				return NULL;
				}
			while (getline (fin, buf)) {
				if (regex_search (buf.c_str (), match, rgName))
					name = match[1];
				else if (regex_search (buf.c_str (), match, rgStory))
					story = match[1];
				else if (regex_search (buf.c_str (), match, rgItem))
					items->push_back (inputItem (match[1]));
				else if (regex_search (buf.c_str (), match, rgKeyItem))
					keyItems.insert (make_pair (match[1], false));
				else if (regex_search (buf.c_str (), match, rgMob))
					mobs->push_back (inputMobileObject (match[1]));
				}
			fin.close ();
			return new Room (name, story, items, keyItems, mobs);
			}
	public:
		Item *inputItem (string fileName) {
			string buf = DIR_ITEM_FILES + fileName + ".dat";
			map <int, string> item;
			vector <string> rgPatterns = {"name:\\s*(.*)",
										  "weight:\\s*(.*)",
										  "lifeUp:\\s*(.*)",
										  "damage:\\s*(.*)",
										  "countUses:\\s*-?(.*)",
										  "special:\\s*(.*)"};
			ifstream fin (buf.c_str ());
			if (!fin) {
				cout << "ОШИБКА: Файл " << fileName << " не существует\n\n";
				return NULL;
				}
			while (getline (fin, buf)) {
				for (size_t i = 0, len = rgPatterns.size(); i != len; ++i) {
					regex rg (rgPatterns[i]);
					cmatch match;
					if (regex_search (buf.c_str (), match, rg)) {
						item[i] = match[1];
						break;
						}
					}
				}
			fin.close ();
			return new Item (item[0],
							 atoi (item[1].c_str ()),
							 atoi (item[2].c_str ()),
							 atoi (item[3].c_str ()),
							 atoi (item[4].c_str ()),
							 atoi (item[5].c_str ()));
			}
	public:
		GameMap *inputGameMap (string fileName) {
			Room *roomStart = NULL;
			vector <Room*> rooms;
			string buf = DIR_MAP_FILES + fileName + ".dat";
			regex rg ("(\\d+)\\s{1}(\\w+)\\s{1}([0-9 \f\n\r\t\v]+)");
			cmatch match;
			ifstream fin (buf.c_str ());
			if (!fin) {
				cout << "ОШИБКА: Файл " << fileName << " не существует\n\n";
				return NULL;
				}
			while (getline (fin, buf)) {
				if (!regex_search (buf.c_str (), match, rg))
					continue;
				rooms.push_back (inputRoom (match[2]));
				if (match[2] == "room_start")
					roomStart = rooms[rooms.size()-1];
				}
			if (roomStart == NULL)
				roomStart = rooms[0];
			fin.clear ();
			fin.seekg (0, ios::beg);
			for (size_t i = 0; getline (fin, buf); ++i) {
				if (!regex_search (buf.c_str (), match, rg))
					continue;
				stringstream str (match[3]);
				while (str >> buf)
					rooms[i]->addRoom(rooms[atoi(buf.c_str())-1]);
				}
			return new GameMap (roomStart, rooms);
			}
	public:
		Player *inputPlayer (string typeDifficulty, string playerName) {
			string buf = DIR_PLAYER_FILES + typeDifficulty + ".dat";
			map <int, string> difficulty;
			vector <string> rgPatterns = {"healthPoints:\\s*-?(.*)",
										  "damage:\\s*-?(.*)",
										  "sizeInventory:\\s*-?(.*)",
										  "damageBonus:\\s*(.*)%{1}"};
			ifstream fin (buf.c_str ());
			if (!fin) {
				cout << "ОШИБКА: Файл " << typeDifficulty << " не существует\n\n";
				return NULL;
				}
			while (getline (fin, buf)) {
				for (size_t i = 0, len = rgPatterns.size(); i != len; ++i) {
					regex rg (rgPatterns[i]);
					cmatch match;
					if (regex_search (buf.c_str (), match, rg)) {
						difficulty[i] = match[1];
						break;
						}
					}
				}
			fin.close ();
			return new Player (playerName,
							   atoi (difficulty[0].c_str ()),
							   atoi (difficulty[1].c_str ()),
							   atoi (difficulty[2].c_str ()),
							   atoi (difficulty[3].c_str ()));
			}
	};

/********************************************
 *				 ИНТЕРФЕЙС					*
 ********************************************/

class UserInterface {
	private:
		Player *player;
		GameMap *gameMap;
	private:
		InputGameObject inputGO;
	private:
		bool createUser () {
			string playerName, typeDifficulty;
			size_t number;
			cout << endl << "Введите имя игрока: ";
			cin >> playerName;
			while (1) {
				cout << endl
					 << "Выберите сложность" << endl
					 << "1) Легко" << endl
					 << "2) Средне" << endl
					 << "3) Сложно" << endl
					 << "Выбранная сложность: ";
				cin >> number;
				if (number > 0 && number < 5)
					break;
				else
					cout << endl << "Неверный вариант ответа!" << endl;
				}
			switch (number) {
				case 1:
					typeDifficulty = "light";
					break;
				case 2:
					typeDifficulty = "medium";
					break;
				case 3:
					typeDifficulty = "hard";
					break;
				}
			player = inputGO.inputPlayer (typeDifficulty, playerName);
			if (player == NULL) {
				cout << endl << "Игра повреждена!" << endl;
				return false;
				}
			cout << endl << "Пользователь создан!" << endl;
			return true;
			}
		bool createGameMap () {
			cout << endl << "Генерация игравой карты..." << endl;
			gameMap = inputGO.inputGameMap ("game_map");
			if (gameMap == NULL) {
				cout << endl << "Игра повреждена!" << endl;
				return false;
				}
			cout << endl << "Игровая карта создана!" << endl;
			return true;
			}
	private:
		void printAddHealthPoints (string name, int count) {
			cout << endl << "Игрок " << name << " получил " << count << " здоровья" << endl;
			}
		void printLostHealthPoints (string name, int count) {
			cout << endl << "Игрок " << name << " потерял " << count << " здоровья" << endl;
			}
		void printDiedPlayer (string name) {
			cout << endl << "Игрок " << name << " мёртв" << endl;
			}
	private:
		int actionTransition () {
			size_t number;
			while (1) {
				cout << endl << "Куда направиться" << endl;
				for (size_t i = 0, len = gameMap->getCurrentRoom().get_ptrRooms()->size(); i != len; ++i)
					cout << i + 1 << ") " << gameMap->getCurrentRoom().get_ptrRooms()->at(i)->getName() << endl;
				cout << gameMap->getCurrentRoom().get_ptrRooms()->size() + 1 << ") Отменить" << endl;
				cout << "Выбранное направление: ";
				cin >> number;
				if (number > 0 && number <= gameMap->getCurrentRoom().get_ptrRooms()->size() + 1)
					break;
				else
					cout << endl << "Неверный вариант ответа!" << endl;
				}
			if (gameMap->getCurrentRoom().get_ptrRooms()->at(number - 1)->getCloseRoom() == true) {
				int number, unit;
				while (1) {
					cout << endl << "Комната заперта. Попытаться открыть?" << endl;
					cout << "1) Да" << endl;
					cout << "2) Нет" << endl;		
					cout << "Выбор: ";				
					cin >> number;
					if (number > 0 && number < 3)
						break;
					else
						cout << endl << "Неверный вариант ответа!" << endl;
					}
				switch (number) {
					case 1:
						unit = actionInventory();  //player->get_ptrItems()->at(unit)->getName()
						if (gameMap->getCurrentRoom().get_ptrRooms()->at(number - 1)->checkKeyItems(player->get_ptrItems()->at(unit)->getName()) == true)
							cout << endl << "Вы открыли комнату" << endl;
						else {
							cout << endl << "Комната не открыта" << endl;
							return -1;
							}
						break;
					case 2:
						return -1;
					}
				}
			if (number != gameMap->getCurrentRoom().get_ptrRooms()->size() + 1) {
				gameMap->setCurrentRoom(gameMap->getCurrentRoom().get_ptrRooms()->at(number - 1));
				return 0;
				}
			else
				return -1;
			}
	private:
		int actionInventory () {
			size_t number;
			while (1) {
				cout << endl << "Что использовать" << endl;
				for (size_t i = 0, len = player->get_ptrItems()->size(); i != len; ++i)
					cout << i + 1 << ") " << player->get_ptrItems()->at(i)->getName() << endl;
				cout << player->get_ptrItems()->size() + 1 << ") Отменить" << endl;
				cout << "Выбранный предмет: ";
				cin >> number;
				if (number > 0 && number <= player->get_ptrItems()->size() + 1)
					break;
				else
					cout << endl << "Неверный вариант ответа!" << endl;
				}
			if (number != player->get_ptrItems()->size() + 1)
				return number - 1;
			else
				return -1;
			}
		int actionRoomItem () {
			size_t number;
			while (1) {
				cout << endl << "Что использовать" << endl;
				for (size_t i = 0, len = gameMap->getCurrentRoom().get_ptrItems()->size(); i != len; ++i)
					cout << i + 1 << ") " << gameMap->getCurrentRoom().get_ptrItems()->at(i)->getName() << endl;
				cout << gameMap->getCurrentRoom().get_ptrItems()->size() + 1 << ") Отменить" << endl;
				cout << "Выбранный предмет: ";
				cin >> number;
				if (number > 0 && number <= gameMap->getCurrentRoom().get_ptrItems()->size() + 1)
					break;
				else
					cout << endl << "Неверный вариант ответа!" << endl;
				}
			if (number != gameMap->getCurrentRoom().get_ptrItems()->size() + 1)
				return number - 1;
			else
				return -1;
			}
	private:
		bool actionFight () {
			size_t number;
			int unit;
			while (gameMap->getCurrentRoom().get_ptrMobs()->size() != 0) {
				int i = 0;
				MobileObject *mob = gameMap->getCurrentRoom().get_ptrMobs()->at(i);
				cout << endl << "Вас атакует " << mob->getName() << endl;
				while (1) {
					player->setHealthPoints (player->getHealthPoints() - mob->getDamage());
					printLostHealthPoints (player->getName(), mob->getDamage());
					if (player->getHealthPoints() <= 0) {
						printDiedPlayer (player->getName());
						return false;
						}
					while (1) {
						cout << endl
							 << "Действия боя" << endl
							 << "1) Удар рукой" << endl
							 << "2) Инвентарь" << endl
							 << "3) Проверить своё здоровье" << endl
							 << "4) Информация о противнике" << endl
							 << "5) Бежать, поджав хвост" << endl
							 << "Выбранное действие: ";
						cin >> number;
						if (!(number > 0 && number < 6)) {
							cout << endl << "Неверный вариант ответа!" << endl;
							continue;
							}
						switch (number) {
							case 1:
								int damage;
								damage = (player->getDamage() * (1 + player->getDamageBonus() / 100) - player->getDamage()) +
										  player->getDamage() * (1 - mob->getArmor() / 100);
								mob->setHealthPoints(mob->getHealthPoints() - damage);
								printLostHealthPoints (mob->getName(), damage);
								break;
							case 2:
								unit = actionInventory();
								if (unit == -1)
									continue;
								damage = (player->get_ptrItems()->at(unit)->getDamage() * (1 + player->getDamageBonus() / 100) - 
										  player->get_ptrItems()->at(unit)->getDamage()) +
										  player->get_ptrItems()->at(unit)->getDamage() * (1 - mob->getArmor() / 100);
								mob->setHealthPoints(mob->getHealthPoints() - damage);
								printLostHealthPoints (mob->getName(), damage);
								if (!player->get_ptrItems()->at(unit)->getSpecial())
									player->get_ptrItems()->at(unit)->use();
								else
									break;
								if (player->get_ptrItems()->at(unit)->getCountUses() == 0) {
									player->setSizeInventory(player->getSizeInventory()-player->get_ptrItems()->at(unit)->getWeight());
									delete player->get_ptrItems()->at(unit);
									player->get_ptrItems()->at(unit) = NULL;
									player->get_ptrItems()->erase (player->get_ptrItems()->begin() + unit);
									}
								break;
							case 3:
								cout << endl << player->getName() << endl 
									 << "здоровье: " << player->getHealthPoints() << endl;
								continue;
							case 4:
								cout << endl << mob->getName() << endl
									 << "здоровье: " << mob->getHealthPoints() << endl
									 << "урон: " << mob->getDamage() << endl
									 << "броня: " << mob->getArmor() << endl;
								continue;
							case 5:
								unit = actionTransition ();
								if (unit == -1)
									continue;
								return true;
							}
						break;
						}
					if (mob->getHealthPoints() <= 0) {
						printDiedPlayer (mob->getName());
						mob = NULL;
						delete gameMap->getCurrentRoom().get_ptrMobs()->at(i);
						gameMap->getCurrentRoom().get_ptrMobs()->at(i) = NULL;
						gameMap->getCurrentRoom().get_ptrMobs()->erase (gameMap->getCurrentRoom().get_ptrMobs()->begin() + i);
						break;
						}
					}
				}
			return true;
			}
	private:
		bool actionBasic () {
			size_t number;
			int unit;
			while (1) {
				cout << endl
					 << "Действия" << endl
					 << "1) Местонахождение" << endl
					 << "2) Обыскать местность" << endl
					 << "3) Обзор инвентаря" << endl
					 << "4) Удалить из инвентаря" << endl
					 << "5) Проверить своё здоровье" << endl
					 << "6) Искать выход" << endl
					 << "7) Выйти из игры" << endl
					 << "Выбранное действие: ";
				cin >> number;
				if (!(number > 0 && number < 8)) {
					cout << endl << "Неверный вариант ответа!" << endl;
					continue;
					}
				switch (number) {
					case 1:
						cout << endl << gameMap->getCurrentRoom().getName() << endl;
						continue;
					case 2:
						unit = actionRoomItem();
						if (unit == -1)
							continue;
						player->get_ptrItems()->push_back(gameMap->getCurrentRoom().get_ptrItems()->at(unit));
						gameMap->getCurrentRoom().get_ptrItems()->erase (gameMap->getCurrentRoom().get_ptrItems()->begin() + unit);
						break;
					case 3:
						unit = actionInventory();
						if (unit == -1)
							continue;
						player->setHealthPoints(player->get_ptrItems()->at(unit)->getLifeUp() + player->getDamage());
						printAddHealthPoints (player->getName(), player->get_ptrItems()->at(unit)->getLifeUp());
						if (!player->get_ptrItems()->at(unit)->getSpecial())
							player->get_ptrItems()->at(unit)->use();
						else
							break;
						if (player->get_ptrItems()->at(unit)->getCountUses() == 0) {
							player->setSizeInventory(player->getSizeInventory()-player->get_ptrItems()->at(unit)->getWeight());
							delete player->get_ptrItems()->at(unit);
							player->get_ptrItems()->at(unit) = NULL;
							player->get_ptrItems()->erase (player->get_ptrItems()->begin() + unit);
							}
						break;
					case 4:
						unit = actionInventory();
						if (unit == -1)
							continue;
						player->setSizeInventory(player->getSizeInventory()-player->get_ptrItems()->at(unit)->getWeight());
						delete player->get_ptrItems()->at(unit);
						player->get_ptrItems()->at(unit) = NULL;
						player->get_ptrItems()->erase (player->get_ptrItems()->begin() + unit);
						break;
					case 5:
						cout << endl << player->getName() << endl 
							 << "здоровье: " << player->getHealthPoints() << endl;
						continue;
					case 6:
						unit = actionTransition ();
						if (unit == -1)
							continue;
						return true;
					case 7:
						if (exitGame ())
							return false;
						else
							continue;
					}
				}
			}
	private:
		bool exitGame () {
			size_t number;
			while (1) {
				cout << endl
					 << "Вы действительно хотите выйти из игры? Пройденный результат будет утерян!" << endl
					 << "1) Да" << endl
					 << "2) Нет" << endl
					 << "Выбранное действие: ";
				cin >> number;
				if (!(number > 0 && number < 3)) {
					cout << endl << "Неверный вариант ответа!" << endl;
					continue;
					}
				switch (number) {
					case 1:
						return true;
					case 2:
						return false;
					}
				}
			}
	public:
		UserInterface () : player (NULL), gameMap (NULL) {
			if (!createUser ())
				return;
			if (!createGameMap ())
				return;
			while (1) {
				if (gameMap->getCurrentRoom().get_ptrMobs() != NULL)
					if (!actionFight ())
						return;
				
				if (!actionBasic ())
					return;
				
				}

			}
		~UserInterface () {
			if (player != NULL)
				delete player;
			if (gameMap != NULL)
				delete gameMap;
			}
	};

int main (void) {
	setlocale (LC_ALL, "RUS");
	InputGameObject igo;
/*
	Item *item;
	item = igo.inputItem ("red_moss");
	if (item == NULL)
		return 1;
	cout << item->getName() << endl;
	cout << item->getLifeUp() << endl;
	cout << item->getDamage() << endl;
	cout << item->getCountUses() << endl;
*/	
/*
	MobileObject *mob;
	mob = igo.inputMobileObject ("wild_dog");
	if (mob == NULL)
		return 1;
	cout << mob->getName() << endl;
	cout << mob->getHealthPoints() << endl;
	cout << mob->getDamage() << endl;
	cout << mob->getArmor() << endl;
*/
/*
	Room *room;
	room = igo.inputRoom ("room_start");
	if (room == NULL)
		return 1;
	cout << room->getName() << endl;
	cout << room->getStory() << endl;
	cout << room->get_ptrItems()->size() << endl;
	cout << room->get_ptrItems()->at(0)->getWeight() << endl;
	delete room;
*/
/*
	Player *player;
	player = igo.inputPlayer ("hard", "Анатоле");
	if (player == NULL)
		return 1;
	cout << player->getName() << endl;
	cout << player->getHealthPoints() << endl;
	cout << player->getInventory() << endl;
	cout << player->getDamageBonus() << endl;
*/
/*
	GameMap *gmap;
	gmap = igo.inputGameMap ("game_map");
	cout << gmap->getCurrentRoom().getName() << endl;
	cout << gmap->getCurrentRoom().get_ptrRooms()->at(0)->getName()<< endl;
	cout << gmap->getCurrentRoom().get_ptrRooms()->at(1)->getName()<< endl;
	cout << gmap->getCurrentRoom().get_ptrRooms()->at(2)->getName()<< endl;
	cout << gmap->getCurrentRoom().get_ptrRooms()->at(3)->getName()<< endl;
	cout << gmap->getCurrentRoom().get_ptrRooms()->at(3)->get_ptrRooms()->at(1)->getName()<< endl;
	cout << gmap->getCurrentRoom().get_ptrRooms()->size() << endl;
	cout << "\n\n";
	cout << gmap->getCurrentRoom().get_ptrRooms()->at(3)->checkKeyItems("Ржавый ключ") << endl;
	delete gmap;
*/

	UserInterface ();

	return 0;
	}
