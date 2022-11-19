#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "globals.hpp"

/*
 * FILE DESCRIPTION:
 * Includes declarations for all structures/functions relating to graphical rendering
 */

// The program window width (excluding letterboxing) in SDL units. Errors are corrected through letterboxing.
#define WINDOW_WIDTH 3840
// The program window height (excluding letterboxing) in SDL units. Errors are corrected through letterboxing.
#define WINDOW_HEIGHT 2160

// The designated color for letterboxing. If the physical window aspect ratio does not equal the SDL program window aspect ratio, letterboxing is used to cover the gaps.
#define LETTERBOX_COLOR { 0, 0, 0, 255 } // 50, 50, 60

//------------------------------------------------------------------------------------------------//
//GRAPHICS DATA TYPES:

// Represents all available textures.
// All indices are expected to be properly loaded, use graphics::load_texture() for every index.
enum TextureIndex : unsigned char {

    //--- GENERAL ---//
	TEXTURE_MULTIPURPOSE_PIXEL,

	//--- GAME ---//
	TEXTURE_PLAYER,
	TEXTURE_TILESET
};

// Represents all available fonts.
// All indices are expected to be properly loaded, use graphics::load_font() for every index.
enum FontIndex : unsigned char {

    //--- GENERAL ---//
	FONT_GAME

};

// Represents an RGBA color
struct Color {
    unsigned char r; // Red channel value (from 0 to 255)
    unsigned char g; // Green channel value (from 0 to 255)
    unsigned char b; // Blue channel value (from 0 to 255)
    unsigned char a; // Alpha channel value (from 0 to 255)
};

// Represents all the required information and attributes to render a texture onto the SDL program window.
struct TextureAttributes {

    //------------------------------------------------------------------------------------------------//
	//TEXTURE RENDERING ATTRIBUTES:

	// The texture to render onto the window.
	SDL_Texture* texture;
	// A rectangle that determines which part of the source texture to render. 
	// It follows the format { x, y, w, h } with (w, h) being the rectangle's dimensions. (x, y) depends on whether the texture is centered. Look at 'center' attribute for more information.
	SDL_Rect srcRect;
	// A rectangle that determines where on the SDL program window to render the texture.
	// It follows the format { x, y, w, h } in terms of SDL units with (x, y) being the top-left corner of the rectangle and (w, h) being the rectangle's dimensions.
	SDL_Rect dstRect;

    //------------------------------------------------------------------------------------------------//
    //TEXTURE MODIFIERS:

	// The clockwise rotation around the texture's rotation point (value of the texture's rotPoint pointer) in terms of degrees.
	float angle;
	// Points to an SDL_Point position that represents the texture's point of rotation.
	// The value of this pointer takes the format (x, y), representing the horizontal and vertical distances in SDL units from the texture's top-left corner to the texture's rotation point.
	SDL_Point* rotPoint;
	// The flip state of the texture. SDL_FLIP_NONE keeps the texture unchanged, SDL_FLIP_HORIZONTAL flips the texture horizontally, and SDL_FLIP_VERTICAL flips the texture vertically.
	SDL_RendererFlip flip;
	// The color modifier of the texture. { 255, 255, 255, 255 } (opaque white) keeps the texture unchanged.
	Color color;
	// Determines if the texture is centered. If true, dstRect (x, y) represents dstRect's center. If false, dstRect (x, y) represents dstRect's top-left corner.
	bool center;
	// Determines how much the texture should be scaled by.
	float scale;

	//--------------------------------------------------------------------------------------------------------------------------------//
	//CONSTRUCTORS:

