#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
//#include <ncurses/ncurses.h>
#define SNAKE_MAX_LEN 256
#define columns 50
#define rows 25
#define apples 50
char board[rows*columns];//1D to that will become the game board
int is_game_over=0;// to track if the game is over

void clear_screen(){
    //refresh();
    system("cls");// the cls is onlyused for windows so for linux or mac make use clear command
}
void make_board()//to fill the 1D array which act as a game board
{

    int i,j;
    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            if (i==0||j==0||i==rows-1||j==columns-1) //to append the # at borders only because it will be at eh ends of the iterations                    
            board[i*columns+j]='#';                  //(i*columns+j) used because the it will force loop to append the characers rows wise 
            else                                      // because i*columns will help skip the previous already elements in the array                      
            board[i*columns+j]=' ';                                         
        }
    }
}

void show_board()//To display the game board on the console
{
       int i,j;

    for(i=0;i<rows;i++){
        for(j=0;j<columns;j++){
            putchar(board[i*columns+j]);;//simply using putchar because best for showing single character at a timee
        }putchar('\n');
    }
}

struct Snake_body_part//It will used to make each body part of the snake and represent it as a point like (x,y) 
{
    int x,y;//used two int variable make them act as coordinate points for the body parts
};

struct Snake// It will be used to make whole snake 
{
    int length;// this member will store the total length of the snake 
                // total length= head + body
                //tells you how many elements of the array part[] are actually being used.
    struct Snake_body_part Part[SNAKE_MAX_LEN];//
                                        // here we are declaring a array named 'part' 
                                        //which is of data type Snake_part  
                                        //length is 256 
                                        //possible body parts of the snake 
};

struct Snake snake_in_game;

struct Apple
{
    int x,y;    //This struct will help us label the coordinates/position of the apple in the array
    int eaten;  // will tell the dev whether the apple at the previous defined coordinates is eaten or not
                // eaten = 0
                // not eaten = 1
                //used struct because it will tell the coordinate and state of the each apple
};

struct Apple apple_in_game[apples];//this statement will help us store each apple and apples in the size will help us not make more apple than desired

void draw_snake()// this will draw the snake from tail to the head
{
    int i;
    for (i=snake_in_game.length-1;i>0;i--){
                                    //this will run a loop which will print the body part of the snake
                                // also the the snake start to form from it's tail not it's head thats why i=snake_in_game.length-1 and not i=0
        board[snake_in_game.Part[i].y*columns+snake_in_game.Part[i].x]='o';}//this logic is being used because it is a 1D array
        
        board[snake_in_game.Part[0].y*columns+snake_in_game.Part[0].x]='0';//this print head evry time draw_snake is called
}
// Moves the snake in the specified direction (DirX, DirY)
void snake_move(int DirX,int DirY)
{
    int i;
    for (i=snake_in_game.length-1;i>0;i--){//will shift the body part to follow his head
        snake_in_game.Part[i]=snake_in_game.Part[i-1];    
    }
    snake_in_game.Part[0].x+=DirX;/*these two statement are used to turn the head of the snake to the desired place*/
    snake_in_game.Part[0].y+=DirY;
}
static int DeltaX = 0, DeltaY = 0;
void read_keyboard() {
    int ch = getch();

    switch(ch) {
        case'W':
        case 72:
        case 'w':if (( DeltaY!=1)){ DeltaX=0;DeltaY=-1;} break;
        case 80:
        case 'S':
        case 's':if ((DeltaY!=-1)){ DeltaX=0;DeltaY=1;} break;
        case 75:
        case 'A':
        case 'a':if ((DeltaX!=1 )) {DeltaX=-1;DeltaY=0;} break;
        case 'D':
        case 77:
        case 'd':if ((DeltaX!=-1)) {DeltaX=1;DeltaY=0;} break;         
    }
    snake_move(DeltaX,DeltaY);

}

void draw_apples(){
    int i;
    for(i=0;i<apples;i++){
        if(!apple_in_game[i].eaten)
        board[apple_in_game[i].y*columns+apple_in_game[i].x]='+';
    }
}

void setup_apple()
{
    int i;
    for (i=0;i<apples;i++){
    apple_in_game[i].x=1+rand()%(columns-2);
    apple_in_game[i].y=1+rand()%(rows-2);
    apple_in_game[i].eaten=0;
}}

void setup_snake(){
    snake_in_game.length=1;
    snake_in_game.Part[0].x=1+rand()%(columns-2);
    snake_in_game.Part[0].y=1+rand()%(rows-2);
}

void game_setup(){
    int i;
    for (i=0;i<apples;i++){//check whether snake collided/eaten the apple with its head
        if(!apple_in_game[i].eaten){
            if((apple_in_game[i].x==snake_in_game.Part[0].x)&&(apple_in_game[i].y==snake_in_game.Part[0].y)){
             apple_in_game[i].eaten=1;
             snake_in_game.length++;}
        }

    }//check collision with the wall
    if(snake_in_game.Part[0].x==0||snake_in_game.Part[0].x==columns-1||snake_in_game.Part[0].y==0||snake_in_game.Part[0].y==rows-1){
    is_game_over=1;}

    for(i=1;i<snake_in_game.length;i++){//check the collision with itself
        if(snake_in_game.Part[0].x==snake_in_game.Part[i].x&&snake_in_game.Part[0].y==snake_in_game.Part[i].y){
        is_game_over=1;}

    }   
}
int main(int argc, char **argv){
srand(time(0));//Seed the pseudo-random number generator with the current time.
                // Without this, rand() would produce the same sequence every run, 
                // making the game predictable and boring.
    //initscr();
    //noecho();
setup_snake();//place snake rnadomly
setup_apple();//place apple randomly
while (!is_game_over) {

    make_board();//prepare the board
    draw_apples();;//place apple on board
    draw_snake();//place snake on board
    game_setup();  //check for snake behaviour
    clear_screen();// clear screen
 
    printf("Snake game, Score %d\n",snake_in_game.length*100);
    
    show_board();//print board
     Sleep(80);
    if (_kbhit()) {   // check if key pressed
        read_keyboard();
    }
     snake_move(DeltaX, DeltaY);
    
}
snake_move(columns,0);printf("Game Over, Final score: %d\n", snake_in_game.length * 100);
while(1) getchar();
    return 0;
}