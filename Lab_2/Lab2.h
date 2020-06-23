//LIBRERIAS UTILIZADAS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//CONSTANTES DEFINIDAS.

#define OPTION 5
#define NAME_FILE 25
#define WORD 5

//STRUCTS UTILIZADOS.

typedef struct{
    int totalCapital;
    int investmentAmount;
}Capital;

typedef struct{
    int* investment;
    int* benefit;
}Investment;

//PROCEDIMIENTOS DEFINIDOS.

Investment* readFileInvestment(char* fileName,Capital capital,Investment* investment);
Capital readFileCapital(char* fileName,Capital capital);
int max(int a, int b);
int knapSack(int W, int wt[], int val[], int n);
void getSolutionCombination(int arr[],int benefit[],int totalCapital,int data[], int start, int end, int index, int r,int length);
void printCurrent(int arr[],int benefit[],int totalCapital,int data[], int start, int end, int index, int r,int length);
void printCombination(int investment[],int benefit[],int totalCapital, int length);
int backtracking(char* fileName);
void menu();
int main();