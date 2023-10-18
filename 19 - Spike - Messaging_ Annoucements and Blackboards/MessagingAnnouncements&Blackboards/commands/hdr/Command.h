#include "GameData.h"

#pragma once
enum CommandType {
	INVALID,
	MOVE,	// go somewhere
	TAKE,	// transfer item
	LOOK,	// display surrounding renderer info
	SHOW,	// display attached component info
	QUIT,	// change game_data is_running to false
};

class Command {
public:
	virtual void triggerEvent() = 0;
};

class MoveCommand : virtual public Command {
private:
	GameData* _game_data = nullptr;
	std::string _exit_UEID;

public:
	MoveCommand();

	void setData(GameData* game_data, std::string exit_UEID);
	void triggerEvent() override;
};

class TakeCommand : virtual public Command {
private:
	C_Inventory* _source = nullptr;
	C_Inventory* _dest = nullptr;
	Entity* _item = nullptr;

public:
	TakeCommand();
	
	void setData(C_Inventory* source, C_Inventory* dest, Entity* item);
	void triggerEvent() override;
};

class LookCommand : virtual public Command {
private:
	GameData* _game_data;


public:
	LookCommand();
	
	void setData();
	void triggerEvent() override;
};

class ShowCommand : virtual public Command {
public:
	ShowCommand();
	
	void setData();
	void triggerEvent() override;
};

class QuitCommand : virtual public Command {
private:
	GameData* _game_data = nullptr;

public:
	QuitCommand();
	
	void setData(GameData* game_data_frame);
	void triggerEvent() override;
};