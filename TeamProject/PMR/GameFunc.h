#pragma once

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

void InitGame();
void ClearGame();

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_LAB = 1;
const int PHASE_PIG = 2;
const int PHASE_MONKEY = 3;
const int PHASE_RABBIT = 4;
const int PHASE_ENDING = 5;
const int PHASE_MINI_PIG = 6;
const int PHASE_MINI_MONKEY = 7;
const int PHASE_MINI_RABBIT = 8;

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern int x; // mosue x좌표
extern int y; // mouse y좌표

// main_char
extern SDL_Texture* g_researcher_texture; // 연구원 복사 받을 곳
extern SDL_Rect g_researcher_pos; // 연구원의 현재 위치
extern SDL_Rect g_researcher_rect; // 연구원 그림에서 잘라올 사각형

// font
extern TTF_Font* font; // 폰트
extern SDL_Color yellow;

class PhaseInterface
{
public:
	PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};