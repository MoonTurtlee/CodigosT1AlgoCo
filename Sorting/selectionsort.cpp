#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <numeric>
#include <fstream>

using namespace std;
using namespace std::chrono;

// Función para Selection Sort
void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}

// Función para leer la lista desde un archivo
vector<int> leerListaDesdeArchivo(const string& nombreArchivo) {
    vector<int> arr;
    ifstream archivo(nombreArchivo);
    int num;
    while (archivo >> num) {
        arr.push_back(num);
    }
    archivo.close();
    return arr;
}

int main() {
    // Tipos de archivos disponibles
    vector<string> tiposDeArchivos = {
        "ordenada_asc",
        "ordenada_desc",
        "semi_ordenada",
        "duplicados",
        "aleatoria",

    };

    // Mostrar opciones disponibles
    cout << "Tipos de archivos disponibles para probar:" << endl;
    for (size_t i = 0; i < tiposDeArchivos.size(); i++) {
        cout << i + 1 << ". " << tiposDeArchivos[i] << endl;
    }

    // Pedir al usuario que elija un tipo de archivo
    cout << "Ingrese el número del tipo de archivo que desea probar: ";
    int eleccion;
    cin >> eleccion;

    // Validar elección del usuario
    if (eleccion < 1 || eleccion > tiposDeArchivos.size()) {
        cout << "Opción no válida." << endl;
        return 1;
    }

    // Filtrar archivos según la elección del usuario
    string tipoSeleccionado = tiposDeArchivos[eleccion - 1];
    vector<string> archivos = {
        "data/lista_" + tipoSeleccionado + "_100.txt",
        "data/lista_" + tipoSeleccionado + "_1000.txt",
        "data/lista_" + tipoSeleccionado + "_10000.txt",
        "data/lista_" + tipoSeleccionado + "_100000.txt",
        "data/lista_" + tipoSeleccionado + "_1000000.txt",
        "data/lista_" + tipoSeleccionado + "_10000000.txt"
    };

    // Probar los archivos seleccionados
    for (const string& archivo : archivos) {
        vector<int> arr = leerListaDesdeArchivo(archivo);

        // Almacenar los tiempos de ejecución
        vector<microseconds> tiempos;

        for (int i = 0; i < 10; i++) {
            vector<int> arr_copy = arr;
            auto start = high_resolution_clock::now();
            selectionSort(arr_copy);
            auto stop = high_resolution_clock::now();

            tiempos.push_back(duration_cast<microseconds>(stop - start));
        }

        // Calcular el tiempo promedio en microsegundos
        auto suma_tiempos = accumulate(tiempos.begin(), tiempos.end(), microseconds(0));
        auto promedio_microsegundos = suma_tiempos.count() / static_cast<double>(tiempos.size());

        // Convertir el tiempo promedio a segundos
        double promedio_segundos = promedio_microsegundos / 1e6;

        cout << "Tiempo promedio para ordenar la lista " << archivo << ": " << promedio_microsegundos << " microsegundos ("<< promedio_segundos << " segundos)" << endl;
    }

    return 0;
}
