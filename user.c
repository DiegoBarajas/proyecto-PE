#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <unistd.h>

// Fn prototypes
int find_user(char user[]);

// Struct of User template
struct User{
    char user[50];
    char passwd[50];
};

// Array of 3 users
struct User users[3] = {
    {"Admin", "secret"},
    {"diego", "2004"},
    {"guest", "algo"}
};

/* Function to sign in into the system
        returns 1 if user loggued in
        returns 0 if can't loggued in
*/
int login(){
    char user[50], passwd[50];
    int i;

    for(i=0;i<3;i++){
        clear();

        printf("Bienvenido usuario, favor de iniciar sesion.\n");
        printf("[ Intentos restantes: %i ]", 3-i);

        if(i==2) printf(" - ULTIMO INTENTO\n\n");
        else printf("\n\n");

        printf(" > Ingrese su usuario: ");
        scanf("%s", &user);

        printf(" > Ingrese su contrase%ca: ", 164);
        scanf("%s", &passwd);

        int usr_indx = find_user(user);
        if(usr_indx < 0){
            clear();
            error("Usuario no encontrado");
            clear();
            continue;
        }

        if(strcmp(passwd, users[usr_indx].passwd) == 0){
            clear();
            success("Acceso concedido.\n          Bienvenido %s", user);
            clear();

            return 1;
        }else{
            clear();
            error("Contrase%ca incorrecta", 164);
            clear();
        }
    }

    return 0;
}

// Get index of user searching by name
int find_user(char user[]){
    int length = sizeof(users)/sizeof(users[0]), i;
    for(i=0;i<length;i++){
        if(strcmp(users[i].user, user) == 0){
            return i;
        }
    }

    return -1;
}
