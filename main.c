#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <pthread.h>


void client();
void service();
void payment();
void storage();
void other();

void *showClock(){
    while(1){
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        int initial_x = csbi.dwCursorPosition.X;
        int initial_y = csbi.dwCursorPosition.Y;
        time_t now = time(NULL);
        struct tm *local = localtime(&now);

        gotoxy(getConsoleWidth() - 12, 0);
        printf("[ %02d:%02d:%02d ]", local->tm_hour, local->tm_min, local->tm_sec);
        gotoxy(getConsoleWidth() - 12, 1);
        printf(" %02d-%02d-%04d ", local->tm_mday, local->tm_mon+1, local->tm_year+1900);
        printf("\n");

        gotoxy(initial_x, initial_y);

        sleep(1);
    }
}



void main(){
    pthread_t thread_id;

    draw_logo();
    pthread_create(&thread_id, NULL, showClock, NULL);

    int loggued = login();
    if(!loggued){
        clear();
        warning("Ha excedido el limite de intentos permitidos");
        clear();
        return;
    }

    char opt;

    while(1){
        opt = main_menu();

        switch(opt){
            case 'a': client();
                break;


            case 'b': service();
                break;


            case 'c': payment();
                break;


            case 'd': storage();
                break;


            case 'e': other();
                break;


            case 'f':
                clear();
                if(confirm("Esta seguro que desea salir?")){
                    clear();
                    info("Cerrando...\n            Hasta la proxima.");
                    return;
                }
                clear();
                info("Operacion cancelada.");
                clear();
                break;

            default:
                clear();
                warning("'%c' No es una opcion valida", opt);
                clear();

        }
    }

}


void _main(){
    client();
}

void client() {
    char opt;
    int tries = 0;

    while (1){
        if(tries > 2) return error("Ha excedido el limite de intentos permitidos. Volviendo al menu principal");
        opt = client_menu();

        switch(opt){
            case 'a': add_client();
                tries = 0;
                break;

            case 'b': delete_client();
                tries = 0;
                break;

            case 'c': show_all_clients();
                tries = 0;
                break;

            case 'd': update_client();
                tries = 0;
                break;

            case 's':
                    clear();
                    info("Volviendo al menu principal.");
                    clear();
                return;

            default:
                clear();
                warning("'%c' No es una opcion valida", opt);
                clear();
                tries++;
        }
    }
}

void service() {

}
void payment() {

}

void storage() {

}

void other() {

}

