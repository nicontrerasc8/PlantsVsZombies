#include "Bono.h"

Bono::Bono(int px, int py)
{
	CambiarX(px); CambiarY(py);
    CambiarMaxCol(1);
    CambiarMaxFil(1);
    CambiarCol(0);
    CambiarFil(0);
}

Bono::~Bono()
{
}

void Bono::DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp)
{
    w = bmp->Width / MaxCol;
    h = bmp->Height / MaxFil;
    Rectangle porcion = Rectangle(col * w, fil * h, w, h);
    g->DrawImage(bmp, x, y, porcion, GraphicsUnit::Pixel);
}
