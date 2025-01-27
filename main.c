#include <stdio.h>
#include <windows.h>

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
            case 'a':
                break;


            case 'b':
                break;


            case 'c':
                break;


            case 'd':
                break;


            case 'e':
                break;


            case 'f':
                if(confirm("Esta seguro que desea salir?")){
                    clear();
                    info("Cerrando...\n\t            Hasta la proxima.");
                    return;
                }
                info("Operacion cancelada.");
                break;

            default:
                warning("'%c' No es una opcion valida", opt);

        }
    }

}
