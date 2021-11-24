#include <iostream>
#include <stdio.h>

using namespace std;

int main(){
    int list[50];
    int temp;
    int i{0};
    for(i=0; i<50; i++){
        scanf("%d", &temp);
        if(temp>0){
            list[i]=temp;
        }
        else{
            cout << "Numero non valido, esco" << endl;
            break;
        }
    }
    cout << "Letti " << i << " valori" << endl;
    for(int j=0; j<i; j++){
    cout << list[j] << " " ;
    }
}