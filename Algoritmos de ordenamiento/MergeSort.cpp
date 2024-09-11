#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;
// Algoritmo basado en https://www.geeksforgeeks.org/cpp-program-for-merge-sort/
// Función para fusionar dos subarreglos ordenados
void merge(std::vector<int>& arr, int izquierda, int centro, int derecha) {
    int n1 = centro - izquierda + 1;
    int n2 = derecha - centro;

    // Crear arreglos temporales
    std::vector<int> izquierdaArr(n1), derechaArr(n2);

    // Copiar datos a los arreglos temporales
    for (int i = 0; i < n1; i++) {
        izquierdaArr[i] = arr[izquierda + i];
    }
    for (int j = 0; j < n2; j++) {
        derechaArr[j] = arr[centro + 1 + j];
    }

    // Fusionar los arreglos temporales
    int i = 0, j = 0, k = izquierda;
    while (i < n1 && j < n2) {
        if (izquierdaArr[i] <= derechaArr[j]) {
            arr[k] = izquierdaArr[i];
            i++;
        } else {
            arr[k] = derechaArr[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes del arreglo izquierdo
    while (i < n1) {
        arr[k] = izquierdaArr[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes del arreglo derecho
    while (j < n2) {
        arr[k] = derechaArr[j];
        j++;
        k++;
    }
}

// Función para implementar el algoritmo MergeSort
void mergeSort(std::vector<int>& arr, int izquierda, int derecha) {
    if (izquierda < derecha) {
        int centro = izquierda + (derecha - izquierda) / 2;

        // Ordenar la mitad izquierda
        mergeSort(arr, izquierda, centro);

        // Ordenar la mitad derecha
        mergeSort(arr, centro + 1, derecha);

        // Fusionar las dos mitades ordenadas
        merge(arr, izquierda, centro, derecha);
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
    mergeSort(linea1,0,linea1.size()-1);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista ordenada: %f segundos\n", tiempo);

    start = clock();
    mergeSort(linea2,0,linea2.size()-1);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista semiOrdenada: %f segundos\n", tiempo);

    start = clock();
    mergeSort(linea3,0,linea3.size()-1);
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista aleatoria: %f segundos\n", tiempo);

    //arreglos ordenados
    //imprimirArreglo(linea1);
    //imprimirArreglo(linea2);
    //imprimirArreglo(linea3);

    return 0;
}
