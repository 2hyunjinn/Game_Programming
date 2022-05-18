#include "GameFunc.h"
#include "stage.h"

Stage1::Stage1()
{
	srand(time(NULL));

	// For Character
	button_state = 4;
	character_x = 470, character_y = 270;
	
	// sound
	g_eat_wav = Mix_LoadWAV("../../resource/eat.mp3");
	g_change_dir_wav = Mix_LoadWAV("../../resource/change.mp3");
	g_max_score_wav = Mix_LoadWAV("../../resource/max_score.mp3"); 
	g_gameover_wav = Mix_LoadWAV("../../resource/gameover.mp3");


	/* picture snake */
	SDL_Surface* snake_surface = IMG_Load("../../image/snake_rect.png");
	g_snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_surface);
	SDL_FreeSurface(snake_surface);
	g_snake_rect = { 0, 0, 402, 402 };
	snake.push_front({ character_x, character_y, WIDTH,HEIGHT });

	/* picture fruits */
	SDL_Surface* fruit_surface = IMG_Load("../../image/item1.png");
	g_fruit_texture = SDL_CreateTextureFromSurface(g_renderer, fruit_surface);
	SDL_FreeSurface(fruit_surface);
	g_fruit_rect = { 0, 0, 750, 492 };
	b_fruit = false; // 아직 아이템 존재하지 않음

	/* text */
	font = TTF_OpenFont("../../resource/Koulen-Regular.ttf", 40);
	yellow = { 255, 212, 0, 0 };
	white = { 255, 255, 255, 0 };

	// game over
	SDL_Surface* game_over_surface = TTF_RenderText_Blended(font, "GAME OVER", white);
	game_over_texture = SDL_CreateTextureFromSurface(g_renderer, game_over_surface);
	SDL_FreeSurface(game_over_surface);
	g_gameover_rect = { 0,0,game_over_surface->w ,game_over_surface->h };
	g_gameover_pos = { 500 - g_gameover_rect.w / 2, 300 - g_gameover_rect.h / 2, g_gameover_rect.w, g_gameover_rect.h };

	// best_score
	SDL_Surface* best_score_surface = TTF_RenderText_Blended(font, "BEST SCORE", yellow);
	best_score_texture = SDL_CreateTextureFromSurface(g_renderer, best_score_surface);
	SDL_FreeSurface(best_score_surface);
	best_score_rect = { 0,0, best_score_surface->w, best_score_surface->h };
	best_score_pos = { 500 - g_gameover_rect.w / 2 - 5, 300 - g_gameover_rect.h / 2 + 40, best_score_rect.w, best_score_rect.h };

	// reset
	play_best_score_music = false;
	gameover = false;
	gameover_button = false;
	score = 0;
}

Stage1::~Stage1()
{
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(g_snake_texture);
}

void Stage1::Reset()
{
	snake.clear();
	character_x = 485, character_y = 285;
	snake.push_front({ character_x, character_y, WIDTH, HEIGHT });

	button_state = 4;
	gameover = false;
	gameover_button = false;
	score = 0;
	play_best_score_music = false;

	SDL_RenderCopy(g_renderer, g_fruit_texture, &g_fruit_rect, &g_fruit_pos);
	SDL_RenderCopy(g_renderer, g_snake_texture, &g_snake_rect, &(snake.front()));

	g_current_game_phase = PHASE_ENDING;
}

void Stage1::Update()
{
	if (gameover) return;

	// throw fruit at random
	fruit_x = rand() % 950 + 10;
	fruit_y = rand() % 550 + 10;
	if (b_fruit == false) {
		for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
			if ((*iter).x == fruit_x && (*iter).y == fruit_y) {
				fruit_x = rand() % 950 + 10;
				fruit_y = rand() % 550 + 10;
			}
			else continue;
		}
		g_fruit_pos = { fruit_x, fruit_y, WIDTH + 10, HEIGHT+10 };
		b_fruit = true;
	}

	//snake move
	snake_x = snake_y = 0;
	if (button_state == character_go_left) { // 왼쪽
		snake_x = -15, snake_y = 0;
	}
	else if (button_state == character_go_right) { // 오른쪽
		snake_x = 15, snake_y = 0;
	}
	else if (button_state == character_go_up) { // 위
		snake_x = 0, snake_y = -15;
	}
	else if (button_state == character_go_down) { // 아래
		snake_x = 0, snake_y = 15;
	}
	snake.push_front({ snake.front().x + snake_x , snake.front().y + snake_y, WIDTH, HEIGHT });
	snake.pop_back();

	// snake item check
	if ((snake.front().x >= g_fruit_pos.x - 10) && (snake.front().x <= g_fruit_pos.x + 20)
		&& (snake.front().y >= g_fruit_pos.y - 10) && (snake.front().y <= g_fruit_pos.y + 20)) {
		snake.push_front({ snake.front().x + snake_x, snake.front().y + snake_y, WIDTH, HEIGHT});

		Mix_PlayChannel(-1, g_eat_wav, 0); // sound when eating
		score += 1;
		b_fruit = false;
	}

	/* check current snake position */
	// check position
	if ((snake.front().x < 0) || (snake.front().x > 985) || (snake.front().y < 0) || (snake.front().y > 585)) {
		gameover = true;
	}
	// check my body
	int head_x = snake.front().x, head_y = snake.front().y;
	for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
		if ((*iter).x == head_x && (*iter).y == head_y) {
			gameover = true;
		}
	}
}


