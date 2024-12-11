#include "symtable.h"
#include "parser.h"
#include "error.h"
#include "hack.h"

struct Symbol* hashArray[SYMBOL_TABLE_SIZE];

int hash(char *str) {

    unsigned long hash = 5381;
    int c; 

    while((c = *str++)){
    hash = ((hash << 5) + hash) + c;
    }
    return hash % SYMBOL_TABLE_SIZE;
} 

void symtable_insert(char* key, hack_addr addr) {
    struct Symbol *item = (struct Symbol*) malloc(sizeof(struct Symbol));
    item->name = strdup(key); //Key is a string passed to the function and it represents the name of the symbol. Strdup creates a new string in memory and copies the contents of key into this string
    item->addr = addr;

    unsigned int i = hash(key);

    while(hashArray[i] != NULL && hashArray[i]->name != NULL) {
        i++;
        i %= SYMBOL_TABLE_SIZE;
    }
    hashArray[i] = item;
    free(item);
    item = NULL;
}
struct Symbol *symtable_find(char * key) {
    unsigned int i = hash(key);
    while(hashArray[i] != NULL) {

        if(strcmp(hashArray[i]->name, key) == 0) {
            return hashArray[i];
        }
        i++;
        i %= SYMBOL_TABLE_SIZE;
    }
    return NULL;
}
void symtable_display_table() {
    int i = 0;
    for(i =0; i< SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL) {
            printf(" {%s, %d}\n", hashArray[i]->name, hashArray[i]->addr);
        } else {
            printf("~~");
        }
        printf("\n");
    }
}
void symtable_print_labels() {
   int i = 0;    
   for(i = 0; i<SYMBOL_TABLE_SIZE; i++) {
        if(hashArray[i] != NULL){
             printf("{%s,%d}\n",hashArray[i]->name,hashArray[i]->addr);
            }
        }
    } 
