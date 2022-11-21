#pragma once
#include "SDL_mixer.h"
#include "globals.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for all structures/functions relating to audio rendering.
 */

//------------------------------------------------------------------------------------------------//
//AUDIO DATA TYPES:

// Represents all of the music files available and their indices.
// All indices are expected to be properly loaded, use audio::load_music() for every index.
enum MusicIndex : unsigned char {
    MUSIC_MENU,
    MUSIC_GAME
};

// Represents all of the SFX sound effects available and their indices.
// All indices are expected to be properly loaded, use audio::load_sfx() for every index.
enum SfxIndex : unsigned char {
    SFX_DASH,
    SFX_BULLET,
    SFX_KILL,
    SFX_DAMAGE
};

namespace audio {

    extern float sfxVol;
    extern float musicVol;

    //------------------------------------------------------------------------------------------------//
	//AUDIO METHODS:

    /* Initializes the audio system.
     * @throws std::ios_base::failure - When audio initialization is unsuccessful.
     * @throws std::invalid_argument - Could be thrown from audio::set_sfx_volume() or audio::set_music_volume().
     */
    void init();
    /* Properly closes the audio system and frees all sound effects and music.
     */
    void deinit();

    /* Loads the song at the given path into memory at the given index.
     * @param idx The index in the MusicIndex enum to load the song to.
     * @param filePath The file path (must lead to a .wav file) to load the song from.
     * @throws std::out_of_range - When a song is loaded at an index out of range.
     * @throws std::ios_base::failure - When song loading is unsuccessful.
     */
    void load_music(MusicIndex idx, const char* filePath);
    /* Loads the SFX sound effect at the given path into memory at the given index.
     * @param idx The index in the SfxIndex enum to load the SFX sound effect to.
     * @param filePath The file path (must lead to a .wav file) to load the SFX sound effect from.
     * @throws std::out_of_range - When an SFX sound effect is loaded at an index out of range.
     * @throws std::ios_base::failure - When SFX sound effect loading is unsuccessful.
     */
    void load_sfx(SfxIndex idx, const char* filePath, unsigned int volume);
    /* Loads all music and SFX needed for the game.
     * @throws Throws exceptions if any song or SFX loading is unsuccessful.
     * Look at audio::load_music() and audio::load_font() for more details on exceptions.
     */
    void load();

    /* Sets the volume of sound effects.
     * @param volume The desired SFX volume. 0 is the minimum, 1 is the maximum.
     * @throws std::domain_error - When the 'vol' argument is below 0 or above 1.
     */
    void set_sfx_vol(float vol);
    /* Sets the music volume.
     * @param volume The desired music volume. 0 is the minimum, 1 is the maximum.
     * @throws std::domain_error - When the 'vol' argument is below 0 or above 1.
     */
    void set_music_vol(float vol);

    /* Plays the SFX file at the given index on the mixer once.
     * @param idx The index in the SfxIndex enum to play.
     */
    void play_sfx(SfxIndex idx);
    /* Plays the music file at the given index on the mixer once. 
     * @param idx The index in the MusicIndex enum to play.
     */
    void play_music(MusicIndex idx);
    /* Checks if the current music on the mixer is paused.
     * @returns true if the current music on the mixer is pause, false if otherwise. 
     */
    bool is_music_paused();
    /* Checks if there is currently music playing on the mixer. Paused music is treating as playing on the mixer.
     * @returns true if there is currently music playing on the mixer, false if otherwise.
     */
    bool is_music_playing();
    /* Pauses the current music on the mixer.
     */
    void pause_music();
    /* Resumes the current music on the mixer.
     */
    void resume_music();
    /* Stops the current music on the mixer.
     */
    void halt_music();

}