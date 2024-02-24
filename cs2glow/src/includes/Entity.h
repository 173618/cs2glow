#pragma once
#include "includes.h"

class Entity
{
public:
	Entity(const Memory& memory, const std::uintptr_t client) : mem(memory), m_client(client)
	{
	}
	~Entity() = default;

	std::uintptr_t get_entity_list_base() const;
	std::vector<std::uintptr_t> get_controllers() const;

private:
	Memory mem;
	std::uintptr_t m_client;
};
