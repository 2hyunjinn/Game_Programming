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
	
	/* ���� ����� */
	// ���� �Է�
	char answer[6] = "BRAIN";
	char input[6] = { 0 };
	string print_input = "_____";
	int cnt;

	// ����
	SDL_Surface* g_print_answer; // "���� �Է� : "
	SDL_Texture* g_print_answer_texture;
	SDL_Rect g_print_answer_rect; // �߶�� �� ũ��

	SDL_Surface* g_input; // �Է��� ��
	SDL_Texture* g_input_texture;
	SDL_Rect g_input_rect; // �߶�� �� ũ��

	Mix_Chunk* keyboard_sound;
	Mix_Chunk* door_sound;
	Mix_Chunk* click_sound;
	Mix_Music* mini_music;

	const Uint8* state = SDL_GetKeyboardState(NULL);
};