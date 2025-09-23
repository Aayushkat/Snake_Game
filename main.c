#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#define rows 20
#define columns 20

char board[rows * columns];
int snakeX=5,snakeY=5;
int isGameover=0;
void fill_board()

{
    int x, y;
    for (y = 0; y < rows; y++)
    {for (x = 0; x < columns; x++)
        {if (x == 0 || y == 0 || x == columns - 1 || y == rows - 1)
            { board[y * columns + x] = '#';
            }
            else
            board[y*columns+x]=' ';//for space
        }
    }
}

void clear_screen(){
    system("cls");
}
void print_board()
{
    int x, y;
    clear_screen();
    for (y = 0; y < rows; y++)
    {for (x = 0; x < columns; x++)
        {
            putchar(board[y * columns + x]);
        }
        putchar('\n');
    }
}
struct snake_Part{
    int x,y;
};
struct snake{
    int length;
};
void draw_snake(){
    board[snakeX* columns + snakeY]='O';
}

void move_snake(int deltaX, int deltaY){
    snakeX+=deltaX;
    snakeY+=deltaY;
}

void read_keyboard(){
int ch=getch();
switch (ch){
    case 'a':move_snake(0,-1);break;
    case 'd':move_snake(0,1);break;
    case 'w':move_snake(-1,0);break;
    case 's':move_snake(1,0);break;
}}

int main()
{
    while(!isGameover){
    fill_board();
    draw_snake();
    print_board();
    read_keyboard();
    
}
    return 0;
}