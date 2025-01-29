#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>

// Array of String that contains the logo
char logo_chars[][69] =
    {
        "  ______     _______                  ______                         ",
        " (  __  \\   (  ____ \\                / ____ \\                        ",
        " | (  \\  )  | (    \\/  __       __  | (    \\/                        ",
        " | |   ) |  | (__      \\ \\     / /  | |_____        __       _    _  ",
        " | |   | |  |  __)      \\ \\   / /    \\_____  \\     /  \\     | |  | | ",
        " | |   ) |  | (          \\ \\_/ /            | |   / /\\ \\    | |  | | ",
        " | (__/  )  | (____/\\     \\   /      / \\___/ /   /  __  \\   | |__| | ",
        " (______/   (_______/      \\_/       \\______/   /_/    \\_\\   \\____/  "
    };

// Move the cursos to the selected coords
void gotoxy(int x, int y) {
    COORD coo;
    coo.X = x;
    coo.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coo);
}

// Show the logo in the console and wait for 10 seconds
void draw_logo(){
    int r, c, i;
    int rows = sizeof( logo_chars ) / sizeof(logo_chars[0]);
    int cols = sizeof( logo_chars[0] )  / sizeof( logo_chars[0][0] );

    int current_row = 1, current_col = 5;

    for(r=0;r<rows;r++){
        gotoxy(current_col, current_row);
        for(c=0;c<cols;c++){
            printf("%c", logo_chars[r][c]);
        }
        current_row++;
    }

    int timer = 5;
    for(i=0;i<timer;i++){
        gotoxy(current_col, current_row+1);
        printf("====================== ");
        printf("Inicializando en %i... ", timer-i);
        printf("======================\n");
        sleep(1);
    }

    clear();
}
