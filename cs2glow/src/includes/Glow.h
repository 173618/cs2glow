#pragma once
#include "includes.h"
#include "Entity.h" //This needs to be here for some odd reason, delete it and find out!

class Glow
{
public:
	Glow(const Memory& memory, const Entity& entity) : mem(memory), ent(entity)
	{
	}
	~Glow() = default;
	void glow_loop();

private:
	Memory mem;
	Entity ent;
};

