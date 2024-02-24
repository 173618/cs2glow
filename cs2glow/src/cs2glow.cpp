#include "./includes/includes.h"

int main()
{
	bool running = true;

	//memory stuff
	Memory mem;
	mem.get_handle();
	auto client = mem.get_module_base();

	//hack loop
	while (running == true)
	{
		std::uintptr_t entity = mem.read<std::uintptr_t>(client + offsets::dwEntityList);
		//std::cout << std::hex << "0x" << entity << std::endl;
		if (GetAsyncKeyState(VK_F9) &1)
			running = false;
	}
}
