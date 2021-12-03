#pragma once 
#include "Controladora.h"

namespace WForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			Graphics^ g = CreateGraphics();
			BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
			BufferedGraphics^ bf = espacio->Allocate(g, ClientRectangle);
			Juego = new Controladora(bf->Graphics);
			FondoBitmap = gcnew Bitmap(Juego->RetornarArchivoBG());
			bmpZombie = gcnew Bitmap(Juego->RetornarArchivoZombie());
			bmpPlantas = gcnew Bitmap(Juego->RetornarArchivoPlantas());
			bpmVelocidad = gcnew Bitmap(Juego->RetornarArchivoVelocidad());
			bpmInmunidad = gcnew Bitmap(Juego->RetornarArchivoInmunidad());
			bpmDisparar = gcnew Bitmap(Juego->RetornarArchivoDisparar());
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
			delete Juego;
		}

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		Controladora* Juego;
		Bitmap^ FondoBitmap;
		Bitmap^ bmpZombie;
		Bitmap^ bmpPlantas;
		Bitmap^ bpmDisparar;
		Bitmap^ bpmVelocidad;
		Bitmap^ bpmInmunidad;
		String^ NombreJugador;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label1;
	private: System::ComponentModel::IContainer^ components;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(52, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(0, 17);
			this->label1->TabIndex = 0;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(978, 557);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	public: void CambiarNombreJugador(String^ nuevo) {
		NombreJugador = nuevo;
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = espacio->Allocate(g, ClientRectangle);
		int Wwidth = bf->Graphics->VisibleClipBounds.Width;
		int Wheight = bf->Graphics->VisibleClipBounds.Height;
		System::Drawing::Font^ f = gcnew System::Drawing::Font("Arial", 30);
		System::Drawing::SolidBrush^ sb = gcnew System::Drawing::SolidBrush(Color::Black);
			bf->Graphics->Clear(Color::White);
			if (Juego->ReturnTermino() == false) {
				bf->Graphics->DrawImage(FondoBitmap, 0, 0, Wwidth, Wheight);
				String^ s = "Cantidad de vidas: " + Juego->RetornarVidasDelJugador();
				bf->Graphics->DrawString(s, f, sb, 10,10);
				Juego->DibujarZombie(bf->Graphics, bmpZombie);
				Juego->DibujarPlantas(bf->Graphics, bmpPlantas);
				Juego->DibujarBonos(bf->Graphics, bpmInmunidad, bpmVelocidad, bpmDisparar);
				Juego->DibujarBalas(bf->Graphics);
				Juego->ColisionBono();
				Juego->ColisionPlantas_Zombies();
				/*Juego->DibujarSoldado(bf->Graphics, bmpSoldado);
				Juego->DibujarBalas(bf->Graphics, bmpBalas);
				Juego->DibujarMonedas(bf->Graphics, bmpMonedas);
				Juego->ColisionMonedasBalas();*/
			}
			else {
					timer1->Enabled = false;
					char Aux[100];
					sprintf(Aux, "%s", NombreJugador);
					vector<string> datos;
					datos.push_back(Aux);
					/*datos.push_back(std::to_string(Juego->RetornarResultado()));
					Juego->GrabarResultado(datos);*/
					bf->Graphics->DrawImage(FondoBitmap, 0,0, Wwidth, Wheight);
					String^ s = (Juego->Gano() ? "Felicidades " + NombreJugador + ", ganaste" : "Perdiste " + NombreJugador + ", sorry");
					bf->Graphics->DrawString(s, f, sb, 10, 10);
			}
			bf->Render(g);
			delete g, espacio, bf;
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		Graphics^ g = CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = espacio->Allocate(g, ClientRectangle);
		if (e->KeyCode == Keys::Left) Juego->DesplazarZombie(direccion::izquierda, bf->Graphics);
		if (e->KeyCode == Keys::Right) Juego->DesplazarZombie(direccion::derecha, bf->Graphics);
		if (e->KeyCode == Keys::Up) Juego->DesplazarZombie(direccion::arriba, bf->Graphics);
		if (e->KeyCode == Keys::Down) Juego->DesplazarZombie(direccion::abajo, bf->Graphics);
		if (e->KeyCode == Keys::Space) Juego->Disparar();
	}
	};
}
