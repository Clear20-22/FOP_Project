#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <string>
#include<fstream>
#include "Macros.h"

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
TTF_Font* font;
Mix_Chunk* hitSound;
Mix_Chunk* gamesesh;
Mix_Music* backgroundMusic;
Mix_Music* levelground;
SDL_Texture* backgc;
SDL_Texture* ballTexture;
SDL_Texture* paddleTexture;
SDL_Texture* brickTexture;
SDL_Texture* specialBrickTexture;

bool running;
int frameCount, timerFPS, lastFrame, fps;
SDL_Color color;
SDL_Rect paddle, ball, lives, brick;
float velY, velX;
int liveCount;
int bricks[ROW * COL];
int score;
int highScore = 0;
const int special = 1;
const int normal = 2;
bool paused;


void initializePaddle_ball();
void initializeBricks();
void resetBricks();
void setBrickPosition(int i);
void writeText(string text, int x, int y);
void update();
void input();
void render();
void cleanup();
int mainmenu(SDL_Renderer* renderer, TTF_Font* font);
int playmenu(SDL_Renderer* renderer, TTF_Font* font);
int levelmenu(SDL_Renderer* renderer, TTF_Font* font);
void showHighScore(SDL_Renderer* renderer, TTF_Font* font);
void showHelp(SDL_Renderer* renderer, TTF_Font* font);
void pauseMenu(SDL_Renderer* renderer, TTF_Font* font);

void initializePaddle_ball() {
    paddle.h = 12;
    paddle.w = WIDTH / 6;
    paddle.y = HEIGHT - paddle.h - 32;
    paddle.x = (WIDTH / 2) - (paddle.w / 2);

    ball.w = SIZE;
    ball.h = SIZE;
    ball.x = paddle.x + (paddle.w / 2) - (ball.w / 2);
    ball.y = paddle.y - ball.h - 5;

    velX = 0;
    velY = -BALL_SPEED;
}

void initializeBricks() {
    brick.w = (WIDTH - (SPACING * COL)) / COL;
    brick.h = 22;
    int check = levelmenu(renderer,font);
    if (check == 1) {
        for (int i = 0; i < COL * ROW; i++) {
            setBrickPosition(i);
            if ((i >= 0 && i <= 14))
                bricks[i] = special;
            else
                bricks[i] = normal;
        }
    }
    else if (check == 2)
    {
        for (int i = 0; i < COL * ROW; i++) {
            setBrickPosition(i);
            if ((i >= 0 && i <= 14) or i % 6 == 0)
                bricks[i] = special;
            else
                bricks[i] = normal;
        }
    }
    else if (check == 3)
    {
        for (int i = 0; i < COL * ROW; i++) {
            setBrickPosition(i);
            if ((i >= 0 && i <= 14) or i % 5 == 0)
                bricks[i] = special;
            else
                bricks[i] = normal;
        }
    }
    else {
        if (Mix_PlayingMusic() != 0) {
            Mix_HaltMusic(); // Stop the music
        }
        running = false;
        mainmenu(renderer, font);
        return;
    }

}

void resetBricks() {
    initializeBricks();
    liveCount = 3;
    score = 0;
    ball.y = paddle.y - (paddle.h * 4);
    velY = BALL_SPEED / 2;
    velX = 0;
    ball.x = WIDTH / 2 - (SIZE / 2);
}

void setBrickPosition(int i) {
    if (Mix_PlayingMusic() != 0) {
        Mix_HaltMusic(); // Stop the music
    }
    brick.x = (((i % COL) + 1) * SPACING) + ((i % COL) * brick.w) - (SPACING / 2);
    brick.y = brick.h * 3 + (((i / COL) + 1) * SPACING) + ((i / COL) * brick.h) - (SPACING / 2);
}

void writeText(string text, int x, int y) {

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    lives.w = surface->w;
    lives.h = surface->h;
    lives.x = x;
    lives.y = y;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &lives);
    SDL_DestroyTexture(texture);
}

