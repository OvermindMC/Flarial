#include "Client/Client.h"

auto init(HMODULE hModule) -> void {

    new Client("Flarial");

};

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)init, hModule, 0, 0);
    
    return TRUE;

};