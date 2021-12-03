#include "Zombie.h"

Zombie::Zombie(int px, int py)
{
	CambiarX(px); CambiarY(py);
	vector <string> parametros = LeerArchivo();
	System::String^ aux_fil = gcnew System::String(parametros.at(2).c_str());
	System::String^ aux_col = gcnew System::String(parametros.at(3).c_str());
    System::String^ aux_v = gcnew System::String(parametros.at(11).c_str());
	CambiarMaxFil(System::Convert::ToInt32(aux_fil));
	CambiarMaxCol(System::Convert::ToInt32(aux_col));
	CambiarCol(2);
	CambiarFil(0);
    V = System::Convert::ToInt32(aux_v);
	MovX = 3;
	MovY = 3;
    PotenciadorVelocidad = 1;
    IsTop = false;
    BalasDisponibles = 5;
}

Zombie::~Zombie()
{
}

void Zombie::Desplazamiento(direccion nueva, Graphics^ g)
{
	orientacion = nueva;
    dx = dy = 0;
    if (orientacion == direccion::arriba) {
        dy = -w / MovY * PotenciadorVelocidad;
        CambiarFil(0);
    }
    if (orientacion == direccion::abajo) {
        dy = w / MovY * PotenciadorVelocidad;
        CambiarFil(2);
    }
    if (orientacion == direccion::izquierda) {
        dx = -w / MovX * PotenciadorVelocidad;
        CambiarFil(3);
    }
    if (orientacion == direccion::derecha) {
        dx = w / MovX * PotenciadorVelocidad;
        CambiarFil(1);
    }
    Mover(g);
}

void Zombie::DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp)
{
    w = bmp->Width / MaxCol;
    h = bmp->Height / MaxFil;
    Rectangle porcion = Rectangle(col * w, fil * h, w, h);
    g->DrawImage(bmp, x, y, porcion, GraphicsUnit::Pixel);
    col++;
    if (col == MaxCol)
        col = 0;
}

void Zombie::Mover(Graphics^ g)
{
    if (x + dx < 1 ||x + dx + w > g->VisibleClipBounds.Width)
        dx = dx * -1;
    x += dx;


    if (y + dy + h > g->VisibleClipBounds.Height)
        dy = dy * -1;
    y += dy;

    if (y + dy < 1) IsTop = true;
}

int Zombie::RetornarV()
{
    return V;
}

int Zombie::RetornarPotenciadorVelocidad()
{
    return PotenciadorVelocidad;
}

void Zombie::IncrementarPotenciadorVelocidad()
{
    PotenciadorVelocidad *= 2;
}

void Zombie::SetearPotenciadorVelocidad()
{
    PotenciadorVelocidad = 1;
}



void Zombie::DisminuirUnaVida()
{
    V = V - 1;
}

bool Zombie::ReturnIsTop()
{
    return IsTop;
}


void Zombie::Disparar()
{
    if (BalasDisponibles) {
        ArrBalas.push_back(new Bala(x, y-h, orientacion));
        --BalasDisponibles;
    }
}

void Zombie::MoverBalas(Graphics^ g)
{
    for (int i = 0; i < ArrBalas.size(); i++)
    {
        ArrBalas.at(i)->DibujarDesdeImagen(g);
        ArrBalas.at(i)->Mover(g);
    }
    for (int i = 0; i < ArrBalas.size(); i++)
    {
        if (ArrBalas.at(i)->RetornarEliminar() == true) {
            ArrBalas.erase(ArrBalas.begin() + i);
        }
    }
}

void Zombie::RecargarCantBalas()
{
    BalasDisponibles += 5;
}
