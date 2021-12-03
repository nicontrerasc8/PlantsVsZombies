#include "Controladora.h"

Controladora::Controladora(Graphics^ g)
{
	InicioApp = time(0);
	puntaje = 0;
	RandomicInmuneTime = rand() % 7 + 6;
	vector <string> parametros = ObjZombie->LeerArchivo();
	AcaboLaDinamica = false;
	EsInmune = false;
	Length = g->VisibleClipBounds.Width;
	Height = g->VisibleClipBounds.Height;
	ObjZombie = new Zombie(Length/2, Height-50);
	System::String^ aux_Cant_Plantas = gcnew System::String(parametros.at(13).c_str());
	System::String^ aux_Cant_Bonos = gcnew System::String(parametros.at(15).c_str());
	for (int i = 0; i < System::Convert::ToInt32(aux_Cant_Plantas); i++)
	{
		int RandomicX = rand() % (Length - 100);
		int RandomicY = rand() % (Height - 300) + 100;
		ArrPlantas.push_back(new Planta(RandomicX, RandomicY));
	}
	for (int i = 0; i < System::Convert::ToInt32(aux_Cant_Bonos); i++)
	{
		int Random = rand() % 3;
		int RandomicX = rand() % (Length - 100);
		int RandomicY = rand() % (Height - 300) + 100;
		if (Random == 0) ArrBonos.push_back(new Inmunidad(RandomicX,RandomicY));
		if (Random == 1) ArrBonos.push_back(new Velocidad(RandomicX, RandomicY));
		if (Random == 2) ArrBonos.push_back(new Bono(RandomicX,RandomicY));
	}
}

Controladora::~Controladora()
{
	delete ObjZombie;
}

void Controladora::DibujarZombie(Graphics^ g, Bitmap^ bpm)
{
	TimerInmune();
	ObjZombie->DibujarDesdeImagen(g, bpm);
}



void Controladora::DesplazarZombie(direccion nueva, Graphics^ g)
{
	ObjZombie->Desplazamiento(nueva, g);
}

void Controladora::DibujarPlantas(Graphics^ g, Bitmap^ bpm)
{
	for (int i = 0; i < ArrPlantas.size(); i++)
	{
		ArrPlantas.at(i)->DibujarDesdeImagen(g, bpm);
		ArrPlantas.at(i)->Mover(g);
	}
	for (int i = 0; i < ArrPlantas.size(); i++)
	{
		if (ArrPlantas.at(i)->RetornarEliminar()) {
			ArrPlantas.erase(ArrPlantas.begin() + i);
		}
	}
}

void Controladora::DibujarBalas(Graphics^ g)
{
	ObjZombie->MoverBalas(g);
}

void Controladora::DibujarBonos(Graphics^ g, Bitmap^ bpmInmunidad, Bitmap^ bpmVelocidad, Bitmap^ bpmDisparar)
{
	for (int i = 0; i < ArrBonos.size(); i++)
	{
		if (dynamic_cast<Inmunidad*> (ArrBonos.at(i)))
			ArrBonos.at(i)->DibujarDesdeImagen(g, bpmInmunidad);
		else if (dynamic_cast<Velocidad*> (ArrBonos.at(i)))
			ArrBonos.at(i)->DibujarDesdeImagen(g, bpmVelocidad);
		else
			ArrBonos.at(i)->DibujarDesdeImagen(g, bpmDisparar);
	}
	for (int i = 0; i < ArrBonos.size(); i++)
	{
		if (ArrBonos.at(i)->RetornarEliminar()) {
			ArrBonos.erase(ArrBonos.begin() + i);
		}
	}
}

int Controladora::RetornarVidasDelJugador()
{
	return ObjZombie->RetornarV();
}

void Controladora::ColisionPlantaBala()
{
}


void Controladora::ColisionPlantas_Zombies()
{
	Rectangle r1 = ObjZombie->RetornarRectangulo();
	for (int i = 0; i < ArrPlantas.size(); i++)
	{
		Rectangle r2 = ArrPlantas.at(i)->RetornarRectangulo();
		if (r1.IntersectsWith(r2) && !EsInmune) {
			ObjZombie->DisminuirUnaVida();
			ObjZombie->CambiarX(Length / 2);
			ObjZombie->CambiarY(Height - ObjZombie->RetornarW() - 20);
			if (ObjZombie->RetornarV() <= 0) AcaboLaDinamica = true;
			ArrPlantas.at(i)->CambiarEliminar(true);
		}
	}
}

void Controladora::ColisionBono()
{
	Rectangle r1 = ObjZombie->RetornarRectangulo();
	for (int i = 0; i < ArrBonos.size(); i++)
	{
		Rectangle r2 = ArrBonos.at(i)->RetornarRectangulo();
		if (r1.IntersectsWith(r2)) {
			if (dynamic_cast<Inmunidad*> (ArrBonos.at(i))) {
				TiempoInmunidad = time(0);
				EsInmune = true;
			}
			else if (dynamic_cast<Velocidad*> (ArrBonos.at(i))) {
				ObjZombie->IncrementarPotenciadorVelocidad();
				TiempoBonoVelocidad = time(0);
			}
			else{
				RecargarBalas();
			}
			ArrBonos.at(i)->CambiarEliminar(true);
		}
	}
}

void Controladora::TimerInmune()
{
	if (difftime(time(0), TiempoInmunidad) > RandomicInmuneTime) 
		EsInmune = false;
}

void Controladora::TimerVelocidad()
{
	if (difftime(time(0), TiempoBonoVelocidad) > 10)
		ObjZombie->SetearPotenciadorVelocidad();
}

void Controladora::Disparar()
{
	ObjZombie->Disparar();
}

void Controladora::RecargarBalas()
{
	ObjZombie->RecargarCantBalas();
}



bool Controladora::ReturnTermino()
{
	if (ObjZombie->ReturnIsTop()) AcaboLaDinamica = true;
	return AcaboLaDinamica;
}

bool Controladora::Gano()
{
	return ObjZombie->ReturnIsTop();
}

System::String^ Controladora::RetornarArchivoBG()
{
	return gcnew System::String(ObjZombie->LeerArchivo().at(0).c_str());
}

System::String^ Controladora::RetornarArchivoZombie()
{
	return gcnew System::String(ObjZombie->LeerArchivo().at(1).c_str());
}

System::String^ Controladora::RetornarArchivoPlantas()
{
	return gcnew System::String(ObjZombie->LeerArchivo().at(4).c_str());
}

System::String^ Controladora::RetornarArchivoInmunidad()
{
	return gcnew System::String(ObjZombie->LeerArchivo().at(16).c_str());
}

System::String^ Controladora::RetornarArchivoDisparar()
{
	return gcnew System::String(ObjZombie->LeerArchivo().at(18).c_str());
}

System::String^ Controladora::RetornarArchivoVelocidad()
{
	return gcnew System::String(ObjZombie->LeerArchivo().at(17).c_str());
}

/*void Controladora::GrabarResultado(vector<string> datos)
{
	objSoldado->GrabarArchivos(datos);
}*/




