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
extern Mix_Music* g_bg_mus_open; // ������ ����
extern Mix_Music* g_bg_mus_end; // ���� ����
 /* ���ΰ� �̹��� */
extern SDL_Texture* g_main_char_texture; // ����� ���� ���� ��
extern SDL_Rect g_main_char_pos; // ������� ���� ��ġ
extern SDL_Rect g_main_char_rect; // ����� �߶�� ���� �簢��


/* ���� �̹��� */
extern SDL_Texture* g_white_texture; // ���� ���� ���� ��
extern SDL_Rect g_white_pos; // ������ ���� ��ġ
extern SDL_Rect g_white_rect[8]; // ���� �߶�� ���� �簢��
extern int white_idx;

class PhaseInterface
{
public:
	PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};
