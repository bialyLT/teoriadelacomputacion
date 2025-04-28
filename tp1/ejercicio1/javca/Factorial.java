public class Factorial {
	public static long calcularFactorial(int n) {
		if (n < 0) {
			throw new IllegalArgumentException("El número debe ser no negativo.");
		}
		if (n == 0 || n == 1) {
			return 1;
		}
		return n * calcularFactorial(n - 1);
	}

	public static void main(String[] args) {
		int numero = 5; // Cambia este valor para probar con otros números
		System.out.println("El factorial de " + numero + " es: " + calcularFactorial(numero));
	}
}
