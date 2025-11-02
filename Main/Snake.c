#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <GL/glut.h>
#include "snake_tileset.c"
//#include <ncurses/ncurses.h>
#define SNAKE_MAX_LEN 256
#define columns 25
#define logo 8
#define rows 25
#define apples 99
char board[columns*rows];//1D to that will become the game board
int is_game_over=0;// to track if the game is over
int game_over_timeout=0;
int delta_x=0, delta_y=0;
unsigned int textureId;
 
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



 
void draw_apples( );
void game_setup( );




void setup_snake(){
    snake_in_game.length=1;
    snake_in_game.Part[0].x=1+rand()%(columns-2);
    snake_in_game.Part[0].y=1+rand()%(rows-2);
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
 void display_function(){
    int x,y;
    static int last_delta_x=0, last_delta_y=0;
    glClear(GL_COLOR_BUFFER_BIT);
    static struct {
        int x1, y1, x2, y2;
    } tiles[] = {
        { 24, 16,  31, 23 }, // '#' Wall
        {  8, 24,  15, 33 }, // '0' Up
        {  0, 16,   7, 23 }, // '0' Down
        {  8,  8,  15, 15 }, // '0' Left
        {  0,  0,   7,  7 }, // '0' Right
        {  8, 16,  15, 23 }, // '~' Up
        {  0, 24,   7, 33 }, // '~' Down
        {  0,  8,   7, 15 }, // '~' Left
        {  8,  0,  15,  7 }, // '~' Right
        { 16,  0,  23,  7 }, // 'o' Snake Body 1
        { 24,  0,  31,  7 }, // 'o' Snake Body 2
        { 16, 16,  23, 23 }, // '+' Snake Food
        {  0, 32,   7, 39 }, // ' ' Empty
        { 24, 16,  31, 23 }, // 'X' Game Over tile
        { 0,  56, 104, 99 }, // Logo
        { 56,  5,  64, 18 }, // Digit 0
        { 72,  5,  80, 18 }, // Digit 1
        { 88,  5,  96, 18 }, // Digit 2
        { 104, 5,  112, 18 }, // Digit 3
        { 120, 5,  127, 18 }, // Digit 4
        { 56,  21,  64, 34 }, // Digit 5
        { 72,  21,  80, 34 }, // Digit 6
        { 88,  21,  96, 34 }, // Digit 7
        { 104, 21,  112, 34 }, // Digit 8
        { 120, 21,  127, 34 }, // Digit 9
    };
        for(y=0;y<rows;y++){
            for(x=0;x<columns;x++){
                int tileId=0;
                int ch = board[y*columns+x];
                float quad_x_size=2/(float)columns;
                float quad_y_size=2/(float)(rows+logo);

                switch(ch){
                    case'#':tileId = 0;
                    break;
                    case'0': if     ( delta_x == 0  && delta_y == -1 ) tileId = 2;
                    else if( delta_x == 0  && delta_y ==  1 ) tileId = 1;
                    else if( delta_x == -1 && delta_y ==  0 ) tileId = 3;
                    else if( delta_x ==  1 && delta_y ==  0 ) tileId = 4;
                    else tileId = 2;
                    break;
                    case '~':
                    // Dont display during a turn, it looks bad.
                    if( last_delta_x == delta_x && last_delta_y == delta_y ) {
                        if     ( delta_x == 0  && delta_y == -1 ) tileId = 6;
                        else if( delta_x == 0  && delta_y ==  1 ) tileId = 5;
                        else if( delta_x == -1 && delta_y ==  0 ) tileId = 7;
                        else if( delta_x ==  1 && delta_y ==  0 ) tileId = 8;
                        else tileId = 6;
                    }else{
                        tileId = 12;
                    }
                    last_delta_x = delta_x;
                    last_delta_y = delta_y;
                    break;
                    case'o':tileId = (x+y)%2 ? 9 : 10;break;

                    case'+':tileId = 11;
                    break;

                    case' ':tileId = 12;
                    break;

                    case'X':tileId = 13;
                    break;
                }
glBegin(GL_QUADS);
glTexCoord2f(tiles[tileId].x1/(float)snakeTileSet.width,(tiles[tileId].y1)/(float)snakeTileSet.height);
glVertex3f(quad_x_size*(x+0)-1,quad_y_size*((rows-y-1)+0)-1,0.0);
glTexCoord2f(tiles[tileId].x2/(float)snakeTileSet.width, (tiles[tileId].y1)/(float)snakeTileSet.height);
glVertex3f(quad_x_size * (x+1) -1, quad_y_size * ((rows-y-1)+0) -1, 0.0);
glTexCoord2f(tiles[tileId].x2/(float)snakeTileSet.width, (tiles[tileId].y2)/(float)snakeTileSet.height);
glVertex3f(quad_x_size * (x+1) -1, quad_y_size * ((rows-y-1)+1) -1, 0.0);
glTexCoord2f(tiles[tileId].x1/(float)snakeTileSet.width, (tiles[tileId].y2)/(float)snakeTileSet.height);
glVertex3f(quad_x_size * (x+0) -1, quad_y_size * ((rows-y-1)+1) -1, 0.0);
            glEnd();

            }
        }
            // Draw logo
    {
        int tileId = 14;
        glBegin(GL_QUADS);
            glTexCoord2f(tiles[tileId].x1/(float)snakeTileSet.width, (tiles[tileId].y1)/(float)snakeTileSet.height);
            glVertex3f(-1, 1.0, 0);
            glTexCoord2f(tiles[tileId].x2/(float)snakeTileSet.width, (tiles[tileId].y1)/(float)snakeTileSet.height);
            glVertex3f( 1, 1.0, 0);
            glTexCoord2f(tiles[tileId].x2/(float)snakeTileSet.width, (tiles[tileId].y2)/(float)snakeTileSet.height);
            glVertex3f( 1, 0.51, 0);
            glTexCoord2f(tiles[tileId].x1/(float)snakeTileSet.width, (tiles[tileId].y2)/(float)snakeTileSet.height);
            glVertex3f(-1, 0.51, 0);
        glEnd();
    }
    
    // Draw score
    {
        int i;
        int score = (snake_in_game.length-1) * 100;
        for(i=0; i<5; i++) {
            int digit = score - ((score / 10) * 10);
            int tileId = 15 + digit;
            score /= 10;
            glBegin(GL_QUADS);
                glTexCoord2f(tiles[tileId].x1/(float)snakeTileSet.width, (tiles[tileId].y1)/(float)snakeTileSet.height);
                glVertex3f( 0.05+(4-i)*0.17, 0.75, 0);
                glTexCoord2f(tiles[tileId].x2/(float)snakeTileSet.width, (tiles[tileId].y1)/(float)snakeTileSet.height);
                glVertex3f( 0.20+(4-i)*0.17, 0.75, 0);
                glTexCoord2f(tiles[tileId].x2/(float)snakeTileSet.width, (tiles[tileId].y2)/(float)snakeTileSet.height);
                glVertex3f( 0.20+(4-i)*0.17, 0.60, 0);
                glTexCoord2f(tiles[tileId].x1/(float)snakeTileSet.width, (tiles[tileId].y2)/(float)snakeTileSet.height);
                glVertex3f( 0.05+(4-i)*0.17, 0.60, 0);
            glEnd();
        }
    }
        
        glFlush();
        glutSwapBuffers();
}


void setup() {
    delta_x = 0;
    delta_y = 0;
    is_game_over = 0;
    game_over_timeout = 60;
    setup_apple();
    setup_snake();
    make_board();
    draw_apples();
    draw_snake();
}

void idleFunc(){
if (is_game_over){
    Sleep(1000/10.0);
    game_over_timeout--;
    if (game_over_timeout==0){
        setup();
    }
    make_board();
    draw_apples();
    draw_snake();

}else{
    Sleep(1000/(7+(snake_in_game.length/(float)apples)*10.0));
    make_board();
    draw_apples();
    draw_snake();
    game_setup();
    snake_move(delta_x,delta_y);

}
glutPostRedisplay();


}

void read_keyboard(unsigned char key, int x, int y) {
    if (!is_game_over){
        switch(key) {
 
       case'W':
        case 72:
        case 'w':delta_x =  0; delta_y = -1; break;
        case 80:
        case 'S':
        case 's': delta_x =  0; delta_y =  1; break;
        case 75:
        case 'A':
        case 'a': delta_x = -1; delta_y =  0; break;
        case 'D':
        case 77:
        case 'd': delta_x =  1; delta_y =  0; break;           
    }}
    switch (key)
    {
    case 'r':
        setup();    
        break;
    }

    
}
void specialFunc(int key, int x, int y) {
    if(!is_game_over) {
        switch(key) {
            case GLUT_KEY_UP:    read_keyboard('w', x, y); break;
            case GLUT_KEY_DOWN:  read_keyboard('s', x, y); break;
            case GLUT_KEY_LEFT:  read_keyboard('a', x, y); break;
            case GLUT_KEY_RIGHT: read_keyboard('d', x, y); break;
        }
    }
}

void init() {
    glEnable(GL_TEXTURE_2D);
        
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    glGenTextures(1, &textureId);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, snakeTileSet.width, snakeTileSet.height, 0, GL_RGB, GL_UNSIGNED_BYTE, snakeTileSet.pixel_data);
}





int main(int argc, char **argv){
   
    srand(time(0));
    
    setup();
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(columns*16, (rows+logo)*16);
    glutCreateWindow("Danger rope food hope");
    
    init();
    
    glutDisplayFunc(display_function);
    glutKeyboardFunc(read_keyboard);
    glutSpecialFunc(specialFunc);
    glutIdleFunc(idleFunc);

    glutMainLoop();
    
    glDeleteTextures(1, &textureId);
    
    return 0;
}

//compile it using 
//gcc Snake.c -o final -lfreeglut -lopengl32 -lglu32 -lwinmm -lgdi32