void update() {
    if (liveCount <= 0) resetBricks();

    if (SDL_HasIntersection(&ball, &paddle)) {
        double rel = (paddle.x + (paddle.w / 2)) - (ball.x + (SIZE / 2));
        double norm = rel / (paddle.w / 2);
        double bounce = norm * (M_PI / 4); 

        velY = -BALL_SPEED * cos(bounce);
        velX = BALL_SPEED * -sin(bounce);
    }


    if (ball.y <= 0) velY = -velY;
    if (ball.y + SIZE >= HEIGHT) {
        liveCount--;
        initializePaddle_ball();
    }
    if (ball.x <= 0 || ball.x + SIZE >= WIDTH) velX = -velX;

    ball.x += velX;
    ball.y += velY;


    if (paddle.x < 0) paddle.x = 0;
    if (paddle.x + paddle.w > WIDTH) paddle.x = WIDTH - paddle.w;

    bool allNormalBricksGone = true;
    for (int i = 0; i < COL * ROW; i++) {
        setBrickPosition(i);
        if (bricks[i] != 0 && SDL_HasIntersection(&ball, &brick)) {
            Mix_PlayChannel(-1, hitSound, 0);
            if (bricks[i] == normal) {
                bricks[i] = 0;
                score += 5;
            }
            if (ball.x + SIZE > brick.x && ball.x < brick.x + brick.w) {
                velY = -velY;
                ball.y = (ball.y < brick.y) ? brick.y - SIZE : brick.y + brick.h;
            }
            else {
                velX = -velX;
                ball.x = (ball.x < brick.x) ? brick.x - SIZE : brick.x + brick.w;
            }
        }
        if (bricks[i] == normal) {
            allNormalBricksGone = false;
        }
    }

    if (allNormalBricksGone) {
        liveCount = 0;
        // resetBricks();
    }
}


void input() {
    SDL_Event e;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) pauseMenu(renderer,font);
    }
    if (keystates[SDL_SCANCODE_ESCAPE]) pauseMenu(renderer,font);
    if (keystates[SDL_SCANCODE_LEFT] or keystates[SDL_SCANCODE_A]) paddle.x -= SPEED;
    if (keystates[SDL_SCANCODE_RIGHT] or keystates[SDL_SCANCODE_D]) paddle.x += SPEED;
    if(keystates[SDL_SCANCODE_P]) pauseMenu(renderer, font);
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgc, NULL, NULL);

    SDL_RenderCopy(renderer, paddleTexture, NULL, &paddle);
    SDL_RenderCopy(renderer, ballTexture, NULL, &ball);

    writeText("Lives: " + to_string(liveCount), FONT_SIZE * 1.2, FONT_SIZE * 0.5);
    writeText("Score: " + to_string(score), WIDTH - FONT_SIZE * 5.5, FONT_SIZE * 0.5);

    for (int i = 0; i < COL * ROW; i++) {
        if (bricks[i] == special) {
            setBrickPosition(i);
            SDL_RenderCopy(renderer, specialBrickTexture, NULL, &brick);
        }
        else if (bricks[i] == normal) {
            setBrickPosition(i);
            SDL_RenderCopy(renderer, brickTexture, NULL, &brick);
        }
    }
    SDL_RenderPresent(renderer);

}



void readHighScore() {
    ifstream file("highscore.txt");
    if (file.is_open()) {
        file >> highScore;
        file.close();
    }
}

void writeHighScore() {
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << highScore;
        file.close();
    }
}


void gameOver(SDL_Renderer* renderer, TTF_Font* font, int score) {

    if (score > highScore) {
        highScore = score;
        writeHighScore();
    }
    Mix_PlayChannel(-1, gamesesh, 0);

    SDL_Texture* gameOverBackground = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/bgBrick.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, gameOverBackground, NULL, NULL);
    writeText("Game Over", WIDTH / 2 - 50, HEIGHT / 2 - 100);
    writeText("Score: " + to_string(score), WIDTH / 2 - 50, HEIGHT / 2 - 50);
    writeText("Press any key or Click to go back to main menu", WIDTH / 2 - 250, HEIGHT / 2);

    SDL_RenderPresent(renderer);
    int x = 0, y = 0;
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            switch(event.type){
            /*case SDL_KEYDOWN:
                SDL_DestroyTexture(gameOverBackground);
                return;*/
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                if (x >= WIDTH / 2 - 200 and x <= WIDTH / 2 + 200)
                {
                    if (y = HEIGHT / 2 - 50 and y <= HEIGHT / 2 + 50)
                        SDL_DestroyTexture(gameOverBackground);
                    return;
                }
                
            }
        }
    }
}




