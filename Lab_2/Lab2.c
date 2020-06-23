#include "Lab2.h"

//Prodecimiento que dado una array y un numero, busca dicho numero en el array y retorna el indice.
//Entrada: Array de integer y entero que se buscara dentro del array.
//Salida: Integer que representa la posicion del numero.
int getIndex(int array[],int number, int lenght){
    for(int i = 0;i < lenght; i++){
        if(number == array[i]){
            return i;
        }
    }
    return -1;
}

//Procedimiento que lee el archivo de entrada y obtiene la cantidad de inversiones y el capital total presentes en el archivo.
//Entrada: Char* que representa el nombre del archivo a leer, Strut Capital, Struct Investment.
//Salida: Integer que representa la cantidad de instrucciones.
Investment* readFileInvestment(char* fileName,Capital capital,Investment* investment){
    FILE* file;
    char fileAux[50];
    char* result;
    int i = 0;

    investment = (Investment*)malloc(sizeof(Investment));
    investment->investment = (int*)malloc(sizeof(int) * capital.investmentAmount);
    investment->benefit = (int*)malloc(sizeof(int) * capital.investmentAmount);

    file = fopen(fileName,"r");
    if(file == NULL){
        printf("El archivo no existe...\n");
        return investment;
    }
    else{
        fscanf(file," %[^\n]",fileAux);
        fscanf(file," %[^\n]",fileAux);
        while(!feof(file)){
            fscanf(file," %[^\n]",fileAux);
            result = strtok(fileAux," ,()");
            investment->investment[i] = atoi(result);
            result = strtok(NULL," ,()");
            investment->benefit[i] = atoi(result);
            i++;
        }
    }

    fclose(file);
    return investment;
}

//Procedimiento que lee el archivo de entrada y obtiene la cantidad de inversiones y el capital total presentes en el archivo.
//Entrada: Char* que representa el nombre del archivo a leer, Struct Capital.
//Salida: Integer que representa la cantidad de instrucciones.
Capital readFileCapital(char* fileName,Capital capital){
    FILE* file;
    char fileAux[50];
    capital.totalCapital = -1;
    capital.investmentAmount = -1;

    file = fopen(fileName,"r");
    if(file == NULL){
        printf("El archivo no existe...\n");
        return capital;
    }
    else{
        fscanf(file," %[^\n]",fileAux);
        capital.totalCapital = atoi(fileAux);
        fscanf(file," %[^\n]",fileAux);
        capital.investmentAmount = atoi(fileAux);
    }

    fclose(file);
    return capital;
}

//Procedimiento que dado dos numeros enteros, devuelve el numero mayor.
//Entrada: Integer a e integer b, que son los enteros a comparar.
//Salida: Integer que representa el numero mayor entre a y b.
int max(int a, int b) { return (a > b) ? a : b; } 

//Procedimiento que dado la logica del problema de la mochila, entrega el maximo beneficio dado un array de beneficios y un array de pesos.
//Entrada: Integer W que corresponde al maximo peso de la mochila, Int array wt que corresponde a las inversiones, INt array val que corresponde al beneficio de cada inversiones
//y integer n que corresponde al largo de los array.
//Salida: Integer que corresponde al beneficio máximo posible dado las distintas inversiones y sus beneficios.
int knapSack(int W, int wt[], int val[], int n){ 
   // Base Case 
   if (n == 0 || W == 0) 
       return 0; 
  
   // If weight of the nth item is more than Knapsack capacity W, then 
   // this item cannot be included in the optimal solution 
   if (wt[n-1] > W) 
       return knapSack(W, wt, val, n-1); 
  
   // Return the maximum of two cases:  
   // (1) nth item included  
   // (2) not included 
   else return max( val[n-1] + knapSack(W-wt[n-1], wt, val, n-1), 
                    knapSack(W, wt, val, n-1) 
                  ); 
} 

//Procedimiento que dado a la generación de combinaciones y que busca la combinacion que corresponda al beneficio máximo, una vez que lo encuentra procede a escribir la informaciones pertinente en un archivo de salida.
//Entrada: Int array de inversiones y beneficios, int capital total disponible y parametros para poder realizar la recursion y generar las combinaciones.
//Salida: No posee salida.
void getSolutionCombination(int arr[],int benefit[],int totalCapital,int data[], int start, int end, int index, int r,int length){ 
    // Current combination is ready to be printed, print it 
    if (index == r) 
    { 
        int maxBenefit = knapSack(totalCapital,arr,benefit,length);
        int count = 0;
        int count2= 0;
        int count3 = 0;

        for(int i = 0; i < r; i++){
            count += data[i];
        }
        
        for (int j=0; j<r; j++){
            if(count <= totalCapital){
                count2 += data[j];
                count3 += benefit[getIndex(arr,data[j],length)];
            }
        }

        if(count3 == maxBenefit){
            FILE* file;
            char* aux = (char*)malloc(sizeof(char) * 25);
            file = fopen("Salida.out","wt");
            sprintf(aux, "%d", count2);
            fputs(aux,file);
            fputs(" ",file);
            sprintf(aux, "%d", count3);
            fputs(aux,file);
            fputs("\n",file);
            if(maxBenefit != 0){
                for(int j=0; j<r; j++){
                    sprintf(aux, "%d", data[j]);
                    fputs(aux,file);
                    fputs(" ",file);
                    sprintf(aux, "%d", benefit[getIndex(arr,data[j],length)]);
                    fputs(aux,file);
                    fputs("\n",file);
                }
            }
            
            fclose(file);
        }
    } 
  
    // replace index with all possible elements. The condition 
    // "end-i+1 >= r-index" makes sure that including one element 
    // at index will make a combination with remaining elements 
    // at remaining positions 
    for (int i=start; i<=end && end-i+1 >= r-index; i++) 
    { 
        data[index] = arr[i]; 
        getSolutionCombination(arr, benefit,totalCapital,data, i+1, end, index+1, r, length); 
    } 
} 

