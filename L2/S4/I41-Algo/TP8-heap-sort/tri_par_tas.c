#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define N 1000


typedef unsigned int uint;
unsigned long long comp = 0;

void print_tas(int *arr, unsigned int n) {
    int depth = floor(log(n)/log(2));
    int k = 0, mid;
    for (int j = 0; j <= depth; j++) {
        for (int i = 0; i < pow(2,depth-j) - 1; i++) {
            printf(" ");
        }

        for(int l = 0; k < n && l < pow(2,j); l++) {
            printf("%d", arr[k]);
            k++;
            for (int i = 0; i < pow(2,depth-j+1)-1; i++) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void swap(int *arr, int i, int j) {
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

void tamiser(int *arr, unsigned int i, unsigned int n) {
    /* 
     ***NAIF ALGO***

    int iright_child = i*2+1;
    int ileft_child = i*2+2;
    print_tas(arr,14);

    if (ileft_child <= n) {
        if (arr[iright_child] < arr[ileft_child] && arr[ileft_child] > arr[i]) {
            swap(arr,ileft_child, i);
            tamiser(arr, ileft_child, n);
        } else if (arr[iright_child] > arr[i]){
            swap(arr, iright_child, i);
            tamiser(arr, iright_child, n);
        }
    }
    else if (iright_child <= n && arr[iright_child] > arr[i]) {
        swap(arr, iright_child, n);
    }
    */
    //print_tas(arr,14);
    int child = 2*i+1;
    if (child < n && arr[child+1] > arr[child]) 
        child += 1;
    if (child <= n && arr[child] > arr[i]) {
        swap(arr, child, i);
        tamiser(arr, child, n);
    comp += 2;
    }
}

void gen_perm(int *new_arr, int n) {
    uint tmp;
    for (uint i = 0; i < n; i++) {
        tmp = rand() % (n-i) + i;
        swap(new_arr, i, tmp);    
    }
}

void entasser(int *arr, unsigned int n) {
    int node = n/2 - 1;
    while (node >= 0) {
        //printf("---->%d\n", node);
        //print_tas(arr,n);
        tamiser(arr, node, n-1);
        node--;
    }
}

void tri_tas(int *arr, unsigned int n) {
    entasser(arr, n);
    //print_tas(arr, n);
    for (int i = n-1; i > 0; i--) {
        swap(arr, 0, i);
        tamiser(arr, 0, i-1);
    }
}

unsigned long long fact (uint n) {
    uint res = 1;
    while (n) {
        res *= n;
        n--;
    }
    return res;
}
    
void main(int argc, char **argv) {
    //int liste[] = {0,1,2,3,4,5,6,7,8,9};
    //print_tas(liste, 10);
    //entasser(liste, 9);
    //print_tas(liste, 10);
    //tri_tas(liste, 10);
    //print_tas(liste, 10);
    unsigned long long nlogn;
    uint fact_n = fact(N);
    srand(time(NULL));
    FILE *file = fopen("tri_tas", "w");
    fprintf(file, "nlogn tri-tas\n0 0\n");
    for (int i = 1; i < N; i++) {
        int *tab = calloc(i, sizeof(int));
        for (int j = 0; j < i; j++) 
            tab[j] = j+1;
        int j;
        for (j = 0; j < 50 ; j++) {
            gen_perm(tab, i);
            tri_tas(tab, i);
        }
        nlogn = i*(log(i)/log(2));
        fprintf(file, "%lld %lld\n", nlogn, comp/50);
        comp = 0;
        free(tab);
        
    }
    fclose(file);
}

