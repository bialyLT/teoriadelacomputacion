public class FactorialCalculator {

    // Método para calcular el factorial
    public long calcularFactorial(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("El número debe ser no negativo.");
        }
        long resultado = 1;
        for (int i = 1; i <= n; i++) {
            resultado *= i;
        }
        return resultado;
    }

    // Método principal de prueba
    public static void main(String[] args) {
        FactorialCalculator calculadora = new FactorialCalculator();
        int numero = 7;
        long factorial = calculadora.calcularFactorial(numero);
        System.out.println("El factorial de " + numero + " es: " + factorial);
    }
}
