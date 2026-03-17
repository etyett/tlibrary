#include "tlib.h"

int main() {   
    loadFromFile();
    int choice;
    
    do {
        printf("\n=== T-Library ===\n");
        printf("1. Add book\n");
        printf("2. View all books\n");
        printf("3. Add to favorites\n");
        printf("4. Change book status\n");
        printf("5. View favorite books\n");
        printf("6. Delete book\n");
        printf("7. Search books\n");
        printf("0. Exit\n");
        printf("Choose an action: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewAllBooks();
                break;
            case 3:
                addToFavorite();
                break;
            case 4:
                changeStatus();
                break;
            case 5:
                viewFavorites();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                searchBooks();
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while(choice != 0);
    
    return 0;
}