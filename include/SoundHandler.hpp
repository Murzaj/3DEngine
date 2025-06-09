#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <SDL_mixer.h>

/// @brief Mened�er d�wi�ku oparty na SDL_mixer.
///
/// Klasa umo�liwia �adowanie, odtwarzanie i zatrzymywanie efekt�w d�wi�kowych oraz muzyki.
/// Obs�uguje zar�wno d�wi�ki jednorazowe, jak i zap�tlone.
class SoundHandler {
public:
    /// @brief Konstruktor inicjalizuj�cy system audio.
    SoundHandler();

    /// @brief Destruktor zwalniaj�cy zasoby audio.
    ~SoundHandler();

    /// @brief �aduje plik d�wi�kowy.
    /// @param name Nazwa identyfikuj�ca d�wi�k.
    /// @param filename �cie�ka do pliku audio.
    /// @param loop Czy d�wi�k ma by� zap�tlany (domy�lnie false).
    /// @return true je�li uda�o si� za�adowa� d�wi�k, false w przeciwnym razie.
    bool loadSound(const std::string& name, const std::string& filename, bool loop = false);

    /// @brief Odtwarza wcze�niej za�adowany d�wi�k.
    /// @param name Nazwa identyfikuj�ca d�wi�k.
    void playSound(const std::string& name);

    /// @brief Zatrzymuje odtwarzanie d�wi�ku.
    /// @param name Nazwa identyfikuj�ca d�wi�k.
    void stopSound(const std::string& name);

    /// @brief Zatrzymuje odtwarzanie wszystkich d�wi�k�w.
    void stopAllSounds();

    /// @brief Sprawdza, czy dany d�wi�k jest aktualnie odtwarzany.
    /// @param name Nazwa identyfikuj�ca d�wi�k.
    /// @return true je�li d�wi�k jest odtwarzany, false w przeciwnym razie.
    bool isPlaying(const std::string& name) const;

private:
    /// @brief Struktura przechowuj�ca informacje o d�wi�ku.
    struct SoundInfo {
        std::string filename;      ///< �cie�ka do pliku audio.
        bool isLooping;            ///< Flaga zap�tlenia.
        Mix_Music* sdl_music;      ///< Wska�nik do struktury SDL dla muzyki.
        Mix_Chunk* sdl_chunk;      ///< Wska�nik do struktury SDL dla efektu d�wi�kowego.
        int channel;               ///< Kana�, na kt�rym odtwarzany jest d�wi�k.

        /// @brief Konstruktor domy�lny.
        SoundInfo() : filename(""), isLooping(false), sdl_music(nullptr), sdl_chunk(nullptr), channel(-1) {}
    };

    std::unordered_map<std::string, SoundInfo> loadedSounds;  ///< Mapa za�adowanych d�wi�k�w.
    bool sdlAudioInitialized;                                  ///< Flaga informuj�ca, czy SDL audio zosta�o poprawnie zainicjalizowane.
};
