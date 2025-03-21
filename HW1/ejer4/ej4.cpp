#include <iostream>
#include <chrono>


// Función constexpr que compara dos cadenas de caracteres al estilo C en tiempo de compilación
constexpr bool compararcadenas(const char* str1, const char* str2) {
    if (*str1 == '\0' && *str2 == '\0') {
        // Si ambas cadenas llegan al final al mismo tiempo, son iguales
        return true;
    }
    if (*str1 != *str2) {
        // Si hay una diferencia en los caracteres actuales, no son iguales
        return false;
    }
    // Llamada recursiva para comparar el siguiente carácter
    return compararcadenas(str1 + 1, str2 + 1);
}

// Se mide el tiempo de compilación de las comparaciones constexpr
auto startTime = std::chrono::high_resolution_clock::now();

// Arreglo de resultados de comparaciones realizadas en tiempo de compilación
constexpr bool comparaciones[4] = {
    compararcadenas("Este es un texto de prueba que contiene mas de 64 caracteres.", "Este es un texto de prueba que contiene mas de 64 caracteres."),
    compararcadenas("Este es un texto de prueba que contiene mas de 64 caracteres.","Este es un texto de prueba que contiene mas de 64 caracteres. "),
    compararcadenas("Este es un texto de prueba que contiene mas de 64 caracteres.", "Este es un texto de prueba que contiene mas de 64 caracteres. "),
    compararcadenas("Este es un texto de prueba que contiene mas de 64 caracteres.", "hola"),
};

// Se mide el tiempo justo después de hacer las comparaciones constexpr
auto endTime = std::chrono::high_resolution_clock::now();

// Se calcula el tiempo transcurrido entre startTime y endTime
auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

int main(){
    // Imprime el tiempo que tomó compilar las comparaciones constexpr
    std::cout << "A comparar cadenas le tomó: " << elapsedTime.count() << " nanosegundos compilar"<< std::endl;

    // Inicia el cronómetro para medir comparaciones en tiempo de ejecución
    auto startTime2 = std::chrono::high_resolution_clock::now();

    // Comparaciones en tiempo de ejecución (aunque la función sea constexpr, no se evalúan en compilación aquí)
    compararcadenas("Este es un texto de prueba que contiene mas de 64 caracteres.", "Este es un texto de prueba que contiene mas de 64 caracteres.");
    compararcadenas("Este es un texto de prueba que contiene mas de 64 caracteres.","Este no es un texto de prueba que contiene mas de 64 caracteres.");
    compararcadenas("Este no es un texto de prueba que contiene mas de 64 caracteres.", "Este es un texto de prueba que contiene mas de 64 caracteres.");
    compararcadenas("Este es un texto de prueba que contiene mas de 64 caracteres.", "hola");

    // Se mide el tiempo después de las comparaciones en tiempo de ejecución
    auto endTime2 = std::chrono::high_resolution_clock::now();

    // Se calcula el tiempo que tardaron las comparaciones en tiempo de ejecución
    auto elapsedTime2 = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2 - startTime2);
    //std::cout << comparaciones[0] << comparaciones[1] << comparaciones[2] << comparaciones[3]<<  std::endl;
    std::cout << "A comparar cedenas le tomó: " << elapsedTime2.count() << " nanosegundos ejecutar"<<  std::endl;
    std::cout << "Conclusion: es mucho mas eficiente realizar las comparaciones al compilar. "<< std::endl;
    std::cout << "eleccion: char*, la razon es que me parecio mas intuitivo y rapido que utilizar string. "<< std::endl;
}