#include "./includes/includes.h"

std::uintptr_t Entity::get_entity_list_base() const
{
	return this->mem.read<std::uintptr_t>(this->m_client + offsets::dwEntityList);
}

std::uintptr_t Entity::local_pawn() const
{
	return this->mem.read<std::uintptr_t>(this->m_client + offsets::dwLocalPlayerPawn);
}

std::uintptr_t Entity::local_player() const
{
	return this->mem.read<std::uintptr_t>(this->m_client + offsets::dwLocalPlayerController);
}

bool Entity::teamcheck(const std::uintptr_t &player) const
{
	const auto local_team = this->mem.read<std::uint32_t>(this->local_player() + offsets::s_teamnum_offset);
	const auto player_team = this->mem.read<std::uint32_t>(player + offsets::s_teamnum_offset);
	if (local_team == player_team)
		return true;
	return false;
}

std::uintptr_t Entity::crsh_idx_to_controller(const std::int32_t& idx) const
{
	const auto ent_list = this->get_entity_list_base();
	const auto entry = mem.read<std::uintptr_t>(ent_list + 0x8 * (idx >> 9) + 16);
	return mem.read<std::uintptr_t>(entry + 120 * (idx & 0x1FF));
}

std::uint32_t Entity::player_hp(const std::uintptr_t& player) const
{
	return mem.read<std::uint32_t>(player + offsets::s_dwPawnHealth_offset);
}

std::vector<std::uintptr_t> Entity::get_controllers() const
{
	std::vector<std::uintptr_t> controller_list;
	const auto entity_base = this->get_entity_list_base();
	const auto controller_list_address = this->mem.read<std::uintptr_t>(entity_base + 0x10);
	const auto local_player = this->mem.read<std::uintptr_t>(this->m_client + offsets::dwLocalPlayerController);

	for (std::size_t i = 0; i < 64; ++i)
	{
		auto buffer = mem.read<std::uintptr_t>(controller_list_address + (offsets::controller_spacing * (i + 1)));
		if (buffer == 0)
			continue;
		if (buffer == local_player)
			continue;
		controller_list.push_back(buffer);
	}
	return controller_list;
}

std::vector<std::uintptr_t> Entity::get_pawns() const
{
	std::vector<std::uintptr_t> pawn_list;
	const auto entity_base = this->get_entity_list_base();
	const auto controller_list = this->get_controllers();
	for (std::size_t i = 0; i < controller_list.size(); ++i)
	{
		const auto pawn_handle = mem.read<std::uint32_t>(controller_list[i] + offsets::m_hPlayerPawn);
		const auto pawn_base = mem.read<std::uintptr_t>(entity_base + 0x10 + 8ll * ((pawn_handle & 0x7FFF) >> 9));
		if (pawn_base == 0)
			continue;
		const auto pawn = mem.read<std::uintptr_t>(pawn_base + offsets::controller_spacing * (pawn_handle & 0x1FF));
		if (pawn == 0)
			continue;
		pawn_list.push_back(pawn);
	}
	return pawn_list;
}
  