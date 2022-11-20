#include "graphics.hpp"

/*
 * FILE DESCRIPTION:
 * Includes definitions for the basic functions relating to graphical rendering.
 */

//------------------------------------------------------------------------------------------------//
//GLOBAL GRAPHICS VARIABLES:

// Use SRC_NULL when you want the entire source file to be rendered.
const SDL_Rect graphics::SRC_NULL = { 0, 0, 0, 0 };

// The window fullscreen status.
bool graphics::isFullscreen = false;

//------------------------------------------------------------------------------------------------//
//LOCAL GRAPHICS VARIABLES:

// The graphics window.
static SDL_Window* window = nullptr;
// The graphics renderer.
static SDL_Renderer* renderer = nullptr;

// The assigned maximum amount of textures for the program. Change at will.
#define MAX_TEXTURES 128
// Contains all loaded textures in the program.
std::array<SDL_Texture*, MAX_TEXTURES> textures;

// The assigned maximum amount of fonts for the program. Change at will.
#define MAX_FONTS 4
// Contains all loaded fonts in the program.
std::array<TTF_Font*, MAX_FONTS> fonts;

//------------------------------------------------------------------------------------------------//
//TEXTURE ATTRIBUTES:

TextureAttributes::TextureAttributes(TextureIndex index, SDL_Rect _srcRect, SDL_Rect _dstRect, float _angle, SDL_Point* _rotPoint, SDL_RendererFlip _flip, Color _color, bool _center, float _scale) {
	texture = textures[index];
	srcRect = _srcRect;
	dstRect = _dstRect;
	angle = _angle;
	rotPoint = _rotPoint;
	flip = _flip;
	color = _color;
	center = _center;
	scale = _scale;
}

TextureAttributes::TextureAttributes(SDL_Texture* _texture, SDL_Rect _srcRect, SDL_Rect _dstRect, float _angle, SDL_Point* _rotPoint, SDL_RendererFlip _flip, Color _color, bool _center, float _scale) {
    TextureAttributes(0, _srcRect, _dstRect, _angle, _rotPoint, _flip, _color, _center, _scale);
    texture = _texture;
}

//------------------------------------------------------------------------------------------------//
//GRAPHICS INITIALIZATION FUNCTIONS:

void graphics::init() {

    // Initialize TTF:
    if (TTF_Init() == -1) {
        std::string sdlErrMsg(SDL_GetError());
        throw std::ios_base::failure("Unable to initialize TTF - " + sdlErrMsg);
    }

    // Initialize SDL Video System
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        std::string sdlErrMsg(SDL_GetError());
        throw std::ios_base::failure("Unable to initialize SDL subsystems - " + sdlErrMsg);
    }

    // Create SDL Window
    window = SDL_CreateWindow(
        "Rhythm Game", 
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH / 5, 
        WINDOW_HEIGHT / 5, 
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        std::string sdlErrMsg(SDL_GetError());
        throw std::ios_base::failure("Unable to create window - " + sdlErrMsg);
    }

    // Create SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        std::string sdlErrMsg(SDL_GetError());
        throw std::ios_base::failure("Unable to initialize renderer - " + sdlErrMsg);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetLogicalSize(renderer, WINDOW_WIDTH, WINDOW_HEIGHT);

    //TODO: Set icon

    // Set letterboxing:
    Color letterboxColor = LETTERBOX_COLOR;
    SDL_SetRenderDrawColor(renderer, letterboxColor.r, letterboxColor.g, letterboxColor.b, letterboxColor.a);

    // Default values for elements in textures and fonts array:
    std::for_each(textures.begin(), textures.end(), [](SDL_Texture* texture) { texture = nullptr; });
    std::for_each(fonts.begin(), fonts.end(), [](TTF_Font* font) { font = nullptr; });

    // Set window:
    Uint32 SDLFullscreenFlag = graphics::isFullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0;
    SDL_SetWindowFullscreen(window, SDLFullscreenFlag);
    SDL_SetWindowResizable(window, SDL_TRUE);
}

void graphics::deinit() {

    // Free textures and fonts:
    std::for_each(textures.begin(), textures.end(), [](SDL_Texture* texture) { SDL_DestroyTexture(texture); });
    std::for_each(fonts.begin(), fonts.end(), [](TTF_Font* font) { TTF_CloseFont(font); });

    // Free SDL window and renderer:
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL subsystems:
    TTF_Quit();
    SDL_Quit();

}

//------------------------------------------------------------------------------------------------//
//RENDERER FUNCTIONS:

void graphics::clear_renderer() {
    SDL_RenderClear(renderer);
}

void graphics::present_renderer() {
    SDL_RenderPresent(renderer);
}

//------------------------------------------------------------------------------------------------//
//LOADING FUNCTIONS:

void graphics::load_texture(TextureIndex idx, const char* filePath) {

    // Check if idx is in range:    
    if (idx >= MAX_TEXTURES) {
        std::string strFilePath(filePath);
        throw std::out_of_range("Maximum texture index reached by " + strFilePath + " at index " + std::to_string(idx));
    }

    // Create temporary surface:
    SDL_Surface* tempSurface = IMG_Load(filePath);
    if (!tempSurface) {
        SDL_FreeSurface(tempSurface);
        std::string strFilePath(filePath);
        std::string imgErrMsg(IMG_GetError());
        throw std::ios_base::failure("[Possible invalid file path argument] Unable to load image from " + strFilePath + " - " + imgErrMsg);
    }

    // Convert temporary surface to a texture loaded in the textures array:
    textures[idx] = SDL_CreateTextureFromSurface(renderer, tempSurface);

    #if !DANIEL

    SDL_FreeSurface(tempSurface);

    #endif

    if (!textures[idx]) {
        std::string sdlErrMsg(SDL_GetError());
        throw std::ios_base::failure("Unable to convert surface to texture - " + sdlErrMsg);
    }
}

