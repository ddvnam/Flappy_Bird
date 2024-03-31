#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "Object.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include "TextureManager.h"

#include "Background.h"
#include "Floor.h"
#include "Bird.h"
#include "Pipe.h"
#include "TextObject.h"


class GameLoop
{
private:
    const int HEIGHT = 768;
    const int WIDTH = 432;
    bool GameState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Background background;
    Bird bird;
    Floor floor1;
    Floor floor2;
    Pipe upPipe[3];
    Pipe downPipe[3];


    bool isDie = false;
    bool isPlaying = false;

    //test
    TTF_Font* testFont;
    TextObject test;
    int fontsize = 32;
    SDL_Color white = { 250, 250, 250 };

public:
    GameLoop();
    bool getGameState();
    void Update();
    void Initialize();
    void Event();
    void Render();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    void CollisionDetection();
    void Clear();
};
#endif // GAMELOOP_H