	/* A default constructor is necessary for TextureAttributes in UIElementsand Scenes to initialize before their constructors are called.
	 * This constructor should not be used for initialization, use the other 2 instead for proper initialization of attribute variables.
	 */ 
	TextureAttributes() = default;
    /* A constructor that takes in a texture index as a parameter.
	 * @param index The texture index that represents the texture wanted to render onto the window.
	 * @param _srcRect A rectangle that determines which part of the source texture to render. Look at 'srcRect' comments in the TextureAttributes struct for formatting.
	 * @param _dstRect A rectangle that determines where on the SDL program window to render the texture. Look at 'dstRect' comments in the TextureAttributes struct for formatting.
     * @param _zOrder The order that the texture should be rendered in relation to other textures being rendered in the same frame.
	 * @param _angle The clockwise rotation around the texture's rotation point (value of the texture's rotPoint pointer) in terms of degrees.
	 * @param _rotPoint Points to an SDL_Point position that represents the texture's point of rotation. Look at 'rotPoint' comments in the TextureAttributes struct for formatting.
	 * @param _flip The flip state of the texture. Takes in three states: SDL_FLIP_NONE, SDL_FLIP_HORIZONTAL, and SDL_FLIP_VERTICAL.
	 * @param _color The color modifier of the texture. { 255, 255, 255, 255 } (opaque white) keeps the texture unchanged.
	 * @param _center Determines if the texture if centered. If true, dstRect (x, y) represents dstRect's center. If false, dstRect (x, y) represents dstRect's top-left corner.
	 * @param _scale Determines how much the texture should be scaled by.
	 * @returns A TextureAttributes struct with properly initialized attributes ready for rendering.
	 */
	TextureAttributes(TextureIndex index, SDL_Rect _srcRect, SDL_Rect _dstRect, float _angle, SDL_Point* _rotPoint, SDL_RendererFlip _flip, Color _color, bool _center, float _scale);
    /* A constructor that takes in a texture as a parameter. This is useful for text rendering as string textures do not have a TextureIndex.
     * NOTE: The TextureIndex enum must have at least 1 constant for this constructor to work.
     * @param _texture The texture to render onto the window.
     * @param * All other parameters are identical to the constructor that takes in a TextureIndex index.
     * @returns A TextureAttributes struct with properly initialized attributes ready for rendering.
     */
	TextureAttributes(SDL_Texture* _texture, SDL_Rect _srcRect, SDL_Rect _dstRect, float _angle, SDL_Point* _rotPoint, SDL_RendererFlip _flip, Color _color, bool _center, float _scale);

};

namespace graphics {

	extern const SDL_Rect SRC_NULL;
	extern bool isFullscreen;

	//------------------------------------------------------------------------------------------------//
	//GRAPHICS METHODS:

	/* Initializes the graphics system.
	 * @throws std::ios_base::failure - When graphics initialization is unsuccessful.
	 */
	void init();
	/* Properly closes the graphics system and frees all textures.
	 */
	void deinit();

	/* Clears the renderer to prepare for rendering. Run this function every frame before anything is rendered.
	 */
	void clear_renderer();
	/* Presents the renderer for the screen to display. RUn this function every frame after all textures for the frame are rendered.
	 */
	void present_renderer();

	/* Loads the texture at the given path into memory at the given index.
	 * @param idx The texture index to load the texture to.
	 * @param filePath The .png file path to get the texture from.
	 * @throws std::out_of_range - When a texture is loaded at an index out of range.
	 * @throws std::ios_base::failure - When image loading or surface-to-texture conversion is unsuccessful.
	 */
	void load_texture(TextureIndex idx, const char* filePath);
	/* Loads the font at the given path into memory at the given index.
	 * @param idx The font index to load the font to.
	 * @param filePath The .ttf file path to get the font from.
	 * @throws std::out_of_range - When a font is loaded at an index out of range.
	 * @throws std::ios_base::failure - When font loading is unsuccessful.
	 */
	void load_font(FontIndex idx, const char* filePath);
	/* Loads all textures and fonts needed for the game.
	 * @throws Throws exceptions if any font or texture loading is unsuccessful.
	 * Look at graphics::load_texture() and graphics::load_font() for more details on exceptions.
	 */
	void load();

	/* Creates a string texture with a given string, fixing the texture's width and height.
	 * All instances of create_string_texture() should be paired with a destroy_string_texture() to avoid memory leaks.
	 * @param str The string that the texture displays.
	 * @param font The font of the string.
	 * @param w A pointer filled in with the width of the texture in pixels.
	 * @param h A pointer filled in with the height of the texture in pixels.
	 * @returns The string texture.
	 */
	SDL_Texture* create_string_texture(std::string str, FontIndex font, int* w, int* h);
	/* Properly destroys a string texture.
	 * @param strTexture The texture to destroy.
	 */
	void destroy_string_texture(SDL_Texture* strTexture);

	/* Renders the given texture to the screen. Be mindful of the order you render textures in.
	 * @param texture Texture to be rendered on the screen.
	 */
	void render_texture(TextureAttributes texture);

	SDL_Renderer* get_renderer();
}