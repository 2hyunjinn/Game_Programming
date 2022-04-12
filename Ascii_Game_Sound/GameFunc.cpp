#include "GameFunc.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
#include <sstream>
#include <atlstr.h>
#include <iomanip>
using namespace std;

// 흘러간 시간 기록
double g_elapsed_time_ms;

/* 방향키 */
int f_state; // 버튼
bool bullet[30]; // 총알
int sum;
int cnt; // 총알의 인덱스
const Uint8* state = SDL_GetKeyboardState(NULL);

/* 세일러문 이미지 */
SDL_Texture* g_plane_texture; // 비행기 복사 받을 곳
SDL_Rect g_char_pos; // 비행기의 현재 위치
SDL_Rect g_source_rect; // 비행기 잘라올 곳의 사각형

/* 미사일 이미지 */
SDL_Texture* g_missile_texture;
SDL_Rect g_missile_pos[30]; // 미사일의 현재 위치
SDL_Rect g_missile_rect; // 미사일 잘라올 곳의 사각형

/* 요술봉 이미지 */
SDL_Texture* g_magic_texture;
SDL_Rect g_magic_pos; // 미사일의 현재 위치
SDL_Rect g_magic_rect[7]; // 미사일 잘라올 곳의 사각형
int g_magic_wing_num;
int g_current_wing_id;
bool magic_wing_b;

/* 배경 이미지 */
SDL_Texture* bg_texture;
SDL_Rect bg_destination_rect; // 배경
SDL_Rect bg_rect; // 배경 잘라올 곳의 사각형

/* 음악 */
Mix_Music* g_bg_mus; // 배경음악
Mix_Chunk* g_gun_wav; // 효과음

/* 글자 출력 */
SDL_Texture* g_title_texture;
TTF_Font* font; // 폰트
SDL_Surface* score; // '점수'
SDL_Rect g_title_rect; // 잘라올 곳 크기

SDL_Surface* score_sum; // 실제 점수
SDL_Texture* g_sum_texture;
SDL_Rect g_score_rect; // 잘라올 곳 

int time_ms_;
/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.
void InitGame() {

    /* 소리 관리 */
    // 배경음악
    g_bg_mus = Mix_LoadMUS("../../resource/moon_music.mp3");
    if (g_bg_mus == 0) { // 오류 잡기
        cout << "Mix_LoadMUS(\"moon_music.mp3\"): " << Mix_GetError() << endl;
    }
    else cout << "Mix_LoadMUS"<< endl;
   
    Mix_VolumeMusic(100);
    Mix_PlayMusic(g_bg_mus, -1);

    // 효과음
    g_gun_wav = Mix_LoadWAV("../../resource/m.MP3");

    // 텍스트 출력 - 한글
    font = TTF_OpenFont("../../resource/CJBOLD.ttf", 30); // 폰트 이름, 크기
    SDL_Color yellow = { 255, 212, 0, 0 }; // RGB 투명도

    // 점수 : 출력
    score = TTF_RenderUTF8_Blended(font, CW2A(L"점수 : ", CP_UTF8), yellow);
    g_title_rect = { 0, 0, score->w, score->h };
    g_title_texture = SDL_CreateTextureFromSurface(g_renderer, score);
    SDL_FreeSurface(score);

    // 실제 점수 출력
    time_ms_ = 0;
    g_sum_texture= 0;

    /* 시간 */
    g_flag_running = true;
    g_elapsed_time_ms = 0;
    

    /* 이미지 관리 */
    /* 배경 이미지 */
    // 배경 이미지 소환
    SDL_Surface* bg_surface = IMG_Load("../../image/back.png");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    // 배경 그림에서 잘라올 곳
    bg_rect = { 0,0,638,360 };
    // 배경 사이즈
    bg_destination_rect = { 0, 0, 1200, 675 };

    /* 세일러문 이미지 */
    // 세일러문 이미지 소환
    SDL_Surface* fighter_plane = IMG_Load("../../image/sailor moon.png");
    g_plane_texture = SDL_CreateTextureFromSurface(g_renderer, fighter_plane);
    SDL_FreeSurface(fighter_plane); // 이제 얘는 필요없으니 메모리 해제

    // 세일러문 그림에서 잘라올 곳
    g_source_rect = { 0, 0, 2000, 2000 };

    // 세일러문 최초 위치
    g_char_pos = { 600, 410, 88, 88 };

    /* 하트 이미지 */
    // 하트 이미지 소환
    SDL_Surface* missile_surface = IMG_Load("../../image/heart2.png");
    g_missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
    SDL_FreeSurface(missile_surface);

    // 하트 그림에서 잘라올 곳
    g_missile_rect = { 0, 0, 720, 720 };

    /* 애니메이션 - 요술봉 */
    // 요술봉 이미지 소환
    g_magic_wing_num = 7;
    g_current_wing_id = 0;

    SDL_Surface* magic_surface = IMG_Load("../../image/wing.png");
    g_magic_texture = SDL_CreateTextureFromSurface(g_renderer, magic_surface);
    SDL_FreeSurface(magic_surface);

    // 요술봉 그림에서 잘라올 곳
    g_magic_rect[0] = { 1, 1449, 861, 465 };
    g_magic_rect[1] = { 8129, 1313, 885, 489 };
    g_magic_rect[2] = { 925, 1201, 645, 709 };
    g_magic_rect[3] = { 63, 49, 428, 876 };
    g_magic_rect[4] = { 705, 9, 477, 853 };
    g_magic_rect[5] = { 1317, 145, 609, 633 };
    g_magic_rect[6] = { 2073, 249, 821, 433 };

    // Clear the console screen.
    // 표준출력 화면을 깨끗히 지운다.
    system("cls");
}

