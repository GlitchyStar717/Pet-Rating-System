#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include "myHeader.h"

float estimate(int, int);

int main()
{
    int i, j, no = 7, r1, r2, k=32, exchange; //r1,r2 are randon integers for faceoff.. choice = user choice..  k = elo constant.. excahnge = point that is exchanged after each battle
    char choice;
    float e1, e2; //e1,e2 = estimated scores for pets..
    char petNames[7][8]= {
        {"Cat"},{"Dog"},{"Bird"},{"Rabbit"},{"Rat"},{"Penguin"},{"Bear"}
    };
    struct pets pet[no],temp;

    FILE *ratings;
    
    
    ratings=fopen("ratings.bin","rb");
    if (ratings == NULL)
    {
        printf("Since we did not find any initial ratings, so please create a new database of ratings using createDB.\n");
        Sleep(10000);
        AllocConsole();
        MessageBox(FindWindowA("ConsoleWindowClass",NULL),"Please Create DB first using MakeDBinitially.exe","ERROR 717",MB_OK);
        return 1;
    }
    
    for(i=0;i<no;i++)
    {
        fread(&pet[i].rating, sizeof(pet[i].rating),1,ratings);
    }


    for (i=0; i<no; i++)
    {
        strcpy(pet[i].petName,petNames[i]);
    }

    printf("Choose one between them : \n");
    while(1==1)
    {
        //generate two random face off opponents
        r1= rand()%no;
        r2= rand()%no;
 
        while(r2 == r1)
        {
            r2= rand()%no;
        }

        printf("1.) %s\t\t2.) %s\t\t3.)Quit\n",pet[r1],pet[r2]);        //display the opponents
        scanf(" %c", &choice);
        while (choice != '1' && choice != '2' && choice != '3')      // ask for input until its 1 or 2 or 3
        {
            printf("Please re enter the option from 1 to 3.");
            scanf(" %c", &choice);
        }

        if(choice == '3')
        {
            break;
        }
        e1 = estimate(pet[r1].rating, pet[r2].rating); // estimate the scores
        e2 = 1-e1;


        if(choice=='1') // exchange the points between loser and winner
        {
            exchange = k*(1-e1);
            pet[r1].rating += exchange;
            pet[r2].rating -= exchange;
        }
        else
        {
            exchange = k*(1-e2);
            pet[r1].rating -= exchange;
            pet[r2].rating += exchange;
        }
    }

        fclose(ratings);
        ratings=fopen("ratings.bin","wb");
    
    for(i=0;i<no;i++)
    {
        fwrite(&pet[i].rating, sizeof(pet[i].rating),1,ratings);
    }

    for (i=0; i<no; i++)    //sort the winners
    {
        for(j=i;j<no;j++)
        {
            if (pet[i].rating< pet[j].rating)
            {
                temp= pet[i];
                pet[i]=pet[j];
                pet[j]=temp;
            }
        }
    }

    printf("The winnnnnnerr iss %s with a total score of %d\n", pet[0].petName, pet[0].rating); //print the winner

    //display the sorted final scores.
    printf("The sorted order stands as : \n");
    for (i=0; i<no; i++)    
    {
        printf(" %-8s : %d\n", pet[i].petName, pet[i].rating);
    }

    return 0;
    fclose(ratings);

}

float estimate (int r1, int r2)    // based on formulas for elo rating
{
    float x,y,z,result;
    x = ((float)r2-r1)/400;
    y = pow(10,x);
    z = 1+y;
    result = 1/z;
    return result;
}
