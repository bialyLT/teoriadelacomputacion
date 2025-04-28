import timeit
import pandas as pd

# Funciones originales
def binarioADecimal(binario):
    decimal = 0
    for i in range(len(binario)):
        decimal += int(binario[i]) * (2 ** (len(binario) - i - 1))
    return decimal

def decimalABinario(decimal):
    if decimal == 0:
        return "0"
    binario = ""
    while decimal > 0:
        binario = str(decimal % 2) + binario
        decimal //= 2
    return binario

# Datos de prueba
numeros = [0, 1, 15, 16, 255, 1024, 65535, 1048576, 2147483647]
repeticiones = 10000

# Función para medir el rendimiento de decimalABinario
def measure_decimal_a_binario():
    for n in numeros:
        decimalABinario(n)

# Función para medir el rendimiento de binarioADecimal
def measure_binario_a_decimal():
    for n in numeros:
        binarios = [decimalABinario(num) for num in numeros]
        for b in binarios:
            binarioADecimal(b)

# Ejecutar las pruebas de rendimiento
tiempo_dec_bin = timeit.timeit("measure_decimal_a_binario()", globals=globals(), number=repeticiones)
tiempo_bin_dec = timeit.timeit("measure_binario_a_decimal()", globals=globals(), number=repeticiones)

# Calcular métricas
llamadas_totales = len(numeros) * repeticiones
prom_dec_bin = tiempo_dec_bin / llamadas_totales
prom_bin_dec = tiempo_bin_dec / llamadas_totales

# Crear el DataFrame de resultados
tabla = pd.DataFrame({
    "Función": ["decimalABinario", "binarioADecimal"],
    "Tiempo Total (s)": [tiempo_dec_bin, tiempo_bin_dec],
    "Llamadas Totales": [llamadas_totales, llamadas_totales],
    "Tiempo Promedio por Llamada (s)": [prom_dec_bin, prom_bin_dec]
})

print(tabla)
