#include "InventorySlot.h"
#include <string>

#pragma once

class C_Inventory : public Component {
private:
	int _entity_id = 999999999;
	ComponentFlag _flag = ComponentFlag::INVENTORY;

	InventorySlot* _head = nullptr;
	int _size = 0;
	int _max_size;

public:
	C_Inventory(int owning_entity_id, std::vector<InventorySlot*> slots = {}, int max_size = 64);

	ComponentFlag getFlag() override;
	InventorySlot* getHead();
	InventorySlot* getTail();
	int getSize();
	int getMaxSize();
	void setHead(InventorySlot* head);

	void addItem(Entity* item);
	void addItem(InventorySlot* slot);
	//void deleteItem(Entity* item);
	//bool hasItem(std::string item_name);
	//Entity* searchItem(std::string item_name);

	void update() override;
	void render() override;
	void about();
};
