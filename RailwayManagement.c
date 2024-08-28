#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20
#define MAX_GEN_LEN 6

typedef struct mynode {
    char name[MAX_NAME_LEN];
    char gen[MAX_GEN_LEN];
    int age;
    int seat;
    struct mynode* link;
} Node;

Node* start = NULL;

char source[MAX_NAME_LEN], des[MAX_NAME_LEN], train[40];
char station[40], cla[40];
int time1, time2, a[55];
const char* ticket_file = "tickets.txt";
const char* login_file = "logins.txt";

void details(int);
int seat(int);
int cal(int, int, int);
void bill(int, int);
void add_node(char lol[MAX_NAME_LEN], char der[MAX_GEN_LEN], int b, int seat);
void save_ticket(int, int);
void login();
void admin_login();
void view_tickets();
void search_tickets(char* username);
void retrieve_ticket();

void main() {
    int j, d;
    char choice;
    
    printf("Welcome to the Railway Reservation System\n");
    printf("1. Login\n2. Register\n3. Admin Login\n4. Retrieve Ticket\n");
    printf("Enter your choice: ");
    fflush(stdin);
    scanf("%c", &choice);

    switch (choice) {
        case '1':
        case '2':
            login();
            break;
        case '3':
            admin_login();
            return;  // Exit after admin operations
        case '4':
            retrieve_ticket();
            return;  // Exit after retrieving the ticket
        default:
            printf("Invalid choice. Exiting...\n");
            return;
    }

    printf("Enter Number Of Passengers: ");
    fflush(stdin);
    scanf("%d", &j);

    details(j);

    printf("Enter Source Station: ");
    fflush(stdin);
    fgets(source, MAX_NAME_LEN, stdin);
    source[strcspn(source, "\n")] = '\0';

    printf("Enter Destination Station: ");
    fflush(stdin);
    fgets(des, MAX_NAME_LEN, stdin);
    des[strcspn(des, "\n")] = '\0';

    printf("\t\tThe Following Trains Are Available.....\n");
    printf("\t\t1. Rajdhani Express.......10:00 a.m........Sealdah Station\n");
    printf("\t\t2. Satabdi Express.......05:00 p.m........Howrah Station\n");
    printf("\t\t3. Humsafar Express.......11:00 p.m........Kolkata Chitpur Station\n");
    printf("\t\t4. Garib-Rath Express.........05:00 p.m........Sealdah Station\n");
    printf("\t\t5. Duronto Express.........07:00 a.m.........Santraganchi Station\n");

    int train_choice;
    scanf("%d", &train_choice);
    switch (train_choice) {
        case 1:
            strcpy(train, "Rajdhani Express");
            strcpy(station, "Sealdah Station");
            time1 = 10;
            time2 = 00;
            d = cal(2099, 1560, j);
            break;
        case 2:
            strcpy(train, "Satabdi Express");
            strcpy(station, "Howrah Station");
            time1 = 05;
            time2 = 00;
            d = cal(1801, 981, j);
            break;
        case 3:
            strcpy(train, "Humsafar Express");
            strcpy(station, "Kolkata Chitpur Express");
            time1 = 11;
            time2 = 00;
            d = cal(2199, 1780, j);
            break;
        case 4:
            strcpy(train, "Garib-Rath Express");
            strcpy(station, "Sealdah Station");
            time1 = 05;
            time2 = 00;
            d = cal(1759, 1200, j);
            break;
        case 5:
            strcpy(train, "Duronto Express");
            strcpy(station, "Santraganchi Station");
            time1 = 07;
            time2 = 00;
            d = cal(2205, 1905, j);
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            return;
    }

    printf("Now Book Your Seats......\n");
    seat(j);
    save_ticket(d, j);
    bill(d, j);
}

