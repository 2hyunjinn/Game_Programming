#include "GameFunc.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
#include <sstream>
#include <atlstr.h>
#include <iomanip>
using namespace std;

// �귯�� �ð� ���
double g_elapsed_time_ms;

/* ����Ű */
int f_state; // ��ư
bool bullet[30]; // �Ѿ�
int sum;
int cnt; // �Ѿ��� �ε���
const Uint8* state = SDL_GetKeyboardState(NULL);

/* ���Ϸ��� �̹��� */
SDL_Texture* g_plane_texture; // ����� ���� ���� ��
SDL_Rect g_char_pos; // ������� ���� ��ġ
SDL_Rect g_source_rect; // ����� �߶�� ���� �簢��

/* �̻��� �̹��� */
SDL_Texture* g_missile_texture;
SDL_Rect g_missile_pos[30]; // �̻����� ���� ��ġ
SDL_Rect g_missile_rect; // �̻��� �߶�� ���� �簢��

/* ����� �̹��� */
SDL_Texture* g_magic_texture;
SDL_Rect g_magic_pos; // �̻����� ���� ��ġ
SDL_Rect g_magic_rect[7]; // �̻��� �߶�� ���� �簢��
int g_magic_wing_num;
int g_current_wing_id;
bool magic_wing_b;

/* ��� �̹��� */
SDL_Texture* bg_texture;
SDL_Rect bg_destination_rect; // ���
SDL_Rect bg_rect; // ��� �߶�� ���� �簢��

/* ���� */
Mix_Music* g_bg_mus; // �������
Mix_Chunk* g_gun_wav; // ȿ����

/* ���� ��� */
SDL_Texture* g_title_texture;
TTF_Font* font; // ��Ʈ
SDL_Surface* score; // '����'
SDL_Rect g_title_rect; // �߶�� �� ũ��

SDL_Surface* score_sum; // ���� ����
SDL_Texture* g_sum_texture;
SDL_Rect g_score_rect; // �߶�� �� 

int time_ms_;
/////////////////////////////////////////////////////////////
// InitGame() 
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.
void InitGame() {

    /* �Ҹ� ���� */
    // �������
    g_bg_mus = Mix_LoadMUS("../../resource/moon_music.mp3");
    if (g_bg_mus == 0) { // ���� ���
        cout << "Mix_LoadMUS(\"moon_music.mp3\"): " << Mix_GetError() << endl;
    }
    else cout << "Mix_LoadMUS"<< endl;
   
    Mix_VolumeMusic(100);
    Mix_PlayMusic(g_bg_mus, -1);

    // ȿ����
    g_gun_wav = Mix_LoadWAV("../../resource/m.MP3");

    // �ؽ�Ʈ ��� - �ѱ�
    font = TTF_OpenFont("../../resource/CJBOLD.ttf", 30); // ��Ʈ �̸�, ũ��
    SDL_Color yellow = { 255, 212, 0, 0 }; // RGB ����

    // ���� : ���
    score = TTF_RenderUTF8_Blended(font, CW2A(L"���� : ", CP_UTF8), yellow);
    g_title_rect = { 0, 0, score->w, score->h };
    g_title_texture = SDL_CreateTextureFromSurface(g_renderer, score);
    SDL_FreeSurface(score);

    // ���� ���� ���
    time_ms_ = 0;
    g_sum_texture= 0;

    /* �ð� */
    g_flag_running = true;
    g_elapsed_time_ms = 0;
    

    /* �̹��� ���� */
    /* ��� �̹��� */
    // ��� �̹��� ��ȯ
    SDL_Surface* bg_surface = IMG_Load("../../image/back.png");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    // ��� �׸����� �߶�� ��
    bg_rect = { 0,0,638,360 };
    // ��� ������
    bg_destination_rect = { 0, 0, 1200, 675 };

    /* ���Ϸ��� �̹��� */
    // ���Ϸ��� �̹��� ��ȯ
    SDL_Surface* fighter_plane = IMG_Load("../../image/sailor moon.png");
    g_plane_texture = SDL_CreateTextureFromSurface(g_renderer, fighter_plane);
    SDL_FreeSurface(fighter_plane); // ���� ��� �ʿ������ �޸� ����

    // ���Ϸ��� �׸����� �߶�� ��
    g_source_rect = { 0, 0, 2000, 2000 };

    // ���Ϸ��� ���� ��ġ
    g_char_pos = { 600, 410, 88, 88 };

    /* ��Ʈ �̹��� */
    // ��Ʈ �̹��� ��ȯ
    SDL_Surface* missile_surface = IMG_Load("../../image/heart2.png");
    g_missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
    SDL_FreeSurface(missile_surface);

    // ��Ʈ �׸����� �߶�� ��
    g_missile_rect = { 0, 0, 720, 720 };

    /* �ִϸ��̼� - ����� */
    // ����� �̹��� ��ȯ
    g_magic_wing_num = 7;
    g_current_wing_id = 0;

    SDL_Surface* magic_surface = IMG_Load("../../image/wing.png");
    g_magic_texture = SDL_CreateTextureFromSurface(g_renderer, magic_surface);
    SDL_FreeSurface(magic_surface);

    // ����� �׸����� �߶�� ��
    g_magic_rect[0] = { 1, 1449, 861, 465 };
    g_magic_rect[1] = { 8129, 1313, 885, 489 };
    g_magic_rect[2] = { 925, 1201, 645, 709 };
    g_magic_rect[3] = { 63, 49, 428, 876 };
    g_magic_rect[4] = { 705, 9, 477, 853 };
    g_magic_rect[5] = { 1317, 145, 609, 633 };
    g_magic_rect[6] = { 2073, 249, 821, 433 };

    // Clear the console screen.
    // ǥ����� ȭ���� ������ �����.
    system("cls");
}

