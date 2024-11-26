#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <windows.h>
#include <algorithm>
#include <locale>
#include <list>
using namespace std;

#define MAX_KEYS 4  // Número máximo de claves por nodo en el Árbol B

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

struct TrieNode {
    TrieNode* child[256];
    vector<Cancion*> canciones;
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
        if (ch == '*') return 73;
        if (ch == '(') return 74;
        if (ch == ')') return 75;

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
    curr->canciones.push_back(cancion);
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

void collectWords(TrieNode* curr, string currentPrefix, vector<Cancion*>& result) {
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
                nextChar = '*';
            } else if (i == 74) {
                nextChar = '(';
            } else if (i == 75) {
                nextChar = ')';
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
            cout << "NO encontrado." << endl;
            return NULL;
        }
        curr = curr->child[index];
    }

collectWords(curr, prefix, result);

if (result.empty()) {
    cout << "No se encontraron coincidencias: " << prefix << endl;
} else {
    int j = 1;
    for (int i = 0; i < result.size(); i++) {
        cout << "|" << j << "| ";
        cout << result[i]->getArtistName() <<" - "<< result[i]->getTrackName() << endl;
        cout << "------------------------" << endl;
        j++;
    }
    cin >> select;

    if (select < 1 || select > result.size()) {
        cout << "Selección no válida." << endl;
        return NULL;
    }

    result[select - 1]->imprimir();
}
return result[select - 1];
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
            insertKey(root, &temp->cancion, temp->cancion.getArtistName()); // Llenamos el trie con el nombre de la canción
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

// Función para validar datos numéricos de tipo float
float validarFloat(const string& str) {
    try {
        return stof(str);  // Intentar convertir la cadena a float
    } catch (...) {
        return 0.0f;  // Si la conversión falla, asigna 0.0 como valor predeterminado
    }
}

class TablaHash {
private:
    vector<list<NodoLista*>> tabla;
    int capacidad;

public:
    TablaHash(int cap) : capacidad(cap) {
        tabla.resize(capacidad);  // Inicializar la tabla con listas vacías
    }

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash + int(c)) % capacidad;
        }
        return hash;
    }

    void insertar(NodoLista* nodo, const string& genre) {
        int index = hashFunction(genre);  // Calcular el índice usando el género
        tabla[index].push_back(nodo);  // Insertar el puntero al nodo de la canción
    }

    void mostrarPorGenero(const string& genre) {
        vector<Cancion*> canciones;

        // Recorrer todos los "buckets" (listas) para recolectar las canciones del género especificado
        for (int i = 0; i < capacidad; ++i) {
            for (auto& nodo : tabla[i]) {
                if (nodo->cancion.getGenre() == genre) {
                    canciones.push_back(&nodo->cancion); // Agregar las canciones del género
                }
            }
        }

        if (!canciones.empty()) {
            // Ordenar las canciones por 'track_name' (o por otro criterio si lo prefieres)
            sort(canciones.begin(), canciones.end(), [](Cancion* a, Cancion* b) {
                return a->getTrackName() < b->getTrackName(); // Orden ascendente por nombre de la canción
            });

            cout << "Canciones del género '" << genre << "':\n";
            for (auto& cancion : canciones) {
                cancion->imprimir();
                cout << "-------------------------\n";
            }
        } else {
            cout << "No se encontraron canciones en el género '" << genre << "'.\n";
        }
    }
};

// Nodo del Árbol B
struct BTreeNode {
    vector<Cancion*> keys;   // Punteros a las canciones
    vector<BTreeNode*> children; // Punteros a los hijos
    bool isLeaf;
    
    BTreeNode(bool leaf) : isLeaf(leaf) {}
};

// Función para comparar canciones por atributos específicos (ej: danceability, energy)
bool compareByAttribute(Cancion* a, Cancion* b, int attribute) {
    switch (attribute) {
        case 1: return a->getDanceability() < b->getDanceability(); // Comparar por danceability
        case 2: return a->getEnergy() < b->getEnergy();             // Comparar por energy
        case 3: return a->getLoudness() < b->getLoudness();         // Comparar por loudness
        case 4: return a->getSpeechiness() < b->getSpeechiness();   // Comparar por speechiness
        case 5: return a->getAcousticness() < b->getAcousticness(); // Comparar por acousticness
        case 6: return a->getInstrumentalness() < b->getInstrumentalness(); // Comparar por instrumentalness
        case 7: return a->getLiveness() < b->getLiveness();         // Comparar por liveness
        case 8: return a->getValence() < b->getValence();           // Comparar por valence
        case 9: return a->getTempo() < b->getTempo();               // Comparar por tempo
        case 10: return a->getDurationMs() < b->getDurationMs();    // Comparar por duration_ms
        default: return false;  // Si no se pasa un atributo válido, no comparar
    }
}

// Declaración de la función splitChild antes de usarla en insertNonFull
void splitChild(BTreeNode* parent, int index);
// Crear un nuevo nodo del Árbol B
BTreeNode* createBTreeNode(bool isLeaf) {
    BTreeNode* node = new BTreeNode(isLeaf);
    return node;
}

