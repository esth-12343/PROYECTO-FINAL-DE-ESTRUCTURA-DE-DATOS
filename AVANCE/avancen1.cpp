#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

class Cancion {
private:
    string artist_name;
    string track_name;
    string track_id;
    int popularity;
    int year;
    string genre;
    float danceability;
    float energy;
    int key;
    float loudness;
    bool mode;
    float speechiness;
    float acousticness;
    float instrumentalness;
    float liveness;
    float valence;
    float tempo;
    int duration_ms;
    int time_signature;

public:
    Cancion(string artist_name, string track_name, string track_id, int popularity, int year,
          string genre, float danceability, float energy, int key, float loudness, bool mode,
          float speechiness, float acousticness, float instrumentalness, float liveness,
          float valence, float tempo, int duration_ms, int time_signature)
        : artist_name(artist_name), track_name(track_name), track_id(track_id),
          popularity(popularity), year(year), genre(genre), danceability(danceability),
          energy(energy), key(key), loudness(loudness), mode(mode),
          speechiness(speechiness), acousticness(acousticness),
          instrumentalness(instrumentalness), liveness(liveness),
          valence(valence), tempo(tempo), duration_ms(duration_ms),
          time_signature(time_signature) {}

    string getTrackName() const { return track_name; }
    string getArtistName() const { return artist_name; }
    // Otros getters según sea necesario...
};

class Nodo {
public:
    Cancion cancion;
    Nodo* siguiente;

    Nodo(const Cancion& c) : cancion(c), siguiente(nullptr) {}
};

class ListaReproduccion {
private:
    Nodo* cabeza;
    int tamano;

public:
    ListaReproduccion() : cabeza(nullptr), tamano(0) {}

    // Función para agregar una canción al final de la lista
    void agregar_cancion(const Cancion& c) {
        Nodo* nuevo = new Nodo(c);
        if (!cabeza) {
            cabeza = nuevo;
        } else {
            Nodo* temp = cabeza;
            while (temp->siguiente) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }
        tamano++;
    }

    // Función para eliminar una canción por su nombre
    void eliminar_cancion(const string& nombreCancion) {
        Nodo* temp = cabeza;
        Nodo* anterior = nullptr;

        while (temp && temp->cancion.getTrackName() != nombreCancion) {
            anterior = temp;
            temp = temp->siguiente;
        }

        if (temp) { // Canción encontrada
            if (anterior) {
                anterior->siguiente = temp->siguiente;
            } else {
                cabeza = temp->siguiente;
            }
            delete temp;
            tamano--;
            cout << "Canción eliminada: " << nombreCancion << endl;
        } else {
            cout << "Canción no encontrada: " << nombreCancion << endl;
        }
    }

    // Función para cambiar la posición de una canción en la lista
    void cambiar_orden(int posicion_actual, int nueva_posicion) {
        if (posicion_actual < 0 || posicion_actual >= tamano || nueva_posicion < 0 || nueva_posicion >= tamano) {
            cout << "Posición no válida.\n";
            return;
        }

        if (posicion_actual == nueva_posicion) return;

        // Obtener el nodo en la posición actual y su anterior
        Nodo* temp = cabeza;
        Nodo* anterior_actual = nullptr;

        for (int i = 0; i < posicion_actual; ++i) {
            anterior_actual = temp;
            temp = temp->siguiente;
        }
        Nodo* cancion_a_mover = temp;

        // Remover el nodo de la posición actual
        if (anterior_actual) {
            anterior_actual->siguiente = cancion_a_mover->siguiente;
        } else {
            cabeza = cancion_a_mover->siguiente;
        }

        // Insertar el nodo en la nueva posición
        temp = cabeza;
        Nodo* anterior_nueva = nullptr;
        for (int i = 0; i < nueva_posicion; ++i) {
            anterior_nueva = temp;
            temp = temp->siguiente;
        }

        if (anterior_nueva) {
            cancion_a_mover->siguiente = anterior_nueva->siguiente;
            anterior_nueva->siguiente = cancion_a_mover;
        } else {
            cancion_a_mover->siguiente = cabeza;
            cabeza = cancion_a_mover;
        }

        cout << "La canción ha sido movida de la posición " << posicion_actual << " a " << nueva_posicion << endl;
    }

    // Función para leer un archivo CSV y agregar las canciones a la lista
    void leerArchivoCSV(const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        if (!archivo.is_open()) {
            cout << "No se pudo abrir el archivo.\n";
            return;
        }

        string linea;
        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string artist_name, track_name, track_id, genre;
            int popularity, year, key, duration_ms, time_signature;
            float danceability, energy, loudness, speechiness, acousticness;
            float instrumentalness, liveness, valence, tempo;
            bool mode;

            // Leer cada campo separado por comas
            getline(ss, artist_name, ',');
            getline(ss, track_name, ',');
            getline(ss, track_id, ',');
            ss >> popularity;
            ss.ignore(1);
            ss >> year;
            ss.ignore(1);
            getline(ss, genre, ',');
            ss >> danceability;
            ss.ignore(1);
            ss >> energy;
            ss.ignore(1);
            ss >> key;
            ss.ignore(1);
            ss >> loudness;
            ss.ignore(1);
            ss >> mode;
            ss.ignore(1);
            ss >> speechiness;
            ss.ignore(1);
            ss >> acousticness;
            ss.ignore(1);
            ss >> instrumentalness;
            ss.ignore(1);
            ss >> liveness;
            ss.ignore(1);
            ss >> valence;
            ss.ignore(1);
            ss >> tempo;
            ss.ignore(1);
            ss >> duration_ms;
            ss.ignore(1);
            ss >> time_signature;

            Cancion cancion(artist_name, track_name, track_id, popularity, year, genre,
                            danceability, energy, key, loudness, mode, speechiness,
                            acousticness, instrumentalness, liveness, valence, tempo,
                            duration_ms, time_signature);
            agregar_cancion(cancion);
        }

        archivo.close();
    }

    // Función para imprimir la lista de canciones
    void imprimirCanciones() const {
        Nodo* temp = cabeza;
        while (temp) {
            cout << "Artista: " << temp->cancion.getArtistName()
                 << ", Título: " << temp->cancion.getTrackName() << endl;
            temp = temp->siguiente;
        }
    }

    ~ListaReproduccion() {
        while (cabeza) {
            Nodo* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

int main() {
    ListaReproduccion lista;

    // Leer el archivo CSV y agregar canciones a la lista
    lista.leerArchivoCSV("canciones.csv");

    // Imprimir las canciones para verificar que fueron cargadas
    lista.imprimirCanciones();

    // Ejemplo de agregar, eliminar y cambiar de posición
    Cancion nuevaCancion("Nuevo Artista", "Nueva Cancion", "1234", 90, 2021, "Pop", 0.8, 0.9, 5, -5.0, true, 0.1, 0.2, 0.0, 0.3, 0.5, 120.0, 200000, 4);
    lista.agregar_cancion(nuevaCancion);
    lista.eliminar_cancion("Nueva Cancion");
    lista.cambiar_orden(0, 2);

    return 0;
}