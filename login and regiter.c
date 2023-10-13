#include <stdio.h>
#include <string.h>

#define MAX_USERS 100
#define MAX_USERNAME_LENGTH 30
#define MAX_PASSWORD_LENGTH 30

struct User {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct User users[MAX_USERS];
int userCount = 0;

void saveUsersToFile() {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
}

int registerUser() {
    if (userCount >= MAX_USERS) {
        printf("User limit reached.\n");
        return 0;
    }

    printf("Enter a username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Username already exists. Please choose another one.\n");
            return 0;
        }
    }

    printf("Enter a password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    strcpy(users[userCount].username, username);
    strcpy(users[userCount].password, password);
    userCount++;

    saveUsersToFile();
    printf("Registration successful.\n");
    return 1;
}

int loginUser() {
    printf("Enter your username: ");
    char username[MAX_USERNAME_LENGTH];
    scanf("%s", username);

    printf("Enter your password: ");
    char password[MAX_PASSWORD_LENGTH];
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful. Welcome, %s!\n", username);
            return 1;
        }
    }

    printf("Invalid username or password.\n");
    return 0;
}

int main() {
    FILE *file = fopen("users.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%s %s", users[userCount].username, users[userCount].password) != EOF) {
            userCount++;
        }
        fclose(file);
    }

    int choice;
    do {
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
