#include <algorithm>
#include "../hdr/Command.h"


/******************************************************************************
*									MoveCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
MoveCommand::MoveCommand() {}

/* Expects the argument to contain only 1 element, the direction to move	*/
void MoveCommand::triggerEvent() {
	_game_data->reinstance_local_entity_cache = true;
}



/******************************************************************************
*									TakeCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
TakeCommand::TakeCommand() {

}

void TakeCommand::triggerEvent() {

}



/******************************************************************************
*									LookCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
LookCommand::LookCommand() {

}

void LookCommand::triggerEvent() {

}



/******************************************************************************
*									ShowCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/
ShowCommand::ShowCommand() {
}

void ShowCommand::triggerEvent() {
	
}



/******************************************************************************
*									QuitCommand
*									Definitions
*
/******************************************************************************
*								Base Class Overrides
******************************************************************************/

QuitCommand::QuitCommand() {
	
}

void QuitCommand::triggerEvent() { }