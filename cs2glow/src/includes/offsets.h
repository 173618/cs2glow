#pragma once

namespace offsets 
{
	//Main addresses
	constexpr DWORD64 dwEntityList = 0x18B3FA8;
	constexpr DWORD64 dwLocalPlayerController = 0x19038F8;
	
	//Other offsets
	constexpr DWORD64 controller_spacing = 0x78;
	constexpr DWORD64 m_hPlayerPawn = 0x7E4;
	constexpr DWORD64 m_flDetectedByEnemySensorTime = 0x1440;
}


namespace active 
{
	inline bool glow = false;
	inline bool trigger = false;
}