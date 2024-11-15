#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wchar.h>
#include <windows.h>

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

    void imprimir();
};

void Cancion::imprimir() {
    cout << "|DNI| " << artist_name << endl;
    cout << "|Nombre| " << track_name << endl;
    cout << "|Apellido PATERNO| " << track_id << endl;
    cout << "|Apellido MATERNO| " << popularity << endl;
    cout << "|Genero| " << year << endl;
    cout << "|Fecha de NACIMIENTO| " << genre << endl;
    cout << "|Estado| " << danceability << endl;
}

class NodoLista {
public:
    Cancion cancion;
    NodoLista* siguiente;

    NodoLista(const Cancion& c) : cancion(c), siguiente(nullptr) {}
};

class ListaReproduccion {
private:
    NodoLista* cabeza;
    NodoLista* ultimo;
    int tamano;
public:
    ListaReproduccion() : cabeza(nullptr), ultimo(nullptr), tamano(0) {}

    void agregar_cancion(const Cancion& c) {
        NodoLista* nuevo = new NodoLista(c);
        if (!cabeza) {
            cabeza = ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        tamano++;
    }

    // Función para eliminar una canción por su nombre
    void eliminar_cancion(const string& nombreCancion) {
        NodoLista* temp = cabeza;
        NodoLista* anterior = nullptr;

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
        NodoLista* temp = cabeza;
        NodoLista* anterior_actual = nullptr;

        for (int i = 0; i < posicion_actual; ++i) {
            anterior_actual = temp;
            temp = temp->siguiente;
        }
        NodoLista* cancion_a_mover = temp;

        // Remover el NodoLista de la posición actual
        if (anterior_actual) {
            anterior_actual->siguiente = cancion_a_mover->siguiente;
        } else {
            cabeza = cancion_a_mover->siguiente;
        }

        // Insertar el nodo en la nueva posición
        temp = cabeza;
        NodoLista* anterior_nueva = nullptr;
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

    // Función para imprimir la lista de canciones
    void imprimirCanciones() const {
        NodoLista* temp = cabeza;
        while (temp) {
            cout << "Artista: " << temp->cancion.getArtistName()
                 << ", Título: " << temp->cancion.getTrackName() << endl;
            temp = temp->siguiente;
        }
    }

    ~ListaReproduccion() {
        while (cabeza) {
            NodoLista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

struct TrieNode {
    TrieNode* child[256];
    vector<Cancion*> canciones;
    bool wordEnd;

    TrieNode() {
        wordEnd = false;
        for (int i = 0; i < 72; i++) {
            child[i] = NULL;
        }
    }

    int getIndex(char ch) {
        if (ch >= 'a' && ch <= 'z') return ch - 'a';          // 0-25: letras minúsculas
        if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;     // 26-51: letras mayúsculas
        if (ch == ' ') return 52;                             // 52: espacio
        if (ch == '\'') return 53;                            // 53: apóstrofe
        if (ch == '-') return 54;                             // 54: guion
        if (ch == '.') return 55;                             // 55: punto
        if (ch >= '0' && ch <= '9') return ch - '0' + 56;     // 56-65: números
        if (ch == '!') return 66;                             // 66: exclamación
        if (ch == '@') return 67;                             // 67: arroba
        if (ch == '#') return 68;                             // 68: numeral
        if (ch == '$') return 69;                             // 69: dólar
        if (ch == '%') return 70;                             // 70: porcentaje
        if (ch == '^') return 71;                             // 71: caret
        if (ch == '&') return 72;                             // 72: ampersand
        if (ch == '*') return 73;                             // 73: asterisco
        if (ch == '(') return 74;                             // 74: paréntesis izquierdo
        if (ch == ')') return 75;                             // 75: paréntesis derecho

        return -1;
    }
};

void insertKey(TrieNode* root, Cancion* cancion, const string& key) {
    TrieNode* curr = root;
    for (char c : key) {
        int index = curr->getIndex(c);
        if (index == -1) {
            cout << key << " Caracter no válido: " << c << endl;
            continue;
        }

        if (curr->child[index] == nullptr) {
            TrieNode* newNode = new TrieNode();
            curr->child[index] = newNode;
        }
        curr = curr->child[index];
    }
    curr->wordEnd = true;
    curr->canciones.push_back(cancion); // Agregar el Cancion al vector
}

bool deleteFromTrie(TrieNode* root, const string& key, int depth = 0) {
    if (!root) return false;

    if (depth == key.size()) {
        if (root->wordEnd) {
            root->wordEnd = false;
            root->canciones.clear(); // Vaciar el vector de Cancions
        }
        for (int i = 0; i < 57; ++i) {
            if (root->child[i]) return false;
        }
        delete root;
        return true;
    }

    int index = root->getIndex(key[depth]);
    if (index == -1 || !root->child[index]) return false;

    bool shouldDelete = deleteFromTrie(root->child[index], key, depth + 1);

    if (shouldDelete) {
        root->child[index] = nullptr;
        if (!root->wordEnd && root->canciones.empty()) {
            for (int i = 0; i < 57; ++i) {
                if (root->child[i]) return false;
            }
            delete root;
            return true;
        }
    }

    return false;
}

void collectWords(TrieNode* curr, string currentPrefix, vector<Cancion*>& result) {
    if (!curr) return;

    if (curr->wordEnd) {
        result.insert(result.end(), curr->canciones.begin(), curr->canciones.end()); // Recoger todos los Cancions
    }

    for (int i = 0; i < 76; ++i) { // Ajustamos el rango a 76 según la cantidad de caracteres soportados
        if (curr->child[i]) {
            char nextChar;
            if (i < 26) {
                nextChar = 'a' + i; // 0-25: letras minúsculas
            } else if (i < 52) {
                nextChar = 'A' + (i - 26); // 26-51: letras mayúsculas
            } else if (i == 52) {
                nextChar = ' '; // 52: espacio
            } else if (i == 53) {
                nextChar = '\''; // 53: apóstrofe
            } else if (i == 54) {
                nextChar = '-'; // 54: guion
            } else if (i == 55) {
                nextChar = '.'; // 55: punto
            } else if (i >= 56 && i <= 65) {
                nextChar = '0' + (i - 56); // 56-65: números
            } else if (i == 66) {
                nextChar = '!'; // 66: exclamación
            } else if (i == 67) {
                nextChar = '@'; // 67: arroba
            } else if (i == 68) {
                nextChar = '#'; // 68: numeral
            } else if (i == 69) {
                nextChar = '$'; // 69: dólar
            } else if (i == 70) {
                nextChar = '%'; // 70: porcentaje
            } else if (i == 71) {
                nextChar = '^'; // 71: caret
            } else if (i == 72) {
                nextChar = '&'; // 72: ampersand
            } else if (i == 73) {
                nextChar = '*'; // 73: asterisco
            } else if (i == 74) {
                nextChar = '('; // 74: paréntesis izquierdo
            } else if (i == 75) {
                nextChar = ')'; // 75: paréntesis derecho
            }

            collectWords(curr->child[i], currentPrefix + nextChar, result);
        }
    }
}

Cancion* getWordsWithPrefix(TrieNode* root, const string& prefix) {
    TrieNode* curr = root;
    vector<Cancion*> result;
    int select;

    for (char c : prefix) {
        int index = curr->getIndex(c);
        if (index == -1 || !curr->child[index]) {
            cout << "Cancion NO encontrado." << endl;
            return NULL;
        }
        curr = curr->child[index];
    }

collectWords(curr, prefix, result);

if (result.empty()) {
    cout << "No se encontraron apellidos que empiecen con el prefijo: " << prefix << endl;
} else {
    int j = 1;
    for (int i = 0; i < result.size(); i++) {
        cout << "|" << j << "| ";
        cout << result[i]->getArtistName() << endl;
        cout << "------------------------" << endl;
        j++;
    }
    cin >> select;

    // Validar la selección para evitar errores de índice fuera de rango
    if (select < 1 || select > result.size()) {
        cout << "Selección no válida." << endl;
        return NULL;
    }

    result[select - 1]->imprimir();
}
return result[select - 1];
}

void freeTrie(TrieNode* node) {
    if (!node) return;

    for (int i = 0; i < 72; ++i) {
        if (node->child[i]) {
            freeTrie(node->child[i]);
        }
    }
    delete node;
}

// Función para leer un archivo CSV y agregar las canciones
void leerArchivoCSV(const string& nombreArchivo, ListaReproduccion& lista, TrieNode* root) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    string linea;

    if (getline(archivo, linea)) {
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dummy, artist_name, track_name, track_id, genre;
        int popularity, year, key, duration_ms, time_signature;
        float danceability, energy, loudness, speechiness, acousticness;
        float instrumentalness, liveness, valence, tempo;
        bool mode;

        // Leer cada campo separado por comas
        getline(ss, dummy, ',');
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

        lista.agregar_cancion(cancion);
        insertKey(root, &cancion, cancion.getArtistName());
    }

    archivo.close();
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    ListaReproduccion lista;
    TrieNode* root = new TrieNode();

    // Leer el archivo CSV y agregar canciones a la lista
    leerArchivoCSV("spotify_data.csv", lista, root);

    // Imprimir las canciones para verificar que fueron cargadas
    //lista.imprimirCanciones();
    /*
    // Ejemplo de agregar, eliminar y cambiar de posición
    Cancion nuevaCancion("Nuevo Artista", "Nueva Cancion", "1234", 90, 2021, "Pop", 0.8, 0.9, 5, -5.0, true, 0.1, 0.2, 0.0, 0.3, 0.5, 120.0, 200000, 4);
    lista.agregar_cancion(nuevaCancion);
    lista.imprimirCanciones();
    lista.eliminar_cancion("Nueva Cancion");
    lista.cambiar_orden(0, 2);
    lista.imprimirCanciones();*/



    freeTrie(root);

    return 0;
}
