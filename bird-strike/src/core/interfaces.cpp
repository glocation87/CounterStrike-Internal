#include <iostream>
#include "interfaces.h"


void Interface::Initialize() noexcept
{
	// init interface vars
	client = Get<IBaseClientDLL>(L"client.dll", "VClient018");
	entityList = Get<IClientEntityList>(L"client.dll", "VClientEntityList003");
	clientMode = **reinterpret_cast<IClientModeShared***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
	globals = **reinterpret_cast<IGlobalVars***>((*reinterpret_cast<uintptr_t**>(client))[11] + 10);
	debugOverlay = Get<IVDebugOverlay>(L"engine.dll", "VDebugOverlay004");
	engine = Get<IVEngineClient>(L"engine.dll", "VEngineClient014");
	modelInfo = Get<IVModelInfo>(L"engine.dll", "VModelInfoClient004");

	// get the exported KeyValuesSystem function
	if (const HINSTANCE handle = GetModuleHandle(L"vstdlib.dll"))
		// set our pointer by calling the function
		keyValuesSystem = reinterpret_cast<void* (__cdecl*)()>(GetProcAddress(handle, "KeyValuesSystem"))();
}

template <typename T>
T* Interface::Get(LPCWSTR module, const char* interface) noexcept
{
	HMODULE handle = GetModuleHandle(module);

	if (!handle)
	{
		std::cout << "GetModuleHandle returned NULL for " << module << std::endl;
		return nullptr;
	}

	using interfacePrototype = T*(__cdecl*)(const char*, int*);
	interfacePrototype createInterface = reinterpret_cast<interfacePrototype>(GetProcAddress(handle, "CreateInterface"));
	return createInterface(interface, nullptr);
}