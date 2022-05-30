/*
** ejemplo.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "auxiliar.h"

void Ayuda(void)
{
	fprintf(stdout, "%s: Uso: %s [ a  [ b ]]\n", argv0, argv0);
	fprintf(stdout, "%s: Sin argumentos muestra un digito aleatorio de 0 a 9.\n", argv0);
	fprintf(stdout, "%s: Con un argumento muestra factorial(a).\n", argv0);
	fprintf(stdout, "%s: Con dos argumentos muestra binomial(a,b).\n", argv0);
	exit(0);
}

/*
type			       bin con fact		       bin con for
unsigned		46/54 = 85% _ 46/78 = 58%	48/56 = 85% _ 48/78 = 61%
ULL			50/58 = 86% _ 50/78 = 64%	54/62 = 87% _ 54/78 = 69%
float			48/56 = 85% _ 48/78 = 61%	58/66 = 87% _ 58/78 = 74%
double			67/75 = 89% _ 67/78 = 85%	70/77 = 90% _ 70/78 = 89%
*/

#if 0
	typedef unsigned big_t;
#	define FRMT	"%u"
#elif 0
	typedef unsigned long long big_t;
#	define FRMT	"%llu"
#elif 0
	typedef float big_t;
#	define FRMT	"%.0f"
#elif 1
	typedef double big_t;
#	define FRMT	"%.0f"
#else
	/*
	 * En C estandar no existe tal cosa, pero alguien podría
	 * usar una biblioteca de aritmética de precisión infinita.
	 */
	typedef huge big_t;
#	define FRMT	"%s"
#endif

/* No detecta parámetro erroneo ni el posible desbordamiento. */
big_t factorial(int n)
{
	if (n <= 1) return 1;
	return factorial(n-1) * n;
}

#if 0
/* Implementación trivial */
/* Se asume que los parámetros son correctos. */
big_t binomial(int n, int k)
{
	return factorial(n)/factorial(n-k)/factorial(k);
}
#else
/* Implementación mejorada */
/* Se asume que los parámetros son correctos. */
big_t binomial(int n, int k)
{
	big_t b = 1;
	int i;
	int l = n - k;
	if (l > k) {
		i = k;
		k = l;
		l = i;
	}
	for (i = 1; i <= l; i++) {
		b *= i + k;
		b /= i;
	}
	return b;
}
#endif

int main(int argc, char * argv[])
{
	int a = -1;
	int b = -1;

	argv0 = "ejemplo";

	switch(argc)
	{
	case 3: /* binomial */

		/* XXX atoi NO ofrece realmente control de error. Cambiar a strtol. */
		a = atoi(argv[1]);
		if (a < 0) {
			Error(EX_USAGE, "El parámetro \"a\" no es un número natural válido.");
		}

		/* XXX atoi NO ofrece realmente control de error. Cambiar a strtol. */
		b = atoi(argv[2]);
		if (b < 0) {
			Error(EX_USAGE, "El parámetro \"b\" no es un número natural válido.");
		}

		if (b > a) {
			Error(EX_USAGE, "El parámetro \"b\" ha de ser menor o igual al \"a\".");
		}

		printf("binomial(%d,%d) = " FRMT "\n", a, b, binomial(a,b));
		break;

	case 2:	/* factorial */

		/* ¿Mostrar ayuda? */
		if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
			Ayuda();
		}

		/* XXX atoi NO ofrece realmente control de error. Cambiar a strtol. */
		a = atoi(argv[1]);
		if (a < 0) {
			Error(EX_USAGE, "El parámetro \"a\" no es un número natural válido.");
		}

		printf("factorial(%d) = " FRMT "\n", a, factorial(a));
		break;

	case 1:	/* aleatorio */

		printf("%u\n", (unsigned)time(0)%10);
		break;

	default:
		Error(EX_USAGE, "El número de argumentos no es correcto.");
	}

	return 0;
}
