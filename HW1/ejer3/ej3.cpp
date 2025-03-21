#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


// Estructura de un nodo para la lista enlazada
struct nodo {
    int val;                    // Valor que almacena el nodo
    shared_ptr<nodo> next;      // Puntero al siguiente nodo
};

// Estructura de la lista, que tiene un puntero al primer nodo
struct list {
    shared_ptr<nodo> inicio;    // Inicio de la lista
};

// Crea un nuevo nodo con un valor dado
shared_ptr<nodo> create_node(int value) {
    return make_shared<nodo>(nodo{value, nullptr});
}

// Inserta un nuevo nodo al inicio de la lista
void push_front(int val, list& lista) {
    shared_ptr<nodo> node = create_node(val);
    node->next = lista.inicio; // El nuevo nodo apunta al antiguo inicio
    lista.inicio = node;       // Se actualiza el inicio de la lista
}

// Inserta un nuevo nodo al final de la lista
void push_back(int val, list& lista) {
    shared_ptr<nodo> node = create_node(val);
    shared_ptr<nodo> temp = lista.inicio;

    // Recorre hasta el último nodo
    while (temp->next) {
        temp = temp->next;
    }

    // Agrega el nuevo nodo al final
    temp->next = node;
}

// Inserta un nodo en una posición específica
void insert(int indice, int val, list& lista) {
    shared_ptr<nodo> node = create_node(val);
    shared_ptr<nodo> temp = lista.inicio;

    // Recorre hasta la posición anterior al índice dado
    while (temp->next && indice - 1) {
        temp = temp->next;
        indice--;
    }

    if (!temp->next) {
        // Si el índice es mayor que el tamaño de la lista, inserta al final
        cout << "insercion fuera de rango, insertado al final" << std::endl;
        push_back(val, lista);
    } else {
        // Inserta entre dos nodos
        node->next = temp->next;
        temp->next = node;
    }
}

// Elimina un nodo en una posición específica
void erase(int indice, list& lista) {
    shared_ptr<nodo> temp = lista.inicio;
    shared_ptr<nodo> temp2 = lista.inicio->next;

    // Recorre hasta el nodo anterior al que se va a eliminar
    while (temp2->next && indice - 1) {
        temp = temp2;
        temp2 = temp2->next;
        indice--;
    }

    if (!temp2->next) {
        // Si el índice es mayor que el tamaño de la lista, elimina el último
        cout << "eliminacion fuera de rango, eliminado el ultimo" << std::endl;
        temp->next = NULL;
    } else {
        // Reemplaza el enlace para omitir el nodo a eliminar
        temp->next = temp2->next;
    }
}

// Imprime la lista enlazada
void printlist(list& lista) {
    shared_ptr<nodo> temp = lista.inicio;

    // Recorre todos los nodos e imprime su valor
    while (temp) {
        cout << temp->val << " -> ";
        temp = temp->next;
    }

    cout << "nullptr\n";
}


// Función principal para probar la lista
int main() {
    list lista;  // Se crea una lista vacía

    cout << "Agregando elementos al frente...\n";
    push_front(3, lista);  // Lista: 3
    push_front(2, lista);  // Lista: 2 -> 3
    push_front(1, lista);  // Lista: 1 -> 2 -> 3
    printlist(lista);

    cout << "Agregando elementos al final...\n";
    push_back(4, lista);   // Lista: 1 -> 2 -> 3 -> 4
    push_back(5, lista);   // Lista: 1 -> 2 -> 3 -> 4 -> 5
    printlist(lista);

    cout << "Insertando 10 en la posición 2...\n";
    insert(2, 10, lista);  // Lista: 1 -> 2 -> 10 -> 3 -> 4 -> 5
    printlist(lista);

    cout << "Eliminando el elemento en la posición 100...\n";
    erase(100, lista);     // Índice fuera de rango, elimina el último
    printlist(lista);

    return 0;
}