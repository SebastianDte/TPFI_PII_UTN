#include <iostream>
#include <locale>
#include <windows.h>
#include "MenuPrincipal.h"

using namespace std;

int main()
{
    //setlocale(LC_ALL, "es_ES.UTF-8");


    // config para poder ver en windows los caracteres especiales
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "");

    MenuPrincipal menu;
    menu.mostrarMenuPrincipal();
    return 0;
}
