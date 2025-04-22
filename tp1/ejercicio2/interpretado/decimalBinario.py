# codigo para pasar de binario a decimal y viceversa 

# 1. Definicion de funciones

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


def main():
        
        # 2. Entrada de datos
        binario = input("Introduce un número binario: ")
        decimal = int(input("Introduce un número decimal: "))
    
        # 3. Proceso y salida de datos
        print(f"El número binario {binario} en decimal es: {binarioADecimal(binario)}")
        print(f"El número decimal {decimal} en binario es: {decimalABinario(decimal)}")
        
if __name__ == "__main__":
    main()