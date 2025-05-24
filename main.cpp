#include <iostream>
#include <locale>
#include "MenuPrincipal.h"
#include "Persona.h"
#include "Fecha.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");
    MenuPrincipal menu;
    menu.mostrarMenuPrincipal();
    return 0;
}