void Stage1::Render()
{
	// if click the left button
	if (gameover_button) Reset();

	// bg
	SDL_RenderClear(g_renderer); // clear the renderer to the draw color
	SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 0);

	// item fruits
	SDL_RenderCopy(g_renderer, g_fruit_texture, &g_fruit_rect, &g_fruit_pos);

	// snake
	for (auto iter = snake.begin(); iter != snake.end(); iter++) {
		SDL_RenderCopy(g_renderer, g_snake_texture, &g_snake_rect, &(*iter));
	}

	// score
	SDL_Surface* score_surface = TTF_RenderText_Blended(font, to_string(score).c_str(), yellow);
	score_texture = SDL_CreateTextureFromSurface(g_renderer, score_surface);
	SDL_FreeSurface(score_surface);
	score_rect = { 0, 0, score_surface->w, score_surface->h };
	score_pos = { 20, 530, score_rect.w, score_rect.h };
	SDL_RenderCopy(g_renderer, score_texture, &score_rect, &score_pos);

	// if game is over
	if (gameover) {
		SDL_RenderCopy(g_renderer, game_over_texture, &g_gameover_rect, &g_gameover_pos);
		if (score!=0 && score >= best_score) {
			// sound when best_score
			if (!play_best_score_music) Mix_PlayChannel(-1, g_max_score_wav, 0); 
			
			SDL_RenderCopy(g_renderer, best_score_texture, &best_score_rect, &best_score_pos);
			best_score = score; // renewal score
		}
		else if (!play_best_score_music) Mix_PlayChannel(-1, g_gameover_wav, 0);
		play_best_score_music = true;
	}

	// best_score
	font2 = TTF_OpenFont("../../resource/Koulen-Regular.ttf", 20);
	string text_best = "BEST_SCORE : " + to_string(best_score);

	SDL_Surface* best_surface = TTF_RenderText_Blended(font2, text_best.c_str(), white);
	best_texture = SDL_CreateTextureFromSurface(g_renderer, best_surface);
	SDL_FreeSurface(best_surface);

	best_rect = { 0,0, best_surface->w, best_surface->h };
	best_pos = { 850, 10, best_rect.w, best_rect.h };
	SDL_RenderCopy(g_renderer, best_texture, &best_rect, &best_pos);

	SDL_RenderPresent(g_renderer); // draw to the screen
}


void Stage1::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			// If the left arrow key is pressed.
			if (event.key.keysym.sym == SDLK_LEFT) {
				if (button_state != character_go_right && button_state != character_go_left) {
					Mix_PlayChannel(-1, g_change_dir_wav, 0); // sound when eating
					button_state = character_go_left;
				}
			}
			if (event.key.keysym.sym == SDLK_RIGHT) {
				if (button_state != character_go_left && button_state != character_go_right) {
					Mix_PlayChannel(-1, g_change_dir_wav, 0); // sound when eating
					button_state = character_go_right;
				}
			}
			if (event.key.keysym.sym == SDLK_UP) {
				if (button_state != character_go_down && button_state != character_go_up){
					Mix_PlayChannel(-1, g_change_dir_wav, 0); // sound when eating
					button_state = character_go_up;
				}
			}
			if (event.key.keysym.sym == SDLK_DOWN) {
				if (button_state != character_go_up && button_state != character_go_down){
					Mix_PlayChannel(-1, g_change_dir_wav, 0); // sound when eating
					button_state = character_go_down;
				}
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (gameover) gameover_button = true;
			}
		default:
			break;
		}
	}
}