#pragma once
#include "0_GameFunc.h";

class MINI_monkey : public PhaseInterface
{
public:
	MINI_monkey();
	~MINI_monkey();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void print_eng(int c);
	virtual void Reset();

private:
	SDL_Texture* texture_; // the SDL_Texture 
	SDL_Rect source_rectangle_; // the rectangle for source image
	SDL_Rect destination_rectangle_; // for destination
	
	/* 글자 입출력 */
	// 글자 입력
	char answer[6] = "BRAIN";
	char input[6] = { 0 };
	string print_input = "_____";
	int cnt;

	// 정답
	SDL_Surface* g_print_answer; // "정답 입력 : "
	SDL_Texture* g_print_answer_texture;
	SDL_Rect g_print_answer_rect; // 잘라올 곳 크기

	SDL_Surface* g_input; // 입력할 값
	SDL_Texture* g_input_texture;
	SDL_Rect g_input_rect; // 잘라올 곳 크기

	Mix_Chunk* keyboard_sound;
	Mix_Chunk* door_sound;
	Mix_Chunk* click_sound;
	Mix_Music* mini_music;

	const Uint8* state = SDL_GetKeyboardState(NULL);
};