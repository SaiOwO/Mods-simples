#include "pch.h"

void Salto(BYTE* address, DWORD jumpTo, DWORD length)
{
    DWORD oldProtect, newProtect, relativeAddress;
    VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &oldProtect);
    relativeAddress = (DWORD)(jumpTo - (DWORD)address) - 5;
    *address = 0xE9;
    *((DWORD*)(address + 0x1)) = relativeAddress;
    for (DWORD x = 0x5; x < length; x++)
    {
        *(address + x) = 0x90;
    }
    VirtualProtect(address, length, oldProtect, &newProtect);
}

DWORD base = (DWORD)GetModuleHandleA(0);
DWORD libcocosbase = (DWORD)GetModuleHandleA("libcocos2d.dll");

DWORD botonRET = base + 0x190BD5;

DWORD createMenu = base + 0x18EE0;
DWORD createWithSpriteFrameName = base + 0x282284;
DWORD createWithSpriteFrameName_ = (DWORD)createWithSpriteFrameName;
DWORD statsBtn = base + 0x2CD6D4;

const char* Textura_ = "GJ_reportBtn_001.png";
DWORD Textura = (DWORD)Textura_;

const char* Titulo_ = "Creditos";
DWORD Titulo = (DWORD)Titulo_;

const char* Texto_ = "<cp>BetterEdit hecho por:</c> HJfod\n<cg>New Icons Texture Pack hecho por:</c> Ghost Power\n<co>Run Info hecho por:</c> Matcool\n<co>Sum Attempts hecho por:</c> Matcool\n<cy>Este boton esta hecho por:</c> Sai";
DWORD Texto = (DWORD)Texto_;
int Cantidad_de_letras = 204;

const char* Boton_OK_ = "OK";
DWORD Boton_OK = (DWORD)Boton_OK_;

DWORD cocos_1 = base + 0xF840;
DWORD cocos_2 = base + 0x22730;
DWORD cocos_3 = base + 0x261E27;
DWORD Valor_NULL = base + 0x31E000;

__declspec(naked) void boton() {
    __asm {
        push Textura
        call dword ptr[createWithSpriteFrameName]
        mov esi, eax
        mov dword ptr[esp], 0x3F800000
        mov ecx, esi
        mov edx, [esi]
        call dword ptr[edx + 0x50]
        push Accion
        push ebx
        mov ecx, esi
        call createMenu
        mov ecx, eax
        add esp, 0x08
        mov eax, [esp + 0x18]
        mov[esp + 0x48], ecx
        push ecx
        mov edx, [eax]
        mov ecx, eax
        call dword ptr[edx + 0x000000E0]
        push statsBtn
        jmp botonRET

        Accion:
            push ebp
            mov ebp, esp
            and esp, -8
            sub esp, 0x08
            mov eax, [Valor_NULL]
            xor eax, esp
            mov[esp + 0x04], eax
            sub esp, 0x18
            mov ecx, esp
            push Cantidad_de_letras
            mov dword ptr[ecx + 0x14], 0x0000000F
            mov dword ptr[ecx + 0x10], 0x00000000
            push Texto
            mov byte ptr[ecx], 0x00
            call cocos_1
            push ecx
            mov dword ptr[esp], 0x43C80000
            mov edx, Titulo
            push 0x00
            push Boton_OK
            xor ecx, ecx
            call cocos_2
            mov ecx, eax
            add esp, 0x24
            mov eax, [ecx]
            call dword ptr[eax + 0x000001FC]
            mov ecx, [esp + 0x04]
            xor ecx, esp
            mov esp, ebp
            pop ebp
            ret 0x0004
    }
}

__declspec(naked) void pointer() {
    __asm {
        pushad
        mov eax, createWithSpriteFrameName_
        mov eax, [eax]
        mov[createWithSpriteFrameName], eax
        popad
        ret
    }
}

__declspec(dllexport) void CodigoDeSai() {
    pointer();
    Salto((BYTE*)base + 0x190BD0, (DWORD)boton, 0x5);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)CodigoDeSai, hModule, 0, nullptr);
    return TRUE;
}
