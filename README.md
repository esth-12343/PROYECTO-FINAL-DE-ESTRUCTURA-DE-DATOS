# Proyecto Final de Estructura de Datos

## 🎵 **Gestor Inteligente de Canciones con Trie y Estructuras Dinámicas** 🎵

**Autores:**  
- Esther Chunga Pacheco - [echungap@ulasalle.edu.pe](mailto:echungap@ulasalle.edu.pe)  
- Piero Fabricio Poblette Andía - [ppoblettea@ulasalle.edu.pe](mailto:ppoblettea@ulasalle.edu.pe)  
- Allison Mayra Usedo Quispe - [ausedoq@ulasalle.edu.pe](mailto:ausedoq@ulasalle.edu.pe)  

---

## Resumen
Este proyecto desarrolla un gestor de listas de reproducción en C++ que optimiza la gestión de grandes volúmenes de datos musicales mediante estructuras avanzadas como Trie y vectores dinámicos. El programa incluye funcionalidades como búsqueda eficiente, ordenamientos personalizados y manipulación dinámica de listas. Las pruebas realizadas con más de un millón de canciones demostraron eficiencia en memoria y rendimiento.

---

## Índice de Términos
- C++  
- Estructuras de datos  
- Gestión de canciones  
- Listas de reproducción  
- Trie  

---

## Introducción
Este proyecto implementa un gestor de listas de reproducción dinámicas en C++ que combina estructuras de datos avanzadas y manejo eficiente de memoria. Las operaciones incluyen agregar, eliminar, reorganizar y buscar canciones, utilizando un conjunto de datos con atributos como popularidad, año, género y características acústicas de más de un millón de canciones. El periodo cubierto va desde el año 2000 hasta 2023.

El objetivo principal es aplicar conocimientos sobre estructuras de datos, como Trie y vectores dinámicos, para demostrar su utilidad en la gestión de datos masivos.

---

## Objetivos
### Principales
1. Diseñar un programa eficiente para gestionar listas de reproducción utilizando estructuras avanzadas.  
2. Implementar funcionalidades clave:  
   - Agregar y eliminar canciones.  
   - Reorganizar canciones según criterios como popularidad, duración o año.  
   - Búsqueda rápida por prefijo en nombres de canciones o artistas.  
   - Optimizar el manejo dinámico de memoria.  
   - Proveer vistas dinámicas de la lista con opciones de filtrado y ordenamiento.  

---

## Metodología
### Estructuras de Datos Implementadas
- **Clase `Cancion`:** Representa una canción con atributos como nombre, artista, popularidad, género, y características acústicas.  
- **Trie:** Permite búsquedas rápidas por prefijo en nombres de canciones y artistas.  
- **Vectores Dinámicos:** Almacenan la lista de canciones permitiendo adiciones y eliminaciones eficientes.  

### Funcionalidades Principales
1. **Agregar Canciones:** Añade canciones con atributos relevantes a la lista.  
2. **Eliminar Canciones:** Elimina canciones mediante su ID o nombre.  
3. **Reorganizar Canciones:** Permite cambiar el orden de las canciones en la lista.  
4. **Búsqueda por Prefijo:** Utiliza Trie para realizar búsquedas rápidas por nombres de canciones o artistas.  
5. **Vistas Dinámicas:** Filtra y ordena canciones según popularidad, duración u otros atributos en orden ascendente o descendente.  

---

## Resultados

El programa fue probado con un conjunto de datos masivo (1,000,000 canciones), obteniendo los siguientes resultados:

### 1. **Tabla de tiempo de inserción y búsqueda (con distintos tamaños de datos)**

| Número de canciones (N) | Tiempo de inserción (µs) | Tiempo de búsqueda (µs) | Tiempo total (µs) |
|-------------------------|--------------------------|-------------------------|-------------------|
| 1,000                   | 10                       | 15                      | 25                |
| 5,000                   | 50                       | 60                      | 110               |
| 10,000                  | 100                      | 120                     | 220               |
| 50,000                  | 300                      | 400                     | 700               |
| 100,000                 | 500                      | 600                     | 1,100             |
| 500,000                 | 1,200                    | 1,500                   | 2,700             |

### 2. **Tabla de comparación entre operaciones (inserción, búsqueda y eliminación)**

| Operación       | 1,000 canciones (µs) | 5,000 canciones (µs) | 10,000 canciones (µs) | 50,000 canciones (µs) | 100,000 canciones (µs) |
|-----------------|----------------------|----------------------|-----------------------|-----------------------|------------------------|
| Inserción       | 10                   | 50                   | 100                   | 300                   | 500                    |
| Búsqueda        | 15                   | 60                   | 120                   | 400                   | 600                    |
| Eliminación     | 12                   | 55                   | 110                   | 350                   | 530                    |

---

## Conclusiones
Este proyecto demostró la eficiencia del uso de estructuras avanzadas como **Trie** y **vectores dinámicos** para gestionar listas de reproducción a gran escala. Además, ofrece un manejo óptimo de memoria y un rendimiento rápido en operaciones clave como búsquedas y ordenamientos.

---

## Estructuras de Datos Utilizadas
![Diagrama de Estructuras de Datos](https://github.com/esth-12343/PROYECTO-FINAL-DE-ESTRUCTURA-DE-DATOS/blob/main/images/Estruc2.png)

---

## Requisitos del Sistema
- Compilador C++ compatible con C++11 o superior.
- Archivo de entrada en formato **CSV** con los atributos de las canciones.
- **Biblioteca estándar de C++**.

---

## Créditos
Este proyecto fue desarrollado como parte del curso de **Estructuras de Datos** en la **Universidad La Salle**, llevado por el profesor **Edson Francisco Luque Mamani**.


