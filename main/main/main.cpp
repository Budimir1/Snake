#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

const int N = 20;
int pole[N][N];
int dlina = 1;
int napravlenie = 0;//0 - vverh, 1 - pravo 2 - vniz 3 -vlevo
bool is_game_over = false;
int x_t, y_t;//хвост
int x_h, y_h;//голова
int x_fr, y_fr;//фрукты


void init_pole() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            pole[i][j] = 0;
    x_h = N / 2;
    y_h = N / 2;
    pole[x_h][y_h] = 1;
}


void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void print_pole() {
    gotoxy(1, 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (pole[j][i] == 0)
                cout << ". ";
            else
                if (pole[j][i] < 0)
                    cout << "0<";
                else
                cout << "[]";
        cout << endl;
    }
}


void print_pole_v2() {
    gotoxy(2*x_t + 1,y_t + 1);
    cout << ". ";
    gotoxy(2 * x_h + 1, y_h + 1);
    cout << "[]";
}


void update_hvost()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if ((i != x_h) || (j != y_h))
                if (pole[i][j] == dlina) {
                    pole[i][j] = 0;
                    x_t = i;
                    y_t = j;
                }
                else
                    if (pole[i][j] > 0)
                        pole[i][j] += 1;
}


void move_head() {
    if (napravlenie == 0)
        y_h -= 1;
    if (napravlenie == 1)
        x_h += 1;
    if (napravlenie == 2)
        y_h += 1;
    if (napravlenie == 3)
        x_h -= 1;

    if (x_h == N)
        x_h = 0;
    if (x_h == -1)
        x_h = N-1;
    if (y_h == N)
        y_h = 0;
    if (y_h == -1)
        y_h = N-1;
    if ((pole[x_h][y_h] == 0) || (pole[x_h][y_h] == -1))
        pole[x_h][y_h] = 1;
    else
        is_game_over = true;

    update_hvost();
}


void gen_frukt() {
    do {
        x_fr = rand() % N;
        y_fr = rand() % N;
    } while (pole[x_fr][y_fr] != 0);
    gotoxy(2 * x_fr, y_fr);
    cout << "0<";
    pole[x_fr][y_fr] = -1;
}


int main()
{
    system("CLS");
    init_pole();
    gen_frukt();
    print_pole();
    int score=0;
    int key = 72;
    int t1 = 0;
    int t0 = 0;
    // цикл игры

    while (!is_game_over) {
        // отрисовка
        //system("CLS");
        //print_pole_v2();

        // обработка нажатия кнопки
        
        if (_kbhit())
            key = _getch();
        if (key == 72)
            if (napravlenie != 2)
                napravlenie = 0;
        if (key == 77)
            if (napravlenie != 3)
                napravlenie = 1;
        if (key == 80)
            if (napravlenie != 0)
                napravlenie = 2;
        if (key == 75)
            if (napravlenie != 1)
                napravlenie = 3;
            

        //сдвинуть змею
        t1 = clock();
        int speed = 300;  
        if (t1 - t0 > speed) {

            move_head();
            t0 = t1;
            print_pole_v2();
        }
        //обновление картинки
        
        //проверка съели или нет фрукт
            // генерация фрукта
        if ((x_fr == x_h) && (y_fr == y_h)) {
            gen_frukt();
            dlina += 1;
            score += 1;

        }

        
        gotoxy(0, N + 1);
        cout << "Your score: " << score << endl;
        gotoxy(0, N + 1);

    }
    
    
    cout << "Game over" << endl;
    
    return 0;
}
