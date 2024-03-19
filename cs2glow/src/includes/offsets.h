#pragma once

namespace offsets 
{
	//Main addresses
	constexpr DWORD64 dwEntityList = 0x18C2D58;
	constexpr DWORD64 dwLocalPlayerController = 0x1912578;
	constexpr DWORD64 dwLocalPlayerPawn = 0x17371A8;
	
	//Other offsets
	constexpr DWORD64 m_iIDEntIndex = 0x15A4;
	constexpr DWORD64 controller_spacing = 0x78;
	constexpr DWORD64 m_hPlayerPawn = 0x7E4;
	constexpr DWORD64 m_flDetectedByEnemySensorTime = 0x1440;
	constexpr DWORD64 s_teamnum_offset = 0x3CB;
	constexpr DWORD64 s_dwPawnHealth_offset = 0x334;
}


namespace active 
{
	inline bool glow = false;
	inline bool trigger = false;
}