#include "util/includes.h"

void DebugMode()
{
    AllocConsole();
    FILE* console;
    freopen_s(&console, "CONOUT$", "w", stdout);

    SetConsoleTitle(L"bird-strike | w00d7");
    std::cout << "Debug Mode Enabled" << std::endl;
}

DWORD WINAPI Entry(void* param)
{
#if _DEBUG
    DebugMode();
#endif


    while (!GetAsyncKeyState(VK_END))
        Sleep(200);

    return 1;
}

void InitializeThread(HMODULE* hModule)
{
    DisableThreadLibraryCalls(*hModule);
    const auto injectionThread = CreateThread(
        nullptr,
        NULL,
        reinterpret_cast<LPTHREAD_START_ROUTINE>(Entry),
        nullptr,
        NULL,
        nullptr
    );
    
    if (injectionThread)
        CloseHandle(injectionThread);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        InitializeThread(&hModule);
    case DLL_PROCESS_DETACH:

        break;
    }
    return TRUE;
}