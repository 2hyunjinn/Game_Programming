#pragma once
#include "0_GameFunc.h";

class MAIN_rabbit : public PhaseInterface
{
public:
	MAIN_rabbit();
	~MAIN_rabbit();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void make_arrow();
	virtual void cat_ans(int input);
	virtual void Reset();

private:
	int character_go_left;
	int character_go_right;
	int character_go_up;
	int character_go_down;
	int button_state; // ��ư
	int character_x;
	int character_y;

	const Uint8* state = SDL_GetKeyboardState(NULL);
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	int show_explain;

	char level[10] = { 0 };
	int flag = 1;
	int difficulty = 1;
	int arrow_direction = 0;
	int arrow_x, arrow_y;
	bool is_game = 0;
	int cnt = 0;

	SDL_Surface* answer; // "���� �Է� : "
	SDL_Texture* answer_texture;
	SDL_Rect answer_rect;
	SDL_Rect answer_pos;

	SDL_Surface* wait;
	SDL_Texture* wait_texture;
	SDL_Rect wait_rect;
	SDL_Rect wait_pos;

	SDL_Surface* input; // �Է��� ��
	SDL_Texture* input_texture;
	SDL_Rect input_rect; // �߶�� �� ũ��
	SDL_Rect input_pos; // �߶�� �� ũ��

	// Game Over
	SDL_Surface* g_game_over; // "���ӿ���"
	SDL_Texture* g_game_over_texture;
	SDL_Rect g_game_over_rect; // �߶�� �� ũ��
	SDL_Rect g_game_over_pos; // �߶�� �� ũ��

	// Game Clear
	SDL_Surface* g_game_clear; // "���� Ŭ����"
	SDL_Texture* g_game_clear_texture;
	SDL_Rect g_game_clear_rect; // �߶�� �� ũ��
	SDL_Rect g_game_clear_pos; // �߶�� �� ũ��

	// Show_Level
	SDL_Surface* g_level; // "Level 1"
	SDL_Texture* g_level_texture;
	SDL_Rect g_level_rect; // �߶�� �� ũ��
	SDL_Rect g_level_pos; // �߶�� �� ũ��

	// Input
	SDL_Surface* g_input; // "�Է�"
	SDL_Texture* g_input_texture;
	SDL_Rect g_input_rect; // �߶�� �� ũ��
	SDL_Rect g_input_pos; // �߶�� �� ũ��

	// Input_num
	SDL_Surface* g_input_num; // �Է¼���
	SDL_Texture* g_input_num_texture;
	SDL_Rect g_input_num_rect; // �߶�� �� ũ��
	SDL_Rect g_input_num_pos; // �߶�� �� ũ��

	// game_ex
	SDL_Texture* game_ex_texture;
	SDL_Rect game_ex_pos;
	SDL_Rect game_ex_rect;

	SDL_Texture* arrow_texture;
	SDL_Rect arrow_rect[4] = {
			{ 22, 36, 23, 32},
			{ 53, 41, 23, 32},
			{ 90, 35, 32, 21},
			{ 141, 36, 34, 21}
	};
	SDL_Rect arrow_dest_rect[10] = {
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
		{0, 0, 180, 180},
	};

	int direction[10] = { 0 };

	char input_[100] = { ' ' };
	char ans[100] = { ' ' };

	int input_cnt = 0;
	int is_correct = 0;
	int show_level = 1;

	bool go_to_rabbit_lab;
	bool gameover;
	bool gameclear;
	int time_;
	bool level_cnt;
	bool level_show;
	int page;
	bool show_arrow_ = false;
	bool input_answer_arrow = false;
	int arr_input[10] = { 0 };
	int idx_input = 0;

	int semi_cnt = 0;

	// sound
	Mix_Chunk* arrow_sound;
	Mix_Chunk* keyboard_sound;
	Mix_Chunk* fail_sound;
	Mix_Chunk* success_sound;
	Mix_Music* game_music;
};