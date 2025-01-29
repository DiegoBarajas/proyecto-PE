#include <stdio.h>
#include <windows.h>

void client();
void service();
void payment();
void storage();
void other();

void main(){
    draw_logo();

    int loggued = login();
    if(!loggued){
        warning("Ha excedido el limite de intentos permitidos");
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
                if(confirm("Esta seguro que desea salir?")){
                    clear();
                    info("Cerrando...\n            Hasta la proxima.");
                    return;
                }
                info("Operacion cancelada.");
                break;

            default:
                warning("'%c' No es una opcion valida", opt);

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

            case 's': info("Volviendo al menu principal.");
                return;

            default:
                warning("'%c' No es una opcion valida", opt);
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