int cal(int y1, int y2, int h) {
    int b, c, i, n;
    printf("\t\tEnter Your Choice......\n");
    printf("\t\t1. Sleeper Class....\n");
    printf("\t\t2. A.C Class.......\n");
    scanf("%d", &i);

    switch (i) {
        case 1:
            strcpy(cla, "Sleeper Class");
            b = y2 * h;
            c = b + (b * 0.18);
            break;
        case 2:
            printf("\t\tEnter Your Choice....\n");
            printf("\t\t1. 3A Class....\n");
            printf("\t\t2. 2A Class....\n");
            printf("\t\t3. 1st Class A.C.....\n");
            scanf("%d", &n);
            switch (n) {
                case 1:
                    strcpy(cla, "3A Class");
                    b = y1 * h;
                    c = b + (b * 0.18);
                    break;
                case 2:
                    strcpy(cla, "2A Class");
                    b = (y1 + 1000) * h;
                    c = b + (b * 0.18);
                    break;
                case 3:
                    strcpy(cla, "1st Class A.C.");
                    b = (y1 + 5000) * h;
                    c = b + (b * 0.18);
                    break;
                default:
                    printf("\t\tEnter Right Choice......\n");
            }
            break;
        default:
            printf("\t\tEnter Right Choice......\n");
    }
    return c;
}

void details(int k) {
    int i, a;
    char val[MAX_NAME_LEN], gen[MAX_GEN_LEN];

    for (i = 1; i <= k; i++) {
        printf("Enter The %dth Passenger Name: ", i);
        fflush(stdin);
        fgets(val, MAX_NAME_LEN, stdin);
        val[strcspn(val, "\n")] = '\0';

        printf("Enter The %dth Passenger Gender: ", i);
        fflush(stdin);
        fgets(gen, MAX_GEN_LEN, stdin);
        gen[strcspn(gen, "\n")] = '\0';

        printf("Enter the %dth Passenger Age: ", i);
        fflush(stdin);
        scanf("%d", &a);
        getchar();

        add_node(val, gen, a, 0);  // Seat number will be assigned later
    }
}

void add_node(char lol[MAX_NAME_LEN], char der[MAX_GEN_LEN], int b, int seat) {
    Node *newptr = NULL, *ptr;

    newptr = (Node*)malloc(sizeof(Node));
    strcpy(newptr->name, lol);
    strcpy(newptr->gen, der);
    newptr->age = b;
    newptr->seat = seat;
    newptr->link = NULL;

    if (start == NULL)
        start = newptr;
    else {
        ptr = start;
        while (ptr->link != NULL)
            ptr = ptr->link;
        ptr->link = newptr;
    }
}

int seat(int p) {
    int i;
    Node* ptr = start;

    printf("\t\t -:SEAT MATRIX:-\n");
    printf("\t(U) (M) (L) (L) (U)\n\n");
    printf("\t01 02 03 04 05\n\n");
    printf("\t06 07 08 09 10\n");
    printf("\t11 12 13 14 15\n\n");
    printf("\t16 17 18 19 20\n");
    printf("\t21 22 23 24 25\n\n");
    printf("\t26 27 28 29 30\n");
    printf("\t31 32 33 34 35\n\n");
    printf("\t36 37 38 39 40\n");
    printf("\t41 42 43 44 45\n\n");
    printf("\t46 47 48 49 50\n");

    for (i = 1; i <= p; i++) {
        printf("\t\tEnter Seat Number For %dth Passenger: ", i);
        scanf("%d", &a[i]);
        ptr->seat = a[i];
        ptr = ptr->link;
    }
    return 0;
}

void bill(int y, int p) {
    int i;
    Node* ptr = start;

    printf("\n\n");
    printf("\t\t\t******************************************\n");
    printf("\t\t\t**\tRAILWAY RESERVATION SYSTEM\t **\n");
    printf("\t\t\t******************************************\n");
    printf("\t\t\t* TRAIN:\t%s\n", train);
    printf("\t\t\t* BOARDING STATION:\t%s\n", station);
    printf("\t\t\t* DESTINATION STATION:\t%s\n", des);
    printf("\t\t\t* CLASS:\t%s\n", cla);
    printf("\t\t\t* TIME:\t%d:%d\n", time1, time2);
    printf("\t\t\t******************************************\n");
    printf("\t\t\t* DETAILS OF PASSENGERS *\n");

    for (i = 1; i <= p; i++) {
        printf("\t\t\t* %d. Name: %s | Gender: %s | Age: %d | Seat No: %d\n",
               i, ptr->name, ptr->gen, ptr->age, ptr->seat);
        ptr = ptr->link;
    }
    printf("\t\t\t******************************************\n");
    printf("\t\t\tTOTAL AMOUNT: Rs.%d Only\n", y);
    printf("\t\t\t******************************************\n");
    printf("\t\t\t**\tTHANK YOU! HAVE A SAFE JOURNEY\t **\n");
    printf("\t\t\t******************************************\n\n\n");
}

