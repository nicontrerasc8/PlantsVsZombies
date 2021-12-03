#include "Planta.h"

Planta::Planta(int Px, int Py)
{
	CambiarX(Px); CambiarY(Py);
	vector <string> parametros = LeerArchivo();
	System::String^ aux_fil = gcnew System::String(parametros.at(5).c_str());
	System::String^ aux_col = gcnew System::String(parametros.at(6).c_str());
	CambiarMaxFil(System::Convert::ToInt32(aux_fil));
	CambiarMaxCol(System::Convert::ToInt32(aux_col));
	int RandomicNumber = rand() % 7;
	CambiarCol(RandomicNumber);
	CambiarFil(0);
	int RandomWay = rand() % 2;
	MovX = ((RandomicNumber) ? -(rand() % 5 + 1) : rand() % 5 + 1);
}

Planta::~Planta()
{
}

void Planta::DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp)
{
	w = bmp->Width / MaxCol;
	h = bmp->Height / MaxFil;
	
	Rectangle porcion = Rectangle(col * w, fil * h, w, h);
	g->DrawImage(bmp, x, y, porcion, GraphicsUnit::Pixel);
}

void Planta::Mover(Graphics^ g)
{
	if (x + dx<1 || x + dx + w > g->VisibleClipBounds.Width) {
		MovX = MovX * -1;
	}
	dx = w / MovX;
	x += dx;
}
