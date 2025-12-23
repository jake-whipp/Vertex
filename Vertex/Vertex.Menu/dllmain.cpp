// dllmain.cpp : The entry point for the Vertex DLL application.
#include "pch.h"

DWORD WINAPI MainThread(LPVOID lpParam) {
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        HANDLE hMainThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, NULL);

        if (hMainThread != NULL)
        {
            CloseHandle(hMainThread);
        }
        else
        {
            DWORD error = GetLastError();
            // TODO: Log error
        }
        break;
    }

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
