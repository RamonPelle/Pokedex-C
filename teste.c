#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main()
{
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
    FILE *fp = fopen("Pokemon.csv", "r");

    char row[152];
    char *token;

    while (feof(fp) != 1)
    {
        fgets(row, 152, fp);
        printf("Row: %s", row);

        token = strtok(row, ",");

        char teste[6][30] = {};
        int i = 0;
        while (token != NULL)
        {
            printf("Token: %s\n", token);
            token = strtok(NULL, ",");
            strcpy(teste[i][30], token);
            i++;
        }

        i = 0;
        while (i != 4)
        {
            printf("\n%s\n", teste[i][30]);
            i++;
        }
    }
    fclose(fp);
}

// char row[152];
// char *token;
// while (feof(fp) != 1)
// {
//     fgets(row, 152, fp);

//     token = strtok(row, ",");

//     while (token != NULL)
//     {
//         printf("Token: %s\n", token);
//         token = strtok(NULL, ",");
//     }
// }