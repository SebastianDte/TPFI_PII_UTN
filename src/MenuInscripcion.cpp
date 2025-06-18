#include "MenuInscripcion.h"
#include <string>
#include <iostream>
#include "Utilidades.h"
void MenuInscripcion::mostrarMenu() {
	InscripcionManager inscripcionManager;
	Utilidades _utilidades;
	int opcion;
	do {
		system("cls");
		_utilidades.limpiarPantallaConEncabezado("MENÚ INSCRIPCION");
		std::cout << "1. Alta Inscripcion\n";
		std::cout << "2. Baja Inscripcion\n";
		std::cout << "3. Modificar Inscripcion\n";
		std::cout << "4. Listar Inscripciones Activas\n";
		std::cout << "5. Listar Inscripciones Inactivas\n";
		std::cout << "6. Listar Todas las Inscripciones\n";
		std::cout <<  "7. Buscar Inscripcion por ID\n";
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
		case 5:
			inscripcionManager.listarInscripcionesInactivas();
			break;
		case 6:
			inscripcionManager.listarTodasInscripciones();
			break;
		case 7:
			int id;
			std::cout << "Ingrese el ID de la inscripción a buscar: ";
			std::cin >> id;
			_utilidades.limpiarPantallaConEncabezado("MENÚ INSCRIPCION");
			inscripcionManager.mostrarInscripcionPorId(id);
			break;
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
