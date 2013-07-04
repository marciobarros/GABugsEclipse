#include <time.h>
#include "stdafx.h"
#include "random.h"

/*
 * Constante de geracao de números uniformes
 */

#define IA		16807
#define IM		2147483647
#define AM		(1.0 / IM)
#define IQ		127773
#define IR		2836
#define NTAB	32
#define NDIV	(1 + (IM-1)/NTAB)
#define EPS		1.2e-7
#define RNMX	(1.0-EPS)

 /*
 * Semente geradora de números aleatórios e matrizes de correlacoes
 */

static long	semente = 1;

void randomize ()
{
	srand((unsigned)time(0));
	semente = rand ();
}

double rand_uniform (void)
{
	int			j;
	long			k;
	static long		iy=0;
	static long		iv[NTAB];
	double			temp;

	if (semente <= 0 || !iy) 
	{
		semente = (-semente < 1) ? 1 : -semente;

		for (j = NTAB+7; j >= 0; j--) 
		{
			k = semente / IQ;
			semente = IA * (semente - k*IQ) - IR * k;
			
			if (semente < 0) 
				semente += IM;
			
			if (j < NTAB) 
				iv[j] = semente;
		}
		
		iy = iv[0];
	}

	k = semente / IQ;
	semente = IA * (semente - k * IQ) - IR * k;
	
	if (semente < 0)
		semente += IM;

	j = iy / NDIV;
	iy = iv[j];
	iv[j] = semente;
	return (((temp = AM*iy) > RNMX) ? RNMX : temp);
}