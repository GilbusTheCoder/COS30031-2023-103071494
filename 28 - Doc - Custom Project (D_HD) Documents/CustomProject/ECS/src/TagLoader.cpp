#include "../hdr/TagLoader.h"

ECS::Tag ECS::TagLoader::loadTagComponent(std::string comp_id, std::string arg) {
	// Here's going to be a phat if else statement if there's lots of tags
	EntityTag tag = ET_INVALID;
	
	if (arg == "hex") { tag = ET_HEX; }
	else if (arg == "army") { tag = ET_ARMY; }
	else if (arg == "building") { tag = ET_BUILDING; }
	else if (arg == "hex_overlay") { tag = ET_HEX_OVERLAY; }

	return { comp_id, C_TAG, tag };
}