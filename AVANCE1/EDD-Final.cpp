#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

// Clase Cancion
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
    // Constructor
    Cancion(int indice, string artist_name, string track_name, string track_id, int popularity, int year,
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

    // Métodos getter
    string getArtistName() const { return artist_name; }
    string getTrackName() const { return track_name; }
    string getTrackId() const { return track_id; }
    int getPopularity() const { return popularity; }
    int getYear() const { return year; }
    string getGenre() const { return genre; }
    float getDanceability() const { return danceability; }
    float getEnergy() const { return energy; }
    int getKey() const { return key; }
    float getLoudness() const { return loudness; }
    bool getMode() const { return mode; }
    float getSpeechiness() const { return speechiness; }
    float getAcousticness() const { return acousticness; }
    float getInstrumentalness() const { return instrumentalness; }
    float getLiveness() const { return liveness; }
    float getValence() const { return valence; }
    float getTempo() const { return tempo; }
    int getDurationMs() const { return duration_ms; }
    int getTimeSignature() const { return time_signature; }

    // Método para imprimir información de la canción
    void imprimir() {
        cout << "|Artist NAME| " << artist_name << endl;
        cout << "|Track NAME| " << track_name << endl;
        cout << "|Track ID| " << track_id << endl;
        cout << "|Popularidad| " << popularity << endl;
        cout << "|Año| " << year << endl;
        cout << "|Genre| " << genre << endl;
        cout << "|Danceability| " << danceability << endl;
        cout << "|Energy| " << energy << endl;
        cout << "|Key| " << key << endl;
        cout << "|Loudness| " << loudness << endl;
        cout << "|Mode| " << mode << endl;
        cout << "|Speechiness| " << speechiness << endl;
        cout << "|Acousticness| " << acousticness << endl;
        cout << "|Instrumentalness| " << instrumentalness << endl;
        cout << "|Liveness| " << liveness << endl;
        cout << "|Valence| " << valence << endl;
        cout << "|Tempo| " << tempo << endl;
        cout << "|Duration MS| " << duration_ms << endl;
        cout << "|Time SIGNATURE| " << time_signature << endl;
    }
};

// Nodo de Trie
struct NodoTrie {
    map<char, NodoTrie*> hijos;
    vector<Cancion*> canciones;
};

// Clase Trie
class Trie {
private:
    NodoTrie* raiz;

public:
    Trie() {
        raiz = new NodoTrie();
    }

    // Insertar canción en el trie
    void insertar(const string &nombreCancion, Cancion* cancion) {
        NodoTrie* nodo = raiz;
        for (char c : nombreCancion) {
            if (nodo->hijos.find(c) == nodo->hijos.end()) {
                nodo->hijos[c] = new NodoTrie();
            }
            nodo = nodo->hijos[c];
        }
        nodo->canciones.push_back(cancion);
    }

    // Buscar canciones por prefijo
    vector<Cancion*> buscarPorPrefijo(const string &prefijo) {
        NodoTrie* nodo = raiz;
        vector<Cancion*> resultados;
        for (char c : prefijo) {
            if (nodo->hijos.find(c) == nodo->hijos.end()) {
                return resultados;
            }
            nodo = nodo->hijos[c];
        }
        recolectarCanciones(nodo, resultados);
        return resultados;
    }

    // Recolectar canciones de los nodos
    void recolectarCanciones(NodoTrie* nodo, vector<Cancion*> &resultados) {
        if (!nodo) return;
        for (Cancion* cancion : nodo->canciones) {
            resultados.push_back(cancion);
        }
        for (auto& hijo : nodo->hijos) {
            recolectarCanciones(hijo.second, resultados);
        }
    }

    // Buscar canción por nombre exacto
    Cancion* buscarPorNombreExacto(const string &nombreCancion) {
        NodoTrie* nodo = raiz;
        for (char c : nombreCancion) {
            if (nodo->hijos.find(c) == nodo->hijos.end()) {
                return nullptr;
            }
            nodo = nodo->hijos[c];
        }
        return nodo->canciones.empty() ? nullptr : nodo->canciones[0];
    }
};

