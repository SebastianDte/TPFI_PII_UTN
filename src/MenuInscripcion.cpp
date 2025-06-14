#include "MenuInscripcion.h"
#include <string>
#include <iostream>

void MenuInscripcion::mostrarMenu() {
	InscripcionManager inscripcionManager;
	int opcion;
	do {
		system("cls");
		std::cout << "=== MENU INSCRIPCION ===\n";
		std::cout << "1. Alta Inscripcion\n";
		std::cout << "2. Baja Inscripcion\n";
		std::cout << "3. Modificar Inscripcion\n";
		std::cout << "4. Listar Inscripciones\n";
		std::cout << "0. Volver al Menu Principal\n";
		std::cout << "===========================\n";
		std::cout << "Ingrese una opcion: ";
		std::cin >> opcion;
		system("cls");
		switch (opcion) {
		case 1:
			inscripcionManager.altaInscripcion();
			break;
		case 2:
			inscripcionManager.bajaInscripcion();
			break;
		case 3:
			inscripcionManager.modificarInscripcion();
			break;
		case 4:
			inscripcionManager.listarInscripcionesActivas();
			break;
		case 0:
			std::cout << "Volviendo al menu principal...\n";
			break;
		default:
			std::cout << "Opcion invalida, intente nuevamente.\n";
			break;
		}
		std::cout << std::endl;
		system("pause");
	} while (opcion != 0);
}