// ���� ��� �Լ�
void PaintText(int time_ms_) {
    string print_score = "00000";
    string current_score = to_string(time_ms_); // ���� ����

    if (current_score.length() <= 5) { // 99999������ ���� ä��
        print_score.replace(5- current_score.length(), current_score.length(), current_score);
    }
    else print_score = "Game Over"; // 99999 �Ѿ�� game over

    SDL_Color yellow = { 255, 212, 0, 0 }; // yellow
    score_sum = TTF_RenderText_Solid(font, print_score.c_str(), yellow); // print_score ���ڿ� - font1�� ����ؼ� ��������� ǥ��
    g_sum_texture = SDL_CreateTextureFromSurface(g_renderer, score_sum);
    g_score_rect = { 0, 0, score_sum->w, score_sum->h };
    SDL_RenderCopy(g_renderer, g_sum_texture, NULL, &g_score_rect);

    // �޸� ����
    SDL_FreeSurface(score_sum);
}

/////////////////////////////////////////////////////////////
// Update() 
// ������ ������ ������Ʈ�ϴ� �Լ�.
// ���� ������ ���� �����ؾ��ϴ� ��.
// ���ӿ��� �Ͼ�� ��ȭ�� ��� �� ������ �����Ѵ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Update() {

    /* ����� */
    if (f_state == 1) { // ����
        g_char_pos.x -= 10;
    }
    else if (f_state == 2) { // ������
        g_char_pos.x += 10;
    }
    else if (f_state == 3) { // ��
        g_char_pos.y -= 10;
    }
    else if (f_state == 4) { // �Ʒ�
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

    /* ������� ��ġ */
    g_current_wing_id++;
    if (g_current_wing_id >= g_magic_wing_num) {
        g_current_wing_id = 0;
    }

    /* ���� ���� */
    if (g_sum_texture != 0)
    {
        SDL_DestroyTexture(g_sum_texture);		// !!!�߿�!!!  �̹� �����Ǿ��ִ� texture �� ������ �ݵ�� �޸𸮿��� �������Ѵ�. !!!
        g_sum_texture = 0;
    }
    PaintText(time_ms_); // ���� ����

    g_elapsed_time_ms += 33;
}

/////////////////////////////////////////////////////////////
// Render() 
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Render() {

    // background
    SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_destination_rect); // �߶�� ���� �簢��, ���� ���� �簢��

    /* �ؽ�Ʈ ��� */
    // ���� :
    SDL_Rect tmp_r;
    tmp_r = { 50,600,g_title_rect.w, g_title_rect.h };
    SDL_RenderCopy(g_renderer, g_title_texture, &g_title_rect, &tmp_r);

    // ���� ����
    SDL_Rect tmp_a;
    tmp_a = { 150, 600, g_score_rect.w, g_score_rect.h };
    SDL_RenderCopy(g_renderer, g_sum_texture, &g_score_rect, &tmp_a);

    // ���Ϸ��� �׸���
    SDL_RenderCopy(g_renderer, g_plane_texture, &g_source_rect, &g_char_pos); // �߶�� ���� �簢��, ���� ���� �簢��

    if (magic_wing_b) {
        // ����� �׸��� 
        SDL_Rect wing = g_magic_pos;
        wing = { g_char_pos.x + 50, g_char_pos.y + 20, 50, 50 };
        SDL_RenderCopy(g_renderer, g_magic_texture, &g_magic_rect[g_current_wing_id], &wing); // �߶�� ���� �簢��, ���� ���� �簢��
    }
    // 3. ��Ʈ �׸��� 
    for (int i = 0; i < 30; i++) {
        if (bullet[i]) {
            if (g_missile_pos[i].y < 0) bullet[cnt] = false;
            // ��Ʈ �߻�
            g_missile_pos[i].y-=10;
            SDL_RenderCopy(g_renderer, g_missile_texture, &g_missile_rect, &g_missile_pos[i]); // �߶�� ���� �簢��, ���� ���� �簢��
        }
    }
    SDL_RenderPresent(g_renderer);
}

void shot_heart() {
    magic_wing_b = true; // ������ ���ư���
    time_ms_ += 10;

    // -1�� ���� ���� �� �� �ִ� ä�� / ���� �� �Ҹ� / �ݺ� Ƚ��
    Mix_PlayChannel(-1, g_gun_wav, 0); // �߻��� �� ���� ȿ����
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
// �̺�Ʈ�� ó���ϴ� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
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
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame(){
    SDL_DestroyTexture(g_plane_texture);
    SDL_DestroyTexture(g_missile_texture);
    SDL_DestroyTexture(g_title_texture);
    SDL_DestroyTexture(g_sum_texture);

    Mix_FreeMusic(g_bg_mus);
    Mix_FreeChunk(g_gun_wav);

    TTF_CloseFont(font);
}