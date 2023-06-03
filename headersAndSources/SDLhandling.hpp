#pragma once

#include "Mouse.hpp"
#include "Hitbox.hpp"

#include <iostream>
#include <SDL_image.h>
#include <SDL.h>
#undef main

enum userInput {
    KEYDOWN_A,
    KEYDOWN_W,
    KEYDOWN_S,
    KEYDOWN_D,
    KEYDOWN_ESC,
    KEYDOWN_SHIFT,

    KEYUP_A,
    KEYUP_W,
    KEYUP_S,
    KEYUP_D,
    KEYUP_SHIFT,
    KEYUP_SPACE,

    MOUSEEVENT,
    QUIT,
    NOTHING
};

//namespace for SDL functionality
namespace SDL {

    class Manager {

    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

    public:
        Manager() {
            renderer = NULL;
            window = NULL;
        }
        Manager(const char* title, int width, int height) {
            setSDL(title, width, height);
        }
        void setSDL(char const* title, int w, int h) {
            if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
                SDL_Log("SDL cannot be started: % s", SDL_GetError());
                exit(1);
            }

            window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
            if (window == NULL) {
                SDL_Log("window cannot be created: %s", SDL_GetError());
                exit(1);
            }

            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
            if (renderer == NULL) {
                SDL_Log("renderer cannot be created: %s", SDL_GetError());
                exit(1);
            }

            SDL_RenderClear(renderer);
            SDL_Init(SDL_INIT_AUDIO);
            IMG_Init(IMG_INIT_PNG);

        }
        SDL_Renderer* getRenderer() const { return renderer; }
        void drawImage(SDL_Texture* texture, int x, int y, int w, int h) const {

            SDL_Rect SrcR;
            SDL_Rect DestR;

            DestR.x = x;
            DestR.y = y;
            DestR.w = w;
            DestR.h = h;

            SrcR.x = 0;
            SrcR.y = 0;
            SrcR.w = 600;
            SrcR.h = 600;

            SDL_RenderCopy(renderer, texture, &SrcR, &DestR);
        }
        void drawCroppedImage(SDL_Texture* texture, int size, int destX, int destY, int x, int y) const {
            SDL_Rect SrcR;
            SDL_Rect DestR;

            DestR.x = destX;
            DestR.y = destY;
            DestR.w = size;
            DestR.h = size;

            SrcR.x = x;
            SrcR.y = y;
            SrcR.w = (930 / 10);
            SrcR.h = (385 / 5);

            SDL_RenderCopy(renderer, texture, &SrcR, &DestR);
        }
        void renderFrame() const { SDL_RenderPresent(renderer); }
        void clearFrame() const { SDL_RenderClear(renderer); }
        int getTime() const { return SDL_GetTicks(); }
        void delay(int ms) const { SDL_Delay(ms); }
        ~Manager() {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }
    };

    class Image {

    private:
        SDL_Texture* texture = nullptr;
        static SDL_Renderer* renderer;

    public:
        Image() { texture = nullptr; }
        Image(const char* fileName) {
            SDL_Surface* tmp = IMG_Load(fileName);
            texture = SDL_CreateTextureFromSurface(renderer, tmp);
            SDL_FreeSurface(tmp);
        }
        static void setRenderer(const SDL::Manager& manager) {
            renderer = manager.getRenderer();
        }
        SDL_Texture* getTexture() const { return texture; }
        void setTexture(const char* fileName) {
            SDL_Surface* tmp = IMG_Load(fileName);
            texture = SDL_CreateTextureFromSurface(renderer, tmp);
            SDL_FreeSurface(tmp);
        }
        void resetTexture(const char* fileName) {
            SDL_DestroyTexture(texture);
            setTexture(fileName);
        }
        void draw(const SDL::Manager& manager, const Hitbox& hitbox) const {
            int x = hitbox.getX();
            int y = hitbox.getY();
            int w = hitbox.getWidth();
            int h = hitbox.getHeight();

            manager.drawImage(texture, x, y, w, h);
        }
        void operator=(const Image& image) { texture = image.getTexture(); }
        ~Image() {
            // SDL_DestroyTexture(texture);
        }
    };

    class Event {

    private:
        SDL_Event event;

    public:
        Event() {}
        int getNewEvent(Mouse& mouse) {
            while (SDL_PollEvent(&event)) {
                
                switch (event.type) {
                    case SDL_KEYDOWN: {
                        switch (event.key.keysym.sym) {
                        case SDLK_d:
                            return KEYDOWN_D;

                        case SDLK_a:
                            return KEYDOWN_A;

                        case SDLK_w:
                            return KEYDOWN_W;

                        case SDLK_LSHIFT:
                            return KEYDOWN_SHIFT;

                        case SDLK_ESCAPE:
                            return KEYDOWN_ESC;
                        }
                        break;
                }

                case SDL_KEYUP: {
                    switch (event.key.keysym.sym) {
                        case SDLK_d:
                            return KEYUP_D;

                        case SDLK_a:
                            return KEYUP_A;

                        case SDLK_LSHIFT:
                            return KEYUP_SHIFT;

                        case SDLK_SPACE:
                            return KEYUP_SPACE;
                        }
                       

                        break;
                }

                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    return MOUSEEVENT;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                        mouse.leftClick = true;
                    return MOUSEEVENT;
           
                case SDL_QUIT:
                    return QUIT;
                }
            }
            return NOTHING;
        }
    };
}