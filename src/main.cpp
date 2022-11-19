#include "globals.hpp"
#include "IO/graphics.hpp"
#include "IO/audio.hpp"
#include "Scenes/Scene.hpp"
#include <SDL.h>

#include "Scenes/GameScene.hpp" // Change depending on what the starting scene is.
#include "quickmath.h"

int main(int argc, char** argv) {

    //--- INITIALIZATION AND LOADING ---//
    try {
        graphics::init();
        graphics::load();
        audio::init();
        audio::load();

        currentScene = std::make_unique<GameScene>();
    }
    catch (std::ios_base::failure& e) {
        std::cerr << "I/O ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::out_of_range& e) {
        std::cerr << "OUT OF RANGE ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::domain_error& e) {
        std::cerr << "DOMAIN ERROR: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cerr << "FATAL: Unexpected exception caught during I/O initialization and loading." << std::endl;
        return EXIT_FAILURE;
    }

    //--- MAIN LOOP ---//
    SDL_Event e;

    using clock = std::chrono::high_resolution_clock;
    clock::time_point currentTime = clock::now();

    while (running) {

        try {
            
            //--- INPUT ---//
            while (SDL_PollEvent(&e)) {

                if (e.type == SDL_MOUSEMOTION) {
                    mousePos.x = e.motion.x;
                    mousePos.y = e.motion.y;
                }

                if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
                    running = false;

                currentScene->handle_input(e);

            }

            //--- UPDATE ---//
            clock::time_point newTime = clock::now();
            clock::duration frameTime = newTime - currentTime;
            float deltaTime = frameTime.count() / 1000000000.0;
            currentTime = newTime;

            currentScene->update(deltaTime);

            //--- RENDER ---//
            graphics::clear_renderer();
            currentScene->render();
            graphics::present_renderer();

        }
        catch (std::ios_base::failure& e) {
            std::cerr << "I/O ERROR: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        catch (std::domain_error& e) {
            std::cerr << "DOMAIN ERROR: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        catch (...) {
            std::cerr << "FATAL: Unexpected exception caught during the game main loop." << std::endl;
            return EXIT_FAILURE;
        }
    }

    //--- DEINIT PROGRAM ---//
    audio::deinit();
    graphics::deinit();

    return EXIT_SUCCESS;
}