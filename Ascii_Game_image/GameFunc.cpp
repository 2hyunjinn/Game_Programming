#include "GameFunc.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
using namespace std;

// 흘러간 시간 기록
double g_elapsed_time_ms;

int f_state;
int f_X, f_Y; // 비행기의 위치
int m_X, m_Y; // 미사일의 위치

bool bullet[30];
short m_pos[30][2];
int cnt;

SDL_Texture* g_plane_texture; // 비행기 복사 받을 곳
SDL_Rect g_char_pos; // 비행기의 현재 위치
SDL_Rect g_source_rect; // 비행기 잘라올 곳의 사각형

// SDL_Rect g_destination_rect; // 붙일 곳의 사각형

SDL_Texture* g_missile_texture;
SDL_Rect g_missile_pos[30]; // 미사일의 현재 위치
SDL_Rect g_missile_rect; // 미사일 잘라올 곳의 사각형

SDL_Texture* bg_texture;
SDL_Rect bg_destination_rect; // 배경
SDL_Rect bg_rect; // 배경 잘라올 곳의 사각형

/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.
void InitGame() {
    g_flag_running = true;
    g_elapsed_time_ms = 0;
    
    // 배경 이미지 소환
    SDL_Surface* bg_surface = IMG_Load("../../image/wallpaperbetter.jpg");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    // 비행기 이미지 소환
    SDL_Surface* fighter_plane = IMG_Load("../../image/fighter.png");
    g_plane_texture = SDL_CreateTextureFromSurface(g_renderer, fighter_plane);
    SDL_FreeSurface(fighter_plane); // 이제 얘는 필요없으니 메모리 해제

    // 미사일 이미지 소환
    SDL_Surface* missile_surface = IMG_Load("../../image/missile.png");
    g_missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
    SDL_FreeSurface(missile_surface);

    // 배경 그림에서 잘라올 곳
    bg_rect = { 0,0,1920,1080 };

    // 배경 사이즈
    bg_destination_rect = { 0,0,800,600 };

    // 비행기 그림에서 잘라올 곳
    g_source_rect = { 0,0,31,26 };

    // 미사일 그림에서 잘라올 곳
    g_missile_rect = { 0, 0, 256, 256 };

    // 비행기 최초 위치
    g_char_pos = { 400, 500, 62, 52 };

    // Clear the console screen.
    // 표준출력 화면을 깨끗히 지운다.
    system("cls");
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
    else {
        g_char_pos.x = g_char_pos.x;
        g_char_pos.y = g_char_pos.y;
    }

    if (g_char_pos.x > 738)
        g_char_pos.x = 738;
    else if (g_char_pos.x < 0)
        g_char_pos.x = 0;
    
    if (g_char_pos.y > 548)
        g_char_pos.y = 548;
    else if (g_char_pos.y < 0)
        g_char_pos.y = 0;

    g_elapsed_time_ms += 33;
}


/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Render() {

    // background
    SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_destination_rect); // 잘라올 곳의 사각형, 붙일 곳의 사각형

    // 비행기 그리기
    SDL_RenderCopy(g_renderer, g_plane_texture, &g_source_rect, &g_char_pos); // 잘라올 곳의 사각형, 붙일 곳의 사각형

    // 3. 미사일 그리기 
    for (int i = 0; i < 30; i++) {
        if (bullet[i]) {
            if (g_missile_pos[i].y < 0) bullet[i] = false;
            // 미사일 발사
            g_missile_pos[i].y-=10;
            SDL_RenderCopy(g_renderer, g_missile_texture, &g_missile_rect, &g_missile_pos[i]); // 잘라올 곳의 사각형, 붙일 곳의 사각형
        }
    }
    SDL_RenderPresent(g_renderer);
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
                bullet[cnt] = true;
                g_missile_pos[cnt] = { g_char_pos.x, g_char_pos.y - 50, 60, 60 };
                cnt++;
                if (cnt > 29) cnt = 0;
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
}
