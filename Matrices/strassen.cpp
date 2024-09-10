#include <bits/stdc++.h>
#include <numeric>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer una matriz desde un archivo
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

// Función para imprimir una matriz
void print(string display, vector<vector<int>> matrix, int start_row, int start_column, int end_row, int end_column) {
    cout << endl << display << " =>" << endl;
    for (int i = start_row; i <= end_row; i++) {
        for (int j = start_column; j <= end_column; j++) {
            cout << setw(10);
            cout << matrix[i][j];
        }
        cout << endl;
    }
    cout << endl;
    return;
}

// Función para guardar una matriz en un archivo
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

// Función para sumar/restar matrices
vector<vector<int>> add_matrix(vector<vector<int>> matrix_A, vector<vector<int>> matrix_B, int split_index, int multiplier = 1) {
    for (int i = 0; i < split_index; i++)
        for (int j = 0; j < split_index; j++)
            matrix_A[i][j] = matrix_A[i][j] + (multiplier * matrix_B[i][j]);
    return matrix_A;
}

// Algoritmo de Strassen para la multiplicación de matrices
vector<vector<int>> multiply_matrix(vector<vector<int>> matrix_A, vector<vector<int>> matrix_B) {
    int col_1 = matrix_A[0].size();
    int row_1 = matrix_A.size();
    int col_2 = matrix_B[0].size();
    int row_2 = matrix_B.size();

    if (col_1 != row_2) {
        cout << "\nError: El número de columnas en la Matriz A debe ser igual al número de filas en la Matriz B\n";
        return {};
    }

    vector<int> result_matrix_row(col_2, 0);
    vector<vector<int>> result_matrix(row_1, result_matrix_row);

    if (col_1 == 1) {
        result_matrix[0][0] = matrix_A[0][0] * matrix_B[0][0];
    } else {
        int split_index = col_1 / 2;
        vector<int> row_vector(split_index, 0);

        // Dividir matrices en submatrices
        vector<vector<int>> a00(split_index, row_vector), a01(split_index, row_vector), a10(split_index, row_vector), a11(split_index, row_vector);
        vector<vector<int>> b00(split_index, row_vector), b01(split_index, row_vector), b10(split_index, row_vector), b11(split_index, row_vector);

        for (int i = 0; i < split_index; i++)
            for (int j = 0; j < split_index; j++) {
                a00[i][j] = matrix_A[i][j];
                a01[i][j] = matrix_A[i][j + split_index];
                a10[i][j] = matrix_A[split_index + i][j];
                a11[i][j] = matrix_A[i + split_index][j + split_index];
                b00[i][j] = matrix_B[i][j];
                b01[i][j] = matrix_B[i][j + split_index];
                b10[i][j] = matrix_B[split_index + i][j];
                b11[i][j] = matrix_B[i + split_index][j + split_index];
            }

        // Algoritmo de Strassen
        vector<vector<int>> p(multiply_matrix(a00, add_matrix(b01, b11, split_index, -1)));
        vector<vector<int>> q(multiply_matrix(add_matrix(a00, a01, split_index), b11));
        vector<vector<int>> r(multiply_matrix(add_matrix(a10, a11, split_index), b00));
        vector<vector<int>> s(multiply_matrix(a11, add_matrix(b10, b00, split_index, -1)));
        vector<vector<int>> t(multiply_matrix(add_matrix(a00, a11, split_index), add_matrix(b00, b11, split_index)));
        vector<vector<int>> u(multiply_matrix(add_matrix(a01, a11, split_index, -1), add_matrix(b10, b11, split_index)));
        vector<vector<int>> v(multiply_matrix(add_matrix(a00, a10, split_index, -1), add_matrix(b00, b01, split_index)));

        // Reconstruir la matriz resultado
        vector<vector<int>> result_matrix_00(add_matrix(add_matrix(add_matrix(t, s, split_index), u, split_index), q, split_index, -1));
        vector<vector<int>> result_matrix_01(add_matrix(p, q, split_index));
        vector<vector<int>> result_matrix_10(add_matrix(r, s, split_index));
        vector<vector<int>> result_matrix_11(add_matrix(add_matrix(add_matrix(t, p, split_index), r, split_index, -1), v, split_index, -1));

        for (int i = 0; i < split_index; i++)
            for (int j = 0; j < split_index; j++) {
                result_matrix[i][j] = result_matrix_00[i][j];
                result_matrix[i][j + split_index] = result_matrix_01[i][j];
                result_matrix[split_index + i][j] = result_matrix_10[i][j];
                result_matrix[i + split_index][j + split_index] = result_matrix_11[i][j];
            }
    }
    return result_matrix;
}

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
    if (eleccion < 1 || eleccion > tiposDeArchivos.size()) {
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
    vector<vector<int>> resultado = multiply_matrix(matrizA, matrizB);  // Multiplicación con Strassen
    auto stop = high_resolution_clock::now();
	tiempos.push_back(duration_cast<microseconds>(stop - start));
    

    // Calcular el tiempo promedio en microsegundos
    auto suma_tiempos = accumulate(tiempos.begin(), tiempos.end(), microseconds(0));
    auto promedio_microsegundos = suma_tiempos.count() / static_cast<double>(tiempos.size());

    // Convertir el tiempo promedio a segundos
    double promedio_segundos = promedio_microsegundos / 1e6;

    cout << "Tiempo para multiplicar las matrices de " << tipoSeleccionado << ": " 
         << promedio_microsegundos << " microsegundos (" << promedio_segundos << " segundos)" << endl;

    // Generar nombre de archivo de salida
    string archivoSalida = "outputs/matriz_resultado_strassen_" + tipoSeleccionado + ".txt";
    
    // Guardar el resultado en el archivo de salida
    guardarMatrizEnArchivo(resultado, archivoSalida);
    cout << "Matriz resultado guardada en: " << archivoSalida << endl;
    return 0;
}
