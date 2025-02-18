#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define TOTAL_CLIENTS 100

// Struct Client
struct Client {
    int folio;
    char name[100];
    char lastname[100];
    char date[11];
    char email[50];
    char phone[11];
    char contact[100];
};

// Globals
struct Client clients[TOTAL_CLIENTS] = {
    {
      1234,
      "Diego",
      "Barajas",
      "05-02-2025",
      "desaubv@gmail.com",
      "3313993250",
      "Iris: 3331306076"
    },{
      2197,
      "Esau",
      "Velez",
      "05-02-2025",
      "desaubv@hotmail.com",
      "3313993250",
      "Victor: 3312129565"
    }
};
int current_clients = 2;

/* Functions */
// Add a new client
void add_client() {
    if(current_clients >= TOTAL_CLIENTS){
        error("Base de datos llena");
        return;
    }

    char name[100];
    char lastname[100];
    int folio;
    char date[20], day[3], year[5], month[3];
    char email[50];
    char phone[11];
    char contact[100];

    clear();
    printf("\n[ CLIENTE ] Agregar nuevo cliente.\n\n");

    // Generate folio
    srand(time(NULL));
    do{
        folio = 100 + rand() % (9999 - 100+1);
    }while(search_by_folio(folio) > -1);

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

        if(!is_empty(lastname)) break;
        printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    // DATE
    time_t t = time(NULL);
    struct tm *fecha = localtime(&t);

    strftime(date, sizeof(date), "%d-%m-%Y", fecha);

    // EMAIL
    while(1){
        flush();
        printf(" > Ingrese el email del cliente: ");
        gets(email);

        if(is_valid_email(email)) break;
        printf("\n[ ERROR ] El email ingresado no es valido.\n");
    }

    // PHONE
    while (1) {
        int i = 0;
        memset(phone, '_', 10);
        phone[10] = '\0';

        printf(" > Ingrese el numero de telefono movil (10 digitos): %s", phone);

        while (i < 10) {
            flush();
            char ch = getch();

            if (ch >= '0' && ch <= '9') {
                phone[i] = ch;
                printf("\r > Ingrese el numero de telefono movil (10 digitos): %s", phone);
                i++;
            } else if (ch == 8 && i > 0) {
                i--;
                phone[i] = '_';
                printf("\r > Ingrese el numero de telefono movil (10 digitos): %s", phone);
            }
        }

        printf("\n");

        if (is_number(phone) && strlen(phone) == 10) break;
        printf("\n[ ERROR ] El numero debe tener exactamente 10 digitos numericos.\n");
    }

    // CONTACT
    while(1){
        flush();
        printf(" > Ingrese la informacion de contacto de emergencia (libre): ");
        gets(contact);

        if(!is_empty(contact)) break;
        printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }

    clear();
    printf("\n[ CLIENTE ] Se agregara el siguiente cliente:\n");
    printf("[ ALTA ] FOLIO: #%d", folio);
    printf("\n\tNombre(s):   %s", name);
    printf("\n\tApellido(s): %s", lastname);
    printf("\n\tCelular:     %s", phone);
    printf("\n\tEmail:       %s", email);
    printf("\n\tContacto:    %s\n\n", contact);

    if(confirm("Desea continuar")){
        strcpy(clients[current_clients].name, name);
        strcpy(clients[current_clients].lastname, lastname);
        clients[current_clients].folio = folio;
        strcpy(clients[current_clients].date, date);
        strcpy(clients[current_clients].email, email);
        strcpy(clients[current_clients].phone, phone);
        strcpy(clients[current_clients].contact, contact);

        current_clients++;
        clear();
        success("Cliente registrado con exito!");
        show_client(current_clients-1);
        clear();
    }else{
        clear();
        info("Operacion cancelada");
        clear();
    }
}

// Print all regustered clients
void show_all_clients() {
    if(current_clients == 0){
        clear();
        info("No hay ningun cliente almacenado");
        clear();
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
    if(current_clients == 0){
        clear();
        warning("No hay ningun cliente registrado.");
        clear();
        return;
    }

    int i, index;
    char folio[10];

    clear();
    printf("\n[ BAJA ] Eliminar un cliente\n\n");

    for(i=0;i<3;i++){
        flush();

        printf(" > Ingrese el folio del cliente: ");
        gets(folio);

        if(is_number(folio) < 1) {
            printf("\n[ ERROR ] Debes ingresar un numero.\n");
            continue;
        }

        int f = atoi(folio);
        index = search_by_folio(f);

        if(index == -1){
            printf("\n[ ERROR ] No se encontro un cliente con el folio %d.\n", f);
            continue;
        }

        clear();
        printf("\n[ BAJA ] Folio: %d\n", f);
        printf("\tNombre(s):      %s\n", clients[index].name);
        printf("\tApellido(s):    %s\n", clients[index].lastname);
        printf("\tFecha registro: %s\n", clients[index].date);
        printf("\tCorreo:         %s\n", clients[index].email);
        printf("\tCelular:        %s\n", clients[index].phone);
        printf("\tContacto:       %s\n\n", clients[index].contact);

        if(confirm("Se eliminara el cliente, desea continuar?")){
            drop_client(index);
            clear();
            success("Se elimino el cliente con folio #%i", f);
            clear();
        }else{
            clear();
            info("Operacion cancelada");
            clear();
        }

        return;
    }

    clear();
    error("Has excedido el numero de intentos permitidos");
    clear();
}

// Update data from a client
void update_client() {

}

// Get index from a client
int search_by_folio(int folio){
    int i;

    for(i=0;i<current_clients;i++){
        if(clients[i].folio == folio) return i;
    }

    return -1;
}

// Show only one client
void show_client(int index){
    printf("[ CLIENTE ] Folio: %d\n", clients[index].folio);
    printf("\tNombre(s):      %s\n", clients[index].name);
    printf("\tApellido(s):    %s\n", clients[index].lastname);
    printf("\tFecha registro: %s\n", clients[index].date);
    printf("\tCorreo:         %s\n", clients[index].email);
    printf("\tCelular:        %s\n", clients[index].phone);
    printf("\tContacto:       %s\n\n", clients[index].contact);
}

int drop_client(int index) {
    if(index < 0 || index > current_clients){
        return 0;
    }

    int i;
    for(i=index;i<current_clients;i++){
        clients[i] = clients[i+1];
    }

    current_clients--;
}
