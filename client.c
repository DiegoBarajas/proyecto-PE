#include <stdio.h>
#include <ctype.h>

#define TOTAL_CLIENTS 100

// Struct Client
struct Client {
    char name[100];
    char lastname[100];
    char account[16];
    char date[20];
    char email[50];
    char phone[10];
    char telephone[10];
    char contact[10];
    char folios[100];
};

// Globals
struct Client clients[TOTAL_CLIENTS];
int current_clients = 0;

/* Functions */
// Add a new client
void add_client() {
    if(current_clients >= TOTAL_CLIENTS){
        error("Base de datos llena");
        return;
    }

    char name[100];
    char lastname[100];
    char account[16];
    char date[20], day[3], year[5], month[3];
    char email[50];
    char phone[11];
    char telephone[11];
    char contact[11];
    char folios[100];

    clear();
    printf("\n[ CLIENTE ] Agregar nuevo cliente.\n\n");

    // NAME
    while(1){
        flush();
        printf(" > Ingrese el/los nombre/s del cliente: ");
        gets(name);

        if(!is_empty(name)) break;
        printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    // LASTNAME
    while(1){
        flush();
        printf(" > Ingrese el/los apellido/s del cliente: ");
        gets(lastname);

        if(!is_empty(name)) break;
        printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    // ACCOUNT
    while(1){
        flush();
        printf(" > Ingrese el numero de cuenta del cliente: ");
        gets(account);

        if(search_by_account(account) >= 0){
            printf("\n[ ERROR ] Ese numero de cuenta ya fue registrado.\n");
            continue;
        }
        if(is_number(account) == 1) break;
        else if(is_number(account) == 0) printf("\n[ ERROR ] Solo puedes ingresar numeros.\n");
        else printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    // DATE
    while(1){
        flush();
        printf(" > Ingrese el dia de registro (dd): ");
        scanf("%s", &day);

        if(is_number(day) == 1){
            int dd = atoi(day);
            if(dd <= 0 || dd > 31) printf("\n[ ERROR ] El dia debe ser un valor mayor que 0 y menor o igual que 31.\n");
            else break;
        }
        else if(is_number(day) == 0) printf("\n[ ERROR ] Solo puedes ingresar numeros.\n");
        else printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    while(1){
        flush();
        printf(" > Ingrese el mes de registro (mm): ");
        scanf("%s", &month);

        if(is_number(month) == 1){
            int mm = atoi(month);
            if(mm <= 0 || mm > 12) printf("\n[ ERROR ] El mes debe ser un valor mayor que 0 y menor o igual que 12.\n");
            else break;
        }
        else if(is_number(month) == 0) printf("\n[ ERROR ] Solo puedes ingresar numeros.\n");
        else printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    while(1){
        flush();
        printf(" > Ingrese el a%co de registro (aaaa): ", 164);
        scanf("%s", &year);

        if(is_number(year) == 1){
            int yy = atoi(year);
            if(yy <= 1900) printf("\n[ ERROR ] El a%co es incorrecto, asegurese que este sea correcto.\n", 164);
            else break;
        }
        else if(is_number(year) == 0) printf("\n[ ERROR ] Solo puedes ingresar numeros.\n");
        else printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    strcpy(date, day);
    strcat(date, "-");
    strcat(date, month);
    strcat(date, "-");
    strcat(date, year);

    // EMAIL
    while(1){
        flush();
        printf(" > Ingrese el email del cliente: ");
        gets(email);

        if(is_valid_email(email)) break;
        printf("\n[ ERROR ] El email ingresado no es valido.\n");
    }

    // PHONE
    while(1){
        flush();
        printf(" > Ingrese el numero de telefono movil (10 digitos): ");
        gets(phone);

        if(is_number(phone) == 1 && strlen(phone) == 10) break;
        printf("\n[ ERROR ] El numero debe tener exactamente 10 digitos numericos.\n");
    }

    // TELEPHONE (OPCIONAL)
    flush();
    printf(" > Ingrese el numero de telefono fijo (opcional, 10 digitos numericos): ");
    gets(telephone);
    if(strlen(telephone) > 0 && (is_number(telephone) == 0 || strlen(telephone) != 10)){
        printf("\n[ ERROR ] El numero debe tener exactamente 10 digitos o estar vacio.\n");
        telephone[0] = '\0'; // Limpiar el valor si es incorrecto
    }

    // CONTACT
    while(1){
        flush();
        printf(" > Ingrese el numero de contacto de emergencia (10 digitos numericos): ");
        gets(contact);

        if(is_number(contact) == 1 && strlen(contact) == 10) break;
        printf("\n[ ERROR ] El numero debe tener exactamente 10 digitos numericos.\n");
    }

    strcpy(clients[current_clients].name, name);
    strcpy(clients[current_clients].lastname, lastname);
    strcpy(clients[current_clients].account, account);
    strcpy(clients[current_clients].date, date);
    strcpy(clients[current_clients].email, email);
    strcpy(clients[current_clients].phone, phone);
    strcpy(clients[current_clients].telephone, telephone);
    strcpy(clients[current_clients].contact, contact);

    current_clients++;
    success("Cliente registrado con exito!");
}

// Print all regustered clients
void show_all_clients() {
    if(current_clients == 0){
        info("No hay ningun cliente almacenado");
        return;
    }

    int i;
    clear();
    for(i=0;i<current_clients;i++){
        show_client(i);
    }

    pause();
}

// Delete a client
void delete_client() {

}

// Update data from a client
void update_client() {
}

// Get index from a client
int search_by_account(char account[]){
    int i;

    for(i=0;i<current_clients;i++){
        if(strcmp(clients[i].account, account) == 0) return i;
    }

    return -1;
}

// Show only one client
void show_client(int index){
    printf("[ CLIENTE ] #%i\n", index+1);
    printf("\tNombre(s):      %s\n", clients[index].name);
    printf("\tApellido(s):    %s\n", clients[index].lastname);
    printf("\tNum. Cuenta:    %s\n", clients[index].account);
    printf("\tFecha registro: %s\n", clients[index].date);
    printf("\tCorreo:         %s\n", clients[index].email);
    printf("\tCelular:        %s\n", clients[index].phone);
    printf("\tTelefono:       %s\n", clients[index].telephone);
    printf("\tContacto:       %s\n\n", clients[index].contact);
}
