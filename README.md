# 📚 Sistema de Gestión Escolar - Trabajo Final Integrador (UTN)

Este proyecto fue realizado como **Trabajo Final Integrador** de la materia *Programación II* en la UTN. Se trata de una aplicación de consola en **C++**, desarrollada de forma grupal, que gestiona los datos de una institución educativa.

## 🧩 Estructura del Proyecto

El sistema está dividido en **módulos independientes**, cada uno con sus respectivas capas:

- **Entidad**: clases que representan objetos del sistema.
- **Archivo**: clases que manejan persistencia en archivos binarios.
- **Manager**: lógica de negocio (altas, bajas, modificaciones, consultas).
- **Menú**: interfaz de usuario en consola para interactuar con el módulo.

## 📦 Módulos del Sistema

- **Alumnos**: altas, bajas, modificación, búsqueda por legajo, listados ordenados y filtrados.
- **Docentes**: gestión por ID, listados por nombre.
- **Cursos**: creación, asignación de docentes, cupo máximo, estado (activo/inactivo).
- **Inscripciones**: asociación alumno-curso, control de cupos, importe y fecha.
- **Reportes**: generación de estadísticas académicas y financieras.

## 📊 Reportes disponibles

- Cantidad de inscriptos por curso.
- Total recaudado por curso o alumno.
- Cursos sin cupo disponible.
- Inscripciones por fecha o entre fechas.
- Profesores con cursos asignados.

## 🛠️ Herramientas y tecnologías

- **Lenguaje**: C++
- **Paradigma**: Programación Orientada a Objetos
- **Persistencia**: Archivos binarios
- **Entorno**: Consola

---

> Este trabajo fue realizado por los estudiantes Sebastián Duarte, Mauro Arias, Kimberly Blandón y Julián Mondillo.
