#pragma once

#include "Scorpion.h"

namespace Scorpion {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Window
	/// </summary>
	public ref class Window : public System::Windows::Forms::Form
	{
	public:
		Window(void)
		{
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Window()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  ProcLbl;
	private: System::Windows::Forms::ListView^  procLV;
	private: System::Windows::Forms::Button^  procRefBt;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Label^  libLbl;
	private: System::Windows::Forms::Button^  addLibBt;
	private: System::Windows::Forms::Panel^  injPanel;



	private: System::Windows::Forms::Button^  injectBt;
	private: System::Windows::Forms::Button^  advsetBt;
	private: System::Windows::Forms::Label^  credLbl;

	private: System::Windows::Forms::ColumnHeader^  procNm;
	private: System::Windows::Forms::ColumnHeader^  procThr;
	private: System::Windows::Forms::ColumnHeader^  procPID;
	private: System::Windows::Forms::ColumnHeader^  procPPID;

	private: System::Windows::Forms::ColumnHeader^  chkBox;
	private: System::Windows::Forms::ListView^  dllView;

	private: System::Windows::Forms::ColumnHeader^  chkCol;
	private: System::Windows::Forms::ColumnHeader^  dllPath;
	private: System::Windows::Forms::OpenFileDialog^  ofDialog;
	private: System::Windows::Forms::Label^  injMethLbl;
	private: System::Windows::Forms::ComboBox^  injMethCb;
	private: System::Windows::Forms::Label^  credLbl2;
	private: System::Windows::Forms::CheckBox^  procAAChk;
	private: System::Windows::Forms::Label^  hpLbl;
	private: System::Windows::Forms::ComboBox^  hpCbx;




	private: System::ComponentModel::IContainer^  components;





	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Window::typeid));
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->procLV = (gcnew System::Windows::Forms::ListView());
			this->chkBox = (gcnew System::Windows::Forms::ColumnHeader());
			this->procNm = (gcnew System::Windows::Forms::ColumnHeader());
			this->procThr = (gcnew System::Windows::Forms::ColumnHeader());
			this->procPID = (gcnew System::Windows::Forms::ColumnHeader());
			this->procPPID = (gcnew System::Windows::Forms::ColumnHeader());
			this->procRefBt = (gcnew System::Windows::Forms::Button());
			this->ProcLbl = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->dllView = (gcnew System::Windows::Forms::ListView());
			this->chkCol = (gcnew System::Windows::Forms::ColumnHeader());
			this->dllPath = (gcnew System::Windows::Forms::ColumnHeader());
			this->addLibBt = (gcnew System::Windows::Forms::Button());
			this->libLbl = (gcnew System::Windows::Forms::Label());
			this->injPanel = (gcnew System::Windows::Forms::Panel());
			this->hpLbl = (gcnew System::Windows::Forms::Label());
			this->hpCbx = (gcnew System::Windows::Forms::ComboBox());
			this->procAAChk = (gcnew System::Windows::Forms::CheckBox());
			this->credLbl2 = (gcnew System::Windows::Forms::Label());
			this->injMethCb = (gcnew System::Windows::Forms::ComboBox());
			this->injMethLbl = (gcnew System::Windows::Forms::Label());
			this->credLbl = (gcnew System::Windows::Forms::Label());
			this->advsetBt = (gcnew System::Windows::Forms::Button());
			this->injectBt = (gcnew System::Windows::Forms::Button());
			this->ofDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->injPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::Color::SteelBlue;
			this->panel1->Controls->Add(this->procLV);
			this->panel1->Controls->Add(this->procRefBt);
			this->panel1->Controls->Add(this->ProcLbl);
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(359, 167);
			this->panel1->TabIndex = 0;
			// 
			// procLV
			// 
			this->procLV->BackColor = System::Drawing::Color::AliceBlue;
			this->procLV->CheckBoxes = true;
			this->procLV->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->chkBox, this->procNm,
					this->procThr, this->procPID, this->procPPID
			});
			this->procLV->FullRowSelect = true;
			this->procLV->GridLines = true;
			this->procLV->HideSelection = false;
			this->procLV->Location = System::Drawing::Point(12, 40);
			this->procLV->Name = L"procLV";
			this->procLV->Size = System::Drawing::Size(335, 115);
			this->procLV->TabIndex = 2;
			this->procLV->UseCompatibleStateImageBehavior = false;
			this->procLV->View = System::Windows::Forms::View::Details;
			// 
			// chkBox
			// 
			this->chkBox->Text = L"";
			this->chkBox->Width = 22;
			// 
			// procNm
			// 
			this->procNm->Text = L"Process";
			this->procNm->Width = 92;
			// 
			// procThr
			// 
			this->procThr->Text = L"Threads";
			this->procThr->Width = 55;
			// 
			// procPID
			// 
			this->procPID->Text = L"PID";
			this->procPID->Width = 65;
			// 
			// procPPID
			// 
			this->procPPID->Text = L"Parent PID";
			this->procPPID->Width = 65;
			// 
			// procRefBt
			// 
			this->procRefBt->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->procRefBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->procRefBt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->procRefBt->ForeColor = System::Drawing::Color::White;
			this->procRefBt->Location = System::Drawing::Point(287, 7);
			this->procRefBt->Name = L"procRefBt";
			this->procRefBt->Size = System::Drawing::Size(60, 40);
			this->procRefBt->TabIndex = 3;
			this->procRefBt->Text = L"↺";
			this->procRefBt->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->procRefBt->UseVisualStyleBackColor = true;
			this->procRefBt->Click += gcnew System::EventHandler(this, &Window::procRefBt_Click);
			// 
			// ProcLbl
			// 
			this->ProcLbl->AutoSize = true;
			this->ProcLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ProcLbl->ForeColor = System::Drawing::Color::White;
			this->ProcLbl->Location = System::Drawing::Point(8, 9);
			this->ProcLbl->Name = L"ProcLbl";
			this->ProcLbl->Size = System::Drawing::Size(98, 25);
			this->ProcLbl->TabIndex = 0;
			this->ProcLbl->Text = L"Processes:";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::IndianRed;
			this->panel2->Controls->Add(this->dllView);
			this->panel2->Controls->Add(this->addLibBt);
			this->panel2->Controls->Add(this->libLbl);
			this->panel2->Location = System::Drawing::Point(0, 167);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(359, 167);
			this->panel2->TabIndex = 4;
			// 
			// dllView
			// 
			this->dllView->BackColor = System::Drawing::Color::MistyRose;
			this->dllView->CheckBoxes = true;
			this->dllView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->chkCol, this->dllPath });
			this->dllView->GridLines = true;
			this->dllView->Location = System::Drawing::Point(12, 37);
			this->dllView->Name = L"dllView";
			this->dllView->Size = System::Drawing::Size(335, 115);
			this->dllView->TabIndex = 6;
			this->dllView->UseCompatibleStateImageBehavior = false;
			this->dllView->View = System::Windows::Forms::View::Details;
			// 
			// chkCol
			// 
			this->chkCol->Text = L"";
			this->chkCol->Width = 27;
			// 
			// dllPath
			// 
			this->dllPath->Text = L"Path";
			this->dllPath->Width = 285;
			// 
			// addLibBt
			// 
			this->addLibBt->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->addLibBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->addLibBt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->addLibBt->ForeColor = System::Drawing::Color::White;
			this->addLibBt->Location = System::Drawing::Point(287, 6);
			this->addLibBt->Name = L"addLibBt";
			this->addLibBt->Size = System::Drawing::Size(60, 33);
			this->addLibBt->TabIndex = 5;
			this->addLibBt->Text = L"+";
			this->addLibBt->UseVisualStyleBackColor = true;
			this->addLibBt->Click += gcnew System::EventHandler(this, &Window::addLibBt_Click);
			// 
			// libLbl
			// 
			this->libLbl->AutoSize = true;
			this->libLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->libLbl->ForeColor = System::Drawing::Color::White;
			this->libLbl->Location = System::Drawing::Point(8, 6);
			this->libLbl->Name = L"libLbl";
			this->libLbl->Size = System::Drawing::Size(138, 25);
			this->libLbl->TabIndex = 0;
			this->libLbl->Text = L"Libraries (*.dll):";
			// 
			// injPanel
			// 
			this->injPanel->BackColor = System::Drawing::Color::DarkSalmon;
			this->injPanel->Controls->Add(this->hpLbl);
			this->injPanel->Controls->Add(this->hpCbx);
			this->injPanel->Controls->Add(this->procAAChk);
			this->injPanel->Controls->Add(this->credLbl2);
			this->injPanel->Controls->Add(this->injMethCb);
			this->injPanel->Controls->Add(this->injMethLbl);
			this->injPanel->Controls->Add(this->credLbl);
			this->injPanel->Controls->Add(this->advsetBt);
			this->injPanel->Controls->Add(this->injectBt);
			this->injPanel->Location = System::Drawing::Point(0, 334);
			this->injPanel->Name = L"injPanel";
			this->injPanel->Size = System::Drawing::Size(359, 80);
			this->injPanel->TabIndex = 4;
			// 
			// hpLbl
			// 
			this->hpLbl->AutoSize = true;
			this->hpLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->hpLbl->ForeColor = System::Drawing::Color::White;
			this->hpLbl->Location = System::Drawing::Point(10, 94);
			this->hpLbl->Name = L"hpLbl";
			this->hpLbl->Size = System::Drawing::Size(106, 17);
			this->hpLbl->TabIndex = 14;
			this->hpLbl->Text = L"Hook Procedure:";
			this->hpLbl->Visible = false;
			// 
			// hpCbx
			// 
			this->hpCbx->BackColor = System::Drawing::Color::MistyRose;
			this->hpCbx->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->hpCbx->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->hpCbx->FormattingEnabled = true;
			this->hpCbx->Items->AddRange(gcnew cli::array< System::Object^  >(15) {
				L"WH_CALLWNDPROC", L"WH_CALLWNDPROCRET", L"WH_CBT",
					L"WH_DEBUG", L"WH_FOREGROUNDIDLE", L"WH_GETMESSAGE", L"WH_JOURNALPLAYBACK", L"WH_JOURNALRECORD", L"WH_KEYBOARD", L"WH_KEYBOARD_LL",
					L"WH_MOUSE", L"WH_MOUSE_LL", L"WH_MSGFILTER", L"WH_SHELL", L"WH_SYSMSGFILTER"
			});
			this->hpCbx->Location = System::Drawing::Point(123, 93);
			this->hpCbx->Name = L"hpCbx";
			this->hpCbx->Size = System::Drawing::Size(224, 21);
			this->hpCbx->TabIndex = 13;
			this->hpCbx->Visible = false;
			// 
			// procAAChk
			// 
			this->procAAChk->AutoSize = true;
			this->procAAChk->ForeColor = System::Drawing::Color::White;
			this->procAAChk->Location = System::Drawing::Point(123, 93);
			this->procAAChk->Name = L"procAAChk";
			this->procAAChk->Size = System::Drawing::Size(231, 30);
			this->procAAChk->TabIndex = 12;
			this->procAAChk->Text = L"Use PROCESS_ALL_ACCESS\?\r\n(enabled by default in NT 6.x environments)";
			this->procAAChk->UseVisualStyleBackColor = true;
			this->procAAChk->Visible = false;
			// 
			// credLbl2
			// 
			this->credLbl2->AutoSize = true;
			this->credLbl2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->credLbl2->ForeColor = System::Drawing::Color::MistyRose;
			this->credLbl2->Location = System::Drawing::Point(3, 145);
			this->credLbl2->Name = L"credLbl2";
			this->credLbl2->Size = System::Drawing::Size(234, 26);
			this->credLbl2->TabIndex = 11;
			this->credLbl2->Text = L"Thanks to: Caroline Rudin for name suggestion, \r\nIlya Ostrovskiy (@iostat) for Wi"
				L"nAPI advice.\r\n";
			this->credLbl2->Visible = false;
			// 
			// injMethCb
			// 
			this->injMethCb->BackColor = System::Drawing::Color::MistyRose;
			this->injMethCb->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->injMethCb->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->injMethCb->FormattingEnabled = true;
			this->injMethCb->Items->AddRange(gcnew cli::array< System::Object^  >(3) {
				L"WinAPI CreateRemoteThread (default)", L"WinAPI SetWindowsHookEx",
					L"Target process fetch via ASM "
			});
			this->injMethCb->Location = System::Drawing::Point(123, 66);
			this->injMethCb->Name = L"injMethCb";
			this->injMethCb->Size = System::Drawing::Size(224, 21);
			this->injMethCb->TabIndex = 10;
			this->injMethCb->Visible = false;
			this->injMethCb->SelectedIndexChanged += gcnew System::EventHandler(this, &Window::injMethCb_SelectedIndexChanged);
			// 
			// injMethLbl
			// 
			this->injMethLbl->AutoSize = true;
			this->injMethLbl->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->injMethLbl->ForeColor = System::Drawing::Color::White;
			this->injMethLbl->Location = System::Drawing::Point(10, 67);
			this->injMethLbl->Name = L"injMethLbl";
			this->injMethLbl->Size = System::Drawing::Size(109, 17);
			this->injMethLbl->TabIndex = 9;
			this->injMethLbl->Text = L"Injection Method:";
			this->injMethLbl->Visible = false;
			// 
			// credLbl
			// 
			this->credLbl->AutoSize = true;
			this->credLbl->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->credLbl->ForeColor = System::Drawing::Color::MistyRose;
			this->credLbl->Location = System::Drawing::Point(3, 59);
			this->credLbl->Name = L"credLbl";
			this->credLbl->Size = System::Drawing::Size(0, 13);
			this->credLbl->TabIndex = 8;
			// 
			// advsetBt
			// 
			this->advsetBt->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->advsetBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->advsetBt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->advsetBt->ForeColor = System::Drawing::Color::White;
			this->advsetBt->Location = System::Drawing::Point(310, 10);
			this->advsetBt->Name = L"advsetBt";
			this->advsetBt->Size = System::Drawing::Size(37, 38);
			this->advsetBt->TabIndex = 7;
			this->advsetBt->Text = L"...";
			this->advsetBt->UseVisualStyleBackColor = true;
			this->advsetBt->Click += gcnew System::EventHandler(this, &Window::advsetBt_Click);
			// 
			// injectBt
			// 
			this->injectBt->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->injectBt->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->injectBt->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->injectBt->ForeColor = System::Drawing::Color::White;
			this->injectBt->Location = System::Drawing::Point(12, 10);
			this->injectBt->Name = L"injectBt";
			this->injectBt->Size = System::Drawing::Size(292, 38);
			this->injectBt->TabIndex = 3;
			this->injectBt->Text = L"Inject";
			this->injectBt->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->injectBt->UseVisualStyleBackColor = true;
			this->injectBt->Click += gcnew System::EventHandler(this, &Window::injectBt_Click);
			// 
			// ofDialog
			// 
			this->ofDialog->Filter = L"DLL files|*.dll";
			this->ofDialog->InitialDirectory = L"%HOMEPATH%\\Desktop";
			this->ofDialog->Multiselect = true;
			// 
			// Window
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(356, 413);
			this->Controls->Add(this->injPanel);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Window";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Scorpion v0.2 (beta)";
			this->Load += gcnew System::EventHandler(this, &Window::Window_Load);
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->injPanel->ResumeLayout(false);
			this->injPanel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private:
		void refreshList();
		System::Void Window_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void procRefBt_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void addLibBt_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void advsetBt_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void injectBt_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void injMethCb_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e);
};
}
