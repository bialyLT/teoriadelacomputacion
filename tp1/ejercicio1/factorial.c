// hacer un calculo para factorial en c (lenguaje imperativo)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int factorial = 1;

    // le pedimos al usuario que ingrese un número

    int entrada = 0;
    printf("Ingrese un número entero positivo: ");
    scanf("%d", &entrada);

    if (entrada < 0) {
        printf("El valor tiene que ser un numero positivo");
        return 1;
    }

    if (entrada > 20) {
        printf("El valor es demasiado grande, el factorial de %d no se puede calcular\n", entrada);
        return 1;
    }

    for (int i = 1; i <= entrada; i++) {
        factorial *= i;
    }

    printf("El factorial de %d es %d\n", entrada, factorial);

    return 0;
}   