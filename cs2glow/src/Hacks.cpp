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
		POINT p;
		const auto local_player = ent.local_pawn();
		const auto idx = mem.read<std::int32_t>(local_player + offsets::m_iIDEntIndex);
		if (GetAsyncKeyState(0x06))
		{
			if (idx != -1)
			{
				GetCursorPos(&p);
				mouse_event(MOUSEEVENTF_LEFTDOWN, p.x, p.y, 0, 0);
				mouse_event(MOUSEEVENTF_LEFTUP, p.x, p.y, 0, 0);
			}
		}
	}
}
