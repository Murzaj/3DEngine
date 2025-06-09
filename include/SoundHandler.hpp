#pragma once

#include <string>
#include <unordered_map>
#include <iostream>
#include <SDL_mixer.h>

/// @brief Mened¿er dŸwiêku oparty na SDL_mixer.
///
/// Klasa umo¿liwia ³adowanie, odtwarzanie i zatrzymywanie efektów dŸwiêkowych oraz muzyki.
/// Obs³uguje zarówno dŸwiêki jednorazowe, jak i zapêtlone.
class SoundHandler {
public:
    /// @brief Konstruktor inicjalizuj¹cy system audio.
    SoundHandler();

    /// @brief Destruktor zwalniaj¹cy zasoby audio.
    ~SoundHandler();

    /// @brief £aduje plik dŸwiêkowy.
    /// @param name Nazwa identyfikuj¹ca dŸwiêk.
    /// @param filename Œcie¿ka do pliku audio.
    /// @param loop Czy dŸwiêk ma byæ zapêtlany (domyœlnie false).
    /// @return true jeœli uda³o siê za³adowaæ dŸwiêk, false w przeciwnym razie.
    bool loadSound(const std::string& name, const std::string& filename, bool loop = false);

    /// @brief Odtwarza wczeœniej za³adowany dŸwiêk.
    /// @param name Nazwa identyfikuj¹ca dŸwiêk.
    void playSound(const std::string& name);

    /// @brief Zatrzymuje odtwarzanie dŸwiêku.
    /// @param name Nazwa identyfikuj¹ca dŸwiêk.
    void stopSound(const std::string& name);

    /// @brief Zatrzymuje odtwarzanie wszystkich dŸwiêków.
    void stopAllSounds();

    /// @brief Sprawdza, czy dany dŸwiêk jest aktualnie odtwarzany.
    /// @param name Nazwa identyfikuj¹ca dŸwiêk.
    /// @return true jeœli dŸwiêk jest odtwarzany, false w przeciwnym razie.
    bool isPlaying(const std::string& name) const;

private:
    /// @brief Struktura przechowuj¹ca informacje o dŸwiêku.
    struct SoundInfo {
        std::string filename;      ///< Œcie¿ka do pliku audio.
        bool isLooping;            ///< Flaga zapêtlenia.
        Mix_Music* sdl_music;      ///< WskaŸnik do struktury SDL dla muzyki.
        Mix_Chunk* sdl_chunk;      ///< WskaŸnik do struktury SDL dla efektu dŸwiêkowego.
        int channel;               ///< Kana³, na którym odtwarzany jest dŸwiêk.

        /// @brief Konstruktor domyœlny.
        SoundInfo() : filename(""), isLooping(false), sdl_music(nullptr), sdl_chunk(nullptr), channel(-1) {}
    };

    std::unordered_map<std::string, SoundInfo> loadedSounds;  ///< Mapa za³adowanych dŸwiêków.
    bool sdlAudioInitialized;                                  ///< Flaga informuj¹ca, czy SDL audio zosta³o poprawnie zainicjalizowane.
};
