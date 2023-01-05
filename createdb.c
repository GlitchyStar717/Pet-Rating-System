#include<stdio.h>

struct pets
{
    char petName[8];
    short rating;
};

float estimate(int, int);

int main()
{
    int i, no=7;
    struct pets pet[no],temp;

    FILE *ratings;

    ratings=fopen("ratings.bin","wb");
    
    pet[0].rating=400;
    for(i=0;i<no;i++)
    {
        fwrite(&pet[0].rating, sizeof(short),1,ratings);
    }


}