int wmain() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "Failed at SDL_Init()" << endl;
        return -1;
    }

    if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer) < 0) {
        cout << "Failed at SDL_CreateWindowAndRenderer()" << endl;
        return -1;
    }

    SDL_SetWindowTitle(window, "Brick Breaker");

    if (TTF_Init() == -1) {
        cout << "Failed to initialize TTF" << endl;
        return -1;
    }

    font = TTF_OpenFont("G:/Boot camp/block/peepo.ttf", FONT_SIZE);
    if (!font) {
        cout << "Failed to load font! TTF Error: " << TTF_GetError() << endl;
        return -1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "Failed to initialize SDL_mixer! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    hitSound = Mix_LoadWAV("G:/Boot camp/block/ball_image_sound/hit.wav");
    gamesesh = Mix_LoadWAV("G:/Boot camp/block/ball_image_sound/gameover.wav");
    if (!hitSound || !gamesesh) {
        cout << "Failed to load sound effects! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }
     backgroundMusic = Mix_LoadMUS("G:/Boot camp/block/ball_image_sound/bgmusic.wav");
     levelground = Mix_LoadMUS("ball_image_sound/background.mp3");
    if (!backgroundMusic || !levelground) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }


    backgc = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/bgBrick.png");
    if (!backgc) {
        cout << "Failed to load background image! IMG Error: " << IMG_GetError() << endl;
        return -1;
    }

    ballTexture = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/ball.png");
    if (!ballTexture) {
        cout << "Failed to load ball texture! IMG Error: " << IMG_GetError() << endl;
        return -1;
    }

    paddleTexture = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/paddle.png");
    if (!paddleTexture) {
        cout << "Failed to load paddle texture! IMG Error: " << IMG_GetError() << endl;
        return -1;
    }

    brickTexture = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/real_brick.png");

    if (!brickTexture) {
        cout << "Failed to load brick texture! IMG Error: " << IMG_GetError() << endl;
        return -1;
    }

    specialBrickTexture = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/doom-org.png");
    if (!specialBrickTexture) {
        cout << "Failed to load special brick texture! IMG Error: " << IMG_GetError() << endl;
        return -1;
    }

    // Show main menu and wait for user to start the game or exit
    bool inMainMenu = true;
    while (inMainMenu) {
        int menuOption = mainmenu(renderer, font);
        switch (menuOption) {
        case 1:
            if (Mix_PlayingMusic() != 0) {
                Mix_HaltMusic(); // Stop the music
            }
            running = true;
            paused = false;
            resetBricks();
            initializePaddle_ball();
            while (running) {

                lastFrame = SDL_GetTicks();
                if (!paused) {
                    update();
                }
                input();
                if (!paused) {
                    render();
                }
                else {
                    pauseMenu(renderer,font);
                }
                if (lastFrame >= (lastFrame + 1000)) {
                    lastFrame = 0;
                    fps = frameCount;
                    frameCount = 0;
                }
                frameCount++;
                timerFPS = SDL_GetTicks() - lastFrame;
                if (timerFPS < (1000 / 60)) {
                    SDL_Delay((1000 / 60) - timerFPS);
                }
                if (liveCount <= 0) {
                    gameOver(renderer, font, score);
                    running = false;
                }
            }
            break;
        case 2:
            readHighScore();
            showHighScore(renderer, font);
            break;
        case 3:
            showHelp(renderer, font);
            break;
        case 4:
            inMainMenu = false;
            break;
        default:
            break;
        }
    }

    cleanup();
    return 0;
}

