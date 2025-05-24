#include <iostream>
#include <locale>
using namespace std;
#include "menus/menuPrincipal.h"
#include "entidades/persona.h"
#include "entidades/fecha.h"
int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");
    MenuPrincipal menu;
    menu.mostrarMenuPrincipal();
    return 0;
}