#include <iostream>

#include <sys/ioctl.h>
#include <termios.h>

#include <chrono>
#include <thread>



using namespace std;

bool kbhit()
{
    termios term;
    tcgetattr(0, &term);

    termios term2 = term;
    term2.c_lflag &= ~ICANON;
    tcsetattr(0, TCSANOW, &term2);

    int byteswaiting;
    ioctl(0, FIONREAD, &byteswaiting);

    tcsetattr(0, TCSANOW, &term);

    return byteswaiting > 0;
}

bool gameOver;

const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;
enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;


void Setup(){
    gameOver = false;
    dir = STOP;

    x = width / 2;
    y = height / 2;

    fruitX = rand() % width;
    fruitY = rand() % height;
}

void Draw(){
    system("clear");

    for (int i = 0; i < width+2 ; i++){
        cout << "#";
    }
    cout << endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            if (j==0){
                cout << "#";
                // cout << " ";
            }
            
            if (i == y && j == x){
                cout << "O";
            }else if (i == fruitY && j == fruitX){
                cout << "F";
            }else{
                cout << " ";
            }

            if(j== width-1){
                cout << "#";
            }
            
        }
        cout << endl;
    }

    for (int i = 0; i < height+2 ; i++){
        cout << "#";
    }
    cout << endl;


}
void Input(){
    if (kbhit())
    {

        switch (getchar())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;

        default:
            break;
        }
    }
}
void Logic(){
    switch (dir)
    {
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;

        default:
            break;
        }
    }
}
int main(){

    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        
        this_thread::sleep_for(chrono::milliseconds(150));

    };

    return 0;
}
