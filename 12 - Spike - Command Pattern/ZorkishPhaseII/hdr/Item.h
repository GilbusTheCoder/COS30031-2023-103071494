#include <iostream>
#pragma once

enum ITEM_TYPES { TEST_TYPE };

class Item {
private:
	std::string _name;
	std::string _description;
	ITEM_TYPES _type;

public:
	Item(std::string name = "", std::string description = "", 
		ITEM_TYPES type = TEST_TYPE);

	std::string getName();
	std::string getDescription();
	ITEM_TYPES getType();
	void setName(std::string name);
	void setDescription(std::string description);
	void setType(ITEM_TYPES type);

	void about();
};

