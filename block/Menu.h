


int mainmenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color yellow = { 255, 255, 0, 255 };
    const char* menuItems[] = { "Play", "High Score", "Help", "Exit" };
    int selected = 0;

    // Load background image
    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "G:/Boot camp/block/ball_image_sound/space-1.png");
    if (!backgroundTexture) {
        cout << "Failed to load menu background image! SDL_image Error: " << IMG_GetError() << endl;
        return 0;
    }

    // Load and play background music
    Mix_Music* bgMusic = Mix_LoadMUS("G:/Boot camp/block/ball_image_sound/background.mp3");
    if (!bgMusic) {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        return 0;
    }
    Mix_PlayMusic(bgMusic, -1);

    SDL_Event event;
    while (true) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the background image
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        SDL_Rect menuRects[4];
        for (int i = 0; i < 4; i++) {
            SDL_Color color = (i == selected) ? yellow : white;
            SDL_Surface* surface = TTF_RenderText_Solid(font, menuItems[i], color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            menuRects[i].x = WIDTH / 2 - surface->w / 2;
            menuRects[i].y = HEIGHT / 2 + i * 50;
            menuRects[i].w = surface->w;
            menuRects[i].h = surface->h;
            SDL_RenderCopy(renderer, texture, NULL, &menuRects[i]);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                Mix_HaltMusic();
                Mix_FreeMusic(bgMusic);
                SDL_DestroyTexture(backgroundTexture);
                return 0;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    selected = (selected > 0) ? selected - 1 : 3;
                    break;
                case SDLK_DOWN:
                    selected = (selected < 3) ? selected + 1 : 0;
                    break;
                case SDLK_RETURN:
                    Mix_HaltMusic();
                    Mix_FreeMusic(bgMusic);
                    SDL_DestroyTexture(backgroundTexture);
                    if (selected == 1) {
                        showHighScore(renderer, font);
                    }
                    else if (selected == 2) {
                        showHelp(renderer, font);
                    }
                    else {
                        return selected;
                    }
                    Mix_PlayMusic(bgMusic, -1); // Resume music after returning from high score or help
                    break;
                case SDLK_ESCAPE:
                    Mix_HaltMusic();
                    Mix_FreeMusic(bgMusic);
                    SDL_DestroyTexture(backgroundTexture);
                    return 0;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                for (int i = 0; i < 4; i++) {
                    if (mouseX >= menuRects[i].x && mouseX <= menuRects[i].x + menuRects[i].w &&
                        mouseY >= menuRects[i].y && mouseY <= menuRects[i].y + menuRects[i].h) {
                        selected = i;
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    Mix_HaltMusic();
                    Mix_FreeMusic(bgMusic);
                    SDL_DestroyTexture(backgroundTexture);
                    if (selected == 1) {
                        showHighScore(renderer, font);
                    }
                    else if (selected == 2) {
                        showHelp(renderer, font);
                    }
                    else {
                        return selected;
                    }
                    Mix_PlayMusic(bgMusic, -1); // Resume music after returning from high score or help
                }
            }
        }
    }
}

void showHighScore(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color yellow = { 255, 255, 0, 255 };
    const char* menuItems[] = { "High Score: 1000", "Back" };
    int selected = 0;

    SDL_Event event;
    while (true) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_Rect menuRects[2];
        for (int i = 0; i < 2; i++) {
            SDL_Color color = (i == selected) ? yellow : white;
            SDL_Surface* surface = TTF_RenderText_Solid(font, menuItems[i], color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            menuRects[i].x = WIDTH / 2 - surface->w / 2;
            menuRects[i].y = HEIGHT / 2 + i * 50;
            menuRects[i].w = surface->w;
            menuRects[i].h = surface->h;
            SDL_RenderCopy(renderer, texture, NULL, &menuRects[i]);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    selected = (selected > 0) ? selected - 1 : 1;
                    break;
                case SDLK_DOWN:
                    selected = (selected < 1) ? selected + 1 : 0;
                    break;
                case SDLK_RETURN:
                    if (selected == 1) {
                        return;
                    }
                    break;
                case SDLK_ESCAPE:
                    return;
                }
            }
            if (event.type == SDL_MOUSEMOTION) {
                int mouseX = event.motion.x;
                int mouseY = event.motion.y;
                for (int i = 0; i < 2; i++) {
                    if (mouseX >= menuRects[i].x && mouseX <= menuRects[i].x + menuRects[i].w &&
                        mouseY >= menuRects[i].y && mouseY <= menuRects[i].y + menuRects[i].h) {
                        selected = i;
                    }
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    if (selected == 1) {
                        return;
                    }
                }
            }
        }
    }
}

void showHelp(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Event event;
    bool show = true;

    while (show) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        const char* helpText = "Use arrow keys to move paddle.\nBreak all the bricks to win.\nPress ESC to go back.";
        SDL_Surface* surface = TTF_RenderText_Solid(font, helpText, white);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect rect;
        rect.x = WIDTH / 2 - surface->w / 2;
        rect.y = HEIGHT / 2 - surface->h / 2;
        rect.w = surface->w;
        rect.h = surface->h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                show = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_RETURN) {
                    show = false;
                }
            }
        }
    }
}




int playmenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color yellow = { 255, 255, 0, 255 };
    const char* menuItems[] = { "New Game", "Back" };
    int selected = 0;

    SDL_Event event;
    while (true) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 2; i++) {
            SDL_Color color = (i == selected) ? yellow : white;
            SDL_Surface* surface = TTF_RenderText_Solid(font, menuItems[i], color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect rect;
            rect.x = WIDTH / 2 - surface->w / 2;
            rect.y = HEIGHT / 2 + i * 50;
            rect.w = surface->w;
            rect.h = surface->h;
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    selected = (selected > 0) ? selected - 1 : 1;
                    break;
                case SDLK_DOWN:
                    selected = (selected < 1) ? selected + 1 : 0;
                    break;
                case SDLK_RETURN:
                    return selected;
                case SDLK_ESCAPE:
                    return 0;
                }
            }
        }
    }
}

int levelmenu(SDL_Renderer* renderer, TTF_Font* font) {
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color yellow = { 255, 255, 0, 255 };
    const char* menuItems[] = { "Level 1", "Level 2", "Back" };
    int selected = 0;

    SDL_Event event;
    while (true) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < 3; i++) {
            SDL_Color color = (i == selected) ? yellow : white;
            SDL_Surface* surface = TTF_RenderText_Solid(font, menuItems[i], color);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect rect;
            rect.x = WIDTH / 2 - surface->w / 2;
            rect.y = HEIGHT / 2 + i * 50;
            rect.w = surface->w;
            rect.h = surface->h;
            SDL_RenderCopy(renderer, texture, NULL, &rect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return 0;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_UP:
                    selected = (selected > 0) ? selected - 1 : 2;
                    break;
                case SDLK_DOWN:
                    selected = (selected < 2) ? selected + 1 : 0;
                    break;
                case SDLK_RETURN:
                    return selected;
                case SDLK_ESCAPE:
                    return 0;
                }
            }
        }
    }
}
