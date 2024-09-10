import numpy as np

# Generar matrices de tamaño n*n con enteros aleatorios, donde n es una potencia de 2, hasta 2048
def generar_y_guardar_dos_matrices_txt_enteros():
    for n in [2**i for i in range(1, 12)]:  # Potencias de 2 desde 2 hasta 2048
        for j in range(1, 3):  # Generar dos matrices por cada tamaño
            matriz = np.random.randint(0, 100, size=(n, n))  # Números enteros entre 0 y 99
            ruta_archivo = f"matriz_{n}x{n}_{j}.txt"  # Guardar con nombre descriptivo
            np.savetxt(ruta_archivo, matriz, fmt='%d')  # Guardar la matriz en un archivo .txt
            print(f"Matriz de {n}x{n} parte {j} guardada en {ruta_archivo}")

# Ejecutar la función
generar_y_guardar_dos_matrices_txt_enteros()
