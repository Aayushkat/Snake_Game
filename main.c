#include <stdio.h>
#define rows 20
#define columns 20


char board[rows * columns];

void fill_board(){
    int x,y;
    for(y=0;y<rows;y++){
        for(x=0;x<columns;x++){
            if(x==0||y==0||x==columns-1||y==columns-1){
                board[y*columns+x]='#';
            }

        }
    }

}

void print_board(){
        int x,y;
    for(y=0;y<rows;y++){
        for(x=0;x<columns;x++){
            if(x==0||y==0||x==columns-1||y==columns-1){
                putchar(board[y*columns+x]);
            }
            putchar('\n');

        }
    }

}

    int
    main()
{

    return 0;
}