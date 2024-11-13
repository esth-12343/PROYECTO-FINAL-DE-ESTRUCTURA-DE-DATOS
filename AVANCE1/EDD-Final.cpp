#include <iostream>
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

};

int main() {
    //Se crea un objeto a manera de prueba
    Cancion myCancion(
        "Piero Poblete",        // artist_name
        "Coco",                 // track_name
        "12345",                // track_id
        85,                     // popularity
        2010,                   // year
        "Pop",                  // genre
        0.75,                   // danceability
        0.80,                   // energy
        5,                      // key
        -5.0,                   // loudness
        true,                   // mode
        0.04,                   // speechiness
        0.1,                    // acousticness
        0.0,                    // instrumentalness
        0.15,                   // liveness
        0.6,                    // valence
        120.0,                  // tempo
        210000,                 // duration_ms
        4                       // time_signature
    );
    //Se comprueban los resultados
    cout << "Artist: " << myCancion.getArtistName() << endl;
    cout << "Track: " << myCancion.getTrackName() << endl;
    cout << "Track ID: " << myCancion.getTrackId() << endl;
    cout << "Popularity: " << myCancion.getPopularity() << endl;
    cout << "Year: " << myCancion.getYear() << endl;
    cout << "Genre: " << myCancion.getGenre() << endl;
    cout << "Danceability: " << myCancion.getDanceability() << endl;
    cout << "Energy: " << myCancion.getEnergy() << endl;
    cout << "Key: " << myCancion.getKey() << endl;
    cout << "Loudness: " << myCancion.getLoudness() << endl;
    cout << "Mode: " << myCancion.getMode() << endl;
    cout << "Speechiness: " << myCancion.getSpeechiness() << endl;
    cout << "Acousticness: " << myCancion.getAcousticness() << endl;
    cout << "Instrumentalness: " << myCancion.getInstrumentalness() << endl;
    cout << "Liveness: " << myCancion.getLiveness() << endl;
    cout << "Valence: " << myCancion.getValence() << endl;
    cout << "Tempo: " << myCancion.getTempo() << endl;
    cout << "Duration: " << myCancion.getDurationMs() << endl;
    cout << "Time Signature: " << myCancion.getTimeSignature() << endl;

    return 0;
}
