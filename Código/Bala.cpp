#include "Bala.h"

Bala::Bala(int px, int py, direccion DireccionBala) 
{
    orientacion = DireccionBala;
    CambiarX(px); CambiarY(py);
    MovX = 1;
    MovY = 1;
    dx = 10;
    dy = 10;
}

Bala::~Bala()
{
}

void Bala::Mover(Graphics^ g)
{
    if (orientacion == direccion::derecha) {
        if (x + dx + w > g->VisibleClipBounds.Width)
            CambiarEliminar(true);
        else
            x += dx;
    }
    else if (orientacion == direccion::izquierda) {
        if (x - dx < 1)
            CambiarEliminar(true);
        else
            x -= dx;
    }
    else if (orientacion == direccion::arriba) {
        if (y - dy < 1)
            CambiarEliminar(true);
        else
            y -= dy;
    }
    else if (orientacion == direccion::abajo) {
        if (y + dy + h > g->VisibleClipBounds.Height)
            CambiarEliminar(true);
        else
            y += dy;
    }
    else if(orientacion == direccion::ninguno) {
        if (y - dy < 1)
            CambiarEliminar(true);
        else
            y -= dy;
    }

}

void Bala::DibujarDesdeImagen(Graphics^ g)
{
    g->DrawEllipse(Pens::Red, x, y, 40,40);
    g->FillEllipse(Brushes::Brown, x, y, 40, 40);
}
