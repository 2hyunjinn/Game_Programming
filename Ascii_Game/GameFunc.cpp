#include "GameFunc.h"
#include <windows.h>
#include <queue>
using namespace std;

int f_state;
int f_X, f_Y; // ������� ��ġ
string f_output;

int m_state;
int m_X, m_Y; // �̻����� ��ġ
string missile;

bool bullet[30];
short m_pos[30][2];
int cnt;

/////////////////////////////////////////////////////////////
// InitGame() 
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.
void InitGame() {
    g_flag_running = true;

    f_state = 0;
    f_output = "*"; // �����
    f_X = 10, f_Y = 20;

    m_state = 0;
    missile = "!";

    cnt = 0;

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
        f_X--;
    }
    else if (f_state == 2) { // ������
        f_X++;
    }
    else if (f_state == 3) { // ��
        f_Y--;
    }
    else if (f_state == 4) { // �Ʒ�
        f_Y++;
    }
    else {
        f_X = f_X, f_Y = f_Y;
    }

    /* ���� �ٱ����� ���������� ���ϰ� */
    if (f_X > 19) {
        f_X = 19;
    }
    else if (f_X < 0) {
        f_X = 0;
    }

    if (f_Y > 29) {
        f_Y = 29;
    }
    else if (f_Y < 0) {
        f_Y = 0;
    }
}


/////////////////////////////////////////////////////////////
// Render() 
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴٴ� ���� ����.
void Render() {
    /* 1. ��� �׸��� */
    // 1-1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
    // <windows.h>���� �����ϴ� �Լ��� ����Ѵ�.
    COORD cur;
    cur.X = 0, cur.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    // 1-2. ��� �κ��� '_'���� ä���.
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 20; j++) {
            std::cout << "_";
        }
        cout << std::endl;
    }

    /* 2. ����� �׸��� */
    // 2-1. Ŀ���� ĳ���Ͱ� �׷��� ��ġ�� �ű��. 
    cur.X = f_X, cur.Y = f_Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    // 2-2. ����⸦ �׸���.
    cout << f_output;

    /* 3. �̻��� �׸��� */
    for (int i = 0; i < 30; i++) {
        if (bullet[i]) {
            COORD pos = { m_pos[i][0], m_pos[i][1]-- };
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

            if (m_pos[i][1] < 0) bullet[i] = false;
            // �̻��� �߻�
            cout << missile;
        }
    }
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
            if (event.key.keysym.sym == SDLK_LEFT) {
                f_state = 1;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                f_state = 2;
            }
            else if (event.key.keysym.sym == SDLK_UP) {
                f_state = 3;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                f_state = 4;
            }
            else if (event.key.keysym.sym == SDLK_SPACE) {
                bullet[cnt] = true;
                m_pos[cnt][0] = f_X;
                m_pos[cnt][1] = f_Y;
                cnt++;
                if (cnt > 30) cnt = 0;
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
void ClearGame()
{
}