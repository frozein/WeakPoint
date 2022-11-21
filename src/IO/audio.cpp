#include "audio.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the basic functions relating to the audio system.
 */

//------------------------------------------------------------------------------------------------//
//GLOBAL AUDIO VARIABLES:

// The global SFX sound effect volume.
float audio::sfxVol;

// The global music volume.
float audio::musicVol;

//------------------------------------------------------------------------------------------------//
//LOCAL GRAPHICS VARIABLES:

// The maximum amount of loaded SFX sound effects. Loading an SFX sound effect with an index above this amount will throw an error.
#define MAX_SFX 64
// Tha array of pointers that point to SFX sound effects. An index not loaded is represented by a null pointer.
static std::array<Mix_Chunk*, MAX_SFX> sfx;

// The maximum amount of loaded music files. Loading a music file with an index above this amount will throw an error.
#define MAX_MUSIC 4
// The array of pointers that point to music files. An index not loaded is represented by a null pointer.
static std::array<Mix_Music*, MAX_MUSIC> music;

//------------------------------------------------------------------------------------------------//
//AUDIO INITIALIZATION FUNCTIONS:

void audio::init() {

    // Initialize sound system:
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		std::string mixErrMsg(Mix_GetError());
        throw std::ios_base::failure("Unable to open sound system - " + mixErrMsg);
	}

	// Set all SFX and music to 'nullptr' to be able to check that they are loaded later:
    std::for_each(sfx.begin(), sfx.end(), [](Mix_Chunk* sfxChunk) { sfxChunk = nullptr; });
    std::for_each(music.begin(), music.end(), [](Mix_Music* song) { song = nullptr; });

    // Initialize global SFX and music volume.
    audio::set_sfx_vol(0.25);
    audio::set_music_vol(0.25);

}

void audio::deinit() {

    // Free all SFX and music:
    std::for_each(sfx.begin(), sfx.end(), [](Mix_Chunk* sfxChunk) { Mix_FreeChunk(sfxChunk); });
    std::for_each(music.begin(), music.end(), [](Mix_Music* song) { Mix_FreeMusic(song); });

    // Close audio system:
    Mix_CloseAudio();

}

//------------------------------------------------------------------------------------------------//
//AUDIO LOADING FUNCTIONS:

void audio::load_music(MusicIndex idx, const char* filePath) {

    // Check if idx is in range:
    if (idx >= MAX_MUSIC) {
        std::string strFilePath(filePath);
        throw std::out_of_range("Maximum music index reached by " + strFilePath + " at index " + std::to_string(idx));
    }

    // Load music and check for failures:
    music[idx] = Mix_LoadMUS(filePath);
    if (!music[idx]) {
        std::string strFilePath(filePath);
        std::string mixErrMsg(Mix_GetError());
        throw std::ios_base::failure("[Possible invalid file path argument] Unable to load music file at " + strFilePath + " - " + mixErrMsg);
    }

}

void audio::load_sfx(SfxIndex idx, const char* filePath, unsigned int volume) {

    // Check if idx is in range:
    if (idx >= MAX_SFX) {
        std::string strFilePath(filePath);
        throw std::out_of_range("Maximum SFX index reached by " + strFilePath + " at index " + std::to_string(idx));
    }

    // Load SFX sound effect and check for failures:
    sfx[idx] = Mix_LoadWAV(filePath);
    if (!sfx[idx]) {
        std::string strFilePath(filePath);
        std::string mixErrMsg(Mix_GetError());
        throw std::ios_base::failure("[Possible invalid file path argument] Unable to load SFX file at " + strFilePath + " - " + mixErrMsg);
    }
    Mix_VolumeChunk(sfx[idx], volume);
}

void audio::load() {

    //--- LOAD MUSIC ---//
    load_music(MUSIC_MENU, "music/menu.wav");
    load_music(MUSIC_GAME, "music/game.wav");

    //--- LOAD SFX ---//
    load_sfx(SFX_DASH, "sfx/dash.wav", 128);
    load_sfx(SFX_BULLET, "sfx/bullet.wav", 25);
    load_sfx(SFX_KILL, "sfx/kill.wav", 128);
    load_sfx(SFX_DAMAGE, "sfx/damage.wav", 128);
}

//------------------------------------------------------------------------------------------------//
//VOLUME FUNCTIONS:

void audio::set_sfx_vol(float vol) {

    // Check if 'vol' argument is in range:
    if (vol < 0.0 || vol > 1.0)
        throw std::domain_error("The SFX volume argument is out of range, either below 0.0 or above 1.0. argument passed = " + std::to_string(vol));

    // Set the global SFX volume:
    sfxVol = vol;

    // Loop through every loaded SFX volume and set its volume.
    std::for_each(sfx.begin(), sfx.end(), [](Mix_Chunk* sfxChunk) {
        if (sfxChunk)
            Mix_VolumeChunk(sfxChunk, (int)(MIX_MAX_VOLUME * sfxVol));
    });

}

void audio::set_music_vol(float vol) {

    // Check if 'vol' argument is in range:
    if (vol < 0.0 || vol > 1.0)
        throw std::domain_error("The music volume argument is out of range, either below 0.0 or above 1.0. argument passed = " + std::to_string(vol));

    // Set the music volume:
    musicVol = vol;
    Mix_VolumeMusic((int)(MIX_MAX_VOLUME * musicVol));

}

//------------------------------------------------------------------------------------------------//
//AUDIO CONTROL FUNCTIONS:

void audio::play_sfx(SfxIndex idx) {
    Mix_PlayChannel(-1, sfx[idx], 0);
}

void audio::play_music(MusicIndex idx) {
    Mix_PlayMusic(music[idx], 1);
}

bool audio::is_music_paused() {
    return Mix_PausedMusic();
}

bool audio::is_music_playing() {
    return Mix_PlayingMusic() != 0;
}

void audio::pause_music() {
    Mix_PauseMusic();
}

void audio::resume_music() {
    Mix_ResumeMusic();
}

void audio::halt_music() {
    Mix_HaltMusic();
}