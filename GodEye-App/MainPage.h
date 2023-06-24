#pragma once
#include "Archivo.h"
#include "MyForm.h"

using namespace System;
using namespace std;

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
		//vector<Button>* vecButtons;
		Graphics^ g;
		BufferedGraphicsContext^ bfc;
	private: System::Windows::Forms::Timer^ timer1;
		   BufferedGraphics^ bf;

		void LeerDatos() {
			fstream arch;
			Dispositivo auxD;
			FILE* archFile;
			Archivo ar;
			ar.LeerDispositivo(vecDispositivos);
			ar.LeerAtributo(vecDispositivos);
		}
		void ButtonPress(double i) {
			MyForm^ myform = gcnew MyForm;
			myform->Show();
		}

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MainPage::timer1_Tick);
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
		//Leer los datos del programa
		this->LeerDatos();
		for (int i = 0; i < vecDispositivos->size(); i++) {
			string auxName = vecDispositivos->at(i).getName();
			Button^ aux=gcnew Button();
			aux->Location = Point(24, 64 + i * 96);
			aux->Height = 28;
			aux->Width = 96;
			aux->BackColor = Color::White;
			aux->Font = gcnew Drawing::Font("Times new roman", 12);
			aux->ForeColor = Color::FromArgb(
				static_cast<System::Int32>(static_cast<System::Byte>(25)),
				static_cast<System::Int32>(static_cast<System::Byte>(23)),
				static_cast<System::Int32>(static_cast<System::Byte>(60)));
			aux->Text = "Acceder";
			aux->Name = "access_" + gcnew String(auxName.data());
			aux->AccessibleName = i.ToString();
			this->Controls->Add(aux);
			aux->Click += gcnew EventHandler(this, &MainPage::Button_Click);
		}
	}
	private: System::Void Button_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ aux = (Button^)sender;
		String^ strName = aux->AccessibleName;
		double id = Convert::ToDouble(strName);
		this->ButtonPress(id);
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Drawing::Font^ fuente = gcnew Drawing::Font("Times new roman", 12);
		Drawing::Font^ fuente2 = gcnew Drawing::Font("Times new roman", 14);
		//Limpiar la pantalla
		bf->Graphics->Clear(this->BackColor);

		for (int i = 0; i < vecDispositivos->size(); i++) {
			//auxiliares
			string auxName = vecDispositivos->at(i).getName();
			string auxTipo = vecDispositivos->at(i).getTipo();
			string auxUbicacion = vecDispositivos->at(i).getUbicacion();
			bool auxEncendido = vecDispositivos->at(i).getEncendido();
			String^ name = gcnew String(auxName.data());
			String^ tipo = gcnew String(auxTipo.data());
			String^ ubicacion = gcnew String(auxUbicacion.data());
			String^ encendido = " ";
			if (auxEncendido) {
				encendido = "Encendido";
			}
			else { encendido = "Apagado"; }
			//drawing
			bf->Graphics->DrawString(name, fuente2, Brushes::White, 24, i * 96);
			bf->Graphics->DrawString(tipo, fuente, Brushes::White, 24, 16 + i * 96);
			bf->Graphics->DrawString(encendido, fuente, Brushes::White, 24, 32 + i * 96);
			bf->Graphics->DrawString(ubicacion, fuente, Brushes::White, 24, 48 + i * 96);
		}
		bf->Render(g);
	}
};
}
