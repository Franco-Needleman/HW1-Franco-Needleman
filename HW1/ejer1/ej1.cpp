#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Función que crea una matriz dinámica de tamaño n x n usando unique_ptr
std::unique_ptr<std::unique_ptr<int[]>[]> ej1a(int n) {
    // Se crea un arreglo de punteros a filas
    auto matrix = std::make_unique<std::unique_ptr<int[]>[]>(n);
    int val = 1;  // Valor inicial a almacenar en la matriz

    // Recorre cada fila
    for (int i = 0; i < n; i++) {
        matrix[i] = std::make_unique<int[]>(n);

        // Se llenan los elementos de la fila con valores consecutivos
        for (int j = 0; j < n; j++) {
            matrix[i][j] = val++;
        }
    }
    return matrix;
}

// Función que imprime los elementos de la matriz en orden inverso
void ej1b(std::unique_ptr<std::unique_ptr<int[]>[]> matrix, int n) {
    // Recorre desde el último elemento hasta el primero
    for (int i = n * n - 1; i >= 0; i--) {
        cout << "matrix[" << i / n << "][" << i % n << "] = " << matrix[i / n][i % n] << endl;
    }
}

int main() {
    // Se crea una matriz 5x5 usando ej1a
    std::unique_ptr<std::unique_ptr<int[]>[]> mat = ej1a(5);

    ej1b(move(mat), 5); // move() transfiere la propiedad del puntero único
}