// 점수 출력 함수
void PaintText(int time_ms_) {
    string print_score = "00000";
    string current_score = to_string(time_ms_); // 현재 점수

    if (current_score.length() <= 5) { // 99999까지만 점수 채점
        print_score.replace(5- current_score.length(), current_score.length(), current_score);
    }
    else print_score = "Game Over"; // 99999 넘어가면 game over

    SDL_Color yellow = { 255, 212, 0, 0 }; // yellow
    score_sum = TTF_RenderText_Solid(font, print_score.c_str(), yellow); // print_score 문자열 - font1을 사용해서 노란색으로 표현
    g_sum_texture = SDL_CreateTextureFromSurface(g_renderer, score_sum);
    g_score_rect = { 0, 0, score_sum->w, score_sum->h };
    SDL_RenderCopy(g_renderer, g_sum_texture, NULL, &g_score_rect);

    // 메모리 해제
    SDL_FreeSurface(score_sum);
}

/////////////////////////////////////////////////////////////
// Update() 
// 게임의 내용을 업데이트하는 함수.
// 실제 게임의 룰을 구현해야하는 곳.
// 게임에서 일어나는 변화는 모두 이 곳에서 구현한다.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Update() {

    /* 비행기 */
    if (f_state == 1) { // 왼쪽
        g_char_pos.x -= 10;
    }
    else if (f_state == 2) { // 오른쪽
        g_char_pos.x += 10;
    }
    else if (f_state == 3) { // 위
        g_char_pos.y -= 10;
    }
    else if (f_state == 4) { // 아래
        g_char_pos.y += 10;
    }
   
    if (g_char_pos.x > 1112)
        g_char_pos.x = 1112;
    else if (g_char_pos.x < 0)
        g_char_pos.x = 0;
    
    if (g_char_pos.y > 590)
        g_char_pos.y = 590;
    else if (g_char_pos.y < 0)
        g_char_pos.y = 0;

    /* 요술봉의 위치 */
    g_current_wing_id++;
    if (g_current_wing_id >= g_magic_wing_num) {
        g_current_wing_id = 0;
    }

    /* 실제 점수 */
    if (g_sum_texture != 0)
    {
        SDL_DestroyTexture(g_sum_texture);		// !!!중요!!!  이미 생성되어있는 texture 가 있으면 반드시 메모리에서 지워야한다. !!!
        g_sum_texture = 0;
    }
    PaintText(time_ms_); // 점수 갱신

    g_elapsed_time_ms += 33;
}