// Función de inserción en el Árbol B
void insertNonFull(BTreeNode* node, Cancion* cancion, int attribute) {
    int i = node->keys.size() - 1;

    // Si el nodo es una hoja, insertamos la canción directamente
    if (node->isLeaf) {
        while (i >= 0 && compareByAttribute(node->keys[i], cancion, attribute)) {
            i--;
        }
        node->keys.insert(node->keys.begin() + i + 1, cancion);
    } else {
        // Si el nodo no es una hoja, debemos encontrar el hijo adecuado
        while (i >= 0 && compareByAttribute(node->keys[i], cancion, attribute)) {
            i--;
        }
        i++;
        // Si el hijo está lleno, lo dividimos
        if (node->children[i]->keys.size() == MAX_KEYS) {
            // Dividir el hijo
            splitChild(node, i);
            if (compareByAttribute(node->keys[i], cancion, attribute)) {
                i++;
            }
        }
        insertNonFull(node->children[i], cancion, attribute);
    }
}

// Dividir un nodo del Árbol B
void splitChild(BTreeNode* parent, int index) {
    BTreeNode* fullChild = parent->children[index];
    BTreeNode* newChild = createBTreeNode(fullChild->isLeaf);
    int mid = MAX_KEYS / 2;

    // Mover la mitad de las claves al nuevo hijo
    newChild->keys.assign(fullChild->keys.begin() + mid + 1, fullChild->keys.end());
    fullChild->keys.resize(mid);

    // Mover los hijos del nodo completo
    if (!fullChild->isLeaf) {
        newChild->children.assign(fullChild->children.begin() + mid + 1, fullChild->children.end());
        fullChild->children.resize(mid + 1);
    }

    // Insertar la nueva clave en el nodo padre
    parent->keys.insert(parent->keys.begin() + index, fullChild->keys[mid]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
}

// Función de inserción en el Árbol B (si el nodo raíz está lleno)
void insert(BTreeNode*& root, Cancion* cancion, int attribute) {
    if (root->keys.size() == MAX_KEYS) {
        // Si el nodo raíz está lleno, creamos un nuevo nodo raíz
        BTreeNode* newRoot = createBTreeNode(false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        root = newRoot;
    }
    insertNonFull(root, cancion, attribute);
}

// Función de búsqueda en el Árbol B
bool search(BTreeNode* node, Cancion* cancion, int attribute) {
    int i = 0;
    while (i < node->keys.size() && compareByAttribute(node->keys[i], cancion, attribute)) {
        i++;
    }

    if (i < node->keys.size() && node->keys[i] == cancion) {
        return true;
    }

    if (node->isLeaf) {
        return false;
    }

    return search(node->children[i], cancion, attribute);
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
                if (isalnum(c) || isspace(c) || c == '-' || c == '\'' || c == '!') {
                    resultado += c;
                }
                break;
        }
    }
    return resultado;
}

void leerArchivoCSV(const string& nombreArchivo,TablaHash& tablaHash, ListaReproduccion& lista, TrieNode* root ) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    string linea;
    if (getline(archivo, linea)) {}  // Saltar encabezados

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

        // Limpiar y normalizar los datos
        artist_name = limpiarCadena(artist_name);
        track_name = limpiarCadena(track_name);
        genre = limpiarCadena(genre);

        // Crear la canción y agregarla a la lista de reproducción
        Cancion cancion(artist_name, track_name, track_id, popularity, year, genre,
                        danceability, energy, key, loudness, mode, speechiness,
                        acousticness, instrumentalness, liveness, valence, tempo,
                        duration_ms, time_signature);



        // Insertar en la tabla hash
        NodoLista* nodo = new NodoLista(cancion);

        tablaHash.insertar(nodo, genre);
        
        lista.agregar_cancion(cancion);

    }

    archivo.close();
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    ListaReproduccion lista;
    TrieNode* root = new TrieNode();
    TablaHash tablaHash(100);  // Tabla hash con capacidad 100


    
    // Crear el Árbol B (para ordenar por un atributo, por ejemplo, "danceability")
    BTreeNode* bTreeRoot = createBTreeNode(true);  // Nodo raíz de tipo hoja

    // Leer el archivo CSV y llenar las estructuras
    leerArchivoCSV("spotify_data.csv", tablaHash, lista, root);

    // Insertar canciones en el Árbol B, ordenadas por el atributo danceability
    for (NodoLista* temp = lista.obtenerCabeza(); temp != nullptr; temp = temp->siguiente) {
        insert(bTreeRoot, &temp->cancion, 1);  // 1 corresponde a danceability
    }

;

    // Mostrar canciones usando el Árbol B (búsqueda por "danceability")
    Cancion* cancionBuscada = new Cancion("Artist", "Track", "ID", 0, 0, "pop", 0.8, 0.7, 5, 0.2, true, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 200000, 4);
    if (search(bTreeRoot, cancionBuscada, 1)) {
        cout << "Canción encontrada por danceability." << endl;
    } else {
        cout << "Canción no encontrada." << endl;
    }

    

    return 0;
}