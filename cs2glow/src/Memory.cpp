#include "./includes/includes.h"

DWORD Memory::get_proc_id()
{
	PROCESSENTRY32W proc_entry32;

	proc_entry32.dwSize = sizeof(PROCESSENTRY32W);

	//Snapshot of all running processes
	const auto h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

	//Snapshot valid?
	if (h_snap == INVALID_HANDLE_VALUE)
	{
		std::cout << "[-] Snapshot failed with error code: 0x" << std::hex << GetLastError() << std::endl;
		return 0;
	}

	//Iterate through all snapshot entrys to find the correct one
	while (Process32NextW(h_snap, &proc_entry32))
	{	
		if (!_wcsicmp(proc_entry32.szExeFile, L"cs2.exe"))
		{
			//Get the proc ID of the cs2 Process
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
		//Snapshot through all modules
		const HANDLE h_snap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->m_proc_id);
		while (Module32NextW(h_snap, &mod_entry))
		{
			//Search for client.dll
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
		//get Proc ID
		this->get_proc_id();
		if(this->m_proc_id == 0)
			continue;
		//Open HANDLE
		this->m_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, this->m_proc_id);
		if (this->m_handle != NULL)
		{
			//Return if it worked
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