/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Render() {

    // background
    SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_destination_rect); // 잘라올 곳의 사각형, 붙일 곳의 사각형

    /* 텍스트 출력 */
    // 점수 :
    SDL_Rect tmp_r;
    tmp_r = { 50,600,g_title_rect.w, g_title_rect.h };
    SDL_RenderCopy(g_renderer, g_title_texture, &g_title_rect, &tmp_r);

    // 실제 점수
    SDL_Rect tmp_a;
    tmp_a = { 150, 600, g_score_rect.w, g_score_rect.h };
    SDL_RenderCopy(g_renderer, g_sum_texture, &g_score_rect, &tmp_a);

    // 세일러문 그리기
    SDL_RenderCopy(g_renderer, g_plane_texture, &g_source_rect, &g_char_pos); // 잘라올 곳의 사각형, 붙일 곳의 사각형

    if (magic_wing_b) {
        // 요술봉 그리기 
        SDL_Rect wing = g_magic_pos;
        wing = { g_char_pos.x + 50, g_char_pos.y + 20, 50, 50 };
        SDL_RenderCopy(g_renderer, g_magic_texture, &g_magic_rect[g_current_wing_id], &wing); // 잘라올 곳의 사각형, 붙일 곳의 사각형
    }
    // 3. 하트 그리기 
    for (int i = 0; i < 30; i++) {
        if (bullet[i]) {
            if (g_missile_pos[i].y < 0) bullet[cnt] = false;
            // 하트 발사
            g_missile_pos[i].y-=10;
            SDL_RenderCopy(g_renderer, g_missile_texture, &g_missile_rect, &g_missile_pos[i]); // 잘라올 곳의 사각형, 붙일 곳의 사각형
        }
    }
    SDL_RenderPresent(g_renderer);
}

void shot_heart() {
    magic_wing_b = true; // 마법봉 돌아가기
    time_ms_ += 10;

    // -1은 가장 빨리 쓸 수 있는 채널 / 내가 쓸 소리 / 반복 횟수
    Mix_PlayChannel(-1, g_gun_wav, 0); // 발사할 때 나는 효과음
    bullet[cnt] = true;
    g_missile_pos[cnt] = { g_char_pos.x + 50, g_char_pos.y - 10, 50, 50 };
    cnt++;
    if (cnt > 29) cnt = 0;
}

void current_Events() {
    if (state[SDL_SCANCODE_LEFT]) f_state = 1;
    if (state[SDL_SCANCODE_RIGHT]) f_state = 2;
    if (state[SDL_SCANCODE_UP]) f_state = 3;
    if (state[SDL_SCANCODE_DOWN]) f_state = 4;
}

/////////////////////////////////////////////////////////////
// HandleEvents() 
// 이벤트를 처리하는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void HandleEvents()
{
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {

        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_SPACE) {
                shot_heart();
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = 1;
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = 2;
            }
            if (event.key.keysym.sym == SDLK_UP) {
                f_state = 3;
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = 4;
            }
            break;

        case SDL_KEYUP:
            f_state = 0;
            current_Events();
            if (state[SDL_SCANCODE_SPACE]) shot_heart();
            else magic_wing_b = false;     
            break;
        default:
            break;
        }
    }
}




/////////////////////////////////////////////////////////////
// ClearGame() 
// 프로그램이 끝날 때 한 번 호출되는 함수.
// 이 함수에서 사용된 자원(이미지, 사운드 등)과 메모리 등을 해제해야한다.
void ClearGame(){
    SDL_DestroyTexture(g_plane_texture);
    SDL_DestroyTexture(g_missile_texture);
    SDL_DestroyTexture(g_title_texture);
    SDL_DestroyTexture(g_sum_texture);

    Mix_FreeMusic(g_bg_mus);
    Mix_FreeChunk(g_gun_wav);

    TTF_CloseFont(font);
}