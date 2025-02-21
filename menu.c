#include <stdio.h>
#include <ctype.h>

// Print menu options in the console and returns the selected option
char main_menu(){
    flush();
    char opt;
    clear();

    printf("\n[ MENU ] Seleccione la opcion deseada");
    printf("\n\t[ C ] Cliente");
    printf("\n\t[ S ] Servicio");
    printf("\n\t[ P ] Pago");
    printf("\n\t[ A ] Almacen");
    printf("\n\t[ O ] Otro");
    printf("\n\t[ X ] Salir");

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
    printf("\n\t[ E ] Editar");
    printf("\n\t[ L ] Listado de clientes");
    printf("\n\t[ X ] Salir");

    printf("\n\n > Ingrese su opcion: ");
    scanf("%c", &opt);

    return tolower(opt);
}
