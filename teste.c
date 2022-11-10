#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./libs/zString/src/zstrtok.h"
int main()
{

    FILE *fp = fopen("./libs/Pokemon.csv", "r");

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