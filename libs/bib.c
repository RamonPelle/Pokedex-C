#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib.h"
#include "zString/src/zstrtok.h"
int heightOfTree(Node *head)
{
    if (head == NULL)
        return 0;
    return 1 + max(heightOfTree(head->left), heightOfTree(head->right));
}
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}
Node *min(Node *head)
{
    Node *no = head;
    while (no->left != NULL)
        no = no->left;
    return no;
}
Pokemon *createPokemon(int id)
{
    FILE *fp = fopen("Pokemon.csv", "r");
    Pokemon *pokemon = (Pokemon *)malloc(sizeof(Pokemon));
    if (!fp)
        printf("Can't open file\n");
    else
    {
        char buffer[1076];
        int row = 0;
        int column = 0;

        while (fgets(buffer, 1076, fp))
        {
            column = 0;
            row++;
            if (row == 1)
                continue;

            char *value = zstrtok(buffer, ", "); // dividindo os dados
            // while (value)
            // {
            //     if (column == 0 && *value == id)
            //     {
            //         if (column == 1)
            //         {
            //             strcpy(pokemon->name, value);
            //         }
            //         if (column == 2)
            //         {
            //             strcpy(pokemon->form, value);
            //         }

            //         if (column == 4)
            //         {
            //             strcpy(pokemon->type1, value);
            //         }
            //         if (column == 5)
            //         {
            //             strcpy(pokemon->type2, value);
            //         }
            //         if (column == 6)
            //         {
            //             pokemon->total = strtol(value, (char **)NULL, 10);
            //         }
            //         if (column == 7)
            //         {
            //             pokemon->hp = strtol(value, (char **)NULL, 10);
            //         }
            //         if (column == 8)
            //         {
            //             pokemon->attack = strtol(value, (char **)NULL, 10);
            //         }
            //         if (column == 9)

            //             pokemon->defense = strtol(value, (char **)NULL, 10);

            //         if (column == 10)
            //         {
            //             pokemon->spAttack = strtol(value, (char **)NULL, 10);
            //         }
            //         if (column == 11)
            //         {
            //             pokemon->spDefense = strtol(value, (char **)NULL, 10);
            //         }
            //         if (column == 12)
            //         {
            //             pokemon->speed = strtol(value, (char **)NULL, 10);
            //         }
            //         if (column == 13)
            //         {
            //             pokemon->gen = strtol(value, (char **)NULL, 10);
            //         }
            //     }

            //     value = zstrtok(NULL, ", ");
            //     column++;
            // }

            printf("\n");
        }

        // Close the file
        fclose(fp);

        pokemon->next = NULL;
    }
    return pokemon;
}
Node *createNode(int id)
{
    Node *no = (Node *)malloc(sizeof(Node));
    no->id = id;
    no->data = createPokemon(id);
    no->left = NULL;
    no->right = NULL;
    no->height = 0;
    return (no);
}
Node *rightRotation(Node *head)
{
    Node *headLeft = head->left;
    Node *headLeftRight = headLeft->right;

    // rotaciona
    headLeft->right = head;
    head->left = headLeftRight;

    // atualiza altura
    head->height = heightOfTree(head);
    headLeft->height = heightOfTree(headLeft);

    return headLeft;
}
Node *leftRotation(Node *head)
{
    Node *headRight = head->right;
    Node *headRightLeft = headRight->left;

    // rotaciona
    headRight->left = head;
    head->right = headRightLeft;

    // atualiza altura
    head->height = heightOfTree(head);
    headRight->height = heightOfTree(headRight);

    return headRight;
}
int balancingFactor(Node *head)
{
    if (head == NULL)
        return 0;
    return heightOfTree(head->left) - heightOfTree(head->right);
}
Node *insert(Node *node, int id)
{
    if (node == NULL)
        return (createNode(id));

    if (id < node->id)
        node->left = insert(node->left, id);
    else if (id > node->id)
        node->right = insert(node->right, id);
    else
        return node; // nao atualiza a arvore, valores repetidos

    // atualiza a altura
    node->height = heightOfTree(node);

    // saber se esta balanceada
    int balance = balancingFactor(node);

    // esquerdona
    if (balance > 1 && id < node->left->id)
        return rightRotation(node);

    // direitona
    if (balance < -1 && id > node->right->id)
        return leftRotation(node);

    // esquerda direita
    if (balance > 1 && id > node->left->id)
    {
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }

    // direita esquerda
    if (balance < -1 && id < node->right->id)
    {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }

    return node;
}
void printAVL(Node *nodo, int tab)
{
    for (int i = 0; i < tab; i++)
    {
        printf("-");
    }
    if (nodo)
    {
        printf("%d\n", nodo->id);
        printAVL(nodo->left, tab + 2);
        printf("\n");
        printAVL(nodo->right, tab + 2);
    }
    else
        printf("*");
}
Node *deleteNode(Node *head, int id)
{
    if (head == NULL)
        return head;

    if (id < head->id)
        head->left = deleteNode(head->left, id);
    else if (id > head->id)
        head->right = deleteNode(head->right, id);
    else // remover o no cabeca
    {
        if ((head->left == NULL) || (head->right == NULL))
        {
            Node *aux = (Node *)malloc(sizeof(Node));
            if (head->left) // aux = head->left ? head->left : head->right ?? !!!!!!!!!!!!!!!!!!!!!########################!#!#!#!!##!#!#!
            {
                aux = head->left;
            }
            else
            {
                aux = head->right;
            }

            // 0 filho
            if (aux == NULL)
            {
                aux = head;
                head = NULL;
            }
            else
                *head = *aux;

            free(aux);
        }
        else
        {
            // 2 filhos
            Node *temp = min(head->right);
            head->id = temp->id;
            head->right = deleteNode(head->right, temp->id);
        }
    }

    // retorno 1 no
    if (head == NULL)
        return head;

    // mudando altura
    head->height = 1 + max(heightOfTree(head->left), heightOfTree(head->right));

    int balance = balancingFactor(head);

    // esquerda esquerda
    if (balance > 1 && balancingFactor(head->left) >= 0)
        return rightRotation(head);

    // esquerda direita
    if (balance > 1 && balancingFactor(head->left) < 0)
    {
        head->left = leftRotation(head->left);
        return rightRotation(head);
    }

    // direita direita
    if (balance < -1 && balancingFactor(head->right) <= 0)
        return leftRotation(head);

    // direita esquerda
    if (balance < -1 && balancingFactor(head->right) > 0)
    {
        head->right = rightRotation(head->right);
        return leftRotation(head);
    }

    return head;
}
void *printPokemon(Node *head, int id)
{
    // Pokemon *aux = (Pokemon *)malloc(sizeof(Pokemon));
    // aux = head->data;
    // while (aux->id != id)
    // {
    //     if (aux == NULL)
    //     {
    //         printf("\nPokemon nao foi insrido\n.");
    //         break;
    //     }
    //     aux->next;
    // }
    // printf("Pokemon %s", aux->name);
}
void *insertPokemon() // Node *head, int idPokemon
{
    FILE *fp = fopen("Pokemon.csv", "r");

    if (!fp)
        printf("Can't open file\n");

    else
    {
        // Here we have taken size of
        // array 1024 you can modify it
        char buffer[1024];

        int row = 0;
        int column = 0;

        while (fgets(buffer,
                     1024, fp))
        {
            column = 0;
            row++;

            if (row == 1)
                continue;
            char *value = zstrtok(buffer, ", ");

            while (value)
            {
                if (column == 0)
                {
                    printf("ID:");
                }

                if (column == 1)
                {
                    printf("\nName:");
                }
                if (column == 2)
                {
                    printf("\nForm:");
                }

                if (column == 4)
                {
                    printf("\nType 1:");
                }
                if (column == 5)
                {
                    printf("\nType 2:");
                }
                if (column == 6)
                {
                    printf("\nTotal:");
                }
                if (column == 7)
                {
                    printf("\nHP:");
                }
                if (column == 8)
                {
                    printf("\nAttack:");
                }
                if (column == 9)

                    printf("\nDefense:");

                if (column == 10)
                {
                    printf("\nSuper Attack:");
                }
                if (column == 11)
                {
                    printf("\nSuper Defense:");
                }
                if (column == 12)
                {
                    printf("\nSpeed:");
                }
                if (column == 13)
                {
                    printf("\nGeneration:");
                }
                printf("%s", value);
                value = zstrtok(NULL, ", ");
                column++;
            }

            printf("\n");
        }

        // Close the file
        fclose(fp);
    }
}
