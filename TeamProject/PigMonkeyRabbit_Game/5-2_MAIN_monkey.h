#pragma once
#include "0_GameFunc.h";

class MAIN_monkey : public PhaseInterface
{
public:
	MAIN_monkey();
	~MAIN_monkey();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void drop_hit();
	virtual void Reset();

private:
	const Uint8* state = SDL_GetKeyboardState(NULL);
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination

	int character_go_left;
	int character_go_right;
	int button_state; // 버튼

	int term = 0;
	int monkey_difficulty = 1;
	int monkey_item_cnt = 0;
	int monkey_game_flag = 1;
	int show_level = 1;

	SDL_Surface* input;
	SDL_Texture* input_texture;
	SDL_Rect input_rect;

	SDL_Texture* monkey_helmet_texture;
	SDL_Texture* monkey_texture;
	SDL_Texture* helmet_texture;
	SDL_Texture* hodu_texture;
	SDL_Texture* hard_hodu_texture;
	SDL_Texture* game_bg_texture;
	SDL_Texture* bomb_texture;

	SDL_Texture* item_texture[5];
	//0 = helmet
	//1 = hard hodu;
	//2 = hodu;
	//3 = bomb;
	SDL_Rect item_rect[5]{
		{0,0,40,30},
		{0,0,40,40},
		{0,0,40,40},
		{0,0,30,40}
	};

	SDL_Rect monkey_rect;
	SDL_Rect monkey_pos;

	typedef struct items {
		bool state = false;
		int what = 0;
		SDL_Rect pos = { 0,0,0,0 };
	} items_;
	items_ items[50];

	int helmet_flag = 0;
	int monkey_score = 0;
	char tmp[15] = { 0 };

	SDL_Surface* monkey_score_title;
	SDL_Texture* monkey_score_title_texture;
	SDL_Rect monkey_score_rect;

	// game_ex
	SDL_Texture* game_ex_texture;
	SDL_Rect game_ex_pos;
	SDL_Rect game_ex_rect;

	// Game Over
	SDL_Surface* g_game_over; // "게임오버"
	SDL_Texture* g_game_over_texture;
	SDL_Rect g_game_over_rect; // 잘라올 곳 크기
	SDL_Rect g_game_over_pos; // 잘라올 곳 크기

	// Game Clear
	SDL_Surface* g_game_clear; // "게임 클리어"
	SDL_Texture* g_game_clear_texture;
	SDL_Rect g_game_clear_rect; // 잘라올 곳 크기
	SDL_Rect g_game_clear_pos; // 잘라올 곳 크기

	int semi_cnt = 0;
	int monkey_success;

	bool go_to_monkey_lab;
	bool gameover;
	bool gameclear;

	int time_;
	int page;

	// sound
	Mix_Chunk* bomb_sound;
	Mix_Chunk* hodu_sound;
	Mix_Chunk* hard_hodu_sound;
	Mix_Chunk* fail_sound;
	Mix_Chunk* success_sound;
	Mix_Music* game_music;
};