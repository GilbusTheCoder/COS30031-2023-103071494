#include "CompLoader.h"

#pragma once
namespace ECS {
	class TagLoader : public CompLoader {
	public:
		static Tag loadTagComponent(std::string comp_id, std::string arg);
	};
}

