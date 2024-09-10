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

// Función para multiplicar dos matrices A y B, y almacenar el resultado en la matriz C
void multiplyMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int colsB = B[0].size();

    // Inicializar la matriz resultante C con ceros
    C.assign(rowsA, vector<int>(colsB, 0));

    // Multiplicación de matrices
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            for (int k = 0; k < colsA; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    clock_t start, end;
    double tiempo;

    ifstream file("512x512.txt");
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

    // Multiplicación de matrices
    start = clock();
    multiplyMatrices(A, B, C);
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
