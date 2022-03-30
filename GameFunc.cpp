#include "GameFunc.h"
#include <windows.h>
#include <queue>
#include "SDL_image.h"
using namespace std;

// �귯�� �ð� ���
double g_elapsed_time_ms;

int f_state;
int f_X, f_Y; // ������� ��ġ
int m_X, m_Y; // �̻����� ��ġ

bool bullet[30];
short m_pos[30][2];
int cnt;

SDL_Texture* g_plane_texture; // ����� ���� ���� ��
SDL_Rect g_char_pos; // ������� ���� ��ġ
SDL_Rect g_source_rect; // ����� �߶�� ���� �簢��

// SDL_Rect g_destination_rect; // ���� ���� �簢��

SDL_Texture* g_missile_texture;
SDL_Rect g_missile_pos[30]; // �̻����� ���� ��ġ
SDL_Rect g_missile_rect; // �̻��� �߶�� ���� �簢��

SDL_Texture* bg_texture;
SDL_Rect bg_destination_rect; // ���
SDL_Rect bg_rect; // ��� �߶�� ���� �簢��

/////////////////////////////////////////////////////////////
// InitGame() 
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.
void InitGame() {
    g_flag_running = true;
    g_elapsed_time_ms = 0;
    
    // ��� �̹��� ��ȯ
    SDL_Surface* bg_surface = IMG_Load("../../image/wallpaperbetter.jpg");
    bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    // ����� �̹��� ��ȯ
    SDL_Surface* fighter_plane = IMG_Load("../../image/fighter.png");
    g_plane_texture = SDL_CreateTextureFromSurface(g_renderer, fighter_plane);
    SDL_FreeSurface(fighter_plane); // ���� ��� �ʿ������ �޸� ����

    // �̻��� �̹��� ��ȯ
    SDL_Surface* missile_surface = IMG_Load("../../image/missile.png");
    g_missile_texture = SDL_CreateTextureFromSurface(g_renderer, missile_surface);
    SDL_FreeSurface(missile_surface);

    // ��� �׸����� �߶�� ��
    bg_rect = { 0,0,1920,1080 };

    // ��� ������
    bg_destination_rect = { 0,0,800,600 };

    // ����� �׸����� �߶�� ��
    g_source_rect = { 0,0,31,26 };

    // �̻��� �׸����� �߶�� ��
    g_missile_rect = { 0, 0, 256, 256 };

    // ����� ���� ��ġ
    g_char_pos = { 400, 500, 62, 52 };

    // Clear the console screen.
    // ǥ����� ȭ���� ������ �����.
    system("cls");
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
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Render() {

    // background
    SDL_RenderCopy(g_renderer, bg_texture, &bg_rect, &bg_destination_rect); // �߶�� ���� �簢��, ���� ���� �簢��

    // ����� �׸���
    SDL_RenderCopy(g_renderer, g_plane_texture, &g_source_rect, &g_char_pos); // �߶�� ���� �簢��, ���� ���� �簢��

    // 3. �̻��� �׸��� 
    for (int i = 0; i < 30; i++) {
        if (bullet[i]) {
            if (g_missile_pos[i].y < 0) bullet[i] = false;
            // �̻��� �߻�
            g_missile_pos[i].y-=10;
            SDL_RenderCopy(g_renderer, g_missile_texture, &g_missile_rect, &g_missile_pos[i]); // �߶�� ���� �簢��, ���� ���� �簢��
        }
    }
    SDL_RenderPresent(g_renderer);
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
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame(){
    SDL_DestroyTexture(g_plane_texture);
    SDL_DestroyTexture(g_missile_texture);
}