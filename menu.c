#include <stdio.h>
#include <ctype.h>

// Print menu options in the console and returns the selected option
char main_menu(){
    flush();
    char opt;

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
