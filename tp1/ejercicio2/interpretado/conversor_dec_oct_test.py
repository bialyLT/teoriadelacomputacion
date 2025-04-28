# Conversor de Decimal ↔ Octal con prueba de rendimiento integrada.

import sys
import timeit
import pandas as pd

def dec_a_oct(n: int) -> str:
    """
    Convierte un entero decimal (puede ser negativo) a su representación en base octal.
    - n: entero decimal con signo.
    - Retorna: cadena con la representación octal, incluyendo el signo si es negativo.
    """
    signo = '-' if n < 0 else ''            # Determina el signo
    valor = abs(n)                          # Trabaja con el valor absoluto
    if valor == 0:                          # Caso especial para cero
        return '0'
    dígitos: list[str] = []                 # Lista para almacenar los dígitos octales
    while valor > 0:
        dígitos.append(str(valor % 8))     # Obtiene el resto (dígito octal)
        valor //= 8                        # Reduce el número
    return signo + ''.join(reversed(dígitos))  # Une los dígitos invertidos y añade el signo

def oct_a_dec(s: str) -> int:
    """
    Convierte una cadena que representa un número en base octal (puede incluir '-') a entero decimal.
    - s: cadena con dígitos octales y opcional signo.
    - Retorna: entero decimal correspondiente.
    """
    s = s.strip()                           # Elimina espacios alrededor
    if not s:
        raise ValueError("Cadena vacía.")   # Error si la cadena está vacía
    signo = -1 if s[0] == '-' else 1        # Determina el signo
    núcleo = s[1:] if s[0] in '+-' else s   # Extrae la parte numérica
    # Valida que solo contenga dígitos de 0 a 7
    if not núcleo.isdigit() or any(ch not in '01234567' for ch in núcleo):
        raise ValueError(f"'{s}' no es una representación octal válida.")
    resultado = 0
    for ch in núcleo:
        resultado = resultado * 8 + int(ch) # Acumula el valor decimal
    return signo * resultado                # Aplica el signo

def modo_interactivo():
    """
    Modo interactivo con menú para el usuario:
    1: Decimal → Octal
    2: Octal → Decimal
    3: Ejecutar prueba de rendimiento
    """
    print("=== Conversor de Unidades (Decimal ↔ Octal) ===")
    print("1) Decimal → Octal")
    print("2) Octal → Decimal")
    print("3) Ejecutar prueba de rendimiento")

    opcion = input("Elija una opción (1–3): ").strip()
    if opcion not in ('1', '2', '3'):
        print(f"Error: opción '{opcion}' no válida.")
        return

    if opcion == '3':
        modo_benchmark()  # Ejecuta benchmark y regresa
        return

    entrada = input("Ingrese el número a convertir: ").strip()
    try:
        if opcion == '1':
            # Decimal → Octal
            n = int(entrada)                # Puede lanzar ValueError
            resultado = dec_a_oct(n)
            print(f"{n} (decimal) → {resultado} (octal)")
        else:
            # Octal → Decimal
            resultado = oct_a_dec(entrada)
            print(f"{entrada} (octal) → {resultado} (decimal)")
    except ValueError as e:
        print(f"Error: {e}")                # Muestra mensajes de error claros

def modo_benchmark():
    """
    Mide el rendimiento de las dos funciones de conversión usando timeit,
    muestra los resultados en tabla pandas.
    """
    # Conjuntos de prueba
    test_numbers = [0, 1, 15, 16, 255, 1024, 65535, 1048576, 2147483647]
    repeats = 10_000

    # Wrappers que ejecutan todas las conversiones para un lote
    fn_dec_to_oct = lambda: [dec_a_oct(n) for n in test_numbers]
    fn_oct_to_dec = lambda: [oct_a_dec(dec_a_oct(n)) for n in test_numbers]

    # Medir tiempo total de cada wrapper
    time_do = timeit.timeit(fn_dec_to_oct, number=repeats)
    time_od = timeit.timeit(fn_oct_to_dec, number=repeats)

    total_calls = len(test_numbers) * repeats
    avg_do = time_do / total_calls   # Tiempo promedio por llamada dec→oct
    avg_od = time_od / total_calls   # Tiempo promedio por llamada oct→dec

    # Crear DataFrame con resultados
    df = pd.DataFrame({
        "Implementación": ["Python", "Python"],
        "Función": ["Dec→Oct", "Oct→Dec"],
        "Tiempo Total (s)": [time_do, time_od],
        "Llamadas Totales": [total_calls, total_calls],
        "Tiempo Promedio por Llamada (s)": [avg_do, avg_od]
    })

    # Mostrar tabla
    print(df.to_string(index=False))

def main():
    """
    Punto de entrada: siempre arranca en modo interactivo.
    """
    modo_interactivo()

if __name__ == '__main__':
    main()

