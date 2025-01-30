#include <stdio.h>
#include <windows.h>

// Fn prototypes
void clear();
void pause();
void error(const char *format, ...);
void success(const char *format, ...);
void warning(const char *format, ...);
void log(const char *format, ...);
int confirm(const char *format, ...);
void flush();
int is_empty(char value[]);
int is_empty(char value[]);
int is_valid_email(char email[]);

// Move the cursos to the selected coords
void gotoxy(int x, int y) {
    COORD coo;
    coo.X = x;
    coo.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coo);
}

// Clear console
void clear(){
    system("cls");
}

// Pause the excecution waitin for user press any key
void pause(){
    system("pause");
}

// Set font color
void color(char color){
    switch(color){
        case 'R': case 'r': system("color 04");
                break;

        case 'G': case 'g': system("color 0A");
                break;

        case 'B': case 'b': system("color 0B");
                break;

        case 'Y': case 'y': system("color 06");
                break;

        case 'W': case 'w': system("color 07");
                break;

        default: system("color 07");
    }
}

// Show an Error in console with formatted text
void error(const char *format, ...){
    color('R');

    va_list args;
    va_start(args, format);
    printf("\n[ ERROR ]: ");
    vprintf(format, args);  // Imprime el mensaje con formato
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
}

// Show success message in console with formatted text
void success(const char *format, ...){
    color('g');

    va_list args;
    va_start(args, format);
    printf("\n[ EXITO ] ");
    vprintf(format, args);  // Imprime el mensaje con formato
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
}

// Show Warning message in console with formatted text
void warning(const char *format, ...){
    color('y');

    va_list args;
    va_start(args, format);
    printf("\n[ ATENCION ] ");
    vprintf(format, args);  // Imprime el mensaje con formato
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
}

// Show Log message in console with formatted text
void info(const char *format, ...){
    color('b');

    va_list args;
    va_start(args, format);
    printf("\n[ SISTEMA ] ");
    vprintf(format, args);
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
}

// Make a question for a confirmation
int confirm(const char *format, ...){
    int i;
    char opt;

    va_list args;
    va_start(args, format);

    for(i=0;i<3;i++){
        flush();

        printf("\n[ CONFIRMAR ] ");
        vprintf(format, args);
        va_end(args);
        printf("\n\t[ A ] Aceptar (predeterminado)");
        printf("\n\t[ c ] Cancelar");
        printf("\n\n > Ingrese su opcion: ");
        scanf("%c", &opt);

        switch(opt){
            case 'A':case 'a':case '1': case '\n':
                return 1;

            case 'C':case 'c':case '0':
                return 0;

            default:
                warning("'%c' No es una opcion valida. %i intentos restantes.", opt, 2-i);
        }
    }

    error("Ha excedido el numero de intentos permitidos.");
    return 0;

}

// Flush input buffer
void flush(){
    fflush(stdin);
}

// Comprobe if a str is empty
int is_empty(char value[]){
    if (value[0] == '\0') return 1;
    return 0;
}

// Comprobe if a str is a number
int is_number(char value[]){
    int i;
    if (is_empty(value)) return -1;

    for (i = 0; value[i] != '\0'; i++) {
        if (!isdigit(value[i])) return 0;
    }
    return 1;
}

// Comprobe if an email is valid
int is_valid_email(char email[]){
    int length = strlen(email), i;
    int hasAt = 0, hasDot = 0;

    if(length < 5) return 0;

    for(i=0;i<length;i++){
        if(email[i] == '@' && i > 0) hasAt = 1;
        if(email[i] == '.' && i > 0 && i+1 < length) hasDot = 1;
    }

    return hasAt && hasDot;
}

