#include "./includes/includes.h"

int main()
{
	bool running = true;

	//memory stuff
	Memory mem;
	mem.get_handle();
	const auto client = mem.get_module_base();

	Entity ent(mem, client);
	Hacks hack(mem, ent);
	std::cout << "\n\n--------------------------------------------------\n";
	std::cout << "Welcome" << std::endl;
	std::cout << "Glow - F1" << std::endl;
	std::cout << "Trigger - F2 (key = Mouse5)" << std::endl;
	//hack loop
	while (running == true)
	{
		if (GetAsyncKeyState(VK_F9) & 1)
		{
			running = false;
		}
		if (GetAsyncKeyState(VK_F1) & 1)
		{
			active::glow = !active::glow;
			std::cout << "Glow: " << std::boolalpha << active::glow << std::endl;
		}
		if (GetAsyncKeyState(VK_F2) & 1)
		{
			active::trigger = !active::trigger;
			std::cout << "Trigger: " << std::boolalpha << active::trigger << std::endl;
		}
		hack.hack_loop();
	}
	mem.close_handle();
}
