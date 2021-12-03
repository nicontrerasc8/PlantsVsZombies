#pragma once
#include "Base.h"
class Planta : public Base
{
public:
	Planta(int Px, int Py);
	~Planta();
	void DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp);
	void Mover(Graphics^ g);
};

