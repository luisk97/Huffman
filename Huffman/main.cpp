#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

/*
 * En esta clase se implementa una solucion del algoritmo de Huffman en la cual se ingresa un arreglo con
 * las letras del mensaje y otro indicando cuantas veces se repite cada letra respectivamente.
 */
class AlgoritmoHuffman {

    //Esta estructura contendra la letra la cantidad de veces que se repite dicha letra y dos punteros a otros dos nodos
    struct Nodo {
        char dato;
        size_t frecuencia;
        Nodo* left;
        Nodo* right;
        Nodo(char data, size_t freq) : dato(data),
                                       frecuencia(freq),
                                       left(nullptr),
                                       right(nullptr)
        {}
        ~Nodo() {
            delete left;
            delete right;
        }
    };

    struct compare {
        bool operator()(Nodo* l, Nodo* r) {
            return (l->frecuencia > r->frecuencia);
        }
    };

    Nodo* top;

    //Con esta funcion imprimiremos el codigo binario de cada caracter del arbol que ingresemos segun su posicion en el arbol
    void printCodigo(Nodo *root, string str) {
        if(root == nullptr)
            return;

        if(root->dato == '$')
        {
            printCodigo(root->left, str + "0");
            printCodigo(root->right, str + "1");
        }

        if(root->dato != '$')
        {
            cout<<root->dato<<" : "<<str<<"\n";
            printCodigo(root->left, str + "0");
            printCodigo(root->right, str + "1");
        }
    }

public:
    AlgoritmoHuffman() {};

    ~AlgoritmoHuffman() {
        delete top;
    }

    //Con esta funcion nos encargamos de generar el arbol con los arreglos ingresados
    void generarCodigo(vector<char> &data, vector<size_t> &freq, size_t size) {
        Nodo* left;
        Nodo* right;
        priority_queue<Nodo*, vector<Nodo*>, compare > minHeap;

        for(size_t i = 0; i < size; ++i) {
            minHeap.push(new Nodo(data[i], freq[i]));
        }

        while(minHeap.size() != 1) {
            left = minHeap.top();
            minHeap.pop();

            right = minHeap.top();
            minHeap.pop();

            top = new Nodo('$', left->frecuencia + right->frecuencia);
            top->left  = left;
            top->right = right;
            minHeap.push(top);
        }
        cout<<"Caracter y su codigo para ubicarlo dentro del arbol:"<<endl;
        printCodigo(minHeap.top(), "");
    }
};

int main() {

    AlgoritmoHuffman set1;
    vector<char> data({'d', 'e', 'b', 'c', 'a', 'f'});
    vector<size_t> freq({16, 9, 13, 12, 45, 5});
    size_t size = data.size();
    set1.generarCodigo(data, freq, size);

    return 0;
}