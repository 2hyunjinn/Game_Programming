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
const int PHASE_STAGE1 = 1;
const int PHASE_ENDING = 2;

extern int play_music;
extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;
extern Mix_Music* g_bg_mus_open; // 오프닝 음악
extern Mix_Music* g_bg_mus_end; // 엔딩 음악
 /* 주인공 이미지 */
extern SDL_Texture* g_main_char_texture; // 비행기 복사 받을 곳
extern SDL_Rect g_main_char_pos; // 비행기의 현재 위치
extern SDL_Rect g_main_char_rect; // 비행기 잘라올 곳의 사각형


/* 영희 이미지 */
extern SDL_Texture* g_white_texture; // 영희 복사 받을 곳
extern SDL_Rect g_white_pos; // 영희의 현재 위치
extern SDL_Rect g_white_rect[8]; // 영희 잘라올 곳의 사각형
extern int white_idx;

class PhaseInterface
{
public:
	PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};
