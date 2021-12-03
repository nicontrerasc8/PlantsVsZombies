#pragma once
#include "Base.h"
#include "Bala.h"
class Zombie : public Base
{
private: 
	bool IsTop;
	int PotenciadorVelocidad;
	int V;
	int BalasDisponibles;
	vector<Bala*> ArrBalas;
public:
	Zombie(int px, int py);
	~Zombie();
	void Desplazamiento(direccion nueva, Graphics^ g);
	void DibujarDesdeImagen(Graphics^ g, Bitmap^ bmp);
	void Mover(Graphics^ g);
	int RetornarV();
	int RetornarPotenciadorVelocidad();
	void IncrementarPotenciadorVelocidad();
	void SetearPotenciadorVelocidad();
	void DisminuirUnaVida();
	bool ReturnIsTop();
	void Disparar();
	void MoverBalas(Graphics^ g);
	void RecargarCantBalas();
};

