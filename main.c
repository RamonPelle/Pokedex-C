#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./libs/bib.h"

int main()
{
    // Criar uma nova pokedex
    Node *pokedex = NULL;

    int op;
    printf("\n\t0 - Sair\t\n\t1 - Incluir pokemon\n\t2 - Buscar e imprimir todos os campos\n\t3 - Editar\n\t4 - Excluir\n\t5 - Imprimir todos os elementos de forma ordenada\n\t6 - Imprimir quantidade de elementos\n\t7 - Informar altura da árvore\n\t8 - Imprimir em estrutura de árvore\n");
    do
    {
        scanf("%d", &op);
        switch (op)
        {
        case 1: // Inserir alguns pokemons
            pokedex = insert(pokedex, 9);
            pokedex = insert(pokedex, 5);
            pokedex = insert(pokedex, 10);
            pokedex = insert(pokedex, 0); // nao vai inserir
            pokedex = insert(pokedex, 6);
            pokedex = insert(pokedex, 11);
            pokedex = insert(pokedex, -1); // nao vai inserir
            pokedex = insert(pokedex, 1);
            pokedex = insert(pokedex, 2);
            break;
        case 2: // Busca e imprime os dados do pokemon
            printPokemon(pokedex, 11);
            break;
        case 3: // Edita os dados de um pokemon
            pokedex = edit(pokedex, 11);
            break;
        case 4: // Exclui um pokemon
            pokedex = deleteNode(pokedex, 10);
            break;
        case 5: // Imprime os IDs de forma ordenada
            printf("Ordem ID: ");
            order(pokedex);
            printf("\n");
            break;
        case 6: // Imprime quantidade de elementos
            int size = ammountOfNodes(pokedex);
            printf("Quantidade: %d\n", size);
            break;
        case 7: // Imprime a altura da árvore
            printf("\nAltura da árvore: %d\n", heightOfTree(pokedex));
            break;
        case 8: // Imrpime a pokedex em estrutura de árvore
            printf("Forma de árvore:\n");
            printAVL(pokedex, 0);
            printf("\n");
            break;
        default:
            if (op != 0)
            {
                printf("Opção inválida!\n");
            }
            break;
        }
    } while (op != 0);

    return 0;
}