void cleanup() {
    Mix_FreeChunk(hitSound);
    Mix_FreeChunk(gamesesh);
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeMusic(levelground);
    SDL_DestroyTexture(backgc);
    SDL_DestroyTexture(ballTexture);
    SDL_DestroyTexture(paddleTexture);
    SDL_DestroyTexture(brickTexture);
    SDL_DestroyTexture(specialBrickTexture);
    TTF_CloseFont(font);
    Mix_CloseAudio();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

int mainmenu(SDL_Renderer* renderer, TTF_Font* font) {

    int x = 0, y = 0;
    SDL_Event event;
    SDL_Texture* mainMenuBackground = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/bgBrick.png");
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(backgroundMusic, -1); // Loop the music
    }


    while (true) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, mainMenuBackground, NULL, NULL);
        writeText("Brick Breaker", WIDTH / 2 - 65, HEIGHT / 2 - 200);
        writeText("1. Play Game", WIDTH / 2 - 50, HEIGHT / 2 - 100);
       // writeText("2. Play", WIDTH / 2 - 50, HEIGHT / 2 - 50);
      //  writeText("2. Levels", WIDTH / 2 - 50, HEIGHT / 2 - 50);
        writeText("2. High Scores", WIDTH / 2 - 50, HEIGHT / 2 - 50);
        writeText("3. Help", WIDTH / 2 - 50, HEIGHT / 2 );
        writeText("4. Exit", WIDTH / 2 - 50, HEIGHT / 2 + 50);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return 4;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                if (x >= WIDTH / 2 - 50 && x <= WIDTH / 2 + 50) {
                    if (y >= HEIGHT / 2 - 100 && y <= HEIGHT / 2 - 50) return 1;
                   // if (y >= HEIGHT / 2 - 50 && y <= HEIGHT / 2) return 2;
                    // if (y >= HEIGHT / 2 - 50 && y <= HEIGHT / 2 ) return 2;
                    if (y >= HEIGHT / 2 -50 && y <= HEIGHT / 2) return 2;
                    if (y >= HEIGHT / 2 && y <= HEIGHT / 2 + 50) return 3;
                    if (y >= HEIGHT / 2 + 50 && y <= HEIGHT / 2 + 100) return 4;
                }
                break;
           /* case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return 5;
                case SDLK_1:
                    return 1;
                case SDLK_2:
                    return 2;
                case SDLK_3:
                    return 3;
                case SDLK_4:
                    return 4;
                default:
                    break;
                }
                break;
                */
            default:
                break;
                
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(mainMenuBackground);
    return 0;
}

void pauseMenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Texture* pauseMenuBackground = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/bgBrick.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, pauseMenuBackground, NULL, NULL);
    writeText("Paused", WIDTH / 2 -40, HEIGHT / 2 - 100);
    writeText("1. Resume", WIDTH / 2 - 50, HEIGHT / 2 - 50);
    writeText("2. Main Menu", WIDTH / 2 - 50, HEIGHT / 2);
    SDL_RenderPresent(renderer);
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(backgroundMusic, -1); // Loop the music
    }

    int x = 0, y = 0;

    SDL_Event event;
    bool wait = true;
    while (wait) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                    case SDLK_1:
                        paused = false;
                        wait = false;
                        break;
                    case SDLK_2: 
                        running = false;
                        wait = false;
                        paused = false;
                }
                    break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                if (x >= WIDTH / 2 - 50 && x <= WIDTH / 2 + 50) {
                    if (y >= HEIGHT / 2 - 50   && y <= HEIGHT / 2 - 10) paused = false, wait = false;
                    if (y >= HEIGHT / 2 + 10 && y <= HEIGHT / 2 + 90) running = false, wait = false, paused = false;
                }
                    break;
            default:
                break;

            }
        }
    }
}

