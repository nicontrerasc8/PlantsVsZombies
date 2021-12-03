#pragma once
#include "Base.h"
class Bono : public Base
{
public:
	Bono(int px, int py);
	~Bono();
	void DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp);
};

