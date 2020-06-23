#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Lab1.h"

//Funcion que calcula el factorial dado un numero.
//Entrada: Un integer.
//Salida: Un integer que representa el factorial del numero ingresado como parametro.
int factorial(int quantityVertex){
    int count = 1;
    while(quantityVertex != 0){
        count = quantityVertex * count;
        quantityVertex -= 1;
    } 
    return count;
}

//Funcion que dado un array de integer de N elementos, retorna el integer de menor valor dentro del arreglo.
//Entrada: Un array de int donde se buscara, un integer que representa el largo del array.
//Salida: Un integer que representa el numero minimo que tiene el array.
int getMin(int* array,int quantityVertex){
    int min = array[0];
    for(int i = 1; i < factorial(quantityVertex)/ 2; i++){
        if(array[i] < min){
            min = array[i];
        }
    }
    return min;
}

//Funcion que dado un numero y un array de integer, retorna el indice donde se encuentra dicho numero en el array.
//Entrada: Un integer que es el numero que se buscara, un array de int donde se buscara el numero, un integer que representa el largo de array.
int getMinIndex(int min,int* array,int quantityVertex){
    int aux;
    for(int i = 0; i < factorial(quantityVertex);i++){
        if(min == array[i]){
            aux =  i;
        }
    }
    return aux;
}

//Funcion que dado un array de integer, retorna el array invertido.
//Entrada: Un array de integer el cual se invertira, un integer que representa el largo del array.
//Salida: Un array de integer que es el inverso de array entregado como parametro.
int* reverseArray(int* vertex,int quantityVertex){
    int aux = quantityVertex;
    int* reverseArray = (int*)malloc(sizeof(int)*quantityVertex);
    int j = 0;
    for(int i = aux - 1; i >= 0; i--){
        reverseArray[j] = vertex[i];
        j += 1;
    }
    
    return reverseArray;
}

//Funcion que dado un array de vectores (Formato "[1 2 3]"), verifica si los dos numeros enteros entregados como parametros corresponden
// a los existentes en las dos primeras casillas del array, si esto es cierto retorna la tercera casilla.(Valor del camino 1 - 2).
//Entrada: Dos integer que son los numeros a comparar, un array de array de int que es donde se buscaran los numeros, un integer que
//representa el largo del array.
//Salida: Integer que representa el valor de camino desde "path1" a "path2"
int getPathValue(int path1, int path2, int** vertexArray, int quantityInstructions){
    int aux;

    for(int i = 0; i < quantityInstructions; i++){
        if((path1 == vertexArray[i][0] && path2 == vertexArray[i][1]) || (path2 == vertexArray[i][0] && path1 == vertexArray[i][1])){
            aux = vertexArray[i][2];
        }
    }
    return aux;
}

//Funcion que dado un array que representa a una posible combinacion, calcula el peso total de dicha combinacion.
//Entrada: Un array integer "actualCombination" que representa la combinacion a estudiar, un entero quantityVertex que representa
//el largo de "actualCombination", un array de array integer que representa todos los caminos leidos y un integer
//quantityisntructions que representa el largo de vertexArray.
//Salida: Integer que representa el peso total de la combinacion.
int getCombinationValue(int* actualCombination, int quantityVertex, int** vertexArray, int quantityInstructions){
    int pathValue = 0;
    int aux;
    for(int i = 0; i < quantityVertex - 1; i++){
        aux = getPathValue(actualCombination[i],actualCombination[i + 1],vertexArray,quantityInstructions);
        pathValue += aux;
    }
    return pathValue;
}

//Funcion que dado un array de combinaciones posibles, calcula todos sus respectivos pesos y los guarda en un array.
//Entrada: Dos array de array de integers, uno representa todas las combinaciones posibles y el otro representa las instrucciones
//a considerar, y dos integer que representan el largo de los arrays.
//Salida: Array de integer el cual representa los pesos de las combinaciones posibles.
int* getAllCombinationsValue(int** actualCombination, int quantityVertex, int** vertexArray, int quantityInstructions){
    int* valueArray = (int*)malloc(sizeof(int) * factorial(quantityVertex) / 2);
    for(int i = 0; i < factorial(quantityVertex) / 2; i++){
        valueArray[i] = getCombinationValue(actualCombination[i],quantityVertex,vertexArray,quantityInstructions);
    }
    return valueArray;
}

