#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TOTAL_SEATS 100

// Define structs
struct Movie {
    char title[100];
    int duration;
    int availableSeats;
    int* seatMatrix; // Dynamically allocate memory for seat matrix
};

struct Booking {
    struct Movie movie;
    char showTime[20];
    int seatNumber;
    int numberOfTickets;
    int canceled;
};

struct Node {
    char data[100];
    struct Node* next;
};

struct Pantry {
    struct Node* head;
};

struct User {
    char name[100];
    int isMember;
    struct Booking* bookedTicket;
};

struct TreeNode {
    char name[100];
    struct TreeNode* parent;
    struct TreeNode* children;
    struct TreeNode* nextSibling;
    void* data; // Pointer to movie struct for leaf nodes
};

enum NodeType { CITY, THEATER, MOVIE, SHOWTIME };

// Function prototypes
struct TreeNode* createTreeNode(const char* name);
struct TreeNode* createMovieNode(const char* title, int duration, int availableSeats);
void addChild(struct TreeNode* parent, struct TreeNode* child);
void displayTree(struct TreeNode* node, int depth);
struct TreeNode* populateTree();
void addToChoicesLinkedList(struct Pantry* pantry, const char* item);
void displayUserChoices(const struct Pantry* pantry);
void displayCityOptions(struct TreeNode* root);
void bookTicket(struct User* user, struct Movie* movie, const char* showTime, int* seatNumbers, int numberOfTickets);

void cancelTicket(struct User* user);

// Function implementations

struct TreeNode* createTreeNode(const char* name) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(newNode->name, name);
    newNode->parent = NULL;
    newNode->children = NULL;
    newNode->nextSibling = NULL;
    newNode->data = NULL;
    return newNode;
}

struct TreeNode* createMovieNode(const char* title, int duration, int availableSeats) {
    struct TreeNode* newNode = createTreeNode(title);
    struct Movie* movie = (struct Movie*)malloc(sizeof(struct Movie));
    strcpy(movie->title, title);
    movie->duration = duration;
    movie->availableSeats = availableSeats;
    movie->seatMatrix = (int*)malloc(availableSeats * sizeof(int));
    for (int i = 0; i < availableSeats; i++) {
        movie->seatMatrix[i] = 1; // Initialize all seats as available
    }
    newNode->data = (void*)movie;
    return newNode;
}

