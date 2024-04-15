#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <bits/stdc++.h>
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
#include "Mouse.h"
#include "Button.h"
#include "TextObject.h"


class GameLoop
{
private:
    const int HEIGHT = 768;
    const int WIDTH = 432;
    bool GameState;
    SDL_Window* window;
    SDL_Renderer* renderer;
    //GAMEPLAY
    Background background;
    Bird bird;
    Floor floor1;
    Floor floor2;
    vector<Pipe> upPipe;
    vector<Pipe> downPipe;
    Mouse* mouse = new Mouse;

    bool isPlaying = false;
    bool isGameOver = false;
    bool gameStarted = false;

    //GAMEOVER
    Background gameOverBg;
    Button* replayButton = new Button(0, 736);
    Button* exitButton = new Button(0, 368);
    //Menu
    Background menuBg;
    Button* playButton = new Button(0,0);
    Button* quitButton = new Button(0,920);
    //GameState
    bool MenuState ;
    bool GamePlayState;
    bool GameOverState;
    //Score
    int textWidth = 64;
    int textHeight = 100;
    int highScore;
    TextObject highestScore;
    int SCORE = 0;
    TTF_Font* scoreFont;
    TextObject score;
    int fontsize = 32;
    SDL_Color white = { 250, 250, 250 };

    //SOUND
    Mix_Music* clickSound;
    Mix_Music* wingSound;
    Mix_Music* dieSound;

public:
    GameLoop();
    bool getGameState();
    void Update();
    void Initialize();
    void Event();
    void Render();
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    void CollisionDetection();
    void ScoreUpdate();
    void HandleCollision();
    void NewGame();
    void Clear();
};
#endif // GAMELOOP_H
