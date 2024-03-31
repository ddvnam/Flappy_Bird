#include "GameLoop.h"

GameLoop::GameLoop()
{
    window = NULL;
    renderer = NULL;
    GameState = false;

    test.setSrc(0, 0, NULL, NULL);
    test.setDest(100, 100, 100, 100);
}

bool GameLoop::getGameState() {
    return GameState;
}

void GameLoop::Initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow("Flappy Bird", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if(window){
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer) {
            std::cout << "Succeeded!" << std::endl;
            GameState = true;

            //Background
            background.CreateTexture("assets/image/background-night.png", renderer);

            //Bird
            bird.CreateTexture("assets/image/yellowbird-midflap.png", renderer);
            bird.CreateTexture1("assets/image/yellowbird-upflap.png", renderer);
            bird.CreateTexture2("assets/image/yellowbird-downflap.png", renderer);

            //Floor
            floor1.CreateTexture("assets/image/floor.png", renderer);
            floor2.CreateTexture("assets/image/floor.png", renderer);
            //Pipe
            for(int i=0; i < 3; i++)
            {
                upPipe[i].CreateTexture("assets/image/top-pipe.png", renderer);
                downPipe[i].CreateTexture("assets/image/bot-pipe.png", renderer);
            }
            for(int i=0; i<3; i++) {
                upPipe[i].setPipe(i);
                downPipe[i].setPipe(i);
            }
        }else {
            std::cout << "Not created!" <<std::endl;
        }
    }else{
        std::cout << "window not created!" << std::endl;
    }

    if(TTF_Init() < 0)
    {
        std::cout << "Text faile to initialize! Error: " << TTF_GetError() << std::endl;
        Clear();
    }
    else
    {
        testFont = TTF_OpenFont("assets/font/flappy-bird-font/ka1.ttf", fontsize);
        test.WriteText("TEST", testFont, white, renderer);
    }

}

void GameLoop::Event() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
        if(isDie) {
            std::cout << "ISDIE" << std::endl;
            break;
        }
    case SDL_KEYDOWN:
    {
        if(event.key.keysym.sym == SDLK_SPACE)
        {
            if(!bird.JumpState() && !isDie) {
                bird.Jump();
            }
        }
        break;
    }
    case SDL_QUIT:
    {
        GameState = false;
        break;
    }
    default:
        {
            Update();
            CollisionDetection();
        }
    }
}

bool GameLoop::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    return SDL_HasIntersection(&object1, &object2);
}

void GameLoop::CollisionDetection()
{
    //Upper Pipe
    if(CheckCollision((&bird)->getDest(), (&upPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&upPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&upPipe[0])->getDest()) )
    {
        isDie = true;
    }

    //DownPipe
    if(CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) ||
       CheckCollision((&bird)->getDest(), (&downPipe[0])->getDest()) )
    {
        isDie = true;
    }

    //Floor
    if(CheckCollision((&bird)->getDest(), (&floor1)->getDest()) ||
       CheckCollision((&bird)->getDest(), (&floor2)->getDest()))
    {
        isDie = true;
    }

}
void GameLoop::Update() {
    //Bird
    bird.Gravity();
    //Pipe
    upPipe[0].upPipeUpdate(0);
    upPipe[1].upPipeUpdate(1);
    upPipe[2].upPipeUpdate(2);
    downPipe[0].downPipeUpdate(0);
    downPipe[1].downPipeUpdate(1);
    downPipe[2].downPipeUpdate(2);
    //Floor
    floor1.Update1();
    floor2.Update2();
}

void GameLoop::Render() {
    SDL_RenderClear(renderer);
    background.Render(renderer);

    upPipe[0].Render(renderer);
    upPipe[1].Render(renderer);
    upPipe[2].Render(renderer);
    downPipe[0].Render(renderer);
    downPipe[1].Render(renderer);
    downPipe[2].Render(renderer);
    floor1.Render(renderer);
    floor2.Render(renderer);
    bird.Render(renderer);
    test.Render(renderer);
    SDL_RenderPresent(renderer);

}

void GameLoop::Clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}