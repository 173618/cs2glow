#include "./includes/includes.h"

DWORD Memory::get_proc_id()
{
	PROCESSENTRY32W proc_entry32;

	proc_entry32.dwSize = sizeof(PROCESSENTRY32W);

	//Snapshot aller laufenden Prozesse
	const auto h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

	//Hat der snapshot geklappt?
	if (h_snap == INVALID_HANDLE_VALUE)
	{
		std::cout << "[-] Snapshot failed with error code: 0x" << std::hex << GetLastError() << std::endl;
		return 0;
	}

	//Durch den Snapshot iterieren und nach cs2 suchen
	while (Process32NextW(h_snap, &proc_entry32))
	{	
		if (!_wcsicmp(proc_entry32.szExeFile, L"cs2.exe"))
		{
			this->m_proc_id = proc_entry32.th32ProcessID;
			CloseHandle(h_snap);
			return this->m_proc_id;
		}
	}
	CloseHandle(h_snap);
	return 0;
}

std::uintptr_t Memory::get_module_base()
{
	std::uintptr_t module_base = 0;
	MODULEENTRY32W mod_entry;
	mod_entry.dwSize = sizeof(mod_entry);

	while (module_base == 0)
	{
		//Snapshot aller Module die der Prozess geladen hat
		const HANDLE h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->m_proc_id);
		while (Module32NextW(h_snap, &mod_entry))
		{
			//Suche nach client.dll
			if (!_wcsicmp(mod_entry.szModule, L"client.dll"))
			{
				module_base = reinterpret_cast<std::uintptr_t>(mod_entry.modBaseAddr);
				std::cout << "[+] Got client.dll -> 0x" << std::hex << module_base << std::endl;
				this->m_client = module_base;
				return module_base;
			}
		}
		Sleep(2000);
	}
	return 0;
}

HANDLE Memory::get_handle()
{
	do
	{
		//Proc ID holen
		this->get_proc_id();
		if(this->m_proc_id == 0)
			continue;
		//Handle öffnen
		this->m_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->m_proc_id);
		if (this->m_handle != NULL)
		{
			//Return wenns geklappt hat
			std::cout << "[+] Got HANDLE!" << std::endl;
			return this->m_handle;
		}
		Sleep(3000);
	} while (this->m_handle == NULL);
}

void Memory::close_handle()
{
	if (this->m_handle != NULL)
		CloseHandle(this->m_handle);
}
