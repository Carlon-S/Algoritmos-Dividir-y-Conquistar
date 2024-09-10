#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <time.h>
#include <algorithm>

using namespace std;

void printArray(const vector<int> &arr) {
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

vector<int> readDataset(const string &filename) {
    ifstream file(filename);
    vector<int> arr;
    if (file.is_open()) {
        string line;
        // Leer la primera línea que contiene el número de elementos
        getline(file, line);
        int n = stoi(line);
        // Leer las siguientes n líneas que contienen los números
        for (int i = 0; i < n; ++i) {
            getline(file, line);
            arr.push_back(stoi(line));
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }
    return arr;
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
    sort(linea1.begin(),linea1.end());
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista ordenada: %f segundos\n", tiempo);

    start = clock();
    sort(linea2.begin(),linea2.end());
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista semiOrdenada: %f segundos\n", tiempo);

    start = clock();
    sort(linea3.begin(),linea3.end());
    end = clock();
    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la lista aleatoria: %f segundos\n", tiempo);

    
    //printArray(linea1);
    //printArray(linea2);
    //printArray(linea3);

    return 0;
}

