#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;

// Función para intercambiar dos elementos del arreglo
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Función para particionar el arreglo
int partition(std::vector<int>& arr, int izquierda, int derecha) {
    int pivot = arr[derecha];
    int i = izquierda - 1;

    for (int j = izquierda; j < derecha; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[derecha]);
    return i + 1;
}

// Función para implementar el algoritmo Quicksort
void quicksort(std::vector<int>& arr, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int pivot = partition(arr, izquierda, derecha);

        quicksort(arr, izquierda, pivot - 1);
        quicksort(arr, pivot + 1, derecha);
    }
}

// Función para imprimir el arreglo
void imprimirArreglo(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
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
    quicksort(linea1, 0, linea1.size()-1);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista ordenada: %f segundos\n", tiempo);

    start = clock();
    quicksort(linea2, 0, linea2.size()-1);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista semiOrdenada: %f segundos\n", tiempo);

    start = clock();
    quicksort(linea3, 0, linea3.size()-1);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista aleatoria: %f segundos\n", tiempo);

    //arreglos ordenados
    //imprimirArreglo(linea1);
    //imprimirArreglo(linea2);
    //imprimirArreglo(linea3);

    return 0;
}