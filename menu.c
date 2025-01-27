#include <stdio.h>
#include <ctype.h>

// Print menu options in the console and returns the selected option
char main_menu(){
    flush();
    char opt;

    printf("\n[ MENU ] Seleccione la opcion deseada");
    printf("\n [ A ] Cliente");
    printf("\n [ B ] Servicio");
    printf("\n [ C ] Pago");
    printf("\n [ D ] Almacen");
    printf("\n [ E ] Otro");
    printf("\n [ F ] Salir");

    printf("\n\n\t> Ingrese su opcion: ");
    scanf("%c", &opt);

    return tolower(opt);
}
