#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstring>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include <windows.h>
#include <queue>
#include <string.h>
#include <sstream>
#include <atlstr.h>
#include <iomanip>

using namespace std;

void InitGame();
void ClearGame();

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_LAB = 1;

const int PHASE_MINI_PIG = 2;
const int PHASE_LAB_PIG = 3;
const int PHASE_MAIN_PIG = 4;

const int PHASE_MINI_MONKEY = 5;
const int PHASE_LAB_MONKEY = 6;
const int PHASE_MAIN_MONKEY = 7;

const int PHASE_MINI_RABBIT = 8;
const int PHASE_LAB_RABBIT = 9;
const int PHASE_MAIN_RABBIT = 10;

const int PHASE_ENDING = 11;

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern int mouse_x; // mosue x좌표
extern int mouse_y; // mouse y좌표
extern bool pig, monkey, rabbit, have_research_journal;

// font
extern TTF_Font* font; // 폰트
extern TTF_Font* font_main_game;
extern SDL_Color yellow;

// clear_pig
extern SDL_Texture* g_clear_pig_texture; // 복사 받을 곳
extern SDL_Rect g_clear_pig_pos; // 현재 위치
extern SDL_Rect g_clear_pig_rect; // 그림에서 잘라올 사각형

// clear_monkey
extern SDL_Texture* g_clear_monkey_texture; // 복사 받을 곳
extern SDL_Rect g_clear_monkey_pos; // 현재 위치
extern SDL_Rect g_clear_monkey_rect; // 그림에서 잘라올 사각형

// clear_rabbit
extern SDL_Texture* g_clear_rabbit_texture; // 복사 받을 곳
extern SDL_Rect g_clear_rabbit_pos; // 현재 위치
extern SDL_Rect g_clear_rabbit_rect; // 그림에서 잘라올 사각형

extern SDL_Surface* char_surface;

// music
extern int music_flag;

// game_clear_all
extern bool all_game_clear;

// game_stop
extern bool game_stop;

class PhaseInterface
{
public:
	PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};