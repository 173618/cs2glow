#include "./includes/includes.h"

int main()
{
	bool running = true;

	//memory stuff
	Memory mem;
	mem.get_handle();
	const auto client = mem.get_module_base();

	Entity ent(mem, client);
	Glow glow(mem, ent);

	//hack loop
	while (running == true)
	{
		glow.glow_loop();
		if (GetAsyncKeyState(VK_F9) &1)
			running = false;
	}
	mem.close_handle();
}