int levelmenu(SDL_Renderer* renderer, TTF_Font* font) {
    int x = 0, y = 0;
    SDL_Event event;
    SDL_Texture* levelMenuBackground = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/bgBrick.png");
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(levelground, -1); // Loop the music
    }

    while (true) {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, levelMenuBackground, NULL, NULL);
        writeText("Level Menu", WIDTH / 2 - 60, HEIGHT / 2 - 100);
        writeText("1. Easy", WIDTH / 2 - 50, HEIGHT / 2 - 50);
        writeText("2. Medium", WIDTH / 2 - 50, HEIGHT / 2);
        writeText("3. Hard", WIDTH / 2 - 50, HEIGHT / 2 + 50);
        writeText("4. Back", WIDTH / 2 - 50, HEIGHT / 2 + 100);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                return 4;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                if (x >= WIDTH / 2 - 50 && x <= WIDTH / 2 + 50) {
                    if (y >= HEIGHT / 2 - 50 && y <= HEIGHT / 2) return 1;
                    if (y >= HEIGHT / 2 && y <= HEIGHT / 2 + 50) return 2;
                    if (y >= HEIGHT / 2 + 50 && y <= HEIGHT / 2 + 100) return 3;
                    if (y >= HEIGHT / 2 + 100 && y <= HEIGHT / 2 + 150) return 4;
                }
                break;
         /*   case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return 4;
                case SDLK_1:
                    return 1;
                case SDLK_2:
                    return 2;
                case SDLK_3:
                    return 3;
                case SDLK_4:
                    return 4;
                default:
                    break;
                }
                break;
                */
            default:
                break;
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(levelMenuBackground);
    return 0;
}

void showHighScore(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Texture* highScoreBackground = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/bgBrick.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, highScoreBackground, NULL, NULL);
    writeText("High Score :", WIDTH / 2 - 50, HEIGHT / 2 - 100);
    writeText( to_string(highScore), WIDTH / 2, HEIGHT / 2 - 50);
    writeText("Reset Score", WIDTH / 2 - 50, HEIGHT / 2 );
    writeText("Press any key or Click to go back", WIDTH / 2 - 170, HEIGHT / 2 + 100);
    SDL_RenderPresent(renderer);
    int x = 0, y = 0;
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {

            switch (event.type) {
             case SDL_MOUSEBUTTONDOWN:
                 SDL_GetMouseState(&x, &y);
                 if (x >= WIDTH / 2 - 50 && x <= WIDTH / 2 + 50) {
                     if (y >= HEIGHT / 2 - 50 && y <= HEIGHT / 2 + 50)
                     {
                         highScore = 0;
                         writeHighScore();
                         showHighScore(renderer, font);
                     }
                 }
                 if (x >= WIDTH / 2 - 100 and x <= WIDTH / 2 + 100)
                 {
                     if (y >= HEIGHT / 2 + 100 and y <= HEIGHT / 2 + 200)
                     {
                         SDL_DestroyTexture(highScoreBackground);
                         return;
                     }
                 }
                 break;
           /* case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_1:
                    highScore = 0;
                    writeHighScore();
                    showHighScore(renderer, font);
                    break;
                    
                default:
                    SDL_DestroyTexture(highScoreBackground);
                    return;
                }
                */
            }
        }
    }
}


void showHelp(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Texture* helpBackground = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/bgBrick.png");
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, helpBackground, NULL, NULL);
    writeText("Help", WIDTH / 2 - 50, HEIGHT / 2 - 200);
    writeText("Use arrow keys to move paddle", WIDTH / 2 - 190, HEIGHT / 2 - 150);
    writeText("Use 'A' and 'D' to move paddle", WIDTH / 2 - 180, HEIGHT / 2 - 100);
    writeText("Break all the bricks to win", WIDTH / 2 - 160, HEIGHT / 2 - 50);
    writeText("Press key 'P' to pause the game", WIDTH / 2 - 190, HEIGHT / 2);
    writeText("Press '1' or Click to reset the High Score",WIDTH /2 - 230 , HEIGHT / 2 + 50);
    writeText("Press any key or Click to go back", WIDTH / 2 - 180, HEIGHT / 2 + 150);
    SDL_RenderPresent(renderer);
    int x = 0, y = 0;
    SDL_Event event;
    while (true) {
        while (SDL_PollEvent(&event)) {
            switch(event.type){
            /*case SDL_KEYDOWN:
                SDL_DestroyTexture(helpBackground);
                return;*/
            case SDL_MOUSEBUTTONDOWN:
              SDL_GetMouseState(&x, &y);
                if (x >= WIDTH / 2 - 100 and x <= WIDTH / 2 + 100)
                {
                    if (y >= HEIGHT / 2 + 150 and y <= HEIGHT / 2 + 200)
                    {
                        SDL_DestroyTexture(helpBackground);
                        return;
                    }
                }
            }
        }
    }
}

