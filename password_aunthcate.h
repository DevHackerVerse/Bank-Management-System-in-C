#include <stdio.h>
#include <string.h>
#include<conio.h>
#include<stdlib.h>

void fordelay(int j)
{   int i,k;
    for(i=0;i<j;i++)
         k=i;
}

void password_aunthcate()
{

    char ch;
    char pass[20], saved_pass[20], user_name[20], saved_name[20];

name:
    printf("Enter username : ");
    scanf("%s", user_name);

    FILE *ptr;
    ptr = fopen("password.dat", "r");

    fscanf(ptr, "%s%s", saved_name, saved_pass);
    if (strcmp(user_name, saved_name) != 0)
    {
        printf("\n********INCORRECT USERNAME******** \nPlease Try again\n");
        goto name;
    }
    else
    {
    start:
        printf("Enter password: ");
        int i = 0;
        while (1)
        {
            ch = getch();
            if (ch == 13)
            {
                pass[i] = '\0';
                break;
            }
            else if (ch == 8)
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else if (ch == 9 || ch == 32)
            {
                continue;
            }
            else
            {
                pass[i++] = ch;
                printf("*");
            }
        }

        int l = strcmp(pass, saved_pass);
        if (l == 0)
        {
            printf("\n********LOGIN SUCCESSFULL********\n");
            printf("LOADING");
            for (i=0;i<=6;i++)
            {
                fordelay(100000000);
                printf(".");
            }
        }
        else
        {
            printf("\n********INCORRECT PASSWORD******** \n");
            goto start;
        }
    }
}