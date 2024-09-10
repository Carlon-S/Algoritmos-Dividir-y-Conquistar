#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <time.h>

using namespace std;

// Función para intercambiar dos elementos
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Función para realizar el algoritmo Selection Sort
void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        // Encontrar el índice del elemento mínimo en el subarray no ordenado
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        // Intercambiar el elemento mínimo con el primer elemento no ordenado
        swap(arr[i], arr[minIndex]);
    }
}

// Función para imprimir el array
void printArray(const vector<int> &arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


int main() {
    clock_t start, end;
    double tiempo;

    ifstream archivo("dataset-15000.txt");
    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    vector<int> linea1,linea2,linea3;
    string linea;
    int contador = 0;

    while (getline(archivo, linea) && contador < 3) {
        istringstream stream(linea);
        int numero;
        vector<int>* linea_actual;

        if (contador == 0) linea_actual = &linea1;
        else if (contador == 1) linea_actual = &linea2;
        else linea_actual = &linea3;

        while (stream >> numero) {
            linea_actual->push_back(numero);
        }

        contador++;
    }

    archivo.close();

    start = clock();
    selectionSort(linea1);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista ordenada: %f segundos\n", tiempo);

    start = clock();
    selectionSort(linea2);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista semiOrdenada: %f segundos\n", tiempo);

    start = clock();
    selectionSort(linea3);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista aleatoria: %f segundos\n", tiempo);

    //arreglos ordenados
    //printArray(linea1);
    //printArray(linea2);
    //printArray(linea3);

    return 0;
}
