#pragma once
#include "Inventory.h"

enum ItemType {
	WEAPON,
	CONTAINER,
	ARMOUR,
	CONSUMABLE,
	MISC,
	TEST_TYPE,
};


class Item {
protected:
	std::string __name;
	ItemType __type;
	std::string __description;

public:
	virtual std::string getName() = 0;
	virtual void setName(std::string name) = 0;
	virtual ItemType getType() = 0;
	virtual std::string getDescription() = 0;
	virtual void setDescription(std::string description) = 0;

	virtual void printDescription() = 0;
};





class Weapon : public Item {
public:
	Weapon(std::string name, std::string description);
	std::string getName() override;
	void setName(std::string name) override;
	ItemType getType() override;
	std::string getDescription() override;
	void setDescription(std::string description) override;

	void printDescription() override;
};





// Do containers with look command
/*class Container : public Item {
private:
	Inventory _inventory;
};*/





class Armour : public Item {
public:	
	Armour(std::string name, std::string description);

	std::string getName() override;
	void setName(std::string name) override;
	ItemType getType() override;
	std::string getDescription() override;
	void setDescription(std::string description) override;

	void printDescription() override;
};





class Consumable : public Item {
public:
	Consumable(std::string name, std::string description);

	std::string getName() override;
	void setName(std::string name) override;
	ItemType getType() override;
	std::string getDescription() override;
	void setDescription(std::string description) override;

	void printDescription() override;
};





class Misc : public Item {
public:
	Misc(std::string name, std::string description);

	std::string getName() override;
	void setName(std::string name) override;
	ItemType getType() override;
	std::string getDescription() override;
	void setDescription(std::string description) override;

	void printDescription() override;
};





class TestType : public Item {
public:
	TestType(std::string name, std::string description);

	std::string getName() override;
	void setName(std::string name) override;
	ItemType getType() override;
	std::string getDescription() override;
	void setDescription(std::string description) override;

	void printDescription() override;
};
