typedef struct pokemon
{
    int id;
    char name[30];
    char form[30];
    char type1[15];
    char type2[15];
    int total;
    int hp;
    int attack;
    int defense;
    int spAttack;
    int spDefense;
    int speed;
    int gen;
    struct pokemon *next;
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
Pokemon *createPokemon(int id);
Node *createNode(int key);
Node *rightRotation(Node *head);
Node *leftRotation(Node *head);
int balancingFactor(Node *head);
Node *insert(Node *node, int key);
void printAVL(Node *nodo, int tab);
Node *min(Node *head);
Node *deleteNode(Node *head, int id);
void *insertPokemon(Node *head, int idPokemon);
void *printPokemon(Node *head, int id);