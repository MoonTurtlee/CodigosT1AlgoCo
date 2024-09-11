#include <bits/stdc++.h>
#include <numeric>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

/*
* Parametros: recibe el nombre de un archivo y el tamñano de la matriz a leer
* 
* Resumen: La funcion guarda la matriz que lee desde un archivo y lo retorna
*
* Retorno: retorna una matriz de enteros
*/
vector<vector<int>> leerMatrizDesdeArchivo(const string& nombreArchivo, int n) {
    vector<vector<int>> matriz(n, vector<int>(n));
    ifstream archivo(nombreArchivo);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            archivo >> matriz[i][j];
        }
    }
    archivo.close();
    return matriz;
}

/*
* Parametros: recibe una matriz y un string con la ruta y nombre de un archivo
* 
* Resumen: La funcion escribe la matriz en el archivo de la ruta especificada
*/
void guardarMatrizEnArchivo(const vector<vector<int>>& matriz, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    for (const auto& fila : matriz) {
        for (int valor : fila) {
            archivo << valor << " ";
        }
        archivo << endl;
    }
    archivo.close();
}

/*
* Parametros: recibe las matrices A y B, en conjunto con el tamaño n.
* 
* Resumen: La funcion transpone la matriz B y luego aplica la multiplicacion de matrices tradicional
*/
vector<vector<int>> multiplicarMatrices(const vector<vector<int>>& matrizA, vector<vector<int>>& matrizB, int n) {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            swap(matrizB[i][j], matrizB[j][i]);
        }
    }

    vector<vector<int>> resultado(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                resultado[i][j] += matrizA[i][k] * matrizB[j][k];
            }
        }
    }
    return resultado;
}



/*
* Parametros: No recibe
* 
* Resumen: Funcion principal del programa, le consulta al usuario el dataset a utilizar y ejecuta el algoritmo
*          que será testeado, posteriormente imprimer por pantalla el tiempo que le tomo al algoritmo terminar
*          y en donde se guardo el output
*/
int main() {
    // Tipos de archivos disponibles
    vector<string> tiposDeArchivos = {
        "2x2", "4x4", "8x8", "16x16", "32x32", "64x64", "128x128", "256x256", "512x512", "1024x1024", "2048x2048"
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
    if (eleccion < 1 || eleccion > static_cast<int>(tiposDeArchivos.size())) {
        cout << "Opción no válida." << endl;
        return 1;
    }

    // Filtrar archivos según la elección del usuario
    string tipoSeleccionado = tiposDeArchivos[eleccion - 1];
    vector<string> archivos = {
        "data/matriz_" + tipoSeleccionado + "_1.txt",
        "data/matriz_" + tipoSeleccionado + "_2.txt"
    };

    // Tamaño de la matriz
    int n = stoi(tipoSeleccionado.substr(0, tipoSeleccionado.find('x')));

    // Leer las dos matrices desde los archivos
    vector<vector<int>> matrizA = leerMatrizDesdeArchivo(archivos[0], n);
    vector<vector<int>> matrizB = leerMatrizDesdeArchivo(archivos[1], n);

    // Almacenar los tiempos de ejecución
    vector<microseconds> tiempos;

    auto start = high_resolution_clock::now();
    vector<vector<int>> resultado = multiplicarMatrices(matrizA, matrizB, n);  // Multiplicación de matrices con B transpuesta
    auto stop = high_resolution_clock::now();
    tiempos.push_back(duration_cast<microseconds>(stop - start));

    // Calcular el tiempo promedio en microsegundos
    auto suma_tiempos = accumulate(tiempos.begin(), tiempos.end(), microseconds(0));
    auto promedio_microsegundos = suma_tiempos.count() / static_cast<double>(tiempos.size());

    // Convertir el tiempo promedio a segundos
    double promedio_segundos = promedio_microsegundos / 1e6;

    cout << "Tiempo para multiplicar las matrices de " << tipoSeleccionado << " (con transposición): " 
         << promedio_microsegundos << " microsegundos (" << promedio_segundos << " segundos)" << endl;

    // Generar nombre de archivo de salida
    string archivoSalida = "outputs/matriz_resultado_transpuesto_" + tipoSeleccionado + ".txt";
    
    // Guardar el resultado en el archivo de salida
    guardarMatrizEnArchivo(resultado, archivoSalida);
    cout << "Matriz resultado guardada en: " << archivoSalida << endl;
    return 0;   
}