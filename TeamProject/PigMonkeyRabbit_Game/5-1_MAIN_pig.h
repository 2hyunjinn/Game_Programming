#pragma once
#include "0_GameFunc.h";

class MAIN_pig : public PhaseInterface
{
public:
	MAIN_pig();
	~MAIN_pig();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void Reset();

private:
	int character_go_left;
	int character_go_right;
	int character_go_up;
	int character_go_down;
	int button_state; // 버튼
	int character_x;
	int character_y;

	// bg
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	// main_char
	SDL_Texture* red_blood_texture; // 연구원 복사 받을 곳
	SDL_Rect red_blood_pos; // 연구원의 현재 위치
	SDL_Rect red_blood_rect; // 연구원 그림에서 잘라올 사각형

	// game_ex
	SDL_Texture* game_ex_texture;
	SDL_Rect game_ex_pos;
	SDL_Rect game_ex_rect;

	// Game Clear
	SDL_Surface* g_game_clear; // "게임 클리어"
	SDL_Texture* g_game_clear_texture;
	SDL_Rect g_game_clear_rect; // 잘라올 곳 크기
	SDL_Rect g_game_clear_pos; // 잘라올 곳 크기

	// Game Over
	SDL_Surface* g_game_over; // "게임오버"
	SDL_Texture* g_game_over_texture;
	SDL_Rect g_game_over_rect; // 잘라올 곳 크기
	SDL_Rect g_game_over_pos; // 잘라올 곳 크기

	const Uint8* state = SDL_GetKeyboardState(NULL);
	bool b_char = true;
	int cnt;

	bool go_to_pig_lab;
	bool gameover;
	bool gameclear;

	int time;
	int page;
	int semi_cnt = 0;
	int _cnt = 0;

	Mix_Chunk* bump_sound;
	Mix_Chunk* fail_sound;
	Mix_Chunk* success_sound;
	Mix_Music* game_music;
};
