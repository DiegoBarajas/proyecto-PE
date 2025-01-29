#include <stdio.h>
#include <ctype.h>

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
struct Client clients[100];
int total_clients = 0;

void add_client() {
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

        if(search_by_account(account) > 0){
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
        printf(" > Ingrese el dia de registro: ");
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
        printf(" > Ingrese el mes de registro: ");
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
        printf(" > Ingrese el a%co de registro: ", 164);
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

    strcpy(clients[total_clients].name, name);
    strcpy(clients[total_clients].lastname, lastname);
    strcpy(clients[total_clients].account, account);
    strcpy(clients[total_clients].date, date);
    strcpy(clients[total_clients].email, email);
    strcpy(clients[total_clients].phone, phone);
    strcpy(clients[total_clients].telephone, telephone);
    strcpy(clients[total_clients].contact, contact);

    total_clients++;
    success("Cliente registrado con exito!");
}

void delete_client() {

}

void update_client() {
}

int search_by_account(char account[]){
    int i;

    for(i=0;i<total_clients;i++){
        if(strcmp(clients[i].account, account) == 0) return i;
    }

    return -1;
}

void show_client(int index){
    printf("\n\n[ CLIENTE ] #%i\n\n", index);
    printf("Nombre(s): %s\n", clients[index].name);
    printf("Apellido(s): %s\n", clients[index].lastname);
    printf("Numero de cuenta: %s\n", clients[index].account);
    printf("Fecha de registro: %s\n", clients[index].date);
    printf("Correo: %s\n", clients[index].email);
    printf("Celular: %s\n", clients[index].phone);
    printf("Telefono: %s\n", clients[index].telephone);
    printf("Contacto: %s\n\n\n", clients[index].contact);
}
