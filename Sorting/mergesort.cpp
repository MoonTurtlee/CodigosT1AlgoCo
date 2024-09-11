#include <bits/stdc++.h>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
 * Resumen: Función que fusiona dos subvectores ordenados en uno solo dentro del vector principal.
 *
 * Parámetros:
 *  - arr: Referencia al vector de enteros que se está ordenando.
 *  - left: Índice izquierdo del subvector.
 *  - mid: Índice medio donde se divide el subvector.
 *  - right: Índice derecho del subvector.
 *
 * Retorno:
 *  - No retorna valores. Modifica el vector `arr` directamente.
 */

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

/*
 * Resumen: Función recursiva que implementa el algoritmo de ordenamiento MergeSort.
 *
 * Parámetros:
 *  - arr: Referencia al vector de enteros a ordenar.
 *  - left: Índice inicial del subvector.
 *  - right: Índice final del subvector.
 *
 * Retorno:
 *  - No retorna valores. Ordena el vector `arr` directamente.
 */
void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
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
 * Resumen: Función principal que permite al usuario seleccionar un tipo de archivo y ejecuta MergeSort en varias listas de diferente tamaño.
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
            mergeSort(arr_copy, 0, arr_copy.size() - 1);
            auto stop = high_resolution_clock::now();

            if(i != 0){
                tiempos.push_back(duration_cast<microseconds>(stop - start));
                // Generar nombre de archivo de salida
                string archivoSalida = "outputs/ordenada_mergesort_" + archivo.substr(archivo.find_last_of("/") + 1);
                
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
