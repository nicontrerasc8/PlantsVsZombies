#include "Base.h"

Base::Base()
{
    Eliminar = false;
}

Base::Base(int px, int py, int pw, int ph)
{
    x = px;
    y = py;
    w = pw;
    h = ph;
    Eliminar = false;
    dx = dy = 0;
    orientacion = direccion::ninguno;
}

Base::Base(int px, int py, int pw, int ph, int pMaxFil, int pMaxCol, int pFil, int pCol)
{
    x = px;
    y = py;
    w = pw;
    h = ph;
    Eliminar = false;
    dx = dy = 0;
    orientacion = direccion::ninguno;
    MaxCol = pMaxCol;
    MaxFil = pMaxFil;
    col = pCol;
    fil = pFil;
}

Base::~Base()
{
}

void Base::CambiarX(int c)
{
    x = c;
}

void Base::CambiarY(int c)
{
    y = c;
}

void Base::CambiarW(int c)
{
    w = c;
}

void Base::CambiarH(int c)
{
    h = c;
}

void Base::CambiarDX(int c)
{
    dx = c;
}

void Base::CambiarDY(int c)
{
    dy = c;
}

void Base::CambiarCol(int c)
{
    col = c;
}

void Base::CambiarFil(int c)
{
    fil = c;
}

void Base::CambiarMaxFil(int c)
{
    MaxFil = c;
}

void Base::CambiarMaxCol(int c)
{
    MaxCol = c;
}

void Base::CambiarEliminar(bool e)
{
    Eliminar = e;
}

void Base::Desplazamiento(direccion nueva)
{
    orientacion = nueva;
    dx = dy = 0;
    if (orientacion == direccion::arriba) {
        dy = -w/MovY;
        fil = 0;
    }
    if (orientacion == direccion::abajo) {
        dy = w/MovY;
        fil = 0;
    }
    if (orientacion == direccion::izquierda) {
        dx = -w/MovX;
        fil = 0;
    }
    if (orientacion == direccion::derecha) {
        dx = w/MovX;
        fil = 0;
    }
}

int Base::RetornarX()
{
    return x;
}

int Base::RetornarY()
{
    return y;
}

int Base::RetornarW()
{
    return w;
}

int Base::RetornarH()
{
    return h;
}

int Base::RetornarDX()
{
    return dx;
}

int Base::RetornarDY()
{
    return dy;
}

int Base::RetornarCol()
{
    return col;
}

int Base::RetornarFil()
{
    return fil;
}

int Base::RetornarMaxFil()
{
    return MaxFil;
}

int Base::RetornarMaxCol()
{
    return MaxCol;
}

bool Base::RetornarEliminar()
{
    return Eliminar;
}

void Base::CambiarMovimientoX(int c)
{
    dx = c;
}

void Base::CambiarMovimientoY(int c)
{
    dy = c;
}

int Base::RetornarMovimientoX()
{
    return dx;
}

int Base::RetornarMovimientoY()
{
    return dy;
}

Rectangle Base::RetornarRectangulo()
{
    return Rectangle(x,y,w,h);
}

void Base::Mover(Graphics^ g)
{
    if (x + dx<1 || x + dx + w > g->VisibleClipBounds.Width)
        dx = dx * -1;
    x += dx;

    if (y + dy<1 || y + dy + h > g->VisibleClipBounds.Height)
        dy = dy * -1;
    y += dy;
}

void Base::Dibujar(Graphics^ g)
{
}

void Base::DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp)
{
    w = bmp->Width / MaxCol;
    h = bmp->Height / MaxFil;
    Rectangle porcion = Rectangle(col * w, fil * h, w, h);
    g->DrawImage(bmp, x, y, porcion, GraphicsUnit::Pixel);
    col++;
    if (col == MaxCol)
    {
        col = 0;
        fil++;
        if (fil == MaxFil)
            fil = 0;
    } 
}

void Base::Borrar(Graphics^ g)
{
}

vector<string> Base::LeerArchivo()
{
    string Linea;
    vector<string> Resultado;
    ifstream MiArchivo("Input.txt");
    if (!MiArchivo.fail())
    {
        while (!MiArchivo.eof())
        {
            getline(MiArchivo, Linea);
            Resultado.push_back(Linea);
        }
        MiArchivo.close();
    }

    return Resultado;
}

void Base::GrabarArchivos(vector<string> datos)
{
    ofstream miarchivo("Output.txt");  // BORRA EL ARCHIVO ANTES DE GRABAR EL NUEVO DATO
    //ofstream miarchivo("OUTPUT.TXT",std::ofstream::app);  // NO BORRA EL ARCHIVO ANTES DE GRABAR EL NUEVO DATO
    if (!miarchivo.fail())
    {
        for (int i = 0; i < datos.size(); i++)
            miarchivo << datos.at(i) << "\n";

        miarchivo.flush();
        miarchivo.close();
    }
}
