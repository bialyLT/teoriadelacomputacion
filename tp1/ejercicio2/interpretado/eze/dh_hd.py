def DecToHex(num):

    """
    Convierte un número decimal a hexadecimal.
    Argumentos:
        int num: El número decimal (entero positivo) a convertir.
    Devoluciones:
        str: El número hexadecimal correspondiente.
    """

    try:
        num = int(num)  # Convertir a entero
    except ValueError:
        raise ValueError("El número debe ser un entero positivo.")
    if num < 0:
        raise ValueError("El número debe ser un entero positivo.")
    if num == 0:
        return "0"  # Caso especial para el número 0
   
    hex_num = ""
    hex_chars = "0123456789ABCDEF"  # Caracteres hexadecimales
   
    # Convertir el número decimal a hexadecimal
    while num > 0:
        indice = num % 16  # Obtener el residuo
        hex_num = hex_chars[indice] + hex_num  # Construir el número hexadecimal
        num //= 16  # Reducir el número dividiéndolo entre 16
   
    return hex_num
 
def HexToDec(hex_num):
    """
    Convierte un número hexadecimal a decimal.
   
    Argumentos:
        str hex_num: El número hexadecimal a convertir.
   
    Devoluciones:
        int: El número decimal correspondiente.
    """
    try:
        hex_num = str(hex_num)  # Asegurarse de que es una cadena
        return int(hex_num, 16)  # Convertir de hexadecimal a decimal
    except ValueError:
        raise ValueError("El número hexadecimal no es válido.")  # Manejar errores de conversión

if __name__ == "__main__":
    # Ejemplo de prueba para DecToHex
    decimal_number = 255
    print(f"Decimal {decimal_number} a Hexadecimal: {DecToHex(decimal_number)}")

    # Ejemplo de prueba para HexToDec
    hexadecimal_number = "FF"
    print(f"Hexadecimal {hexadecimal_number} a Decimal: {HexToDec(hexadecimal_number)}")