//Procedimiento que permite imprimir como se van generando todas las combinaciones, muestra por pantalla la combinacion, el monto de inversion y beneficio que lleva acumulado.
//Entrada: Int array de inversiones y beneficios, int capital total disponible y parametros para poder realizar la recursion y generar las combinaciones.
//Salida: No posee salida.
void printCurrent(int arr[],int benefit[],int totalCapital,int data[], int start, int end, int index, int r,int length){     
        // Current combination is ready to be printed, print it 
        if (index == r) 
        { 
            int count = 0;
            int count2 = 0;
            int count3 = 0;

            for(int i = 0; i < r; i++){
                count += data[i];
            }

            #ifdef DEBUG
            while(getchar() != '\n');

            for (int j=0; j<r; j++){
                if(count > totalCapital) break;
                else{
                    count2 += data[j];
                    count3 += benefit[getIndex(arr,data[j],length)];
                    printf("%d ",data[j]); 
                }
            }
            if(count2 != 0){
                printf("\nSu peso es: %d y su beneficio total es: %d \n",count2, count3);
                printf("\n");
                printf("Presione Enter para continuar...\n");
            }
            else{
                for (int j=0; j<r; j++){
                    printf("%d ",data[j]); 
                }
                printf("\nCombinacion invalida, no se ha tomado en cuenta\n");
                printf("\n");
                printf("Presione Enter para continuar...\n");
            }
            #endif 
        } 
    
        // replace index with all possible elements. The condition 
        // "end-i+1 >= r-index" makes sure that including one element 
        // at index will make a combination with remaining elements 
        // at remaining positions 
        for (int i=start; i<=end && end-i+1 >= r-index; i++) 
        { 
            data[index] = arr[i]; 
            printCurrent(arr, benefit,totalCapital,data, i+1, end, index+1, r, length); 
        }
} 

//Procedimiento que dado un array de inversiones, un array de beneficios y el largo de estos arrays, realiza el print current desde 0 hasta el largo del array.
//Entrada: Int array de inversiones, Int array de beneficios, int capital total y largo de los arrays.
//Salida: No posee salida.
void printCombination(int investment[],int benefit[],int totalCapital, int length){ 
    
    //Array que contiene a las combinaciones validas.
    int data[length]; 

    for(int i = 0; i <= length; i++){
        printCurrent(investment,benefit,totalCapital,data, 0, length-1, 0, i, length);
        getSolutionCombination(investment,benefit,totalCapital,data, 0, length-1, 0, i, length); 
    }
} 

//Prodecimiento dadotodas las variables que solicitaron memoria en este programa, libera la memoria solicitaa por cada una de estas.
//Entrada: Struct investment y int** matrix, el primero representa a los objetos que entraran a la mochila, el segundo la matriz solución.
//Salida: No posee salida.
void freeMemory(Investment* investment){
    free(investment);
}

//Procedimiento "BackTracking" que dado el nombre del archivo de entrada, acciona las demas funciones siguiendo la logica de backtracking.
//Entrada: Char* que representa el nombre del archvio de entrada.
//Salida: No posee salida.
int backTracking(char* fileName){
    Capital capital;
    Investment* investment;

    capital = readFileCapital(fileName,capital);
    if(capital.investmentAmount == -1) return 0;
    else{
        investment = readFileInvestment(fileName,capital,investment);
        printf("\n");
        printCombination(investment->investment,investment->benefit,capital.totalCapital,capital.investmentAmount);
        freeMemory(investment);
        return 1;
    }
}

//Procedimiento que despliega un menu en consola para que el usuario ponga en marcha la fuerza bruta.
//Entrada: No posee entrada.
//Salida: No posee salida.
void menu(){
    char* option = (char*)malloc(sizeof(char)* OPTION);
    char* fileName = (char*)malloc(sizeof(char) * NAME_FILE);
    int auxInt;

    while(true){
        printf("\nSeleccione una opción...\n");
        printf("1- Ingresar nombre de archivo con la lista de posibles inversiones.\n");
        printf("2- Salir del programa.\n");
        printf("Opcion: ");
        scanf("%s",option);
        if(strcmp("1",option) == 0){
            printf("Ingrese el nombre de archivo de texto: ");
            scanf("%s",fileName);
            auxInt = backTracking(fileName);
        }
        else if(strcmp("2",option) == 0){
            printf("\nCerrando...\n\n");
            free(option);
            free(fileName);
            break;
        }
        else{
            printf("\nIngrese una opcion valida.\n\n");
        }
    }
}

//Procedimiento inicia la ejecucion el programa.
//Entrada: No posee entrada.
//Salida: Retorna un integer para terminar la ejecucion del programa.
int main(){
    menu();
    return 0;
}