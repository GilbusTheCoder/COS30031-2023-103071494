#include "../header/pch.h"
#include "../header/Items.h"

// Weapon Definitions
Weapon::Weapon(std::string name = "WeaponName", std::string description = "Weapon Description") {
	__name = name;
	__type = WEAPON;
	__description = description;
}
std::string Weapon::getName() { return __name; }
void Weapon::setName(std::string name) { __name = name; }
ItemType Weapon::getType() { return __type; }
std::string Weapon::getDescription() { return __description; }
void Weapon::setDescription(std::string description) { __description = description; }

void Weapon::printDescription() {
	std::cout << "Name: " << __name << std::endl;
	std::cout << "Type: Weapon" << std::endl;
	std::cout << "Desc: " << __description << std::endl;
};





// Armour Definitions
Armour::Armour(std::string name = "ArmourName", std::string description = "ArmourDesc") {
	__name = name;
	__type = ARMOUR;
	__description = description;
}

std::string Armour::getName() { return __name; }
void Armour::setName(std::string name) { __name = name; }
ItemType Armour::getType() { return __type; }
std::string Armour::getDescription() { return __description; }
void Armour::setDescription(std::string description) { __description = description; }

void Armour::printDescription() {
	std::cout << "Name: " << __name << std::endl;
	std::cout << "Type: Armour" << std::endl;
	std::cout << "Desc: " << __description << std::endl;
};





// Consumable Definitions
Consumable::Consumable(std::string name = "ArmourName", std::string description = "ArmourDesc") {
	__name = name;
	__type = CONSUMABLE;
	__description = description;
}
std::string Consumable::getName() { return __name; }
void Consumable::setName(std::string name) { __name = name; }
ItemType Consumable::getType() { return __type; }
std::string Consumable::getDescription() { return __description; }
void Consumable::setDescription(std::string description) { __description = description; }

void Consumable::printDescription() {
	std::cout << "Name: " << __name << std::endl;
	std::cout << "Type: Consumable" << std::endl;
	std::cout << "Desc: " << __description << std::endl;
};





// Misc Definitions
Misc::Misc(std::string name = "MiscName", std::string description = "MiscDesc") {
	__name = name;
	__type = MISC;
	__description = description;
};

std::string Misc::getName() { return __name; }
void Misc::setName(std::string name) { __name = name; }
ItemType Misc::getType() { return __type; }
std::string Misc::getDescription() { return __description; }
void Misc::setDescription(std::string description) { __description = description; }

void Misc::printDescription() {
	std::cout << "Name: " << __name << std::endl;
	std::cout << "Type: Miscellaneous " << std::endl;
	std::cout << "Desc: " << __description << std::endl;
};





// TestType Definitions
TestType::TestType(std::string name = "TestName", std::string description = "TestDesc") {
	__name = name;
	__type = TEST_TYPE;
	__description = description;
}

std::string TestType::getName() { return __name; }
void TestType::setName(std::string name) { __name = name; }
ItemType TestType::getType() { return __type; }
std::string TestType::getDescription() { return __description; }
void TestType::setDescription(std::string description) { __description = description; }

void TestType::printDescription() {
	std::cout << "Name: " << __name << std::endl;
	std::cout << "Type: TestType " << std::endl;
	std::cout << "Desc: " << __description << std::endl;
};