// Función para convertir caracteres especiales
string convertirCaracteres(const string &texto) {
    map<string, string> reemplazos = {
        {"├í", "á"}, {"├®", "é"}, {"├¡", "í"}, {"├│", "ó"}, {"├║", "ú"},
        {"├▒", "ñ"}, {"├ü", "ü"}, {"├Á", "Á"}, {"├É", "É"}, {"├Í", "Í"},
        {"├Ó", "Ó"}, {"├Ú", "Ú"}, {"├Ñ", "Ñ"}
    };

    string textoConvertido = texto;
    for (const auto &par : reemplazos) {
        size_t pos = 0;
        while ((pos = textoConvertido.find(par.first, pos)) != string::npos) {
            textoConvertido.replace(pos, par.first.length(), par.second);
            pos += par.second.length();
        }
    }
    return textoConvertido;
}

// Función para dividir líneas CSV respetando comillas dobles
vector<string> dividirLineaCSV(const string &linea) {
    vector<string> campos;
    string campo;
    bool dentroDeComillas = false;

    for (char c : linea) {
        if (c == '"' && (campo.empty() || campo.back() != '\\')) {
            dentroDeComillas = !dentroDeComillas;
        } else if (c == ',' && !dentroDeComillas) {
            campos.push_back(campo);
            campo.clear();
        } else {
            campo += c;
        }
    }
    campos.push_back(campo); // Agregar último campo
    return campos;
}

// Leer archivo CSV y cargar canciones en lista enlazada y trie
void cargarArchivoCSV(const string &nombreArchivo, Trie &trie) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Leer encabezado y descartarlo

    int contador = 0;
    while (getline(archivo, linea) && contador < 1000) { // Solo las primeras 1000 canciones
        vector<string> campos = dividirLineaCSV(linea);
        if (campos.size() < 3) { // Validar que haya al menos índice, artista y canción
            cerr << "Línea malformada: " << linea << endl;
            continue;
        }

        // Asignar los valores de la línea CSV a los atributos de Cancion
        int indice = stoi(campos[0]); // Convertir el índice a entero
        string artistName = convertirCaracteres(campos[1]);
        string trackName = convertirCaracteres(campos[2]);
        string trackId = convertirCaracteres(campos[3]);
        int popularity = stoi(campos[4]);
        int year = stoi(campos[5]);
        string genre = convertirCaracteres(campos[6]);
        float danceability = stof(campos[7]);
        float energy = stof(campos[8]);
        int key = stoi(campos[9]);
        float loudness = stof(campos[10]);
        bool mode = (stoi(campos[11]) != 0);
        float speechiness = stof(campos[12]);
        float acousticness = stof(campos[13]);
        float instrumentalness = stof(campos[14]);
        float liveness = stof(campos[15]);
        float valence = stof(campos[16]);
        float tempo = stof(campos[17]);
        int duration_ms = stoi(campos[18]);
        int time_signature = stoi(campos[19]);

        // Crear la canción y agregarla al trie
        Cancion *cancion = new Cancion(indice, artistName, trackName, trackId, popularity, year,
                                      genre, danceability, energy, key, loudness, mode,
                                      speechiness, acousticness, instrumentalness, liveness,
                                      valence, tempo, duration_ms, time_signature);

        trie.insertar(trackName, cancion);
        contador++;
    }

    archivo.close();
}

// Función para mostrar menú y realizar búsqueda
void menu(Trie &trie) {
    int opcion;
    string busqueda;
    while (true) {
        cout << "\n1. Buscar canción por prefijo" << endl;
        cout << "2. Buscar canción por nombre exacto" << endl;
        cout << "3. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el prefijo para buscar canciones: ";
                cin >> busqueda;
                {
                    vector<Cancion*> canciones = trie.buscarPorPrefijo(busqueda);
                    if (canciones.empty()) {
                        cout << "No se encontraron canciones." << endl;
                    } else {
                        for (auto* cancion : canciones) {
                            cancion->imprimir();
                        }
                    }
                }
                break;
            case 2:
                cout << "Ingrese el nombre exacto de la canción: ";
                cin >> busqueda;
                {
                    Cancion* cancion = trie.buscarPorNombreExacto(busqueda);
                    if (cancion) {
                        cancion->imprimir();
                    } else {
                        cout << "Canción no encontrada." << endl;
                    }
                }
                break;
            case 3:
                return;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    }
}

int main() {
    Trie trie;
    cargarArchivoCSV("spotify_data.csv", trie);
    menu(trie);
    return 0;
}

