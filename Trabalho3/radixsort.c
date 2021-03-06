#include "getMax.c"
void countingsort(int *vet, int n, int exp) { 
    int saida[n];
    int i, cont[10] = {0}; //Todas as posições incialmente como 0
  
    
    for (i = 0; i < n; i++) 
        cont[(vet[i] / exp) % 10]++; 
  
    for (i = 1; i < 10; i++) 
        cont[i] += cont[i - 1]; 
  
    
    for (i = n - 1; i >= 0; i--) { 
        saida[cont[(vet[i] / exp) % 10] - 1] = vet[i]; 
        cont[(vet[i] / exp) % 10]--; 
    }

    for (i = 0; i < n; i++) 
        vet[i] = saida[i]; 
} 

void radixsort(int *vet, int n) { 
    
    int m = getMax(vet, n); 

    for (int exp = 1; m / exp > 0; exp *= 10) 
        countingsort(vet, n, exp); 
} 