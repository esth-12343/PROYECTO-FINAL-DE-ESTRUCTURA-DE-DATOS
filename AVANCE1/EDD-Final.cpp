#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <locale>
#include <list>
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

    void imprimir() const;
};

void Cancion::imprimir() const{
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

const Cancion* MostrarSeleccion(vector<const Cancion*> result) {
    if (result.empty()) {
        cout << "No se encontraron coincidencias." << endl;
        return nullptr;
    }

    const int cancionesPorPagina = 50;
    int select = 0;

    int totalCanciones = result.size();
    int indiceActual = 0;

    while (indiceActual < totalCanciones) {
        for (int i = indiceActual; i < min(indiceActual + cancionesPorPagina, totalCanciones); ++i) {
            cout << "|" << (i + 1) << "| ";
            cout << result[i]->getArtistName() << " - " << result[i]->getTrackName() << endl;
            cout << "------------------------" << endl;
        }

        indiceActual += cancionesPorPagina;

        if (indiceActual < totalCanciones) {
            cout << "Presione '+' para mostrar más o elija una canción (1-" << totalCanciones << "): ";
        } else {
            cout << "Elija una canción (1-" << totalCanciones << "): ";
        }

        string input;
        getline(cin, input);

        if (!input.empty() && all_of(input.begin(), input.end(), ::isdigit)) {
            select = stoi(input);
            if (select >= 1 && select <= totalCanciones) {
                break;
            } else {
                cout << "Selección no válida. Por favor, intente de nuevo." << endl;
                indiceActual -= cancionesPorPagina;
            }
        } else if (input == "+") {
            continue;
        } else {
            cout << "Entrada no válida. Por favor, intente de nuevo." << endl;
            indiceActual -= cancionesPorPagina;
        }
    }

    if (select < 1 || select > totalCanciones) {
        cout << "No se realizó una selección válida." << endl;
        return nullptr;
    }

    result[select - 1]->imprimir();
    return result[select - 1];
}

struct TrieNode {
    TrieNode* child[256];
    vector<const Cancion*> canciones;
    bool wordEnd;

    TrieNode() {
        wordEnd = false;
        for (int i = 0; i < 76; i++) {
            child[i] = NULL;
        }
    }

    int getIndex(char ch) {
        if (ch >= 'a' && ch <= 'z') return ch - 'a';
        if (ch >= 'A' && ch <= 'Z') return ch - 'A' + 26;
        if (ch == ' ') return 52;
        if (ch == '\'') return 53;
        if (ch == '-') return 54;
        if (ch == '.') return 55;
        if (ch >= '0' && ch <= '9') return ch - '0' + 56;
        if (ch == '!') return 66;
        if (ch == '@') return 67;
        if (ch == '#') return 68;
        if (ch == '$') return 69;
        if (ch == '%') return 70;
        if (ch == '_') return 71;
        if (ch == '&') return 72;
        if (ch == '"') return 73;
        if (ch == '(') return 74;
        if (ch == ')') return 75;

        return -1;
    }
};

void insertKey(TrieNode* root, const Cancion* cancion, const string& key) {
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
    curr->canciones.push_back(cancion);  // Almacenamos el puntero
}


bool deleteFromTrie(TrieNode* root, const string& key, int depth = 0) {
    if (!root) return false;

    if (depth == key.size()) {
        if (root->wordEnd) {
            root->wordEnd = false;
            root->canciones.clear();
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

void collectWords(TrieNode* curr, string currentPrefix, vector<const Cancion*>& result) {
    if (!curr) return;

    if (curr->wordEnd) {
        result.insert(result.end(), curr->canciones.begin(), curr->canciones.end());
    }

    for (int i = 0; i < 76; ++i) {
        if (curr->child[i]) {
            char nextChar;
            if (i < 26) {
                nextChar = 'a' + i;
            } else if (i < 52) {
                nextChar = 'A' + (i - 26);
            } else if (i == 52) {
                nextChar = ' ';
            } else if (i == 53) {
                nextChar = '\'';
            } else if (i == 54) {
                nextChar = '-';
            } else if (i == 55) {
                nextChar = '.';
            } else if (i >= 56 && i <= 65) {
                nextChar = '0' + (i - 56);
            } else if (i == 66) {
                nextChar = '!';
            } else if (i == 67) {
                nextChar = '@';
            } else if (i == 68) {
                nextChar = '#';
            } else if (i == 69) {
                nextChar = '$';
            } else if (i == 70) {
                nextChar = '%';
            } else if (i == 71) {
               nextChar = '_';
            } else if (i == 72) {
                nextChar = '&';
            } else if (i == 73) {
                nextChar = '"';
            } else if (i == 74) {
                nextChar = '(';
            } else if (i == 75) {
                nextChar = ')';
            }

            collectWords(curr->child[i], currentPrefix + nextChar, result);
        }
    }
}

const Cancion* getWordsWithPrefix(TrieNode* root, const string& prefix) {
    TrieNode* curr = root;
    vector<const Cancion*> result;

    for (char c : prefix) {
        int index = curr->getIndex(c);
        if (index == -1 || !curr->child[index]) {
            cout << "No encontrado." << endl;
            return nullptr;
        }
        curr = curr->child[index];
    }

    collectWords(curr, prefix, result);
    const Cancion* seleccionada = MostrarSeleccion(result);
    return seleccionada;
}

class TablaHash {
private:
    vector<vector<const Cancion*>> tablaGenero;
    int capacidad;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash + int(c)) % capacidad;
        }
        return hash;
    }

public:
    TablaHash(int cap) : capacidad(cap) {
        tablaGenero.resize(capacidad);
    }

    void insertarPorGenero(const Cancion* cancion, const string& genre) {
        int index = hashFunction(genre);
        tablaGenero[index].push_back(cancion);
    }

    const Cancion* mostrarPorGenero(const string& genre) {
        vector<const Cancion*> canciones;
        int index = hashFunction(genre);

        for (auto& cancion : tablaGenero[index]) {
            if (cancion->getGenre() == genre) {
                canciones.push_back(cancion);
            }
        }

        const Cancion* seleccionada = MostrarSeleccion(canciones);
        return seleccionada;
    }

    const Cancion* imprimirTablaGeneros() {
        for (int i = 0; i < capacidad; ++i) {
            cout << "Índice " << 2000 + i << ":" << endl;
            if (!tablaGenero[i].empty()) {
                for (auto& cancion : tablaGenero[i]) {
                    const Cancion* seleccionada = MostrarSeleccion(tablaGenero[i]);
                    return seleccionada;
                }
            }
        }
        return nullptr;
    }
};

class IndiceCancionesYear {
private:
    vector<vector<const Cancion*>> indice;

public:
    IndiceCancionesYear() {
        indice.resize(24);
    }

    void insertarYear(int indiceCategoria, const Cancion* cancion) {
        if (indiceCategoria >= 2000 && indiceCategoria <= 2023) {
            indice[indiceCategoria-2000].push_back(cancion);
        } else {
            //cout << "Índice fuera de rango! " << indiceCategoria << " " << cancion->getTrackName() << endl;
        }
    }

    const Cancion* buscarYear(int indiceCategoria) {
        if (indiceCategoria >= 2000 && indiceCategoria <= 2023) {
            const Cancion* seleccionada = MostrarSeleccion(indice[indiceCategoria-2000]);
            return seleccionada;
        } else {
            cout << "Índice fuera de rango!" << std::endl;
            return {};
        }
    }

    void eliminar(int indiceCategoria, const Cancion* cancion) {
        if (indiceCategoria >= 0 && indiceCategoria < indice.size()) {
            auto& canciones = indice[indiceCategoria];
            for (auto it = canciones.begin(); it != canciones.end(); ++it) {
                if (*it == cancion) {
                    canciones.erase(it);
                    delete cancion;
                    return;
                }
            }
            std::cout << "Canción no encontrada!" << std::endl;
        } else {
            std::cout << "Índice fuera de rango!" << std::endl;
        }
    }

    const Cancion* mostrarYear() {
        for(int i=0; i<=23; i++){
            const Cancion* seleccionada = MostrarSeleccion(indice[i]);
            return seleccionada;
        }
    }
};

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
    ListaReproduccion() : cabeza(nullptr), ultimo(nullptr), tamano(0) {
    root = new TrieNode();  // Inicializa root con una nueva instancia de TrieNode
    tablaHashGenre = new TablaHash(82);  // Inicializa la tablaHashGenre con capacidad 82
    year = new IndiceCancionesYear();  // Inicializa year con una nueva instancia de IndiceCancionesYear
}
    TrieNode* root;                  // Puntero a la raíz del trie
    TablaHash* tablaHashGenre;       // Puntero a la tabla hash
    IndiceCancionesYear* year;

        void insertar(const Cancion* c) {
            // Agregar canción a la lista
            NodoLista* nuevo = new NodoLista(*c);
            if (!cabeza) {
                cabeza = ultimo = nuevo;
            } else {
                ultimo->siguiente = nuevo;
                ultimo = nuevo;
            }
            tamano++;

            // Actualizar Trie
            if (root) {
                insertKey(root, c, c->getArtistName());
            }

            // Actualizar Tabla Hash por Género
            if (tablaHashGenre) {
                tablaHashGenre->insertarPorGenero(c, c->getGenre()); // Suponiendo que insertar() maneja la inserción de canciones por género
            }

            // Actualizar Índice de Canciones por Año
            if (year) {
                year->insertarYear(c->getYear(), c); // Suponiendo que insertar() maneja la inserción de canciones por año
            }
        }

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

    void eliminar_cancion(const string& nombreCancion) {
        NodoLista* temp = cabeza;
        NodoLista* anterior = nullptr;

        while (temp && temp->cancion.getTrackName() != nombreCancion) {
            anterior = temp;
            temp = temp->siguiente;
        }

        if (temp) {
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

    void cambiar_orden(int posicion_actual, int nueva_posicion) {
        if (posicion_actual < 0 || posicion_actual >= tamano || nueva_posicion < 0 || nueva_posicion >= tamano) {
            cout << "Posición no válida.\n";
            return;
        }

        if (posicion_actual == nueva_posicion) return;

        NodoLista* temp = cabeza;
        NodoLista* anterior_actual = nullptr;

        for (int i = 0; i < posicion_actual; ++i) {
            anterior_actual = temp;
            temp = temp->siguiente;
        }
        NodoLista* cancion_a_mover = temp;

        if (anterior_actual) {
            anterior_actual->siguiente = cancion_a_mover->siguiente;
        } else {
            cabeza = cancion_a_mover->siguiente;
        }

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

    void imprimirCanciones() const {
        NodoLista* temp = cabeza;
        while (temp) {
            cout << "Artista: " << temp->cancion.getArtistName()
                 << ", Título: " << temp->cancion.getTrackName() << endl;
            temp = temp->siguiente;
        }
    }

    NodoLista* obtenerCabeza() {
        return cabeza;
    }

    void llenarTrie(TrieNode* root) {
        NodoLista* temp = cabeza;
        while (temp) {
            insertKey(root, &temp->cancion, temp->cancion.getArtistName());
            temp = temp->siguiente;
        }
    }

    void llenarIndiceYear(IndiceCancionesYear* year) {
        NodoLista* temp = cabeza;
        while (temp) {
            year->insertarYear(temp->cancion.getYear(), &temp->cancion);
            temp = temp->siguiente;
        }
    }

    void llenarTablaHashPorGenero(TablaHash& tabla) {
        NodoLista* temp = cabeza;
        while (temp) {
            tabla.insertarPorGenero(&temp->cancion, temp->cancion.getGenre());
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

void freeTrie(TrieNode* node) {
    if (!node) return;

    for (int i = 0; i < 76; ++i) {
        if (node->child[i]) {
            freeTrie(node->child[i]);
        }
    }
    delete node;
}

float validarFloat(const string& str) {
    try {
        return stof(str);
    } catch (...) {
        return 0.0f;
    }
}

string limpiarCadena(const string& input) {
    string resultado;
    for (char c : input) {
        switch (c) {
            case 'á': case 'Á': resultado += 'a'; break;
            case 'é': case 'É': resultado += 'e'; break;
            case 'í': case 'Í': resultado += 'i'; break;
            case 'ó': case 'Ó': resultado += 'o'; break;
            case 'ú': case 'Ú': resultado += 'u'; break;
            case 'ñ': case 'Ñ': resultado += 'n'; break;
            case 'ç': case 'Ç': resultado += 'c'; break;
            default:
                if (isalnum(c) || isspace(c) || c == '-' || c == '\'' || c == '!' || c == '(' || c == ')') {
                    resultado += c;
                }
                break;
        }
    }
    return resultado;
}

void leerArchivoCSV(const string& nombreArchivo, TablaHash& tablaHashGenre, ListaReproduccion& lista, TrieNode* root, IndiceCancionesYear* year ) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    string linea;
    if (getline(archivo, linea)) {}

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string dummy, artist_name, track_name, track_id, genre;
        int popularity, year, key, duration_ms, time_signature;
        float danceability, energy, loudness, speechiness, acousticness;
        float instrumentalness, liveness, valence, tempo;
        bool mode;

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

        artist_name = limpiarCadena(artist_name);
        track_name = limpiarCadena(track_name);
        genre = limpiarCadena(genre);

        Cancion cancion(artist_name, track_name, track_id, popularity, year, genre,
                        danceability, energy, key, loudness, mode, speechiness,
                        acousticness, instrumentalness, liveness, valence, tempo,
                        duration_ms, time_signature);

        NodoLista* nodo = new NodoLista(cancion);

        lista.agregar_cancion(cancion);

    }

    archivo.close();
}

void menu(ListaReproduccion& lista) {
    map<string, ListaReproduccion> listasReproduccion;
    int opcion;

    do {
        cout << "\n=== Menú ===" << endl;
        cout << "1. Crear una nueva lista de reproducción" << endl;
        cout << "2. Seleccionar una lista para trabajar" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer de entrada.

        switch (opcion) {
            case 1: {
                string nombreLista;
                cout << "Ingrese el nombre de la nueva lista de reproducción: ";
                getline(cin, nombreLista);

                if (listasReproduccion.find(nombreLista) != listasReproduccion.end()) {
                    cout << "Ya existe una lista con ese nombre. Intente con otro nombre." << endl;
                } else {
                    ListaReproduccion nuevaLista;
                    nuevaLista.root = new TrieNode();
                    nuevaLista.tablaHashGenre = new TablaHash(82);
                    nuevaLista.year = new IndiceCancionesYear();

                    // Agregar la nueva lista al mapa
                    listasReproduccion[nombreLista] = nuevaLista;

                    cout << "Lista de reproducción '" << nombreLista << "' creada con éxito." << endl;
                }
                break;
            }

            case 2: {
                if (listasReproduccion.empty()) {
                    cout << "No hay listas de reproducción creadas aún." << endl;
                } else {
                    cout << "Listas de reproducción disponibles:" << endl;
                    for (const auto& lista : listasReproduccion) {
                        cout << "- " << lista.first << endl;
                    }

                    string nombreLista;
                    cout << "Ingrese el nombre de la lista de reproducción que desea seleccionar: ";
                    getline(cin, nombreLista);

                    auto it = listasReproduccion.find(nombreLista);
                    if (it != listasReproduccion.end()) {
                        cout << "Trabajando con la lista de reproducción '" << nombreLista << "'." << endl;

                        bool salir = false;
                        while (!salir) {
                            cout << "\nOpciones:\n";
                            cout << "1. Agregar canción\n";
                            cout << "2. Eliminar canción\n";
                            cout << "3. Mostrar canciones\n";
                            cout << "4. Volver al menú principal\n";
                            cout << "Seleccione una opción: ";

                            int opcion;
                            cin >> opcion;
                            cin.ignore(); // Limpiar el buffer de entrada

                            switch (opcion) {
                                case 1: {
                                    //const Cancion* r = lista.year->buscarYear(2000);
                                    const Cancion* r = lista.tablaHashGenre->mostrarPorGenero("rock");
                                    it->second.insertar(r);
                                    //cout << "Canción '" << nombreCancion << "' agregada a la lista." << endl;
                                    break;
                                }
                                case 2: {
                                    // Eliminar canción
                                    string nombreCancion;
                                    cout << "Ingrese el nombre de la canción a eliminar: ";
                                    getline(cin, nombreCancion);

                                    it->second.eliminar_cancion(nombreCancion);
                                    break;
                                }
                                case 3: {
                                    // Mostrar canciones
                                    it->second.imprimirCanciones();
                                    break;
                                }
                                case 4:
                                    // Salir del submenú
                                    salir = true;
                                    break;
                                default:
                                    cout << "Opción no válida. Intente nuevamente." << endl;
                            }
                        }
                    } else {
                        cout << "La lista '" << nombreLista << "' no existe." << endl;
                    }
                }
                break;
            }

            case 3:
                cout << "Saliendo del programa." << endl;
                break;

            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);
    }


int main() {
    SetConsoleOutputCP(CP_UTF8);

    ListaReproduccion lista;

    lista.root = new TrieNode();
    lista.tablaHashGenre = new TablaHash(82);
    lista.year = new IndiceCancionesYear();

    leerArchivoCSV("spotify_data.csv", *(lista.tablaHashGenre), lista, lista.root, lista.year);
    lista.llenarTrie(lista.root);
    lista.llenarIndiceYear(lista.year);
    lista.llenarTablaHashPorGenero(*(lista.tablaHashGenre));

    //lista.year->mostrarYear();

    menu(lista);
    /*string select;
    cout<<"Ingresa :D "<<endl;
    cin>>select;
    tablaHashGenre.mostrarPorGenero(select);
    year->mostrarYear();
    //year->buscarYear(select);
    //getWordsWithPrefix(root, select);
    */
    freeTrie(lista.root);

    return 0;
}


