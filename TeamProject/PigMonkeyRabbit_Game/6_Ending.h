#pragma once
#include "0_GameFunc.h";

class Ending : public PhaseInterface
{
public:
	Ending();
	~Ending();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	SDL_Texture* texture_[7]; // the SDL_Texture 
	SDL_Rect source_rectangle_[7]; // the rectangle for source image
	SDL_Rect destination_rectangle_[7]; // for destination
	
	// exit 
	SDL_Texture* exit_texture; // the SDL_Texture 
	SDL_Rect exit_rectangle; // the rectangle for source image
	SDL_Rect exit_pos; // for destination

	SDL_Surface* temp_surface;

	Mix_Music* end_music;

	int time;
	int cnt;
};
