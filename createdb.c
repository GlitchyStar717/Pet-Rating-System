#include<stdio.h>
#include<windows.h>
#include "myHeader.h"


int main()
{
    int i, no, sizeName=10;

    
    FILE *ratings;

    ratings=fopen("ratings.bin","rb");
    if (ratings != NULL)
    {
        printf("There is already a database \"ratings.bin\" that exists . Please copy it or rename to run this program..\n");
        MessageBox(NULL, "Database already exists. Please, rename, relocate or delete the \"ratings.bin\" first and re run the program. Or use RatingApp.exe to rate.", "Error 77", MB_ICONERROR | MB_OK);
        return 1;
    }

    printf("Enter the no of Pets you want to compete.\n");
    scanf("%d",&no);
    struct pets pet[no],temp;


    ratings=fopen("ratings.bin","wb");

    fwrite(&no, sizeof(int),1,ratings);

    pet[0].rating=400;
    for(i=0;i<no;i++)
    {   
        printf("Enter Pet %d : ",i);
        scanf("%s",&pet[i].petName);
        fwrite(&pet[0].rating, sizeof(short),1,ratings);
        fwrite(&pet[i].petName,sizeName,1,ratings);

    }


}
