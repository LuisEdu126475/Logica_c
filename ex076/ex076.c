#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int main(){
    int l,c,matriz[5][5];
    srand(time(NULL));
    for(l=0;l<5;l++){

        for ( c = 0; c < 5; c++){
            matriz[l][c]= 10 + rand()%90;
            
        }
        for ( l = 0; l < 5; l++)
        {
            for ( c = 0; c < 5; c++)
            {
            printf("%d\t",matriz[l][c]);
        }
        printf("\n");
    }
    printf("\nDiagonal principal:\n");
    for ( l = 0; l < 5; l++){
        for(c=0;c<5;c++){
            if(l==c){
                printf("%d\t",matriz[l][c]);
            }
        }
        else{
            printf("\t");
        }
    }
    printf("\n");
}

}