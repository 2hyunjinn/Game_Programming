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
	int button_state; // ��ư
	int character_x;
	int character_y;

	// bg
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	// main_char
	SDL_Texture* red_blood_texture; // ������ ���� ���� ��
	SDL_Rect red_blood_pos; // �������� ���� ��ġ
	SDL_Rect red_blood_rect; // ������ �׸����� �߶�� �簢��

	// game_ex
	SDL_Texture* game_ex_texture;
	SDL_Rect game_ex_pos;
	SDL_Rect game_ex_rect;

	// Game Clear
	SDL_Surface* g_game_clear; // "���� Ŭ����"
	SDL_Texture* g_game_clear_texture;
	SDL_Rect g_game_clear_rect; // �߶�� �� ũ��
	SDL_Rect g_game_clear_pos; // �߶�� �� ũ��

	// Game Over
	SDL_Surface* g_game_over; // "���ӿ���"
	SDL_Texture* g_game_over_texture;
	SDL_Rect g_game_over_rect; // �߶�� �� ũ��
	SDL_Rect g_game_over_pos; // �߶�� �� ũ��

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
