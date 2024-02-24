#pragma once

namespace offsets 
{
	//Main offsets
	constexpr DWORD64 dwEntityList = 0x18B3FA8;
	
	//Other offsets
	constexpr DWORD64 controller_spacing = 0x78;
}


namespace active 
{
	inline bool glow = false;
	inline bool trigger = false;
}