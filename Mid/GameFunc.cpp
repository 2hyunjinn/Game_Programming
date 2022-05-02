#include "GameFunc.h"
#include "intro.h"
#include "stage.h"
#include "ending.h"

Intro intro;
Stage1 stage1;
Ending ending;

void InitGame() {
	g_flag_running = true;
}

void ClearGame() {
    stage1.ClearGame();
    SDL_DestroyTexture(g_main_char_texture);
    SDL_DestroyTexture(g_white_texture);

    Mix_FreeMusic(g_bg_mus_open);
    Mix_FreeMusic(g_bg_mus_end);
}