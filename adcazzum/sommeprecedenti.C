#include <stdio.h>

#define NVAL 5

void sommeprecedenti(float * valori, int n_val, float * somme);

int main(){
    float valori[NVAL], somme[NVAL];
    for(int i=0; i<NVAL; i++){
        scanf("%f", &valori[i]);
    }
    sommeprecedenti(valori, NVAL, somme);
    for(int i=0; i<NVAL; i++){
        printf("%f \t", somme[i]);
    }
    printf("\n");
    return 0;
}

void sommeprecedenti(float * valori, int n_val, float * somme){
    somme[0] = valori[0];
    for(int i=1; i<n_val; i++){
        somme[i] = somme[i-1] + valori[i];
    }
}