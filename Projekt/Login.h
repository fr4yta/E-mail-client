#pragma once
#include "SMTPLogin.h";
#include "POP3Login.h";
#include "SMTP.h";
#include "POP3.h";

#include <msclr\marshal_cppstd.h>

namespace Projekt {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/** Klasa glowna odpowiedzialna za logowanie do danego protokolu `POP3` / `SMTP` */
	public ref class Login : public System::Windows::Forms::Form {
	public:
		/** Konstruktor dla klasy `Login`, ktory inicjuje wszystkie niezbedne komponenty */
		Login(void) {
			InitializeComponent();
		}

	protected:
		/** Destruktor dla klasy `Login`, ktory usuwa wszystkie utworzone wczesniej komponenty */
		~Login() {
			if (components) {
				delete components;
			}
		}

	private: System::Windows::Forms::TextBox^ Input_serveraddress;
	private: System::Windows::Forms::Label^ Label_Server;
	private: System::Windows::Forms::Label^ Label_user;
	private: System::Windows::Forms::TextBox^ Input_username;
	private: System::Windows::Forms::Label^ Label_password;
	private: System::Windows::Forms::TextBox^ Input_password;
	private: System::Windows::Forms::Label^ Label_port;
	private: System::Windows::Forms::TextBox^ Input_port;
	private: System::Windows::Forms::CheckBox^ Checkbox_POP3;
	private: System::Windows::Forms::CheckBox^ Checkbox_SMTP;
	private: System::Windows::Forms::Button^ Button_login;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::Label^ topicLogin;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ labelPOP3;
	private: System::Windows::Forms::Label^ labelSMTP;
	private: System::Windows::Forms::Label^ copy;
	private: System::ComponentModel::Container ^components;

		/** Metoda `InitializeComponent()` inicjalizuje niezbedne komponenty */
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(Login::typeid));
			this->Input_serveraddress = (gcnew System::Windows::Forms::TextBox());
			this->Label_Server = (gcnew System::Windows::Forms::Label());
			this->Label_user = (gcnew System::Windows::Forms::Label());
			this->Input_username = (gcnew System::Windows::Forms::TextBox());
			this->Label_password = (gcnew System::Windows::Forms::Label());
			this->Input_password = (gcnew System::Windows::Forms::TextBox());
			this->Label_port = (gcnew System::Windows::Forms::Label());
			this->Input_port = (gcnew System::Windows::Forms::TextBox());
			this->Checkbox_POP3 = (gcnew System::Windows::Forms::CheckBox());
			this->Checkbox_SMTP = (gcnew System::Windows::Forms::CheckBox());
			this->Button_login = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->topicLogin = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->labelPOP3 = (gcnew System::Windows::Forms::Label());
			this->labelSMTP = (gcnew System::Windows::Forms::Label());
			this->copy = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->SuspendLayout();
			// 
			// Input_serveraddress
			// 
			this->Input_serveraddress->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->Input_serveraddress->Location = System::Drawing::Point(114, 3);
			this->Input_serveraddress->MaxLength = 256;
			this->Input_serveraddress->Name = L"Input_serveraddress";
			this->Input_serveraddress->Size = System::Drawing::Size(898, 20);
			this->Input_serveraddress->TabIndex = 1;
			// 
			// Label_Server
			// 
			this->Label_Server->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->Label_Server->AutoSize = true;
			this->Label_Server->Location = System::Drawing::Point(31, 6);
			this->Label_Server->Name = L"Label_Server";
			this->Label_Server->Size = System::Drawing::Size(77, 13);
			this->Label_Server->TabIndex = 2;
			this->Label_Server->Text = L"Adres serwera:";
			// 
			// Label_user
			// 
			this->Label_user->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->Label_user->AutoSize = true;
			this->Label_user->Location = System::Drawing::Point(3, 32);
			this->Label_user->Name = L"Label_user";
			this->Label_user->Size = System::Drawing::Size(105, 13);
			this->Label_user->TabIndex = 4;
			this->Label_user->Text = L"Nazwa u¿ytkownika:";
			// 
			// Input_username
			// 
			this->Input_username->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->Input_username->Location = System::Drawing::Point(114, 29);
			this->Input_username->MaxLength = 256;
			this->Input_username->Name = L"Input_username";
			this->Input_username->Size = System::Drawing::Size(898, 20);
			this->Input_username->TabIndex = 3;
			// 
			// Label_password
			// 
			this->Label_password->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->Label_password->AutoSize = true;
			this->Label_password->Location = System::Drawing::Point(69, 58);
			this->Label_password->Name = L"Label_password";
			this->Label_password->Size = System::Drawing::Size(39, 13);
			this->Label_password->TabIndex = 6;
			this->Label_password->Text = L"Has³o:";
			// 
			// Input_password
			// 
			this->Input_password->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->Input_password->Location = System::Drawing::Point(114, 55);
			this->Input_password->MaxLength = 256;
			this->Input_password->Name = L"Input_password";
			this->Input_password->PasswordChar = '*';
			this->Input_password->Size = System::Drawing::Size(898, 20);
			this->Input_password->TabIndex = 5;
			// 
			// Label_port
			// 
			this->Label_port->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->Label_port->AutoSize = true;
			this->Label_port->Location = System::Drawing::Point(79, 84);
			this->Label_port->Name = L"Label_port";
			this->Label_port->Size = System::Drawing::Size(29, 13);
			this->Label_port->TabIndex = 8;
			this->Label_port->Text = L"Port:";
			// 
			// Input_port
			// 
			this->Input_port->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->Input_port->Location = System::Drawing::Point(114, 81);
			this->Input_port->MaxLength = 256;
			this->Input_port->Name = L"Input_port";
			this->Input_port->Size = System::Drawing::Size(898, 20);
			this->Input_port->TabIndex = 7;
			// 
			// Checkbox_POP3
			// 
			this->Checkbox_POP3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->Checkbox_POP3->AutoSize = true;
			this->Checkbox_POP3->Checked = true;
			this->Checkbox_POP3->CheckState = System::Windows::Forms::CheckState::Checked;
			this->Checkbox_POP3->Location = System::Drawing::Point(114, 107);
			this->Checkbox_POP3->Name = L"Checkbox_POP3";
			this->Checkbox_POP3->Size = System::Drawing::Size(898, 17);
			this->Checkbox_POP3->TabIndex = 9;
			this->Checkbox_POP3->Text = L"POP3";
			this->Checkbox_POP3->UseVisualStyleBackColor = true;
			this->Checkbox_POP3->CheckedChanged += gcnew System::EventHandler(this, &Login::checkBox_POP3);
			// 
			// Checkbox_SMTP
			// 
			this->Checkbox_SMTP->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->Checkbox_SMTP->AutoSize = true;
			this->Checkbox_SMTP->Location = System::Drawing::Point(114, 130);
			this->Checkbox_SMTP->Name = L"Checkbox_SMTP";
			this->Checkbox_SMTP->Size = System::Drawing::Size(898, 17);
			this->Checkbox_SMTP->TabIndex = 10;
			this->Checkbox_SMTP->Text = L"SMTP";
			this->Checkbox_SMTP->UseVisualStyleBackColor = true;
			this->Checkbox_SMTP->CheckedChanged += gcnew System::EventHandler(this, &Login::checkBox_SMTP);
			// 
			// Button_login
			// 
			this->Button_login->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Button_login->Location = System::Drawing::Point(114, 160);
			this->Button_login->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			this->Button_login->Name = L"Button_login";
			this->Button_login->Size = System::Drawing::Size(898, 23);
			this->Button_login->TabIndex = 11;
			this->Button_login->Text = L"Zaloguj";
			this->Button_login->UseVisualStyleBackColor = true;
			this->Button_login->Click += gcnew System::EventHandler(this, &Login::button1_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->BackColor = System::Drawing::SystemColors::ScrollBar;
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->topicLogin, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(1015, 61);
			this->tableLayoutPanel1->TabIndex = 12;
			// 
			// topicLogin
			// 
			this->topicLogin->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->topicLogin->AutoSize = true;
			this->topicLogin->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->topicLogin->ForeColor = System::Drawing::SystemColors::ControlText;
			this->topicLogin->Location = System::Drawing::Point(339, 15);
			this->topicLogin->Name = L"topicLogin";
			this->topicLogin->Size = System::Drawing::Size(336, 31);
			this->topicLogin->TabIndex = 0;
			this->topicLogin->Text = L"Logowanie do systemu poczty";
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel2->ColumnCount = 3;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel2->Controls->Add(this->Label_Server, 1, 0);
			this->tableLayoutPanel2->Controls->Add(this->Input_serveraddress, 2, 0);
			this->tableLayoutPanel2->Controls->Add(this->Input_username, 2, 1);
			this->tableLayoutPanel2->Controls->Add(this->Label_user, 1, 1);
			this->tableLayoutPanel2->Controls->Add(this->Input_password, 2, 2);
			this->tableLayoutPanel2->Controls->Add(this->Label_password, 1, 2);
			this->tableLayoutPanel2->Controls->Add(this->Input_port, 2, 3);
			this->tableLayoutPanel2->Controls->Add(this->Label_port, 1, 3);
			this->tableLayoutPanel2->Controls->Add(this->Checkbox_POP3, 2, 4);
			this->tableLayoutPanel2->Controls->Add(this->Checkbox_SMTP, 2, 5);
			this->tableLayoutPanel2->Controls->Add(this->Button_login, 2, 6);
			this->tableLayoutPanel2->Controls->Add(this->labelPOP3, 1, 4);
			this->tableLayoutPanel2->Controls->Add(this->labelSMTP, 1, 5);
			this->tableLayoutPanel2->Location = System::Drawing::Point(12, 79);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 7;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
			this->tableLayoutPanel2->Size = System::Drawing::Size(1015, 235);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// labelPOP3
			// 
			this->labelPOP3->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->labelPOP3->AutoSize = true;
			this->labelPOP3->Location = System::Drawing::Point(26, 109);
			this->labelPOP3->Name = L"labelPOP3";
			this->labelPOP3->Size = System::Drawing::Size(82, 13);
			this->labelPOP3->TabIndex = 12;
			this->labelPOP3->Text = L"Protokó³ POP3:";
			// 
			// labelSMTP
			// 
			this->labelSMTP->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->labelSMTP->AutoSize = true;
			this->labelSMTP->Location = System::Drawing::Point(24, 132);
			this->labelSMTP->Name = L"labelSMTP";
			this->labelSMTP->Size = System::Drawing::Size(84, 13);
			this->labelSMTP->TabIndex = 13;
			this->labelSMTP->Text = L"Protokó³ SMTP:";
			// 
			// copy
			// 
			this->copy->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->copy->AutoSize = true;
			this->copy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->copy->Location = System::Drawing::Point(927, 464);
			this->copy->Margin = System::Windows::Forms::Padding(3, 15, 3, 0);
			this->copy->Name = L"copy";
			this->copy->Size = System::Drawing::Size(107, 13);
			this->copy->TabIndex = 14;
			this->copy->Text = L"Copyright by Arek";
			// 
			// Login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1046, 486);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->copy);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"Login";
			this->Text = L"Login";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		/** Wydarzenie (event) checkBox_POP3() zamienia wlasnosc checkbox na `checked` (Klikniety) */
		private: System::Void checkBox_POP3(System::Object^ sender, System::EventArgs^ e) {
			if (this->Checkbox_POP3->Checked) {
				this->Checkbox_SMTP->Checked = false;
			}
		}

		/** Wydarzenie (event) checkBox_SMTP() zamienia wlasnosc checkbox na `checked` (Klikniety) */
		private: System::Void checkBox_SMTP(System::Object^ sender, System::EventArgs^ e) {
			if (this->Checkbox_SMTP->Checked) {
				this->Checkbox_POP3->Checked = false;
			}
		}

		/** Wydarzenie (event) button1_Click() loguje na wybrany protokol */
		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
			if (this->Input_serveraddress->Text->Length > 0 && this->Input_username->Text->Length > 0 && this->Input_password->Text->Length > 0 && this->Input_port->Text->Length > 0) {
				if (this->Checkbox_POP3->Checked || this->Checkbox_SMTP->Checked) {
					if (this->Checkbox_POP3->Checked) {
						//Logowanie do POP3:
						string serverAddress = msclr::interop::marshal_as<string>(this->Input_serveraddress->Text);
						string userName = msclr::interop::marshal_as<string>(this->Input_username->Text);
						string password = msclr::interop::marshal_as<string>(this->Input_password->Text);
						int port = stoi(msclr::interop::marshal_as<string>(this->Input_port->Text));

						if (port == 110 || port == 995) {
							POP3Login checkLogin(serverAddress, userName, password, port);

							if (checkLogin.loginPOP3() == "ok") {
								MessageBox::Show("Sukcess! Poprawnie po³¹czono z us³ug¹ POP3.", "Success!", MessageBoxButtons::OK, MessageBoxIcon::Information);
								this->Hide();
								POP3 pop3(this->Input_serveraddress, this->Input_username, this->Input_password, port);
								pop3.ShowDialog();
							}
							else {
								String^ getError = gcnew String(checkLogin.loginPOP3().c_str());
								MessageBox::Show("B³¹d! " + getError, "#[000003] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
							}
						}
						else {
							MessageBox::Show("B³¹d! Nieobs³ugiwany port dla us³ugi POP3.", "#[000002] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
					}
					else {
						//Logowanie do SMTP:
						string serverAddress = msclr::interop::marshal_as<string>(this->Input_serveraddress->Text);
						string userName = msclr::interop::marshal_as<string>(this->Input_username->Text);
						string password = msclr::interop::marshal_as<string>(this->Input_password->Text);
						int port = stoi(msclr::interop::marshal_as<string>(this->Input_port->Text));

						if (port == 25 || port == 587 || port == 465) {
							SMTPLogin checkLogin(serverAddress, userName, password, port);
							if (checkLogin.loginSMTP() == "ok") {
								MessageBox::Show("Sukcess! Poprawnie po³¹czono z us³ug¹ SMTP.", "Success!", MessageBoxButtons::OK, MessageBoxIcon::Information);
								this->Hide();
								SMTP smtp(this->Input_serveraddress, this->Input_username, this->Input_password, port);
								smtp.ShowDialog();
							}
							else {
								String^ getError = gcnew String(checkLogin.loginSMTP().c_str());
								MessageBox::Show("B³¹d! " + getError, "#[000003] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
							}
						}
						else {
							MessageBox::Show("B³¹d! Nieobs³ugiwany port dla us³ugi SMTP.", "#[000002] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
						}
					}
				}
				else {
					MessageBox::Show("B³¹d! Wybierz odpowiedni protokó³.", "#[000001] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			else {
				MessageBox::Show("B³¹d! Wype³nij wszystkie pola.", "#[000001] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	};
}
