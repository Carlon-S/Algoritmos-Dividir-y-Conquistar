#include <iostream>
#include <vector>
#include <fstream>
#include <limits>
#include <time.h>

using namespace std;

// Función para leer una matriz desde un archivo
vector<vector<int>> readMatrix(ifstream& file, int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file >> matrix[i][j];
        }
    }
    return matrix;
}

// Función para transponer una matriz
void transponerMatriz(vector<vector<int>>& matriz, vector<vector<int>>& transpuesta, int N) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            transpuesta[j][i] = matriz[i][j];
        }
    }
}

// Función para multiplicar matrices (A * B) con la matriz B transpuesta para optimizar la localidad de datos
void multiplicarMatricesOptimizado(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int N) {
    // Crear la transpuesta de B
    vector<vector<int>> B_T(N, vector<int>(N));
    transponerMatriz(const_cast<vector<vector<int>>&>(B), B_T, N); // Transponer B para mejorar la localidad

    // Multiplicación de matrices utilizando la transpuesta de B
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int suma = 0;
            for (int k = 0; k < N; ++k) {
                suma += A[i][k] * B_T[j][k];
            }
            C[i][j] = suma;
        }
    }
}


int main() {
    clock_t start, end;
    double tiempo;
    ifstream file("256x256.txt");
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo 'dataset.txt'" << endl;
        return 1;
    }

    int rowsA, colsA;
    file >> rowsA >> colsA;

    // Leer la primera matriz
    vector<vector<int>> A = readMatrix(file, rowsA, colsA);

    // Leer el espacio en blanco entre las matrices
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    int rowsB, colsB;
    file >> rowsB >> colsB;

    // Leer la segunda matriz
    vector<vector<int>> B = readMatrix(file, rowsB, colsB);

    // Comprobar si las matrices se pueden multiplicar
    if (colsA != rowsB) {
        cerr << "Las dimensiones de las matrices no son compatibles para la multiplicación." << endl;
        return 1;
    }

    // Matriz resultante
    vector<vector<int>> C;
    C.assign(rowsA, vector<int>(colsB, 0));

    start = clock();
    multiplicarMatricesOptimizado(A, B, C, rowsA);
    end = clock();

    tiempo = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución para la multiplicación de matrices tradicional: %f ms\n", tiempo);
    // Mostrar el resultado
    /* 
    cout << "Resultado de la multiplicación de matrices:" << endl;
    for (const auto& row : C) {
        for (const auto& elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
    */
    file.close();
    return 0;
}