void graphics::load_font(FontIndex idx, const char* filePath) {

    // Check if idx is in range:
    if (idx >= MAX_FONTS) {
        std::string strFilePath(filePath);
        throw std::out_of_range("Maximum font index reached by " + strFilePath + " at index " + std::to_string(idx));
    }

    // Create font:
    fonts[idx] = TTF_OpenFont(filePath, 72);
    if (!fonts[idx]) {
        fonts[idx] = nullptr;
        std::string strFilePath(filePath);
        std::string ttfErrMsg(TTF_GetError());
        throw std::ios_base::failure("[Possible invalid file path argument] Unable to load font at " + strFilePath + " - " + ttfErrMsg);
    }
}

void graphics::load() {
    #if DANIEL
    //--- LOAD TEXTURES ---//

    //- general -//
    graphics::load_texture(TEXTURE_MULTIPURPOSE_PIXEL, "../../assets/art/multipurpose_pixel.png");

    //- menu -//
    graphics::load_texture(TEXTURE_ANIMATED_BUTTON, "../../art/animated_button.png");
    graphics::load_texture(TEXTURE_LOGO, "../../art/logo.png");

    //- game -//
    graphics::load_texture(TEXTURE_PLAYER, "../../assets/art/player.png");
    graphics::load_texture(TEXTURE_TILESET, "../../assets/art/tileset.png");

    graphics::load_texture(TEXTURE_BULLET, "../../assets/art/bullet.png");
    graphics::load_texture(TEXTURE_DRONE_GREEN, "../../assets/art/droneGreen.png");
    graphics::load_texture(TEXTURE_DRONE_PURPLE, "../../assets/art/dronePurple.png");
    graphics::load_texture(TEXTURE_DRONE_RED, "../../assets/art/droneRed.png");
    graphics::load_texture(TEXTURE_LINE, "../../assets/art/line.png");

    //--- LOAD FONTS ---//
    graphics::load_font(FONT_GAME, "../../assets/fonts/FFFFORWA.TTF");

    #else
    //--- LOAD TEXTURES ---//

    //- general -//
    graphics::load_texture(TEXTURE_MULTIPURPOSE_PIXEL, "art/multipurpose_pixel.png");

    //- menu -//
    graphics::load_texture(TEXTURE_ANIMATED_BUTTON, "art/animated_button.png");
    graphics::load_texture(TEXTURE_LOGO, "art/logo.png");

    //- game -//
    graphics::load_texture(TEXTURE_PLAYER, "art/player.png");
    graphics::load_texture(TEXTURE_TILESET, "art/tileset.png");

    graphics::load_texture(TEXTURE_BULLET, "art/bullet.png");
    graphics::load_texture(TEXTURE_DRONE_GREEN, "art/droneGreen.png");
    graphics::load_texture(TEXTURE_DRONE_PURPLE, "art/dronePurple.png");
    graphics::load_texture(TEXTURE_DRONE_RED, "art/droneRed.png");
    graphics::load_texture(TEXTURE_LINE, "art/line.png");

    //--- LOAD FONTS ---//
    graphics::load_font(FONT_GAME, "fonts/FFFFORWA.TTF");

    #endif
}

//------------------------------------------------------------------------------------------------//
//STRING FUNCTIONS:

SDL_Texture* graphics::create_string_texture(std::string str, FontIndex font, int* w, int* h) {

    #if DANIEL

    return NULL;

    #endif

    // Create temporary surface:
    SDL_Surface* tempSurface = TTF_RenderText_Blended_Wrapped(fonts[font], str.c_str(), { 255, 255, 255, 255 }, WINDOW_WIDTH);
    if (!tempSurface) {
        //CRASH_LOG("ERROR: Unable to create string texture - " << TTF_GetError());
        SDL_FreeSurface(tempSurface);
        std::string ttfErrMsg(TTF_GetError());
        throw std::ios_base::failure("Unable to create string texture - " + ttfErrMsg);
    }

    // Convert temporary surface to string texture:
    SDL_Texture* strTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    SDL_QueryTexture(strTexture, NULL, NULL, w, h);
    return strTexture;

}

void graphics::destroy_string_texture(SDL_Texture* strTexture) {
    SDL_DestroyTexture(strTexture);
}

//------------------------------------------------------------------------------------------------//
//RENDERING FUNCTIONS:

void graphics::render_texture(TextureAttributes txt) {
    SDL_SetTextureColorMod(txt.texture, txt.color.r, txt.color.g, txt.color.b);
    SDL_SetTextureAlphaMod(txt.texture, txt.color.a);

    SDL_Rect* src = SDL_RectEquals(&txt.srcRect, &graphics::SRC_NULL) ? NULL : &txt.srcRect;
    SDL_Rect  dst = txt.dstRect;
    dst.w = txt.dstRect.w * txt.scale;
    dst.h = txt.dstRect.h * txt.scale;
    if (txt.center) {
        dst.x -= dst.w / 2;
        dst.y -= dst.h / 2;
    }

    SDL_RenderCopyEx(renderer, txt.texture, src, &dst, txt.angle, txt.rotPoint, txt.flip);

    SDL_SetTextureColorMod(txt.texture, 255, 255, 255);
    SDL_SetTextureAlphaMod(txt.texture, 255);
}

SDL_Renderer* graphics::get_renderer()
{
    return renderer;
}