void save_ticket(int amount, int num_passengers) {
    FILE* file = fopen(ticket_file, "a");
    Node* ptr = start;

    fprintf(file, "******************************************\n");
    fprintf(file, "TRAIN: %s\n", train);
    fprintf(file, "BOARDING STATION: %s\n", station);
    fprintf(file, "DESTINATION STATION: %s\n", des);
    fprintf(file, "CLASS: %s\n", cla);
    fprintf(file, "TIME: %d:%d\n", time1, time2);
    fprintf(file, "******************************************\n");
    fprintf(file, "DETAILS OF PASSENGERS:\n");

    for (int i = 1; i <= num_passengers; i++) {
        fprintf(file, "%d. Name: %s | Gender: %s | Age: %d | Seat No: %d\n",
                i, ptr->name, ptr->gen, ptr->age, ptr->seat);
        ptr = ptr->link;
    }
    fprintf(file, "******************************************\n");
    fprintf(file, "TOTAL AMOUNT: Rs.%d Only\n", amount);
    fprintf(file, "******************************************\n\n\n");

    fclose(file);
}

void login() {
    char username[MAX_NAME_LEN], password[MAX_NAME_LEN];
    FILE* file;

    printf("Enter Username: ");
    fflush(stdin);
    fgets(username, MAX_NAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fflush(stdin);
    fgets(password, MAX_NAME_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    file = fopen(login_file, "r");
    if (file == NULL) {
        printf("Error: Cannot open login file.\n");
        return;
    }

    char file_username[MAX_NAME_LEN], file_password[MAX_NAME_LEN];
    int found = 0;

    while (fscanf(file, "%s %s", file_username, file_password) != EOF) {
        if (strcmp(username, file_username) == 0 && strcmp(password, file_password) == 0) {
            printf("Login Successful!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Login failed. Registering as a new user...\n");
        fclose(file);
        file = fopen(login_file, "a");
        fprintf(file, "%s %s\n", username, password);
        printf("Registration Successful! You can now log in.\n");
    }

    fclose(file);
}

void admin_login() {
    char admin_user[MAX_NAME_LEN], admin_pass[MAX_NAME_LEN];

    printf("Enter Admin Username: ");
    fflush(stdin);
    fgets(admin_user, MAX_NAME_LEN, stdin);
    admin_user[strcspn(admin_user, "\n")] = '\0';

    printf("Enter Admin Password: ");
    fflush(stdin);
    fgets(admin_pass, MAX_NAME_LEN, stdin);
    admin_pass[strcspn(admin_pass, "\n")] = '\0';

    if (strcmp(admin_user, "Admin") == 0 && strcmp(admin_pass, "Admin@1234") == 0) {
        printf("Admin Login Successful!\n");
        view_tickets();
    } else {
        printf("Invalid Admin Credentials. Exiting...\n");
    }
}

void view_tickets() {
    char choice, search_user[MAX_NAME_LEN];

    printf("1. View All Tickets\n2. Search Tickets by Username\nEnter your choice: ");
    fflush(stdin);
    scanf("%c", &choice);

    if (choice == '1') {
        FILE* file = fopen(ticket_file, "r");
        if (file == NULL) {
            printf("Error: Cannot open ticket file.\n");
            return;
        }

        char ch;
        while ((ch = fgetc(file)) != EOF)
            putchar(ch);

        fclose(file);
    } else if (choice == '2') {
        printf("Enter Username to Search: ");
        fflush(stdin);
        fgets(search_user, MAX_NAME_LEN, stdin);
        search_user[strcspn(search_user, "\n")] = '\0';
        search_tickets(search_user);
    } else {
        printf("Invalid choice. Exiting...\n");
    }
}

void search_tickets(char* username) {
    FILE* file = fopen(ticket_file, "r");
    char line[256];
    int found = 0;

    if (file == NULL) {
        printf("Error: Cannot open ticket file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, username)) {
            found = 1;
            printf("Ticket Found:\n%s", line);
            while (fgets(line, sizeof(line), file) && strncmp(line, "******************************************", 42) != 0) {
                printf("%s", line);
            }
            printf("\n");
        }
    }

    if (!found)
        printf("No tickets found for user: %s\n", username);

    fclose(file);
}

void retrieve_ticket() {
    char username[MAX_NAME_LEN];

    printf("Enter Username to Retrieve Ticket: ");
    fflush(stdin);
    fgets(username, MAX_NAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    search_tickets(username);
}
