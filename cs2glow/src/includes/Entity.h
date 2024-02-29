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
	std::uintptr_t local_pawn() const;
	std::uintptr_t local_player() const;
	bool teamcheck(const std::uintptr_t& player) const;
	std::uintptr_t crsh_idx_to_controller(const std::int32_t& idx) const;
	std::uint32_t player_hp(const std::uintptr_t& player) const;
	std::vector<std::uintptr_t> get_controllers() const;
	std::vector<std::uintptr_t> get_pawns() const;

private:
	Memory mem;
	std::uintptr_t m_client;
};
