#include <bits/stdc++.h>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para fusionar dos subvectores en MergeSort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Crear subvectores temporales
    vector<int> L(n1), R(n2);

    // Copiar datos a los subvectores L[] y R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Fusionar los subvectores temporales de nuevo en arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copiar los elementos restantes de L[], si los hay
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copiar los elementos restantes de R[], si los hay
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Función recursiva para MergeSort
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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

    for (const string& archivo : archivos) {
        vector<int> arr = leerListaDesdeArchivo(archivo);

        // Almacenar los tiempos de ejecución
        vector<microseconds> tiempos;

        for (int i = 0; i < 10; i++) {
             
            vector<int> arr_copy = arr;
            auto start = high_resolution_clock::now();
            mergeSort(arr, 0, arr_copy.size() - 1);
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
