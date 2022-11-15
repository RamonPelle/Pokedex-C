typedef struct pokemon
{
    int id;
    char name[30];
    char type1[15];
    char type2[15];
    int total;
} Pokemon;

typedef struct node
{
    int id;     // quando maior que ID vai pra direita, menor esquerda.
    int height; // altura da arvore
    struct node *left;
    struct node *right;
    Pokemon *data;
} Node;
int heightOfTree(Node *head);
int max(int a, int b);
Node *min(Node *head);
Pokemon *createPokemon(int id);
Node *createNode(int key);
Node *rightRotation(Node *head);
Node *leftRotation(Node *head);
int balancingFactor(Node *head);
Node *insert(Node *node, int key);
void printAVL(Node *nodo, int tab);
Node *deleteNode(Node *head, int id);
void *printPokemon(Node *head, int id);
void order(Node *head);
Node *edit(Node *head, int id);
Node *buscaID(Node *head, int id);
int ammountOfNodes(Node *head);