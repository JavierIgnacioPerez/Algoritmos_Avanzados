#define OPTION 5
#define NAME_FILE 25
#define WORD 5
#define LINE_INSTRUCTIONS 3

int factorial(int quantityVertex);
int getMin(int* array,int quantityVertex);
int getMinIndex(int min,int* array,int quantityVertex);
int* reverseArray(int* vertex,int quantityVertex);
int getPathValue(int path1, int path2, int** vertexArray, int quantityInstructions);
int getCombinationValue(int* actualCombination, int quantityVertex, int** vertexArray, int quantityInstructions);
int* getAllCombinationsValue(int** actualCombination, int quantityVertex, int** vertexArray, int quantityInstructions);
bool inListArray(int** array, int* secondArray, int quantityVertex);
int** getActualCombinations(int** combinations,int quantityVertex);
void printCurrent(int* combination,int quantityVertex);
int** generateCombinations(int quantityVertex, int* actualVertex);
int* bubbleSort(int* actualVertex,int quantityVertex);
bool inListInt(int valor, int* valorArray, int quantityVertex);
int* locateVertex(int** vertexArray, int quantityVertex, int quantityInstructions);
int** readFile(char* fileName, int quantityInstructions);
int readAuxInstructions(char* fileName);
int readAuxVertex(char* fileName);
void writeFile(int value, int* finalPath, int quantityVertex);
void bruteForce(char* fileName);
void menu();
int main();