//Funcion que verifica si un array de integer esta contenido dentro de un array de array de integers.
//Entrada: Array de array integer que es donde se comparara el array de integer, y un integer que representa el largo de ambos array.
//Salida: Bool, True si el array esta contenido, Falso en caso contrario.
bool inListArray(int** array, int* secondArray, int quantityVertex){
    if(array == NULL){
        return false;
    }
    else{
        int fact = factorial(quantityVertex)/2;
        for(int i = 0; i < fact; i++){
            int count = 0;
            for(int j = 0; j < quantityVertex; j++){
                if(array[i][j] == secondArray[j]){
                    count += 1;
                    if (count == quantityVertex){
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

//Funcion que dado un array de combinaciones posibles, elimina los array los cuales su inverso esta repetido.
//Entrada: Array de array de integer que representa las combinaciones, integer que representa el largo del array.
//Salida: Array de array de integer que representa las combinaciones que no se repite su inverso.
int** getActualCombinations(int** combinations,int quantityVertex){
    int fact = factorial(quantityVertex);
    bool verify = true;
    int j = 0;
    int value = fact / 2;
    int** actualCombinations = (int**)malloc(sizeof(int*) * value);
    for(int i = 0; i < value; i ++){
        actualCombinations[i] = (int*)malloc(sizeof(int*) * quantityVertex);
    }
    for(int i = 0; i < fact; i++){
        verify = inListArray(actualCombinations,reverseArray(combinations[i],quantityVertex),quantityVertex);
        if(verify == false){
            actualCombinations[j] = combinations[i];
            j += 1;
        }
    }

    return actualCombinations;
}

//Funcion que dado un array que representa una combinacion posible, imprime dicha combinacion de manera que se van creando.
//Entrada: Array de int que representa la combinación, Integer que representa el largo del array.
//Salida: No posee salida.
void printCurrent(int* combination,int quantityVertex){
    #ifdef DEBUG
    while(getchar() != '\n');
        printf("La combinacion es: ");
        for(int i = 0; i < quantityVertex; i++){
            printf("%d",combination[i]);
        }
        printf("\n");
        printf("Presione Enter para continuar...\n");
    #endif
}

//Funcion que dado un vector 'generico' y el largo de este vector, genera todas las combinaciones posibles.
//El vector generico es uno que contiene todos los vectores sin repeticion. EJ: Cantidad de vertices 5, vector generico ->(1,2,3,4,5)
//Entrada: Array de integer que representa al vector generico, y un integer que representa el largo del array.
int** generateCombinations(int quantityVertex, int* actualVertex){
    int count = 0;
    int i,j;
    int quantityCombinations = factorial(quantityVertex);
    int aux;

    int** combinations = (int**)malloc(sizeof(int*) * quantityCombinations);
    for(int i = 0; i < quantityCombinations; i++)
    {
        combinations[i] = (int*)malloc(sizeof(int)*quantityVertex);
    }
    printf("\n");
    while (count != quantityCombinations) {
        printCurrent(actualVertex,quantityVertex);
        for(int i = 0; i < quantityVertex; i++){
            combinations[count][i] = actualVertex[i];
        }
        i=quantityVertex-2;
        while(actualVertex[i] > actualVertex[i+1] ) i--;
        j=quantityVertex-1;
        while(actualVertex[j] < actualVertex[i] ) j--;
        aux=actualVertex[j];
        actualVertex[j]=actualVertex[i];
        actualVertex[i]=aux;
        i++;
        for (j = quantityVertex-1; j > i; i++, j--) {
            aux = actualVertex[i];
            actualVertex[i] = actualVertex[j];
            actualVertex[j] = aux;
        }
    count++;
   }
   return combinations;
}

//Funcion que dado un array de integer, los ordena de forma creciente.
//Entrada: Array de integer a revisar, integer que representa el largo del array.
//Salida: Array de integer que representa el array ingresado, pero ordenado de manera creciente.
int* bubbleSort(int* actualVertex,int quantityVertex){
    int aux;

    for (int i = 0; i < quantityVertex; i++) {
        for (int j = i + 1; j < quantityVertex; j++) {
            if (actualVertex[i] > actualVertex[j]) {
                aux = actualVertex[i];
                actualVertex[i] = actualVertex[j];
                actualVertex[j] = aux;
            }
        }
    }
    return actualVertex;
}

//Funcion que dado un int y un array de integer, verifica si este valor se encuentra en el array.
//Entrada: Array de integer a comparar, integer que se buscara en el array y un integer que representa el largo del array.
//Salida: Bool, True si el valor se encuentra en el array, False en caso contrario.
bool inListInt(int valor, int* valorArray, int quantityVertex){
    
    for(int i = 0; i < quantityVertex; i++)
    {
       if(valor == valorArray[i]){
           return true;
       }
    }
    return false;
}

//Funcion que dado un arary de array de int, filtra los vertices retornan una lista que contiene a los distintos vertices sin repeticion.
//Entrada: Array de array de integer a comparar, integer que representa la cantidad de vertices, integer que representa la cantidad de instruccions("[1 2 3]")
//Salida: Array de integer que representa los vertices sin repetición.
int* locateVertex(int** vertexArray, int quantityVertex, int quantityInstructions){
    int* actualVertex = (int*)malloc(sizeof(int)* quantityVertex);
    bool verify = true;
    int count = 0;

    for(int i = 0; i < quantityInstructions; i++){
        for(int j = 0; j < LINE_INSTRUCTIONS - 1; j++){
                verify = inListInt(vertexArray[i][j],actualVertex,quantityVertex);
                if(verify == false){
                    actualVertex[count] = vertexArray[i][j];
                    count += 1;
                }
        }
    } 

    return actualVertex;  
}

//Funcion que permite leer el archivo de entrada y obtener su informacion
//Entrada: char* que representa el nombre del archivo a leer y un integer que representa la cantidad de isntrucciones que tiene el archivo de entrada.
//Salida: Array de array de integer que representa los distintos vertices con sus conecciones y el coste de las conecciones.
int** readFile(char* fileName, int quantityInstructions){
    FILE* file;
    char* separatedString;
    char wordAux[50];
    int i = 0;
    int p = 0;

    int** arrayVertex = (int**)malloc(sizeof(int*)* quantityInstructions);
    for(int j = 0; j <= quantityInstructions; j++)
    {
       arrayVertex[j] = (int*)malloc(sizeof(int)*LINE_INSTRUCTIONS);
    }
    

    file = fopen(fileName,"r");
    if(file == NULL){
        printf("El archivo no existe...\n");
    }
    else{
        fscanf(file," %[^\n]",wordAux);
        while(!feof(file)){
            i = 0;
            fscanf(file," %[^\n]",wordAux);
            separatedString = strtok (wordAux," ,.-()");
            while (separatedString != NULL){
                char* auxInt= (char*)malloc(sizeof(char)*WORD);
                auxInt = separatedString;
                arrayVertex[p][i] = atoi(auxInt);
                separatedString = strtok (NULL, " ,.-()");
                i += 1;
            }
            p += 1;
        }  
    }
    fclose(file);

    return  arrayVertex;
}

//Funcion auxiliar que lee el archivo de entrada y obtiene la cantidad de instrucciones presentes en el archivo.
//Entrada: char* que representa el nombre del archivo a leer.
//Salida: Integer que representa la cantidad de instrucciones.
int readAuxInstructions(char* fileName){
    FILE* file;
    int quantityInstructions;
    char wordAux[50];
    char vertexAux[50];
    
    file = fopen(fileName,"r");
    quantityInstructions = 0;
    if(file == NULL){
        printf("El archivo no existe...\n");
    }
    else{
        fscanf(file," %[^\n]",vertexAux);
        while(!feof(file)){
            fscanf(file," %[^\n]",wordAux);
            quantityInstructions += 1;
        }  
    }
    fclose(file);

    return quantityInstructions;
}

//Funcion auxiliar que lee el archivo de entrada y obtiene la cantidad de vertice presentes en el archivo.
//Entrada: char* que representa el nombre del archivo a leer.
//Salida: Integer que representa la cantidad de vertice.
int readAuxVertex(char* fileName){
    FILE* file;
    int quantityVertex;
    char vertexAux[50];
    
    file = fopen(fileName,"r");
    if(file == NULL){
        printf("El archivo no existe...\n");
    }
    else{
        fscanf(file," %[^\n]",vertexAux);
        quantityVertex = atoi(vertexAux);
    }
    fclose(file);
    return quantityVertex;
}

//Funcion que permite escribir el resultado final del programa en un archivo de texto llamado "Salida.out".
//Entrada: Integer que representa el coste de la solucion, array de integer que representa la combinacion con el resultado optimo, integer que representa el largo del array.
//Salida: No posee salida.
void writeFile(int value, int* finalPath, int quantityVertex){
    FILE* file;
    char aux[2];
    file = fopen("Salida.out","wt");
    sprintf(aux, "%d", value + 2);
    fputs(aux,file);
    fputs("\n",file);
    fputs("0 - ",file);
    for(int i = 0; i < quantityVertex; i++){
        sprintf(aux, "%d", finalPath[i]);
        fputs(aux,file);
        fputs(" - ",file);
    }
    fputs("0",file);
    
    fclose(file);
}

//Funcion "bruteForce" que dado el nombre del archivo de entrada, acciona las demas funciones siguiendo la logica del algoritmo de "Fuerza Bruta".
//Entrada: Char* que representa el nombre del archvio de entrada.
//Salida: No posee salida.
void bruteForce(char* fileName){
    int** vertexArray;
    int** combinations;
    int** actualCombinations;
    int* actualVertex;
    int* valueArray;
    int quantityVertex;
    int quantityInstructions;
    int min;
    int index;

    quantityInstructions = readAuxInstructions(fileName);
    vertexArray = readFile(fileName,quantityInstructions);
    quantityVertex = readAuxVertex(fileName);
    actualVertex = locateVertex(vertexArray,quantityVertex,quantityInstructions);
    actualVertex = bubbleSort(actualVertex,quantityVertex);
    combinations = generateCombinations(quantityVertex,actualVertex);
    actualCombinations = getActualCombinations(combinations,quantityVertex);
    valueArray = getAllCombinationsValue(actualCombinations,quantityVertex,vertexArray,quantityInstructions);
    min = getMin(valueArray,quantityVertex);
    index = getMinIndex(min,valueArray,quantityVertex);
    writeFile(min,actualCombinations[index],quantityVertex);
}

//Funcion que despliega un menu en consola para que el usuario ponga en marcha la fuerza bruta.
//Entrada: No posee entrada.
//Salida: No posee salida.
void menu(){
    char* option = (char*)malloc(sizeof(char)* OPTION);
    char* fileName = (char*)malloc(sizeof(char) * NAME_FILE);

    while(true){
        printf("\nSeleccione una opción...\n");
        printf("1- Ingresar nombre de archivo con las rutas posibles entre puntos de abastecimiento.\n");
        printf("2- Salir del programa.\n");
        printf("Opcion: ");
        scanf("%s",option);
        if(strcmp("1",option) == 0){
            printf("Ingrese el nombre de archivo de texto: ");
            scanf("%s",fileName);
            bruteForce(fileName);
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
//Funcion inicia la ejecucion el programa.
//Entrada: No posee entrada.
//Salida: retorna un integer para terminar la ejecucion del programa.
int main(){
    menu();

    return 0;
}