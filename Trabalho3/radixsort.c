#include "getMax.c"
void countSort(int arr[], int n, int exp) 
{ 
    int output[n];
    int i, count[10] = {0}; //Todas as posições incialmente como 0
  
    
    for (i = 0; i < n; i++) 
        count[(arr[i] / exp) % 10]++; 
  
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    
    for (i = n - 1; i >= 0; i--) { 
        output[count[(arr[i] / exp) % 10] - 1] = arr[i]; 
        count[(arr[i] / exp) % 10]--; 
    }

    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 

void radixsort(int *vet, int n) { 
    
    int m = getMax(vet, n); 

    for (int exp = 1; m / exp > 0; exp *= 10) 
        countSort(vet, n, exp); 
} 