#ifndef TLIB_H
#define TLIB_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char title[100];
    char author[100];
    char genre[50];
    int year;
    char description[200];
    int isRead;
    int isFavorite;
} Book;

extern Book library[100];
extern int bookCount;

void saveToFile();
void loadFromFile();
void addBook();
void viewAllBooks();
void addToFavorite();
void changeStatus();
void viewFavorites();
void deleteBook();
void searchBooks();

#endif