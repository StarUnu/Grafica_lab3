# Laboratorio 3 de Grafica
**Algoritmo de la curva de Bézier**:Su funcionamiento recae en la siguiente parte de codigo.

```void bezier (wcPt3D * ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
	wcPt3D bezCurvePt;
	GLfloat u;
	GLint *C, k;
	/* Reserva espacio para los coeficientes binomiales*/
	C= new GLint [nCtrlPts];
	
	binomialCoeffs (nCtrlPts - 1, C);
	for (k=0; k <= nBezCurvePts; k++) {
	u = GLfloat (k) / GLfloat (nBezCurvePts);
	computeBezPt (u, &bezCurvePt, nCtrlPts, ctrlPts, C);
	plotPoint_b (bezCurvePt);
	}
	delete [ ] C;
}
```
![](Curvas/ejecucion.jpeg)

**Cuatree**: Se realiza se divide la imagen en bloque de cuatro, sucesivamente. Obteniendo una imagen simplificada. Realiza los siguientes pasos:

![](Quatree/framessonic/000000.png)
![](Quatree/framessonic/000025.png)
![](Quatree/framessonic/000040.png)
![](Quatree/framessonic/000110.png)
![](Quatree/salidasoni.png)
