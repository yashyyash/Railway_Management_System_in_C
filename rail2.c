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
const char* admin_username = "Admin";
const char* admin_password = "Admin@1234";
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
    printf("\t\t\t* BOARDING TIME:\t%d: %d\n", time1, time2);
    printf("\t\t\t* TOTAL FARE:\t%d Rs\n", y);
    printf("\t\t\t*........................................*\n");
    printf("\t\t\t* PASSENGERS:\n");

    for (i = 1; i <= p; i++) {
        printf("\t\t\t\t%d. %s\n", i, ptr->name);
        printf("\t\t\t\t\tGender:\t%s\n", ptr->gen);
        printf("\t\t\t\t\tAge:\t%d\n", ptr->age);
        printf("\t\t\t\t\tSeat Number:\t%d\n", ptr->seat);
        ptr = ptr->link;
    }

    printf("\t\t\t*........................................*\n");
    printf("\t\t\t******************************************\n\n\n");
    printf("\t\t\t\tThank You! Visit Again!!\n\n\n");
}

void save_ticket(int fare, int passenger_count) {
    FILE* fp = fopen(ticket_file, "a");
    if (fp == NULL) {
        printf("Error opening file for saving ticket details.\n");
        return;
    }

    Node* ptr = start;
    fprintf(fp, "Train: %s\n", train);
    fprintf(fp, "Boarding Station: %s\n", station);
    fprintf(fp, "Destination Station: %s\n", des);
    fprintf(fp, "Class: %s\n", cla);
    fprintf(fp, "Boarding Time: %d:%d\n", time1, time2);
    fprintf(fp, "Total Fare: %d Rs\n", fare);
    fprintf(fp, "Passengers:\n");

    for (int i = 1; i <= passenger_count; i++) {
        fprintf(fp, "Passenger %d: %s, Gender: %s, Age: %d, Seat Number: %d\n",
                i, ptr->name, ptr->gen, ptr->age, ptr->seat);
        ptr = ptr->link;
    }

    fprintf(fp, "----------------------------------------\n");
    fclose(fp);
    printf("Ticket details saved successfully!\n");
}

void retrieve_ticket() {
    FILE* fp = fopen(ticket_file, "r");
    if (fp == NULL) {
        printf("Error opening file for reading ticket details.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

void register_user(char* username) {
    char password[MAX_NAME_LEN];

    printf("Enter a Password: ");
    fflush(stdin);
    fgets(password, MAX_NAME_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';  // Corrected: Removed extra parentheses

    FILE* fp = fopen(login_file, "a");
    if (fp == NULL) {
        printf("Error opening login file for registration.\n");
        return;
    }

    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("Registration successful! You can now log in.\n");
}

void admin_login() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    printf("Enter Admin Username: ");
    fflush(stdin);
    fgets(username, MAX_NAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Admin Password: ");
    fflush(stdin);
    fgets(password, MAX_NAME_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(username, admin_username) == 0 && strcmp(password, admin_password) == 0) {
        printf("Admin login successful!\n");
        // Call the admin function to view tickets or perform other admin tasks
        view_tickets();
    } else {
        printf("Invalid admin credentials.\n");
    }
}
void login() {
    char username[MAX_NAME_LEN];
    char password[MAX_NAME_LEN];

    printf("Enter Username: ");
    fflush(stdin);
    fgets(username, MAX_NAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter Password: ");
    fflush(stdin);
    fgets(password, MAX_NAME_LEN, stdin);
    password[strcspn(password, "\n")] = '\0';
    
    // Implement actual authentication logic here
}

void view_tickets() {
    FILE* fp = fopen(ticket_file, "r");
    if (fp == NULL) {
        printf("Error opening file for reading tickets.\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}
