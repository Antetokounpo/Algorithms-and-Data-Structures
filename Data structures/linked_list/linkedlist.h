#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include<stdbool.h>

void first();

void last();

void next();

void preceding();

bool empty();

bool is_first();

bool is_last();

int length();

void append(int data);

void prepend(int data);

void insert(int data);

void replace(int data);

void delete();

struct LinkedList** get_index();

#endif