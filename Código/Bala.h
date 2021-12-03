#pragma once
#include "Base.h"
class Bala : public Base
{
public:
	Bala(int px, int py, direccion DireccionBala);
	~Bala();
	void Mover(Graphics^ g);
	void DibujarDesdeImagen(Graphics^ g);
};

