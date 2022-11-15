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

    char teste[6][30];
    int i = 0, flag = 0;
    char row[152];
    char *token;

    while ((feof(fp) != 1) && (flag == 0))
    { // FLAG PRA QUANDO ACHAR O VALOR IGUAL DE ID NO ARQUIVO
        fgets(row, 152, fp);
        token = strtok(row, ",");
        strcpy(teste[0], token);

        if (atoi(teste[0]) == id && atoi(teste[0]) != 0)
        { // TESTE != 0 PARA N PEGAR PRIMEIRA LINHA Q é "NAME TYPE1 ETC"
            flag = 1;
            i = 1;
            while (i < 5)
            {
                token = strtok(NULL, ",");
                strcpy(teste[i], token);
                fflush(stdout);
                i++;
            }
        }
    }
    fclose(fp);
    if (flag == 1)
    {
        pokemon->id = atoi(teste[0]);
        strcpy(pokemon->name, teste[1]);
        strcpy(pokemon->type1, teste[2]);
        strcpy(pokemon->type2, teste[3]);
        pokemon->total = atoi(teste[4]);
        return (pokemon);
    }
    return NULL; // SE N ACHAR ID RETORNA NULL?
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
Node *insert(Node *head, int id)
{
    if (id <= 0 || id > 151) // n existe no arquivo
        return head;
    if (head == NULL)
        return (createNode(id));

    if (id < head->id)
        head->left = insert(head->left, id);
    else if (id > head->id)
        head->right = insert(head->right, id);
    else
        return head; // nao atualiza a arvore, valores repetidos

    // atualiza a altura
    head->height = heightOfTree(head);

    // saber se esta balanceada
    int balance = balancingFactor(head);

    // esquerdona
    if (balance > 1 && id < head->left->id)
        return rightRotation(head);

    // direitona
    if (balance < -1 && id > head->right->id)
        return leftRotation(head);

    // esquerda direita
    if (balance > 1 && id > head->left->id)
    {
        head->left = leftRotation(head->left);
        return rightRotation(head);
    }

    // direita esquerda
    if (balance < -1 && id < head->right->id)
    {
        head->right = rightRotation(head->right);
        return leftRotation(head);
    }

    return head;
}
void printAVL(Node *node, int tab)
{
    for (int i = 0; i < tab; i++)
        printf("-");
    if (node)
    {
        printf("%d\n", node->id);
        printAVL(node->left, tab + 2);
        printf("\n");
        printAVL(node->right, tab + 2);
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
            if (head->left)
                aux = head->left;
            else
                aux = head->right;

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
    Node *aux = buscaID(head, id);

    if (aux)
        printf("ID: %d\nPokemon: %s\nTipo 1: %s\nTipo 2: %s\nTotal: %d\n", aux->data->id, aux->data->name, aux->data->type1, aux->data->type2, aux->data->total);
    else
        printf("Pokemon inexistente.\n");
}
void order(Node *head)
{
    if (head == NULL)
        return;
    order(head->left);
    printf("%d ", head->id);
    order(head->right);
}
Node *edit(Node *head, int id)
{
    Node *aux = buscaID(head, id);
    if (aux)
    {
        printf("\nPokemon NOME: ");
        scanf("%s", aux->data->name);
        printf("\nPokemon TYPE1: ");
        scanf("%s", aux->data->type1);
        printf("\nPokemon TYPE2: ");
        scanf("%s", aux->data->type2);
        printf("\nPokemon TOTAL: ");
        scanf("%d", &aux->data->total);
    }
    return head;
}
Node *buscaID(Node *head, int id)
{
    Node *aux = head;

    while (aux && aux->id != id)
    {
        if (id > aux->id)
            aux = aux->right;
        else
            aux = aux->left;
    }
    return aux;
}
int ammountOfNodes(Node *head)
{
    if (head == NULL)
        return 0;
    else
        return 1 + ammountOfNodes(head->left) + ammountOfNodes(head->right);
}