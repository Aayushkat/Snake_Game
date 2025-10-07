#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <GL/glut.h>
//#include <ncurses/ncurses.h>
#define SNAKE_MAX_LEN 256
#define columns 20
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
            board[i*columns+j]=(is_game_over?'X':' ');                                         
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

void display_function(){
    int x,y;
    glClear(GL_COLOR_BUFFER_BIT);
        for(y=0;y<rows;y++){
            for(x=0;x<columns;x++){
                int ch = board[y*columns+x];
                float quad_x_size=2/(float)columns;
                float quad_y_size=2/(float)rows;

                switch(ch){
                    case'#':glColor3f(0.5,0.5,0.5);break;
                    case'0':glColor3f(1.0,0.0,0.0);break;
                    case'o':glColor3f(1.0,0.0,0.0);break;
                    case'+':glColor3f(0.0,1.0,0.0);break;
                    case' ':glColor3f(0.0,0.0,0.0);break;
                    case'X':glColor3f(0.5,0.5,0.5);break;

                }
glBegin(GL_QUADS);
glVertex3f(quad_x_size*(x+0) -1,quad_y_size*((rows-y-1)+0)-1,0.0);
glVertex3f(quad_x_size*(x+1) -1,quad_y_size*((rows-y-1)+0)-1,0.0);
glVertex3f(quad_x_size*(x+1) -1,quad_y_size*((rows-y-1)+1)-1,0.0);
glVertex3f(quad_x_size*(x+0) -1,quad_y_size*((rows-y-1)+1)-1,0.0);
glEnd();
            }
        }glFlush();
        glutSwapBuffers();
}
 int DeltaX = 0, DeltaY = 0;
 void draw_apples( );
void game_setup( );
void read_keyboard(unsigned char key, int x, int y) {
    

    switch(key) {
 
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
void idleFunc(){
    Sleep(100);
    make_board();
    draw_apples();
    draw_snake();
    game_setup();
    if(!is_game_over){
        snake_move(DeltaX,DeltaY);
    }
        glutPostRedisplay();
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
    make_board();
setup_snake();//place snake randomly
setup_apple();//place apple randomly
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
glutInitWindowSize(400,400);
glutCreateWindow("Snake Game");

glutDisplayFunc(display_function);
glutKeyboardFunc(read_keyboard);
glutIdleFunc(idleFunc);
glClearColor(0.0,0.0,0.0,0.1);
glutMainLoop();
return 0;
}

//compile it using 
//gcc main.c -o final -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
