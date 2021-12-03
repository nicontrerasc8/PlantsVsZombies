#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
public enum direccion {arriba, abajo, derecha, izquierda, ninguno};
using namespace System::Drawing;
class Base
{
protected:
	int x, y, w, h, dx, dy;
	bool Eliminar;
	direccion orientacion;
	int MaxFil, MaxCol, col, fil;
	int MovX, MovY;
public:
	Base();
	Base(int px, int py, int pw, int ph);
	Base(int px, int py, int pw, int ph, int pMaxFil, int pMaxCol, int Fil, int Col);
	~Base();
	void CambiarX(int c);
	void CambiarY(int c);
	void CambiarW(int c);
	void CambiarH(int c);
	void CambiarDX(int c);
	void CambiarDY(int c);
	void CambiarCol(int c);
	void CambiarFil(int c);
	void CambiarMaxFil(int c);
	void CambiarMaxCol(int c);
	void CambiarEliminar(bool e);
	virtual void Desplazamiento(direccion nueva);
	int RetornarX();
	int RetornarY();
	int RetornarW(); 
	int RetornarH();
	int RetornarDX();
	int RetornarDY();
	int RetornarCol();
	int RetornarFil();
	int RetornarMaxFil();
	int RetornarMaxCol();
	bool RetornarEliminar();
	void CambiarMovimientoX(int c);
	void CambiarMovimientoY(int c);
	int RetornarMovimientoX();
	int RetornarMovimientoY();
	Rectangle RetornarRectangulo();
	virtual void Mover(Graphics^ g);
	void Dibujar(Graphics^ g);
	virtual void DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp);
	void Borrar(Graphics^ g);
	vector<string> LeerArchivo();
	void GrabarArchivos(vector<string> datos);
};

