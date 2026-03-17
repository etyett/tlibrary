#include "tlib.h"

Book library[100];
int bookCount = 0;

void saveToFile() {
    FILE *file = fopen("library.txt", "w");
    
    if (file == NULL) {
        printf("Error!\n");
        return;
    }
    
    fprintf(file, "%d\n", bookCount);
    
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s\n", library[i].title);
        fprintf(file, "%s\n", library[i].author);
        fprintf(file, "%s\n", library[i].genre);
        fprintf(file, "%d\n", library[i].year);
        fprintf(file, "%s\n", library[i].description);
        fprintf(file, "%d\n", library[i].isRead);
        fprintf(file, "%d\n", library[i].isFavorite);
    }
    
    fclose(file);
    printf("Saved to library.txt\n");
}

void loadFromFile() {
    FILE *file = fopen("library.txt", "r");
    
    if (file == NULL) {
        printf("File not found!\n");
        return;
    }
    
    fscanf(file, "%d\n", &bookCount);
    
    for (int i = 0; i < bookCount; i++) {
        fgets(library[i].title, 100, file);
        library[i].title[strcspn(library[i].title, "\n")] = 0;
        
        fgets(library[i].author, 100, file);
        library[i].author[strcspn(library[i].author, "\n")] = 0;
        
        fgets(library[i].genre, 50, file);
        library[i].genre[strcspn(library[i].genre, "\n")] = 0;
        
        fscanf(file, "%d\n", &library[i].year);
        
        fgets(library[i].description, 200, file);
        library[i].description[strcspn(library[i].description, "\n")] = 0;
        
        fscanf(file, "%d\n", &library[i].isRead);
        fscanf(file, "%d\n", &library[i].isFavorite);
    }
    
    fclose(file);
    printf("Loaded from library.txt\n");
}

void addBook() {
    printf("\n=== Add new book ===\n");
    
    printf("Enter book title: ");
    getchar();
    fgets(library[bookCount].title, 100, stdin);
    library[bookCount].title[strcspn(library[bookCount].title, "\n")] = 0;
    
    printf("Enter author: ");
    fgets(library[bookCount].author, 100, stdin);
    library[bookCount].author[strcspn(library[bookCount].author, "\n")] = 0;
    
    printf("Enter genre: ");
    fgets(library[bookCount].genre, 50, stdin);
    library[bookCount].genre[strcspn(library[bookCount].genre, "\n")] = 0;
    
    printf("Enter year: ");
    scanf("%d", &library[bookCount].year);
    
    getchar();
    printf("Enter description: ");
    fgets(library[bookCount].description, 200, stdin);
    library[bookCount].description[strcspn(library[bookCount].description, "\n")] = 0;
    
    library[bookCount].isRead = 0;
    library[bookCount].isFavorite = 0;
    
    bookCount++;
    printf("Book added!\n");
    
    saveToFile();
}

void viewAllBooks() {
    if (bookCount == 0) {
        printf("\nNo books in library!\n");
        return;
    }
    
    printf("\n\n");
    for (int i = 0; i < bookCount; i++) {
        printf("\nBook #%d\n", i + 1);
        printf("Title: %s\n", library[i].title);
        printf("Author: %s\n", library[i].author);
        printf("Genre: %s\n", library[i].genre);
        printf("Year: %d\n", library[i].year);
        printf("Description: %s\n", library[i].description);
        printf("Status: %s\n", library[i].isRead ? "Read" : "Not read");
        printf("Featured: %s\n", library[i].isFavorite ? "Yes" : "No");
        printf("------------------------\n");
    }
}

void addToFavorite() {
    if (bookCount == 0) {
        printf("\nNo books in library\n");
        return;
    }
    
    viewAllBooks();
    
    int choice;
    printf("\nEnter book number: ");
    scanf("%d", &choice);
    
    if (choice >= 1 && choice <= bookCount) {
        library[choice-1].isFavorite = 1;
        printf("Book added to favorites!\n");
        saveToFile();
    } else {
        printf("Error!\n");
    }
}

void changeStatus() {
    if (bookCount == 0) {
        printf("\nNo books in library!\n");
        return;
    }
    
    viewAllBooks();
    
    int choice;
    printf("\nEnter book number: ");
    scanf("%d", &choice);
    
    if (choice >= 1 && choice <= bookCount) {
        if (library[choice-1].isRead == 0) {
            library[choice-1].isRead = 1;
            printf("Status changed to read\n");
        } else {
            library[choice-1].isRead = 0;
            printf("Status changed to not read\n");
        }
        saveToFile();
    } else {
        printf("Error!\n");
    }
}

void viewFavorites() {
    int found = 0;
    printf("\n=== Favorite books ===\n");
    
    for (int i = 0; i < bookCount; i++) {
        if (library[i].isFavorite == 1) {
            printf("\nTitle: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Genre: %s\n", library[i].genre);
            printf("Year: %d\n", library[i].year);
            found = 1;
        }
    }
    
    if (found == 0) {
        printf("No favorite books!\n");
    }
}

void deleteBook() {
    if (bookCount == 0) {
        printf("\nLibrary is empty!\n");
        return;
    }
    
    viewAllBooks();
    
    int choice;
    printf("\nEnter book number to delete: ");
    scanf("%d", &choice);
    
    if (choice >= 1 && choice <= bookCount) {
        for (int i = choice-1; i < bookCount-1; i++) {
            library[i] = library[i+1];
        }
        bookCount--;
        printf("Book deleted!\n");
        saveToFile();
    } else {
        printf("Invalid book number!\n");
    }
}

void searchBooks() {
    if (bookCount == 0) {
        printf("\nLibrary is empty!\n");
        return;
    }
    
    getchar();
    char keyword[100];
    printf("Enter keyword to search: ");
    fgets(keyword, 100, stdin);
    keyword[strcspn(keyword, "\n")] = 0;
    
    int found = 0;
    printf("\n--- Search results ---\n");
    
    for (int i = 0; i < bookCount; i++) {
        if (strstr(library[i].title, keyword) != NULL ||
            strstr(library[i].author, keyword) != NULL ||
            strstr(library[i].description, keyword) != NULL) {
            
            printf("\nTitle: %s\n", library[i].title);
            printf("Author: %s\n", library[i].author);
            printf("Genre: %s\n", library[i].genre);
            printf("Year: %d\n", library[i].year);
            found = 1;
        }
    }
    
    if (found == 0) {
        printf("No books found!\n");
    }
}