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

vector<vector<int>> sumMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Función para restar dos matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Función que divide una matriz en cuatro submatrices
void divideMatrix(const vector<vector<int>>& A, vector<vector<int>>& A11, vector<vector<int>>& A12, 
                  vector<vector<int>>& A21, vector<vector<int>>& A22) {
    int newSize = A.size() / 2;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];                          // Top-left
            A12[i][j] = A[i][j + newSize];                // Top-right
            A21[i][j] = A[i + newSize][j];                // Bottom-left
            A22[i][j] = A[i + newSize][j + newSize];      // Bottom-right
        }
    }
}

// Función que combina cuatro submatrices en una sola matriz
void combineMatrix(vector<vector<int>>& C, const vector<vector<int>>& C11, const vector<vector<int>>& C12,
                   const vector<vector<int>>& C21, const vector<vector<int>>& C22) {
    int newSize = C11.size();
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];                          // Top-left
            C[i][j + newSize] = C12[i][j];                // Top-right
            C[i + newSize][j] = C21[i][j];                // Bottom-left
            C[i + newSize][j + newSize] = C22[i][j];      // Bottom-right
        }
    }
}

// Función principal del algoritmo de Strassen
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Caso base: multiplicación directa si la matriz es 1x1
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    int newSize = n / 2;

    // Inicializar las submatrices
    vector<vector<int>> A11(newSize, vector<int>(newSize));
    vector<vector<int>> A12(newSize, vector<int>(newSize));
    vector<vector<int>> A21(newSize, vector<int>(newSize));
    vector<vector<int>> A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize));
    vector<vector<int>> B12(newSize, vector<int>(newSize));
    vector<vector<int>> B21(newSize, vector<int>(newSize));
    vector<vector<int>> B22(newSize, vector<int>(newSize));

    // Dividir las matrices A y B
    divideMatrix(A, A11, A12, A21, A22);
    divideMatrix(B, B11, B12, B21, B22);

    // Calcular los productos intermedios de Strassen
    vector<vector<int>> M1 = strassen(sumMatrices(A11, A22), sumMatrices(B11, B22));  // M1 = (A11 + A22) * (B11 + B22)
    vector<vector<int>> M2 = strassen(sumMatrices(A21, A22), B11);                    // M2 = (A21 + A22) * B11
    vector<vector<int>> M3 = strassen(A11, subtractMatrices(B12, B22));               // M3 = A11 * (B12 - B22)
    vector<vector<int>> M4 = strassen(A22, subtractMatrices(B21, B11));               // M4 = A22 * (B21 - B11)
    vector<vector<int>> M5 = strassen(sumMatrices(A11, A12), B22);                    // M5 = (A11 + A12) * B22
    vector<vector<int>> M6 = strassen(subtractMatrices(A21, A11), sumMatrices(B11, B12));  // M6 = (A21 - A11) * (B11 + B12)
    vector<vector<int>> M7 = strassen(subtractMatrices(A12, A22), sumMatrices(B21, B22));  // M7 = (A12 - A22) * (B21 + B22)

    // Calcular las submatrices de la matriz resultante C
    vector<vector<int>> C11 = sumMatrices(subtractMatrices(sumMatrices(M1, M4), M5), M7);  // C11 = M1 + M4 - M5 + M7
    vector<vector<int>> C12 = sumMatrices(M3, M5);                                        // C12 = M3 + M5
    vector<vector<int>> C21 = sumMatrices(M2, M4);                                        // C21 = M2 + M4
    vector<vector<int>> C22 = sumMatrices(subtractMatrices(sumMatrices(M1, M3), M2), M6);  // C22 = M1 + M3 - M2 + M6

    // Combinar las submatrices en la matriz resultante C
    vector<vector<int>> C(n, vector<int>(n));
    combineMatrix(C, C11, C12, C21, C22);

    return C;
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

    start = clock();
    vector<vector<int>> C = strassen(A, B);
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