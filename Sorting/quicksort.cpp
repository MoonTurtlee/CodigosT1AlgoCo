#include <bits/stdc++.h>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
 * Resumen: Realiza la partición del vector en QuickSort utilizando un pivote.
 *
 * Parámetros:
 *  - vec: Referencia al vector de enteros que se está ordenando.
 *  - low: Índice inicial del subvector a particionar.
 *  - high: Índice final del subvector a particionar.
 *
 * Retorno:
 *  - El índice de la posición del pivote después de la partición.
 */
int partition(vector<int>& vec, int low, int high) {
    int mid = low + (high - low) / 2;
    int pivot = vec[mid];
    swap(vec[mid], vec[high]);
    int i = low - 1;
    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
}

/*
 * Resumen: Función recursiva que implementa el algoritmo de ordenamiento QuickSort.
 *
 * Parámetros:
 *  - vec: Referencia al vector de enteros a ordenar.
 *  - low: Índice inicial del subvector a ordenar.
 *  - high: Índice final del subvector a ordenar.
 *
 * Retorno:
 *  - No retorna valores. Ordena el vector `vec` directamente.
 */
void quickSort(vector<int>& vec, int low, int high) {
    if (low < high) {
        int pi = partition(vec, low, high);
        quickSort(vec, low, pi - 1);
        quickSort(vec, pi + 1, high);
    }
}

/*
 * Resumen: Lee una lista de números enteros desde un archivo y los almacena en un vector.
 *
 * Parámetros:
 *  - nombreArchivo: Nombre del archivo que contiene la lista de enteros.
 *
 * Retorno:
 *  - Un vector de enteros que contiene los números leídos desde el archivo.
 */
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

/*
 * Resumen: Guarda un vector de enteros en un archivo de texto, cada número en una nueva línea.
 *
 * Parámetros:
 *  - arr: Referencia al vector de enteros que se va a guardar.
 *  - nombreArchivo: Nombre del archivo donde se guardará la lista de enteros.
 *
 * Retorno:
 *  - No retorna valores. Escribe la lista en el archivo especificado.
 */
void guardarListaEnArchivo(const vector<int>& arr, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo); // Sobreescribirá el archivo si ya existe
    for (int num : arr) {
        archivo << num << endl;
    }
    archivo.close();
}

/*
 * Resumen: Función principal que permite al usuario seleccionar un tipo de archivo y ejecuta QuickSort en varias listas de diferente tamaño.
 *
 * Parámetros:
 *  - Ninguno.
 *
 * Retorno:
 *  - Retorna 0 si la ejecución es exitosa, o 1 si ocurre un error en la selección del archivo.
 */
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

        for (int i = 0; i < 6; i++) {
             
            vector<int> arr_copy = arr;
            auto start = high_resolution_clock::now();
            quickSort(arr_copy, 0, arr_copy.size() - 1);
            auto stop = high_resolution_clock::now();

            if(i != 0){
                tiempos.push_back(duration_cast<microseconds>(stop - start));
                // Generar nombre de archivo de salida
                string archivoSalida = "outputs/ordenada_quicksort_" + archivo.substr(archivo.find_last_of("/") + 1);
                
                // Guardar la lista ordenada en el archivo de salida
                guardarListaEnArchivo(arr_copy, archivoSalida);
                cout << "Lista ordenada guardada en: " << archivoSalida << endl;
            }
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
