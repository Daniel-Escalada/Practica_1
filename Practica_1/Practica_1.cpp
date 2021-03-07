#include <stdio.h>
#include <math.h>

typedef struct
{
	float x;
	float y;
	double radio;
} punto;

typedef struct
{
	float ext1_x;
	float ext1_y;
	float ext2_x;
	float ext2_y;
} segmento;

float Distancia(punto p1, segmento s1)
{
	// Proyeccion del seg en x 
	float delta_segx = s1.ext2_x - s1.ext1_x;
	
	// Proyeccion del seg en y
	float delta_segy = s1.ext2_y - s1.ext1_y;
	
	// Proyeccion de p1x -> s1x
	float delta_psx = p1.x - s1.ext1_x;
	
	// Proyeccion de p1y -> s1y
	float delta_psy = p1.y - s1.ext1_y;
	
	// Calculos auxiliares para simplificar codigo
	float norma_seg = delta_segx * delta_segx + delta_segy * delta_segy;
	
	// Parametro p que determina si el punto se encuentra dentro de las proyecciones
	// p se iguala a 2 por si el segmento tiene longitud 0 (uno de los casos del if)
	float p = 2;
	
	// Calculo del parametro p 
	if (norma_seg != 0) p = (delta_psx * delta_segx + delta_psy * delta_segy) / norma_seg;
	
	// Punto de menor distancia del segmento 
	float min_x, min_y;

	// Caso cuando el punto mas cercano es el extremo 1
	if (p < 0) {
		min_x = s1.ext1_x;
		min_y = s1.ext1_y;
	}
	// Caso cuando el punto mas cercano es el extremo 2 (tambien se incluye el caso cuando longitud seg = 0)
	else if (p > 1) {
		min_x = s1.ext2_x;
		min_y = s1.ext2_y;
	}
	// Caso cuando el punto mas cercano pertenece al segmento
	else {
		min_x = s1.ext1_x + p * delta_segx;
		min_y = s1.ext1_y + p * delta_segy;
	}

    // Distancia del punto minimo a p1
	float delta_x = p1.x - min_x;
	float delta_y = p1.y - min_y;
	float norma = delta_x * delta_x + delta_y * delta_y;
	double dist = sqrt(norma);
	return dist;

}

 punto DatosCirc()
{
	 punto circ;
	 printf("Introduzca las coordenadas del centro de la circunferencia\n");
	 scanf_s("%f %f", &circ.x, &circ.y);
	 printf("Introduzca el radio de la circunferencia\n");
	 scanf_s("%lf", &circ.radio);
	 return circ;

}

segmento DatosSeg()
{
	 segmento seg;
	 printf("Introduzca las coordenadas del extremo 1\n");
	 scanf_s("%f %f", &seg.ext1_x, &seg.ext1_y);
	 printf("Introduzca las coordenadas del extremo 2\n");
	 scanf_s("%f %f", &seg.ext2_x, &seg.ext2_y);
	 return seg;

}

bool Colision(punto r, float d) {
	return (r.radio >= d ? 1 : 0);
}

int main(void)
{
	punto punto1;
	segmento seg1;

	// Solicitar datos de la circunferencia
	punto1 = DatosCirc();

	// Solicitar datos del segmento
	seg1 = DatosSeg();
	float dist = Distancia(punto1, seg1);
	bool d = Colision(punto1, dist); 
	if (d==0) printf("La circunferencia no colisiona con el segmento");
	else printf("La circunferencia si colisiona con el segmento");

	return 0;

}