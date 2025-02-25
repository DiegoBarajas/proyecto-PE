#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define ESC 27

// Struct Client
struct Client {
    char name[100];
    char lastname[100];
    char date[11];
    char email[50];
    char phone[11];
    char contact[100];
};

// Struct Client Node
typedef struct {
    int folio;
    struct Client client;
    struct Client_Node *next;
} Client_Node;

// Head pointer
Client_Node *head = NULL;

Client_Node* find_node(int folio);

/* Functions */
// Add a new client
void add_client() {
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
    }while(exists_node(folio) > 0);

    // NAME
   while (1) {
        print_bottom(" PULSE [ESC] PARA CANCELAR");
        flush();
        printf(" > Ingrese el/los nombre/s del cliente: ");

        int i = 0;
        char ch;

        // Get user input
        while ((ch = getch()) != '\r') {
            if (ch == ESC) { // If ESC key pressed, return
                return 0;
            }
            if (ch == '\b' && i > 0) { // Backspace handler
                printf("\b \b");
                i--;
            } else if (i < sizeof(name) - 1) { // Adding chars on name
                name[i++] = ch;
                printf("%c", ch);
            }
        }
        name[i] = '\0';

        printf("\n");

        if (!is_empty(name)) break;
        printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
    }
    print_bottom("                                      ");

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
        struct Client new_client;
        strcpy(new_client.name, name);
        strcpy(new_client.lastname, lastname);
        strcpy(new_client.date, date);
        strcpy(new_client.email, email);
        strcpy(new_client.phone, phone);
        strcpy(new_client.contact, contact);

        // Create new client node
        add_client_node(folio, new_client);

        clear();
        success("Cliente registrado con exito!");
        show_last_client();
        clear();
    }else{
        clear();
        info("Operacion cancelada");
        clear();
    }
}

// Print all regustered clients
void show_all_clients() {
    if(!head){
        clear();
        warning("No hay ningun cliente registrado.");
        clear();
        return;
    }

    Client_Node *current = head;
    clear();

    while (current != NULL) {
        printf("[ CLIENTE ] Folio: %d\n", current->folio);
        printf("\tNombre(s):      %s\n", current->client.name);
        printf("\tApellido(s):    %s\n", current->client.lastname);
        printf("\tFecha registro: %s\n", current->client.date);
        printf("\tCorreo:         %s\n", current->client.email);
        printf("\tCelular:        %s\n", current->client.phone);
        printf("\tContacto:       %s\n\n", current->client.contact);
        current = current->next;
    }

    pause();
}

