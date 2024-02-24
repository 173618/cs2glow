#include "./includes/includes.h"

std::uintptr_t Entity::get_entity_list_base() const
{
	return this->mem.read<std::uintptr_t>(this->m_client + offsets::dwEntityList);
}

std::vector<std::uintptr_t> Entity::get_controllers() const
{
	std::vector<std::uintptr_t> controller_list;
	const auto entity_base = this->get_entity_list_base();
	const auto controller_list_address = this->mem.read<std::uintptr_t>(entity_base + 0x10);
	for (std::size_t i = 0; i < 64; ++i)
	{
		auto buffer = mem.read<std::uintptr_t>(controller_list_address + (offsets::controller_spacing * i));
		if (buffer == 0)
			continue;
		controller_list.push_back(buffer);
	}
	return controller_list;
}

std::vector<std::uintptr_t> Entity::get_pawns() const
{
	std::vector<std::uintptr_t> pawn_list;
}
  