#include "Component.h"
#include "InventorySlot.h"
#include <string>

#pragma once

class C_Inventory : public Component {
private:
	std::string _ucid;
	ComponentFlag _flag = ComponentFlag::C_INVENTORY;

	InventorySlot* _head = nullptr;
	int _size = 0;
	int _max_size;

public:
	std::vector<std::string> held_item_EUIDs;
	
	C_Inventory(std::string ucid, std::vector<InventorySlot*> slots = {}, 
		int max_size = 64);

	ComponentFlag getFlag() override;
	InventorySlot* getHead();
	InventorySlot* getTail();
	int getSize();
	int getMaxSize();
	void setHead(InventorySlot* head);

	int hasItem(Entity* item = nullptr, std::string UEID = "");
	Entity* getItem(int offset);
	void addItem(Entity* item);
	void addItem(InventorySlot* slot);
	void deleteItem(Entity* item);

	void update() override;
	void render() override;
};
