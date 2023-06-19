#pragma once
#include "Archivo.h"

namespace GodEyeApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MainPage
	/// </summary>
	public ref class MainPage : public System::Windows::Forms::Form
	{
	public:
		MainPage(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
			g = this->CreateGraphics();
			bfc = BufferedGraphicsManager::Current;
			bf = bfc->Allocate(g, this->ClientRectangle);
			vecDispositivos = new vector<Dispositivo>;
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MainPage()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::ComponentModel::IContainer^ components;
	protected:


	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>

		vector<Dispositivo>* vecDispositivos;
		Graphics^ g;
		BufferedGraphicsContext^ bfc;
		BufferedGraphics^ bf;

		void LeerDatos() {
			fstream arch;
			Dispositivo auxD;
			FILE* archFile;

			//Dispositivos
			//Crea el archivo si no existe
			arch.open("Dispositivos.txt", ios::in);
			if (arch.fail()) {
				arch.open("Dispositivos.txt", ios::out);
				arch << "Cs12345 1 Camara SalaEstar" << endl;
				arch << "Ss29156 0 Sensor Patio";
			}
			arch.close();
			//De todas formas, lee el archivo
			char name[7];
			int encendido;
			char tipo[20];
			char ubicacion[20];
			archFile = fopen("Dispositivos.txt", "r");
			while (fscanf(archFile, "%s%d%s%s", name, &encendido, tipo, ubicacion) != EOF) {
				auxD = Dispositivo(name, encendido, tipo, ubicacion);
				vecDispositivos->push_back(auxD);
			}
			fclose(archFile);
			//Atributos
			//Crea el archivo si no existe
			arch.open("Atributos.txt", ios::in);
			if (arch.fail()) {
				arch.open("Atributos.txt", ios::out);
				arch << "0 13:00 10/10/23 0" << endl;
				arch << "0 14:00 10/10/23 0" << endl;
				arch << "0 15:00 10/10/23 0" << endl;
				arch << "0 13:00 10/08/23 1" << endl;
				arch << "1 14:00 10/08/23 1" << endl;
				arch << "1 15:00 10/08/23 1";
			}
			arch.close();
			//De todas formas, lee el archivo
			int movimiento; char hora[5]; char fecha[8]; int dispositivoID;
			archFile = fopen("Atributos.txt", "r");
			while (fscanf(archFile, "%d%s%s%d", &movimiento, hora, fecha, &dispositivoID) != EOF) {
				vecDispositivos->at(dispositivoID).addAtributo(movimiento, hora, fecha);
			}
			fclose(archFile);
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MainPage
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(23)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			this->ClientSize = System::Drawing::Size(342, 593);
			this->ForeColor = System::Drawing::Color::White;
			this->Name = L"MainPage";
			this->Text = L"MainPage";
			this->Load += gcnew System::EventHandler(this, &MainPage::MainPage_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void MainPage_Load(System::Object^ sender, System::EventArgs^ e) {
		this->LeerDatos();
		Drawing::Font^ fuente = gcnew Drawing::Font("Times new roman", 12);
		Drawing::Font^ fuente2 = gcnew Drawing::Font("Times new roman", 14);
		for (int i = 0; i < vecDispositivos->size(); i++) {
			Dispositivo aux = vecDispositivos->at(i);
			String^ name = gcnew String(aux.getName().data());
			String^ tipo = gcnew String(aux.getTipo().data());
			String^ ubicacion = gcnew String(aux.getUbicacion().data());
			String^ encendido = " ";
			if (aux.getEncendido()) {
				encendido = "Encendido";
			}
			else { encendido = "Apagado"; }
			//drawing
			bf->Graphics->DrawString(name, fuente2, Brushes::White, 16, i * 64);
			bf->Graphics->DrawString("Tipo:" + tipo, fuente, Brushes::White, 16, 16 + i * 64);
			bf->Graphics->DrawString("Estado: "+ encendido, fuente, Brushes::White, 16, 16 + i * 64);
			bf->Graphics->DrawString("Ubicación: " + ubicacion, fuente, Brushes::White, 16, 16 + i * 64);
			bf->Render(g);
		}
	}
	};
}
