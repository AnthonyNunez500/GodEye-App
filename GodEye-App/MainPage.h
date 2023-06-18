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
			Archivo arch;
			//vector<Dispositivo> auxVec = vector<Dispositivo>();
			arch.LeerDispositivo();
			//auxVec = arch.GetDispositivos();
			int n = arch.getDispositivosSize();
			for (int i = 0; i < n; i++) {
				Dispositivo aux = arch.GetDispositivo(i);
				vecDispositivos->push_back(aux);
			}
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
	}
	};
}
