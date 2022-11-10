#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/bib.h"

/* Driver program to test above function*/
int main()
{
    Node *pokedex = NULL;
    pokedex = insert(pokedex, 9);
    pokedex = insert(pokedex, 5);
    pokedex = insert(pokedex, 10);
    pokedex = insert(pokedex, 0);
    pokedex = insert(pokedex, 6);
    pokedex = insert(pokedex, 11);
    pokedex = insert(pokedex, -1);
    pokedex = insert(pokedex, 1);
    pokedex = insert(pokedex, 2);

    pokedex = deleteNode(pokedex, 10);

    printAVL(pokedex, 0);
    // printPokemon(pokedex, 0);
    return 0;
}