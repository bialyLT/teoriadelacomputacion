import timeit  # Para medir el tiempo de ejecución
import pandas as pd  # Para crear el DataFrame de resultados
from dh_hd import DecToHex, HexToDec  # Importar las funciones a probar

# Datos de prueba
# Lista de números de prueba que se utilizarán para medir el rendimiento de las funciones
test_numbers = [0, 1, 15, 16, 255, 1024, 65535, 1048576, 2147483647]
# Número de repeticiones para cada prueba
repeats = 10000
 
# Función para medir el rendimiento de DecToHex
def measure_dec_to_hex():
    # Convierte cada número de prueba de decimal a hexadecimal
    for n in test_numbers:
        DecToHex(n)
 
# Función para medir el rendimiento de HexToDec
def measure_hex_to_dec():
    # Convierte cada número de prueba de decimal a hexadecimal y luego de hexadecimal a decimal
    for n in test_numbers:
        HexToDec(DecToHex(n))
 
# Ejecutar las pruebas de rendimiento
# Mide el tiempo total que toma ejecutar measure_dec_to_hex() 'repeats' veces
time_dh = timeit.timeit("measure_dec_to_hex()", globals=globals(), number=repeats)
# Mide el tiempo total que toma ejecutar measure_hex_to_dec() 'repeats' veces
time_hd = timeit.timeit("measure_hex_to_dec()", globals=globals(), number=repeats)
 
# Calcular el número total de llamadas realizadas
total_calls = len(test_numbers) * repeats
# Calcular el tiempo promedio por llamada para DecToHex
avg_dh = time_dh / total_calls
# Calcular el tiempo promedio por llamada para HexToDec
avg_hd = time_hd / total_calls
 
# Crear un DataFrame de pandas para mostrar los resultados de rendimiento
df = pd.DataFrame({
    "Función": ["DecToHex", "HexToDec"],  # Nombres de las funciones
    "Tiempo Total (s)": [time_dh, time_hd],  # Tiempo total de ejecución
    "Llamadas Totales": [total_calls, total_calls],  # Número total de llamadas realizadas
    "Tiempo Promedio por Llamada (s)": [avg_dh, avg_hd]  # Tiempo promedio por llamada
})
# Mostrar el DataFrame con los resultados
print(df)