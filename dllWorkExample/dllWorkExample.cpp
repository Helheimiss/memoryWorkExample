#include <iostream>
#include <cstdint>
#include <Windows.h>


DWORD WINAPI MainThread(LPVOID hModule)
{
    /* bad idea for a console app
    FILE* fl;
    freopen_s(&fl, "CONOUT$", "w", stdout);
    
    std::cout << "test" << std::endl;

    system("pause");

    fclose(stdout);
    FreeConsole();
    */

    // for static memory
    // may change during recompilation
    // uintptr_t bss_int_ptr = 0x???;
    // uintptr_t global_int_ptr = 0x???;

    // for heap/stack memory
    // may change with some code modifications
    uintptr_t ptrOffset = 0x000A5018;
    uintptr_t offsets[] = {0x60};
    size_t offsetCount = std::size(offsets);
    size_t varSize = sizeof(int);
    uintptr_t heap_int_ptr {}; // null


    const uintptr_t basePtr = reinterpret_cast<uintptr_t>(GetModuleHandleA("memoryWorkExample.exe"));
    if (!basePtr) return 1;

    uintptr_t currentPtr = *reinterpret_cast<uintptr_t*>(basePtr + ptrOffset);
    for (size_t i = 0; i < offsetCount; i++)
        currentPtr += offsets[i];

    if (IsBadReadPtr(reinterpret_cast<void*>(currentPtr), varSize))
        return 1;

    heap_int_ptr = currentPtr;
    // end for heap/stack memory


    // try write
    // *(int *)bss_int_ptr = -1;    // may change during recompilation
    // *(int *)global_int_ptr = -1; // may change during recompilation
    *(int *)heap_int_ptr = -1;      // may change with some code modifications


    FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(hModule), 0);
    return 0;
}




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        // AllocConsole(); // bad idea for a console app
        MessageBoxA(NULL, "1) DLL_PROCESS_ATTACH", "notification", MB_OK);
        CreateThread(nullptr, 0, MainThread, hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
        MessageBoxA(NULL, "2) DLL_THREAD_ATTACH", "notification", MB_OK);
        break;
    case DLL_THREAD_DETACH:
        MessageBoxA(NULL, "3) DLL_THREAD_DETACH", "notification", MB_OK);
        break;
    case DLL_PROCESS_DETACH:
        MessageBoxA(NULL, "4) DLL_PROCESS_DETACH", "notification", MB_OK);
        break;
    }
    return TRUE;
}