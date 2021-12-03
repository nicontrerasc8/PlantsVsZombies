#pragma once
#include <vector>
#include <time.h>
#include "Base.h"
#include "Planta.h"
#include "Zombie.h"
#include "Inmunidad.h"
#include "Velocidad.h"
#include "Disparar.h"
using namespace std;
class Controladora
{
private:
	//vector<*> arrX;
	vector <Planta*> ArrPlantas;
	vector <Bono*> ArrBonos;
	Zombie* ObjZombie;
	bool AcaboLaDinamica;
	int puntaje;
	int RandomicInmuneTime;
	int Length, Height;
	bool EsInmune;
	time_t InicioApp;
	time_t TiempoInmunidad;
	time_t TiempoBonoVelocidad;

public:
	Controladora(Graphics^ g);
	~Controladora();
	void DibujarZombie(Graphics^ g, Bitmap^ bpm);
	void DesplazarZombie(direccion nueva, Graphics^ g);
	void DibujarPlantas(Graphics^ g, Bitmap^ bpm);
	void DibujarBalas(Graphics^ g);
	void DibujarBonos(Graphics^ g, Bitmap^ bpmInmunidad, Bitmap^ bpmVelocidad, Bitmap^ bpmDisparar);
	int RetornarVidasDelJugador();
	void ColisionPlantaBala();
	//void Dibujar1(Graphics^ g, Bitmap^ bpm);
	//void Dibujar2(Graphics^ g, Bitmap^ bpm);
	//void Dibujar3(Graphics^ g, Bitmap^ bpm);
	//void DesplazarObjeto(direccion nueva);
	void ColisionPlantas_Zombies();
	void ColisionBono();
	void TimerInmune();
	void TimerVelocidad();
	void Disparar();
	void RecargarBalas();
	bool ReturnTermino();
	bool Gano();
	System::String^ RetornarArchivoBG();
	System::String^ RetornarArchivoZombie();
	System::String^ RetornarArchivoPlantas();
	System::String^ RetornarArchivoInmunidad();
	System::String^ RetornarArchivoDisparar();
	System::String^ RetornarArchivoVelocidad();
	//void GrabarResultado(vector<string> datos);
	//System::String^ RetornarArchivo1();
	//System::String^ RetornarArchivo2();
	//System::String^ RetornarArchivo3();
};

