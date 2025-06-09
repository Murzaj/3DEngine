#include "SoundHandler.hpp"
#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>

SoundHandler::SoundHandler() {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SoundHandler: Nie uda³o siê zainicjowaæ SDL Audio! SDL_Error: " << SDL_GetError() << std::endl;
        sdlAudioInitialized = false;
        return;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SoundHandler: Nie uda³o siê otworzyæ urz¹dzenia audio! Mix_Error: " << Mix_GetError() << std::endl;
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        sdlAudioInitialized = false;
        return;
    }
    Mix_AllocateChannels(16);
    sdlAudioInitialized = true;
    std::cout << "SoundHandler: Zainicjalizowano SDL_mixer." << std::endl;
}

SoundHandler::~SoundHandler() {
    if (sdlAudioInitialized) {
        std::cout << "SoundHandler: Zamykanie SDL_mixer." << std::endl;
        stopAllSounds();
        for (auto& pair : loadedSounds) {
            if (pair.second.sdl_music) Mix_FreeMusic(pair.second.sdl_music);
            if (pair.second.sdl_chunk) Mix_FreeChunk(pair.second.sdl_chunk);
        }
        loadedSounds.clear();
        Mix_CloseAudio();
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}

bool SoundHandler::loadSound(const std::string& name, const std::string& filename, bool loop) {
    if (!sdlAudioInitialized) {
        std::cerr << "SoundHandler: Próba za³adowania dŸwiêku, gdy SDL_mixer nie jest zainicjowany." << std::endl;
        return false;
    }
    if (loadedSounds.count(name)) {
        loadedSounds[name].isLooping = loop;
        return true;
    }

    SoundInfo info;
    info.filename = filename;
    info.isLooping = loop;

    if (loop) {
        info.sdl_music = Mix_LoadMUS(filename.c_str());
        if (!info.sdl_music) {
            std::cerr << "SoundHandler: Nie uda³o siê za³adowaæ muzyki '" << filename << "': " << Mix_GetError() << std::endl;
            return false;
        }
    }
    else {
        info.sdl_chunk = Mix_LoadWAV(filename.c_str());
        if (!info.sdl_chunk) {
            std::cerr << "SoundHandler: Nie uda³o siê za³adowaæ efektu dŸwiêkowego '" << filename << "': " << Mix_GetError() << std::endl;
            return false;
        }
    }
    loadedSounds[name] = info;
    std::cout << "SoundHandler: Za³adowano dŸwiêk '" << name << "' z pliku '" << filename << (loop ? "' (zapêtlony)." : "'.") << std::endl;
    return true;
}

void SoundHandler::playSound(const std::string& name) {
    if (!sdlAudioInitialized) return;
    auto it = loadedSounds.find(name);
    if (it != loadedSounds.end()) {
        if (it->second.sdl_music) {
            if (Mix_PlayMusic(it->second.sdl_music, it->second.isLooping ? -1 : 0) == -1) { 
                std::cerr << "SoundHandler: Nie uda³o siê odtworzyæ muzyki '" << name << "': " << Mix_GetError() << std::endl;
            }
            else {
                std::cout << "SoundHandler: Odtwarzanie muzyki '" << name << "'." << std::endl;
            }
        }
        else if (it->second.sdl_chunk) {
            int channel = Mix_PlayChannel(-1, it->second.sdl_chunk, 0); 
            if (channel == -1) {
                std::cerr << "SoundHandler: Nie uda³o siê odtworzyæ efektu '" << name << "': " << Mix_GetError() << std::endl;
            }
            else {
                it->second.channel = channel; 
                std::cout << "SoundHandler: Odtwarzanie efektu '" << name << "' na kanale " << channel << "." << std::endl;
            }
        }
    }
    else {
        std::cerr << "SoundHandler: Nie znaleziono dŸwiêku '" << name << "'." << std::endl;
    }
}

void SoundHandler::stopSound(const std::string& name) {
    if (!sdlAudioInitialized) return;
    auto it = loadedSounds.find(name);
    if (it != loadedSounds.end()) {
        if (it->second.sdl_music && Mix_PlayingMusic()) {
            Mix_HaltMusic();
            std::cout << "SoundHandler: Zatrzymano muzykê (globalnie) dla ¿¹dania '" << name << "'." << std::endl;
        }
        else if (it->second.sdl_chunk && it->second.channel != -1) {
            if (Mix_Playing(it->second.channel)) {
                Mix_HaltChannel(it->second.channel);
                std::cout << "SoundHandler: Zatrzymano efekt '" << name << "' na kanale " << it->second.channel << "." << std::endl;
            }
            it->second.channel = -1; 
        }
    }
    else {
        std::cerr << "SoundHandler: Nie znaleziono dŸwiêku '" << name << "' do zatrzymania." << std::endl;
    }
}

void SoundHandler::stopAllSounds() {
    if (!sdlAudioInitialized) return;
    std::cout << "SoundHandler: Zatrzymywanie wszystkich dŸwiêków." << std::endl;
    Mix_HaltMusic();
    Mix_HaltChannel(-1); 
    for (auto& pair : loadedSounds) {
        pair.second.channel = -1; 
    }
}

bool SoundHandler::isPlaying(const std::string& name) const {
    if (!sdlAudioInitialized) return false;
    auto it = loadedSounds.find(name);
    if (it != loadedSounds.end()) {
        if (it->second.sdl_music) {
            return Mix_PlayingMusic() == 1 && Mix_GetMusicHookData() == it->second.sdl_music; 
            return Mix_PlayingMusic() == 1; 
        }
        else if (it->second.sdl_chunk && it->second.channel != -1) {
            return Mix_Playing(it->second.channel) == 1;
        }
    }
    return false;
}