#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "linkedlist.h"

struct LinkedList {
    int value;
    struct LinkedList *preceding;
    struct LinkedList *next;
};

static struct LinkedList *index = NULL;

void first(){
    if(index == NULL){
        return;
    }else{
        while(index->preceding != NULL){
            index = index->preceding;
        }
    }
}

void last(){
    if(index == NULL){
        return;
    }else{
        while(index->next != NULL){
            index = index->next;
        }
    }
}

void next(){
    if(index == NULL){
        return;
    }else{
        if(index->next == NULL){
            return;
        }else{
            index = index->next;
        }
    }
}

void preceding(){
    if(index == NULL){
        return;
    }else{
        if(index->preceding == NULL){
            return;
        }else{
            index = index->preceding;
        }
    }
}

bool empty(){
    if(index == NULL){
        return true;
    }else{
        return false;
    }
}

bool is_first(){
    if(index == NULL){
        return;
    }else{
        if(index->preceding == NULL){
            return true;
        }else{
            return false;
        }
    }
}

bool is_last(){
    if(index == NULL){
        return;
    }else{
        if(index->next == NULL){
            return true;
        }else{
            return false;
        }
    }
}

int length(){
    first();
    int c = 0;
    if(index == NULL){
        return 0;
    }else{
        while(index->next != NULL){
            ++c;
            next();
        }
        c += 1;
        return c;
    }
}

void append(int data){
    last();
    struct LinkedList *new = malloc(sizeof(struct LinkedList));
    if(new == NULL){
        exit(0);
    }else{
        new->value = NULL;

        new->value = malloc(sizeof(int));
        if(new->value == NULL){
            exit(0);
        }
        new->preceding = malloc(sizeof(struct LinkedList*));
        if(new->preceding == NULL){
            exit(0);
        }
        new->next = malloc(sizeof(struct LinkedList*));
        if(new->next == NULL){
            exit(0);
        }

        new->value = data;
        new->preceding = index;
        new->next = NULL;

        if(index == NULL){
            index = new;
        }else{
            index->next = new;
        }
    }
}

void prepend(int data){
    first();
    struct LinkedList *new = malloc(sizeof(struct LinkedList));
    if(new == NULL){
        exit(0);
    }else{
        new->value = NULL;
        new->preceding = NULL;
        new->next = NULL;

        new->value = malloc(sizeof(int));
        if(new->value == NULL){
            exit(0);
        }
        new->preceding = malloc(sizeof(struct LinkedList*));
        if(new->preceding == NULL){
            exit(0);
        }
        new->next = malloc(sizeof(struct LinkedList*));
        if(new->next == NULL){
            exit(0);
        }

        new->value = data;
        new->preceding = NULL;
        new->next = index;
        if(index == NULL){
            index = new;
        }else{
            index->preceding = new;
        }
    }
}

void insert(int data){
    if(index == NULL){
        return;
    }

    first();
    struct LinkedList *new = malloc(sizeof(struct LinkedList));
    if(new == NULL){
        exit(0);
    }else{
        new->value = NULL;
        new->preceding = NULL;
        new->next = NULL;

        new->value = malloc(sizeof(int));
        if(new->value == NULL){
            exit(0);
        }
        new->preceding = malloc(sizeof(struct LinkedList*));
        if(new->preceding == NULL){
            exit(0);
        }
        new->next = malloc(sizeof(struct LinkedList*));
        if(new->next == NULL){
            exit(0);
        }

        new->value = data;
        new->preceding = index->preceding;
        new->next = index;

        index->preceding->next = new;
        index->preceding = new;
    }

}

void replace(int data){
    if(index == NULL){
        return;
    }else{
        index->value = data;
    }
}

void delete(){
    index->preceding->next = index->next;
    index->next->preceding = index->preceding;
    struct LinkedList *new = malloc(sizeof(struct LinkedList));
    if(new == NULL){
        exit(0);
    }
    new = index->preceding;
    free(index);
}

struct LinkedList** get_index(){
    return &index;
}


int main(){
    append(64);
    prepend(128);
    int len = length();
    first();

    for(int i = 0;i<len;i++){
        printf("%d\n",index->value);
        next();
    }
}