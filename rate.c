#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

struct pets
{
    char petName[8];
    short rating;
};

int main()
{
    int i, no = 7, r1, r2, power, choice, e1, e2, k=16; //r1,r2 are randon integers for faceoff.. choice = user choice.. e1,e2 = estimated scores for pets.. k = elo constant..
    char petNames[7][8]= {
        {"Cat"},{"Dog"},{"Bird"},{"Rabbit"},{"Rat"},{"Penguin"},{"Bear"}
    };
    struct pets pet[no];

    for (i=0; i<no; i++)
    {
        strcpy(pet[i].petName,petNames[i]);
        pet[i].rating = 400;
    }

    printf("Choose between one : \n");
    for(i=0; i<5; i++)
    {
        r1= rand()%no;
        r2= rand()%no;
        printf("1.) %s\t\t2.) %s\n",pet[r1],pet[r2]);
        scanf("%d", &choice);
        power= pow(10,(pet[r2].rating-pet[r1].rating)/400);
        e1 = 1/(1+power);
        power= pow(10,(pet[r1].rating-pet[r2].rating)/400);
        e2 = 1/(1+power);
        printf("%d\t%d\n",power,e2);
        if(choice==1)
        {
            pet[r2].rating=pet[r2].rating-k*(e2);
            pet[r1].rating+=k*(1-e1);
        }
        else
        {
            pet[r2].rating+=k*(1-e2);
            pet[r1].rating=pet[r1].rating-k*(e1);
        }
    }
    for (i=0; i<no; i++)
    {
        printf("The current ratings stand as : %d for %s.\n", pet[i].rating, pet[i].petName);
    }
}