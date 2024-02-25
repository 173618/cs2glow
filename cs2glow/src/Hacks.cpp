#include "./includes/includes.h"

void Hacks::hack_loop()
{
	const auto pawn_list = this->ent.get_pawns();
	if (active::glow)
	{
		for (const auto pawn : pawn_list)
		{
			mem.write<float>((pawn + offsets::m_flDetectedByEnemySensorTime), 86400.f);
		}
	}
	if (!active::glow)
	{
		for (const auto pawn : pawn_list)
		{
			mem.write<float>((pawn + offsets::m_flDetectedByEnemySensorTime), 0.f);
		}
	}
	if (active::trigger)
	{

	}
}
