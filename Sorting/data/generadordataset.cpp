#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

void guardarEnArchivo(const vector<int>& lista, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    for (int num : lista) {
        archivo << num << "\n";
    }
    archivo.close();
}

int main() {
    srand(time(0)); // Inicializar la semilla del generador de números aleatorios

    // Generar listas de diferentes tamaños
    vector<int> tamaños = {100,1000,10000,100000,1000000,10000000};

    for (int tamaño : tamaños) {
        // Lista Aleatoria
        vector<int> lista_aleatoria(tamaño);
        for (int& num : lista_aleatoria) num = rand() % 10000000;
        guardarEnArchivo(lista_aleatoria, "lista_aleatoria_" + to_string(tamaño) + ".txt");

        // Lista Ordenada Ascendentemente
        vector<int> lista_ordenada_asc(tamaño);
        for (int i = 0; i < tamaño; ++i) lista_ordenada_asc[i] = i;
        guardarEnArchivo(lista_ordenada_asc, "lista_ordenada_asc_" + to_string(tamaño) + ".txt");

        // Lista Ordenada Descendentemente
        vector<int> lista_ordenada_desc(tamaño);
        for (int i = 0; i < tamaño; ++i) lista_ordenada_desc[i] = tamaño - i;
        guardarEnArchivo(lista_ordenada_desc, "lista_ordenada_desc_" + to_string(tamaño) + ".txt");

        // Lista Semi-Ordenada (50% ordenada, 50% aleatoria)
        vector<int> lista_semi_ordenada(tamaño);
        for (int i = 0; i < tamaño / 2; ++i) lista_semi_ordenada[i] = i;
        for (int i = tamaño / 2; i < tamaño; ++i) lista_semi_ordenada[i] = rand() % 10000000;
        guardarEnArchivo(lista_semi_ordenada, "lista_semi_ordenada_" + to_string(tamaño) + ".txt");

        // Lista con Duplicados
        vector<int> lista_duplicados(tamaño);
        for (int& num : lista_duplicados) num = rand() % 100;
        guardarEnArchivo(lista_duplicados, "lista_duplicados_" + to_string(tamaño) + ".txt");
    }

    cout << "Listas generadas y guardadas en archivos de texto." << endl;
    return 0;
}
