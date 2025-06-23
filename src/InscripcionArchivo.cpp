#include "InscripcionArchivo.h"
#include "Inscripcion.h"


InscripcionArchivo::InscripcionArchivo(const std::string& n) {
	strncpy(_nombreArchivo, n.c_str(), sizeof(_nombreArchivo));
	_nombreArchivo[sizeof(_nombreArchivo) - 1] = '\0';
	_tamanioRegistro = sizeof(Inscripcion);
}

bool InscripcionArchivo::alta(const Inscripcion& regInscripcion) {
	FILE* pInscripcion = fopen(_nombreArchivo, "ab");
	if (pInscripcion == nullptr) return false;
	bool escribio = fwrite(&regInscripcion, _tamanioRegistro, 1, pInscripcion) == 1;
	fclose(pInscripcion);
	return escribio;
}

int InscripcionArchivo::buscar(int idInscripcion) const {
	FILE* pInscripcion = fopen(_nombreArchivo, "rb");
	if (pInscripcion == nullptr) return -1;
	Inscripcion inscripcionEncontrada;
	int posicion = 0;
	while (fread(&inscripcionEncontrada, _tamanioRegistro, 1, pInscripcion) == 1) {
		if (inscripcionEncontrada.getEstado() == true && inscripcionEncontrada.getIdInscripcion() == idInscripcion) {
			fclose(pInscripcion);
			return posicion;
		}
		posicion++;
	}
	fclose(pInscripcion);
	return -1;

}

bool InscripcionArchivo::baja(int idInscripcion) {
	int posicion = buscar(idInscripcion);
	if (posicion == -1) return false;

	Inscripcion inscripcion;
	if (!leer(posicion, inscripcion)) return false;

	inscripcion.setEstado(false);
	return modificar(inscripcion, posicion);
}

bool InscripcionArchivo::modificar(const Inscripcion& regInscripcion, int posicion) {
	FILE* pInscripcion = fopen(_nombreArchivo, "r+b");
	if (pInscripcion == nullptr) return false;
	fseek(pInscripcion, posicion * _tamanioRegistro, SEEK_SET);
	bool escribio = fwrite(&regInscripcion, _tamanioRegistro, 1, pInscripcion) == 1;
	fclose(pInscripcion);
	return escribio;
}

bool InscripcionArchivo::leer(int posicion, Inscripcion& insc) const {
	FILE* pInscripcion = fopen(_nombreArchivo, "rb");
	if (pInscripcion == nullptr) return false;
	if (fseek(pInscripcion, posicion * _tamanioRegistro, SEEK_SET) != 0) {
		fclose(pInscripcion);
		return false;
	}
	bool ok = fread(&insc, _tamanioRegistro, 1, pInscripcion) == 1;
	fclose(pInscripcion);
	return ok;
}

int InscripcionArchivo::cantRegistros() const {
	FILE* pInscripcion = fopen(_nombreArchivo, "rb");
	if (pInscripcion == nullptr) return 0;
	fseek(pInscripcion, 0, SEEK_END);
	int cantidad = ftell(pInscripcion) / _tamanioRegistro;
	fclose(pInscripcion);
	return cantidad;
}

int InscripcionArchivo::obtenerProximoId() {
	int cantidad = cantRegistros();
	int maxId = 0;
	Inscripcion insc;
	for (int i = 0; i < cantidad; i++) {
		if (leer(i, insc)) {
			if (insc.getIdInscripcion() > maxId) {
				maxId = insc.getIdInscripcion();
			}
		}
	}
	return maxId + 1;
}

