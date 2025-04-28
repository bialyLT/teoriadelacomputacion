#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>

// Convierte un número decimal a hexadecimal
std::string DecToHex(int num) {
    if (num < 0) {
        throw std::invalid_argument("El número debe ser un entero positivo.");
    }

    if (num == 0) {
        return "0"; // Caso especial para el número 0
    }

    std::string hex_num = "";
    const std::string hex_chars = "0123456789ABCDEF";

    // Convertir el número decimal a hexadecimal
    while (num > 0) {
        int indice = num % 16; // Obtener el residuo
        hex_num = hex_chars[indice] + hex_num; // Construir el número hexadecimal
        num /= 16; // Reducir el número dividiéndolo entre 16
    }

    return hex_num;
}

// Convierte un número hexadecimal a decimal
int HexToDec(const std::string& hex_num) {
    int decimal_num = 0;


    if (hex_num.empty()) {
        throw std::invalid_argument("La cadena hexadecimal no puede estar vacía.");
    }


    try {
        decimal_num = std::stoi(hex_num, nullptr, 16); // Convertir de hexadecimal a decimal
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("El número hexadecimal no es válido."); // Manejar errores de conversión
    } catch (const std::out_of_range&) {
        throw std::out_of_range("El número hexadecimal está fuera de rango.");
    }

    return decimal_num;
}

int main() {
    try {
        // Prueba de DecToHex
        int decimal = 255;
        std::string hex = DecToHex(decimal);
        std::cout << "Decimal " << decimal << " en hexadecimal es: " << hex << std::endl;

        // Prueba de HexToDec
        std::string hex_input = "FF";
        int dec = HexToDec(hex_input);
        std::cout << "Hexadecimal " << hex_input << " en decimal es: " << dec << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
