#include <stdio.h>
#include <stdbool.h> // for true and false value

#define NUM_ROOMS 5
#define FILENAME "rooms.txt"

// Struct to represent a hotel room
typedef struct {
    int roomNumber;
    bool isOccupied;
} Room;

// Function prototypes/
void displayMenu();
void viewRoomAvailability(Room rooms[]);
void bookRoom(Room rooms[]);
void checkOut(Room rooms[]);
void updateFile(Room rooms[]);

int main() {
    Room rooms[NUM_ROOMS];
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Error opening file %s. Creating new rooms.\n", FILENAME);
        for (int i = 0; i < NUM_ROOMS; i++) {
            rooms[i].roomNumber = 101 + i;
            rooms[i].isOccupied = false;
        }
        updateFile(rooms);
    } else {
        for (int i = 0; i < NUM_ROOMS; i++) {
            fscanf(file, "%d %d", &rooms[i].roomNumber, &rooms[i].isOccupied);
        }
        fclose(file);
    }

    int choice;
    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                viewRoomAvailability(rooms);
                break;
            case 2:
                bookRoom(rooms);
                break;
            case 3:
                checkOut(rooms);
                break;
            case 4:
                updateFile(rooms); // Update file before exiting
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while(choice != 4);

    return 0;
}

void displayMenu() {
    printf("Hotel Menu:\n");
    printf("1. View Room Availability\n");
    printf("2. Book a Room\n");
    printf("3. Check Out\n");
    printf("4. Exit\n");
}

void viewRoomAvailability(Room rooms[]) {
    printf("Room Availability:\n");
    for (int i = 0; i < NUM_ROOMS; i++) {
        printf("Room %d: %s\n", rooms[i].roomNumber, rooms[i].isOccupied ? "Occupied" : "Available");
    }
}

void bookRoom(Room rooms[]) {
    int roomNum;
    printf("Enter the room number to book: ");
    scanf("%d", &roomNum);

    // Find the room in the array
    for (int i = 0; i < NUM_ROOMS; i++) {
        if (rooms[i].roomNumber == roomNum) {
            if (rooms[i].isOccupied) {
                printf("Sorry, the room is already occupied.\n");
            } else {
                rooms[i].isOccupied = true;
                printf("Room %d booked successfully.\n", roomNum);
            }
            updateFile(rooms); // Update file after booking
            return;
        }
    }
    printf("Invalid room number.\n");
}

void checkOut(Room rooms[]) {
    int roomNum;
    printf("Enter the room number to check out: ");
    scanf("%d", &roomNum);

    // Find the room in the array
    for (int i = 0; i < NUM_ROOMS; i++) {
        if (rooms[i].roomNumber == roomNum) {
            if (rooms[i].isOccupied) {
                rooms[i].isOccupied = false;
                printf("Checked out of room %d.\n", roomNum);
            } else {
                printf("Room %d is not occupied.\n", roomNum);
            }
            updateFile(rooms); // Update file after check out
            return;
        }
    }
    printf("Invalid room number.\n");
}

void updateFile(Room rooms[]) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file %s for writing.\n", FILENAME);
        return;
    }

    for (int i = 0; i < NUM_ROOMS; i++) {
        fprintf(file, "%d %d\n", rooms[i].roomNumber, rooms[i].isOccupied);
    }

    fclose(file);
}
