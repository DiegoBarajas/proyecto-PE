#include <stdio.h>
#include <ctype.h>

// Print menu options in the console and returns the selected option
char main_menu(){
    flush();
    char opt;
    clear();

    printf("\n[ MENU ] Seleccione la opcion deseada");
    printf("\n\t[ A ] Cliente");
    printf("\n\t[ B ] Servicio");
    printf("\n\t[ C ] Pago");
    printf("\n\t[ D ] Almacen");
    printf("\n\t[ E ] Otro");
    printf("\n\t[ F ] Salir");

    printf("\n\n> Ingrese su opcion: ");
    scanf("%c", &opt);

    return tolower(opt);
}

// Print menu options in the console and returns the selected option
char client_menu(){
    flush();
    clear();
    char opt;

    printf("\n[ CLIENTE ] Seleccione la opcion deseada");
    printf("\n\t[ A ] Alta");
    printf("\n\t[ B ] Baja");
    printf("\n\t[ C ] Ver todos los clientes");
    printf("\n\t[ E ] Editar");
    printf("\n\t[ S ] Salir");

    printf("\n\n > Ingrese su opcion: ");
    scanf("%c", &opt);

    return tolower(opt);
}
