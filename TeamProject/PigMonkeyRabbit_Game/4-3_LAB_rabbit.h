#pragma once
#include "0_GameFunc.h";

class Lab_rabbit : public PhaseInterface
{
public:
	Lab_rabbit();
	~Lab_rabbit();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();
	virtual void current_Events();

private:
	const Uint8* state = SDL_GetKeyboardState(NULL);

	int character_go_left;
	int character_go_right;
	int character_go_up;
	int character_go_down;
	int button_state; // ��ư
	int character_x;
	int character_y;

	SDL_Surface* temp_surface;

	// bg
	SDL_Texture* texture_[5]; // the SDL_Texture 
	SDL_Rect source_rectangle_[5]; // the rectangle for source image
	SDL_Rect destination_rectangle_[5]; // for destination

	// main_char
	SDL_Texture* g_researcher_texture; // ������ ���� ���� ��
	SDL_Rect g_researcher_pos; // �������� ���� ��ġ
	SDL_Rect g_researcher_rect; // ������ �׸����� �߶�� �簢��

	int show_explain = 0;
	bool lever = 0;
	int rabbit_pc_flag = 0;

	// sound
	int on_lever = 0;
	int on_pc = 0;
	Mix_Chunk* lever_up_sound;
	Mix_Chunk* lever_down_sound;
	Mix_Chunk* pc_on_sound;
	Mix_Chunk* pc_off_sound;
	Mix_Chunk* keyboard_sound;
	Mix_Chunk* door_sound;
	Mix_Music* lab_music;
};