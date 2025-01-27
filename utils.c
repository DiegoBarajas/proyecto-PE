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
    clear();
    color('R');

    va_list args;
    va_start(args, format);
    printf("\t[ ERROR ]: ");
    vprintf(format, args);  // Imprime el mensaje con formato
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
    clear();
}

// Show success message in console with formatted text
void success(const char *format, ...){
    clear();
    color('g');

    va_list args;
    va_start(args, format);
    printf("\t[ EXITO ] ");
    vprintf(format, args);  // Imprime el mensaje con formato
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
    clear();
}

// Show Warning message in console with formatted text
void warning(const char *format, ...){
    clear();
    color('y');

    va_list args;
    va_start(args, format);
    printf("\t[ ATENCION ] ");
    vprintf(format, args);  // Imprime el mensaje con formato
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
    clear();
}



// Show Log message in console with formatted text
void info(const char *format, ...){
    clear();
    color('b');

    va_list args;
    va_start(args, format);
    printf("\t[ SISTEMA ] ");
    vprintf(format, args);
    va_end(args);

    printf("\n\n");
    pause();
    color('W');
    clear();
}

// Make a question for a confirmation
int confirm(const char *format, ...){
    int i;
    char opt;

    va_list args;
    va_start(args, format);

    for(i=0;i<3;i++){
        clear();
        flush();

        printf("[ ATENCION ] ");
        vprintf(format, args);
        va_end(args);
        printf("\n   [ S/Y/A/1 ] Aceptar");
        printf("\n   [ N/C/X/0 ] Cancelar");
        printf("\n\n\t> Ingrese su opcion: ");
        scanf("%c", &opt);

        switch(opt){
            case 'S':case 's':case 'y':case 'Y':case 'a':case 'A':case '1':
                return 1;

            case 'N':case 'n':case 'C':case 'c':case 'x':case 'X':case '0':
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