void addChild(struct TreeNode* parent, struct TreeNode* child) {
    child->parent = parent;
    if (parent->children == NULL) {
        parent->children = child;
    } else {
        struct TreeNode* temp = parent->children;
        while (temp->nextSibling != NULL) {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
}

void displayTree(struct TreeNode* node, int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s\n", node->name);

    struct TreeNode* child = node->children;
    while (child != NULL) {
        displayTree(child, depth + 1);
        child = child->nextSibling;
    }
}

struct TreeNode* populateTree() {
    // Node for Root
    struct TreeNode* root = createTreeNode("Cities");
    
    // Node for city Pune
    struct TreeNode* city1 = createTreeNode("Pune");
    addChild(root, city1);
    
    // Tree for Rahul cinema
    struct TreeNode* Rahul_Cinema = createTreeNode("Rahul Cinema");
    addChild(city1, Rahul_Cinema);

    struct TreeNode* BMCM = createMovieNode("Bade Miyan Choten Miyan", 120, TOTAL_SEATS);
    struct TreeNode* maidaan = createMovieNode("Maidaan", 120, TOTAL_SEATS);
    struct TreeNode* svsr = createMovieNode("Swatantrya Veer Savarkar", 120, TOTAL_SEATS);
    struct TreeNode* god = createMovieNode("Godzilla X Kong: The New Empire", 120, TOTAL_SEATS);
    struct TreeNode* magdaon = createMovieNode("Magdaon", 120, TOTAL_SEATS);

    addChild(Rahul_Cinema, BMCM);
    addChild(Rahul_Cinema, maidaan);
    addChild(Rahul_Cinema, svsr);
    addChild(Rahul_Cinema, god);
    addChild(Rahul_Cinema, magdaon);

    struct TreeNode* showtime1 = createTreeNode("09:00 AM");
    struct TreeNode* showtime2 = createTreeNode("12:00 PM");
    struct TreeNode* showtime3 = createTreeNode("03:00 PM");
    struct TreeNode* showtime4 = createTreeNode("06:00 PM");
    struct TreeNode* showtime5 = createTreeNode("09:00 PM");

    addChild(BMCM, showtime1);
    addChild(maidaan, showtime2);
    addChild(svsr, showtime3);
    addChild(god, showtime4);
    addChild(magdaon, showtime5);



    // Tree for Inox Mall

    struct TreeNode* Inox = createTreeNode("Inox");
    addChild(city1, Inox);

    struct TreeNode* BMCM2= createMovieNode("Bade Miyan Choten Miyan", 120, TOTAL_SEATS);
    struct TreeNode* maidaan2 = createMovieNode("Maidaan", 120, TOTAL_SEATS);
    struct TreeNode* svsr2 = createMovieNode("Swatantrya Veer Savarkar", 120, TOTAL_SEATS);
    struct TreeNode* god2 = createMovieNode("Godzilla X Kong: The New Empire", 120, TOTAL_SEATS);
    struct TreeNode* magdaon2 = createMovieNode("Magdaon", 120, TOTAL_SEATS);

    addChild(Inox, god2);
    addChild(Inox, magdaon2);
    addChild(Inox, BMCM2);
    addChild(Inox, maidaan2);
    addChild(Inox, svsr2);

    struct TreeNode* showtime11 = createTreeNode("09:00 AM");
    struct TreeNode* showtime22 = createTreeNode("12:00 PM");
    struct TreeNode* showtime33 = createTreeNode("03:00 PM");
    struct TreeNode* showtime44 = createTreeNode("06:00 PM");
    struct TreeNode* showtime55 = createTreeNode("09:00 PM");

    addChild(BMCM2, showtime22);
    addChild(maidaan2, showtime33);
    addChild(svsr2, showtime11);
    addChild(god2, showtime44);
    addChild(magdaon2, showtime55);


    // Tree for Pheonix Mall

    struct TreeNode* Pheonix = createTreeNode("Pheonix Mall");

    addChild(city1, Pheonix);

    struct TreeNode* BMCM3= createMovieNode("Bade Miyan Choten Miyan", 120, TOTAL_SEATS);
    struct TreeNode* maidaan3 = createMovieNode("Maidaan", 120, TOTAL_SEATS);
    struct TreeNode* svsr3 = createMovieNode("Swatantrya Veer Savarkar", 120, TOTAL_SEATS);
    struct TreeNode* god3= createMovieNode("Godzilla X Kong: The New Empire", 120, TOTAL_SEATS);
    struct TreeNode* magdaon3 = createMovieNode("Magdaon", 120, TOTAL_SEATS);

    addChild(Pheonix, god3);
    addChild(Pheonix, magdaon3);
    addChild(Pheonix, BMCM3);
    addChild(Pheonix, maidaan3);
    addChild(Pheonix, svsr3);

    struct TreeNode* showtime111 = createTreeNode("09:00 AM");
    struct TreeNode* showtime222 = createTreeNode("12:00 PM");
    struct TreeNode* showtime333 = createTreeNode("03:00 PM");
    struct TreeNode* showtime444 = createTreeNode("06:00 PM");
    struct TreeNode* showtime555 = createTreeNode("09:00 PM");

    addChild(BMCM3, showtime444);
    addChild(maidaan3, showtime333);
    addChild(svsr3, showtime555);
    addChild(god3, showtime222);
    addChild(magdaon3, showtime111);


    // Tree for Mangala
    struct TreeNode* Mangala = createTreeNode("Mangala");
    addChild(city1, Mangala);

    struct TreeNode* BMCM4= createMovieNode("Bade Miyan Choten Miyan", 120, TOTAL_SEATS);
    struct TreeNode* maidaan4 = createMovieNode("Maidaan", 120, TOTAL_SEATS);
    struct TreeNode* svsr4 = createMovieNode("Swatantrya Veer Savarkar", 120, TOTAL_SEATS);
    struct TreeNode* god4= createMovieNode("Godzilla X Kong: The New Empire", 120, TOTAL_SEATS);
    struct TreeNode* magdaon4 = createMovieNode("Magdaon", 120, TOTAL_SEATS);

    addChild(Mangala, god4);
    addChild(Mangala, magdaon4);
    addChild(Mangala, BMCM4);
    addChild(Mangala, maidaan4);
    addChild(Mangala, svsr4);

    struct TreeNode* showtime1111 = createTreeNode("09:00 AM"); 
    struct TreeNode* showtime2222 = createTreeNode("12:00 PM");
    struct TreeNode* showtime3333 = createTreeNode("03:00 PM");
    struct TreeNode* showtime4444 = createTreeNode("06:00 PM");
    struct TreeNode* showtime5555 = createTreeNode("09:00 PM");

    addChild(BMCM4, showtime4444);
    addChild(maidaan4, showtime3333);
    addChild(svsr4, showtime5555);
    addChild(god4, showtime2222);
    addChild(magdaon4, showtime1111);

   // Add more cities, theaters, movies, and show times as needed

    return root;
}


void addToChoicesLinkedList(struct Pantry* pantry, const char* item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    strcpy(newNode->data, item);
    newNode->next = NULL;

    if (!pantry->head) {
        pantry->head = newNode;
    } else {
        struct Node* temp = pantry->head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void displayUserChoices(const struct Pantry* pantry) {
    if (!pantry->head) {
        printf("No choices made yet.\n");
    } else {
        printf("User Choices:\n");
        struct Node* temp = pantry->head;
        while (temp) {
            printf("%s\n", temp->data);
            temp = temp->next;
        }
    }
}


void bookTicket(struct User* user, struct Movie* movie, const char* showTime, int* seatNumbers, int numberOfTickets) {
    if (user->bookedTicket) {
        free(user->bookedTicket); // Release previous booking
    }
    
    // Check if requested number of tickets is available
    if (numberOfTickets > movie->availableSeats) {
        printf("Sorry, there are not enough available seats for %s.\n", movie->title);
        return;
    }

    // Check if all requested seats are available
    for (int i = 0; i < numberOfTickets; i++) {
        if (movie->seatMatrix[seatNumbers[i] - 1] == 0) {
            printf("Seat %d is not available.\n", seatNumbers[i]);
            return;
        }
    }

    // Book the tickets
    user->bookedTicket = (struct Booking*)malloc(sizeof(struct Booking));
    user->bookedTicket->movie = *movie;
    strcpy(user->bookedTicket->showTime, showTime);
    user->bookedTicket->numberOfTickets = numberOfTickets;
    user->bookedTicket->canceled = 0;

    // Update available seats
    for (int i = 0; i < numberOfTickets; i++) {
        int seatNumber = seatNumbers[i];
        movie->seatMatrix[seatNumber - 1] = 0; // Mark booked seat as unavailable
        user->bookedTicket->seatNumber = seatNumber; // Store only the first seat number for display purposes
    }
    movie->availableSeats -= numberOfTickets;

    printf("\n*********************************************\n");
    printf("\n");
    printf("Ticket booked for %s \n", user->bookedTicket->movie.title);
    printf("Your movie at: %s \n", user->bookedTicket->showTime);
    printf("You have booked %d number of Tickets \n", user->bookedTicket->numberOfTickets);
    printf("Your Seat numbers are : ");
    for (int i = 0; i < numberOfTickets; i++) {
        printf("%d ", seatNumbers[i]);
    }
    printf("\n");
    printf("\n*********************************************\n");

    printf("\n\n");
}


void cancelTicket(struct User* user) {
    if (user->bookedTicket && !user->bookedTicket->canceled) {
        struct Movie* movie = &(user->bookedTicket->movie);
        for (int i = user->bookedTicket->seatNumber - 1; i < user->bookedTicket->seatNumber - 1 + user->bookedTicket->numberOfTickets; i++) {
            movie->seatMatrix[i] = 1; // Mark canceled seats as available
        }
        movie->availableSeats += user->bookedTicket->numberOfTickets;
        
        user->bookedTicket->canceled = 1;
        printf("\n****************************************************************\n");
        printf("Booking canceled for %s at %s, Seat: %d\n",
               user->bookedTicket->movie.title, user->bookedTicket->showTime, user->bookedTicket->seatNumber);
        printf("\n****************************************************************\n");
    } else {
        printf("No active booking to cancel.\n");
    }
}
void displayTreeLimited(struct TreeNode* node, int depth, int maxDepth) {
    if (depth >= maxDepth) {
        printf("%s\n", node->name);
    } else {
        struct TreeNode* child = node->children;
        while (child != NULL) {
            displayTreeLimited(child, depth + 1, maxDepth);
            child = child->nextSibling;
        }
    }
}

void displayCityOptions(struct TreeNode* root) {
    // Display available cities
    printf("Available Cities:\n 1. ");
    displayTreeLimited(root, 0, 1);
}

void displayChildren(struct TreeNode* parent, int depth) {
    struct TreeNode* child = parent->children;
    int count = 1;
    while (child != NULL) {
        printf("%d. %s\n", count, child->name);
        child = child->nextSibling;
        count++;
    }
}

void displayOptions(struct TreeNode* parent, const char* parentName) {
    printf("Available %ss in %s:\n", parentName, parent->name);
    displayChildren(parent, 1);
}

int getChildrenCount(struct TreeNode* parent);
int getChildrenCount(struct TreeNode* parent) {
    int count = 0;
    struct TreeNode* child = parent->children;
    while (child != NULL) {
        count++;
        child = child->nextSibling;
    }
    return count;
}


int selectOption(struct TreeNode* parent, const char* parentName) {
    int selectedOption;
    do {
        printf("Enter the %s number you want to choose: ", parentName);
        scanf("%d", &selectedOption);
        if (selectedOption < 1 || selectedOption > getChildrenCount(parent)) {
            printf("Invalid %s selection.\n", parentName);
        } else {
            break;
        }
    } while (1);
    return selectedOption;
}

struct TreeNode* selectNode(struct TreeNode* parent, int option) {
    struct TreeNode* selectedNode = parent->children;
    for (int i = 1; i < option && selectedNode != NULL; i++) {
        selectedNode = selectedNode->nextSibling;
    }
    return selectedNode;
}


int main() {
    struct TreeNode* cityTree = populateTree();

    struct Pantry userPantry = {NULL};

    printf("Welcome to the Pantry! Please choose from the following items before booking the tickets\n");
    printf("1. Chips\n");
    printf("2. Juice\n");
    printf("3. Popcorn\n");
    int userChoice;
    do {
        printf("Enter your choice (1, 2, or 3), or enter 0 to finish: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                addToChoicesLinkedList(&userPantry, "Chips");
                break;
            case 2:
                addToChoicesLinkedList(&userPantry, "Juice");
                break;
            case 3:
                addToChoicesLinkedList(&userPantry, "Popcorn");
                break;
            case 0:
                printf("Thank you for choosing! Here are your selections:\n");
                displayUserChoices(&userPantry);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (userChoice != 0);

    printf("Welcome to the Movie Booking System!\n");

    struct User user = {0};

    printf("Please enter your name: ");
    scanf(" %[^\n]s", user.name);
    user.isMember = 1; // Assume the user is a member

    // Display available cities
    displayCityOptions(cityTree);

    int selectedCityNumber = selectOption(cityTree, "city");
    struct TreeNode* selectedCity = selectNode(cityTree, selectedCityNumber);

    printf("Available Theaters in %s:\n", selectedCity->name);
    displayOptions(selectedCity, "theater");

    int selectedTheaterNumber = selectOption(selectedCity, "theater");
    struct TreeNode* selectedTheater = selectNode(selectedCity, selectedTheaterNumber);

    printf("Available Movies in %s at %s:\n", selectedCity->name, selectedTheater->name);
    displayOptions(selectedTheater, "movie");

    int selectedMovieNumber = selectOption(selectedTheater, "movie");
    struct TreeNode* selectedMovie = selectNode(selectedTheater, selectedMovieNumber);

    printf("Available Showtimes for %s at %s:\n", selectedMovie->name, selectedTheater->name);
    displayOptions(selectedMovie, "showtime");

    int selectedShowtimeNumber = selectOption(selectedMovie, "showtime");
    struct TreeNode* selectedShowtime = selectNode(selectedMovie, selectedShowtimeNumber);

    struct Movie* movie = (struct Movie*)selectedMovie->data;

    // Display available seats for the selected showtime
    printf("Available Seats for %s at %s:\n", selectedMovie->name, selectedShowtime->name);
    printf("Seat Matrix:\n");

     // Display available seats
    
    printf("  -----------------------------  \n");
    for (int row = 0; row < 10; ++row) {
        printf("%2d | ", 10 - row);
        for (int col = 0; col < 10; ++col) {
            printf("%2d ", row * 10 + col + 1);
        }
        printf("\n");
    }
    printf("  -----------------------------\n");
    printf("  A  B  C  D  E  F  G  H  I  J \n");

    

   int selectedNumberOfTickets;
    printf("Enter the number of tickets you want to buy: ");
    scanf("%d", &selectedNumberOfTickets);

    int selectedSeatNumbers[selectedNumberOfTickets];
    printf("Enter the seat numbers you want to book (%d seats): ", selectedNumberOfTickets);
    for (int i = 0; i < selectedNumberOfTickets; i++) {
        scanf("%d", &selectedSeatNumbers[i]);
    }

    // Book the tickets
    bookTicket(&user, movie, selectedShowtime->name, selectedSeatNumbers, selectedNumberOfTickets);


    // Provide options for further interaction
    
    do {
        printf("\nOptions:\n");
        printf("1. Cancel Ticket\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                cancelTicket(&user);
                break;
            case 2:
                printf("Dear %s!\n", user.name);
                printf("Your Ticket Has Been Booked\n");
                printf("Thank you for using the Movie Booking System!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (userChoice != 2);

    // Clean up dynamically allocated memory
    free(user.bookedTicket);

    return 0;
}