// Delete a client
void delete_client() {
    if(!head){
        clear();
        warning("No hay ningun cliente registrado.");
        clear();
        return;
    }

    int i, index;
    char folio[10];

    clear();
    printf("\n[ BAJA ] Eliminar un cliente\n\n");

    // Getting folio
    for(i=0;i<3;i++){
        flush();
        while (1) {
            print_bottom(" PULSE [ESC] PARA CANCELAR");
            flush();
            printf(" > Ingrese el folio del cliente: ");

            int i = 0;
            char ch;

            // Get user input
            while ((ch = getch()) != '\r') {
                if (ch == ESC) { // If ESC key pressed, return
                    return 0;
                }
                if (ch == '\b' && i > 0) { // Backspace handler
                    printf("\b \b");
                    i--;
                } else if (i < sizeof(folio) - 1) { // Adding chars on folio
                    folio[i++] = ch;
                    printf("%c", ch);
                }
            }
            folio[i] = '\0';

            printf("\n");

            if (!is_empty(folio)) break;
            printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
        }
        print_bottom("                                      ");

        if(is_number(folio) < 1) {
            printf("\n[ ERROR ] Debes ingresar un numero.\n");
            continue;
        }

        int f = atoi(folio);
        if(exists_node(f) == 0){
            printf("\n[ ERROR ] No se encontro un cliente con el folio %d.\n", f);
            continue;
        }

        clear();
        printf("[ BAJA ]\n");
        show_client(f);

        if(confirm("Se eliminara el cliente, desea continuar?")){
            drop_client_node(f);
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
    if(!head) {
        clear();
        warning("No hay ningun cliente registrado.");
        clear();
        return;
    }

    int i;
    char folio[10];

    clear();
    printf("\n[ ACTUALIZAR ] Modificar un cliente\n\n");

    for(i=0; i<3; i++) {
        flush();
        while (1) {
            print_bottom(" PULSE [ESC] PARA CANCELAR");
            flush();
            printf(" > Ingrese el folio del cliente: ");

            int i = 0;
            char ch;

            // Get user input
            while ((ch = getch()) != '\r') {
                if (ch == ESC) { // If ESC key pressed, return
                    return 0;
                }
                if (ch == '\b' && i > 0) { // Backspace handler
                    printf("\b \b");
                    i--;
                } else if (i < sizeof(folio) - 1) { // Adding chars on folio
                    folio[i++] = ch;
                    printf("%c", ch);
                }
            }
            folio[i] = '\0';

            printf("\n");

            if (!is_empty(folio)) break;
            printf("\n[ ERROR ] Necesitas ingresar un valor.\n");
        }
        print_bottom("                                      ");

        if(is_number(folio) < 1) {
            printf("\n[ ERROR ] Debes ingresar un numero.\n");
            continue;
        }

        int f = atoi(folio);
        Client_Node *client_node = find_node(f);

        if(client_node == NULL) {
            printf("\n[ ERROR ] No se encontro un cliente con el folio %d.\n", f);
            continue;
        }

        clear();
        printf("\n[ CLIENTE ACTUAL ]\n");
        show_client(f);  // Show the current data

        char name[100], lastname[100], email[50], phone[11], contact[100];
        int phone_changed = 0;

        // Asking for name
        printf("\n[ Nombre actual: %s ]\n", client_node->client.name);
        printf(" > Ingrese el nuevo nombre (dejar vacio para conservar): ");
        gets(name);

        // Asking for lastname
        printf("\n[ Apellido actual: %s ]\n", client_node->client.lastname);
        printf(" > Ingrese el nuevo apellido (dejar vacio para conservar): ");
        gets(lastname);

        // Asking for email
        printf("\n[ Email actual: %s ]\n", client_node->client.email);
        printf(" > Ingrese el nuevo email (dejar vacio para conservar): ");
        gets(email);

        // Asking for phone
        printf("\n[ Telefono actual: %s ]\n", client_node->client.phone);
        while (1) {
            int i = 0;
            memset(phone, '_', 10);
            phone[10] = '\0';

            printf(" > Ingrese el nuevo numero de telefono movil (10 digitos): %s", phone);

            while (i < 10) {
                flush();
                char ch = getch();

                if((ch == 13) && (i == 0)){
                    phone_changed = 0;
                    break;
                }
                if (ch >= '0' && ch <= '9') {
                    phone[i] = ch;
                    printf("\r > Ingrese nuevo el numero de telefono movil (10 digitos): %s", phone);
                    i++;
                } else if (ch == 8 && i > 0) {
                    i--;
                    phone[i] = '_';
                    printf("\r > Ingrese nuevo el numero de telefono movil (10 digitos): %s", phone);
                }
            }

            printf("\n");

            if (!phone_changed) break;
            if (is_number(phone) && strlen(phone) == 10) break;
            printf("\n[ ERROR ] El numero debe tener exactamente 10 digitos numericos.\n");
        }

        // Asking for contact information
        printf("\n[ Contacto actual: %s ]\n", client_node->client.contact);
        printf(" > Ingrese la nueva informacion de contacto (dejar vacio para conservar): ");
        gets(contact);

        clear();
        printf("\n[ CONFIRMACION DE CAMBIOS ]\n");
        printf(" [  Nombre  ] %s -> %s\n", client_node->client.name, is_empty(name) ? client_node->client.name : name);
        printf(" [ Apellido ] %s -> %s\n", client_node->client.lastname, is_empty(lastname) ? client_node->client.lastname : lastname);
        printf(" [   Email  ] %s -> %s\n", client_node->client.email, is_valid_email(email) ? email : client_node->client.email);
        printf(" [ Telefono ] %s -> %s\n", client_node->client.phone, (is_number(phone) && strlen(phone) == 10) ? phone : client_node->client.phone);
        printf(" [ Contacto ] %s -> %s\n", client_node->client.contact, is_empty(contact) ? client_node->client.contact : contact);

        if(confirm("Desea aplicar los cambios?")) {
            if(!is_empty(name)) strcpy(client_node->client.name, name);
            if(!is_empty(lastname)) strcpy(client_node->client.lastname, lastname);
            if(is_valid_email(email)) strcpy(client_node->client.email, email);
            if(is_number(phone) && strlen(phone) == 10) strcpy(client_node->client.phone, phone);
            if(!is_empty(contact)) strcpy(client_node->client.contact, contact);

            clear();
            success("Cliente actualizado con exito!");
            show_client(f);
        } else {
            clear();
            warning("Operacion cancelada, no se realizaron cambios.");
        }

        clear();
        return;
    }

    clear();
    error("Has excedido el numero de intentos permitidos");
    clear();
}

/* NODES FUNCTIONS */
// Function to add a new node
void add_client_node(int folio, struct Client client) {
    Client_Node *new_node = (Client_Node *)malloc(sizeof(Client_Node));
    new_node->folio = folio;
    new_node->client = client;
    new_node->next = head;

    head = new_node;
}

// Function to delete a node by folio
void drop_client_node(int folio) {
    Client_Node *current = head;
    Client_Node *prev = NULL;

    while (current != NULL && current->folio != folio) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return; // Not found

    if (prev == NULL) {
        head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
}


// Show only one client
void show_client(int folio){
    Client_Node *current = head;
    while (current != NULL) {
        if (current->folio == folio) {
            printf("[ CLIENTE ] Folio: %d\n", current->folio);
            printf("\tNombre(s):      %s\n", current->client.name);
            printf("\tApellido(s):    %s\n", current->client.lastname);
            printf("\tFecha registro: %s\n", current->client.date);
            printf("\tCorreo:         %s\n", current->client.email);
            printf("\tCelular:        %s\n", current->client.phone);
            printf("\tContacto:       %s\n\n", current->client.contact);
            return;
        }
        current = current->next;
    }
    return error("No se encontro el cliente");
}

// Show lastone client
void show_last_client(){
    if(!head) return error("No se encontro el cliente");
    printf("[ CLIENTE ] Folio: %d\n", head->folio);
    printf("\tNombre(s):      %s\n", head->client.name);
    printf("\tApellido(s):    %s\n", head->client.lastname);
    printf("\tFecha registro: %s\n", head->client.date);
    printf("\tCorreo:         %s\n", head->client.email);
    printf("\tCelular:        %s\n", head->client.phone);
    printf("\tContacto:       %s\n\n", head->client.contact);
}

// Comprobe id exists a client by folio
int exists_node(int folio) {
    Client_Node *current = head;

    while (current != NULL) {
        if (current->folio == folio) return 1;
        current = current->next;
    }

    return 0;
}

// Find a node by folio
Client_Node* find_node(int folio) {
    Client_Node *current = head;

    while (current != NULL) {
        if (current->folio == folio) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

void add_dev_clients() {
    struct Client c1 = {
      "Diego",
      "Barajas",
      "05-02-2025",
      "desaubv@gmail.com",
      "3313993250",
      "Iris: 3331306076"
    }, c2 = {
      "Esau",
      "Velez",
      "07-02-2025",
      "desaubv2@gmail.com",
      "3326150831",
      "Jonas: 3331223076"
    }, c3 = {
      "Lizeth",
      "Velazquez",
      "15-02-2025",
      "lizethvelazquez49@gmail.com",
      "3331209909",
      "Angelica: angelica@gmail.com"
    };

    add_client_node(1234, c1);
    add_client_node(1487, c2);
    add_client_node(831, c3);
}
