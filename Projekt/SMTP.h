#pragma once
#include "WriteMail.h";
#include "Files.h";

#include <msclr\marshal_cppstd.h>

namespace Projekt {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/** Klasa SMTP odpowiedzialna za wysylanie wiadomosci, dzialajaca za pomoca protokolu `SMTP` */
	public ref class SMTP : public System::Windows::Forms::Form {
	public:
		/// `Textbox` adresu serwera POP3
		TextBox^ serverAddress;
		/// `Textbox` nazwy uzytkownika
		TextBox^ userName;
		/// `Textbox` hasla uzytkownika
		TextBox^ password;
		/// Port serwera POP3
		int port;

		/** Konstruktor dla klasy `SMTP`, ktory inicjuje wszystkie niezbedne komponenty oraz zapisuje niezbedne dane do wysylania wiadomosci, zmienia tytul dla formularza (Zaznacza na jakim emailu jestesmy zalogowani */
		SMTP(TextBox^ serverAddress, TextBox^ userName, TextBox^ password, int port) : serverAddress(serverAddress), userName(userName), password(password), port(port) {
			InitializeComponent();
			this->topicSMTP->Text = L"Wysy³anie wiadomoœci SMTP (Zalogowany jako: " + this->userName->Text + ")";
			this->input_CC->Text = this->userName->Text;
		}

	protected:
		/** Destruktor dla klasy `SMTP`, ktory usuwa wszystkie utworzone wczesniej komponenty */
		~SMTP() {
			if (components) {
				delete components;
			}
		}

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel3;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel4;
	private: System::Windows::Forms::Label^ topicSMTP;
	private: System::Windows::Forms::Label^ label_CC;
	private: System::Windows::Forms::TextBox^ input_CC;
	private: System::Windows::Forms::Label^ label_sendTo;
	private: System::Windows::Forms::TextBox^ input_To;
	private: System::Windows::Forms::Label^ label_topic;
	private: System::Windows::Forms::TextBox^ input_topic;
	private: System::Windows::Forms::RichTextBox^ input_textArea;
	private: System::Windows::Forms::Label^ label_status;
	private: System::Windows::Forms::ProgressBar^ progressBar;
	private: System::Windows::Forms::Button^ button_send;
	private: System::ComponentModel::Container ^components;

		/** Metoda `InitializeComponent()` inicjalizuje niezbedne komponenty */
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SMTP::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->input_topic = (gcnew System::Windows::Forms::TextBox());
			this->label_topic = (gcnew System::Windows::Forms::Label());
			this->label_sendTo = (gcnew System::Windows::Forms::Label());
			this->label_CC = (gcnew System::Windows::Forms::Label());
			this->input_To = (gcnew System::Windows::Forms::TextBox());
			this->input_CC = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->input_textArea = (gcnew System::Windows::Forms::RichTextBox());
			this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->label_status = (gcnew System::Windows::Forms::Label());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->button_send = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->topicSMTP = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tableLayoutPanel3->SuspendLayout();
			this->tableLayoutPanel4->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->AutoSize = true;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				6.98174F)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				93.01826F)));
			this->tableLayoutPanel1->Controls->Add(this->input_topic, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->label_topic, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->label_sendTo, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->label_CC, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->input_To, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->input_CC, 1, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 48);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 3;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 43)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(931, 143);
			this->tableLayoutPanel1->TabIndex = 0;
			// 
			// input_topic
			// 
			this->input_topic->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->input_topic->Location = System::Drawing::Point(67, 111);
			this->input_topic->Name = L"input_topic";
			this->input_topic->Size = System::Drawing::Size(861, 20);
			this->input_topic->TabIndex = 2;
			// 
			// label_topic
			// 
			this->label_topic->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label_topic->AutoSize = true;
			this->label_topic->Location = System::Drawing::Point(21, 115);
			this->label_topic->Name = L"label_topic";
			this->label_topic->Size = System::Drawing::Size(40, 13);
			this->label_topic->TabIndex = 2;
			this->label_topic->Text = L"Temat:";
			// 
			// label_sendTo
			// 
			this->label_sendTo->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label_sendTo->AutoSize = true;
			this->label_sendTo->Location = System::Drawing::Point(9, 68);
			this->label_sendTo->Name = L"label_sendTo";
			this->label_sendTo->Size = System::Drawing::Size(52, 13);
			this->label_sendTo->TabIndex = 1;
			this->label_sendTo->Text = L"Wyœlij do:";
			// 
			// label_CC
			// 
			this->label_CC->Anchor = System::Windows::Forms::AnchorStyles::Right;
			this->label_CC->AutoSize = true;
			this->label_CC->Location = System::Drawing::Point(37, 18);
			this->label_CC->Name = L"label_CC";
			this->label_CC->Size = System::Drawing::Size(24, 13);
			this->label_CC->TabIndex = 0;
			this->label_CC->Text = L"Od:";
			// 
			// input_To
			// 
			this->input_To->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->input_To->Location = System::Drawing::Point(67, 65);
			this->input_To->Name = L"input_To";
			this->input_To->Size = System::Drawing::Size(861, 20);
			this->input_To->TabIndex = 1;
			// 
			// input_CC
			// 
			this->input_CC->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
			this->input_CC->Location = System::Drawing::Point(67, 15);
			this->input_CC->Name = L"input_CC";
			this->input_CC->ReadOnly = true;
			this->input_CC->Size = System::Drawing::Size(861, 20);
			this->input_CC->TabIndex = 3;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel2->AutoSize = true;
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->input_textArea, 0, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(12, 197);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(931, 177);
			this->tableLayoutPanel2->TabIndex = 0;
			// 
			// input_textArea
			// 
			this->input_textArea->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->input_textArea->Location = System::Drawing::Point(3, 3);
			this->input_textArea->Name = L"input_textArea";
			this->input_textArea->Size = System::Drawing::Size(925, 171);
			this->input_textArea->TabIndex = 4;
			this->input_textArea->Text = L"";
			// 
			// tableLayoutPanel3
			// 
			this->tableLayoutPanel3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel3->AutoSize = true;
			this->tableLayoutPanel3->ColumnCount = 1;
			this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel3->Controls->Add(this->label_status, 0, 0);
			this->tableLayoutPanel3->Controls->Add(this->progressBar, 0, 1);
			this->tableLayoutPanel3->Controls->Add(this->button_send, 0, 2);
			this->tableLayoutPanel3->Location = System::Drawing::Point(12, 380);
			this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
			this->tableLayoutPanel3->RowCount = 3;
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.71751F)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 31)));
			this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 31)));
			this->tableLayoutPanel3->Size = System::Drawing::Size(931, 88);
			this->tableLayoutPanel3->TabIndex = 1;
			// 
			// label_status
			// 
			this->label_status->AutoSize = true;
			this->label_status->Location = System::Drawing::Point(3, 10);
			this->label_status->Margin = System::Windows::Forms::Padding(3, 10, 3, 3);
			this->label_status->Name = L"label_status";
			this->label_status->Size = System::Drawing::Size(173, 13);
			this->label_status->TabIndex = 0;
			this->label_status->Text = L"Status: Oczekiwanie na wys³anie...";
			// 
			// progressBar
			// 
			this->progressBar->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->progressBar->Location = System::Drawing::Point(3, 29);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(925, 23);
			this->progressBar->TabIndex = 1;
			// 
			// button_send
			// 
			this->button_send->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->button_send->Location = System::Drawing::Point(710, 60);
			this->button_send->Name = L"button_send";
			this->button_send->Size = System::Drawing::Size(218, 23);
			this->button_send->TabIndex = 2;
			this->button_send->Text = L"Wyœlij wiadomoœæ";
			this->button_send->UseVisualStyleBackColor = true;
			this->button_send->Click += gcnew System::EventHandler(this, &SMTP::button_send_Click);
			// 
			// tableLayoutPanel4
			// 
			this->tableLayoutPanel4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel4->BackColor = System::Drawing::SystemColors::ControlDark;
			this->tableLayoutPanel4->ColumnCount = 1;
			this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel4->Controls->Add(this->topicSMTP, 0, 0);
			this->tableLayoutPanel4->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
			this->tableLayoutPanel4->RowCount = 1;
			this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel4->Size = System::Drawing::Size(931, 30);
			this->tableLayoutPanel4->TabIndex = 2;
			// 
			// topicSMTP
			// 
			this->topicSMTP->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->topicSMTP->AutoSize = true;
			this->topicSMTP->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->topicSMTP->Location = System::Drawing::Point(3, 3);
			this->topicSMTP->Name = L"topicSMTP";
			this->topicSMTP->Size = System::Drawing::Size(449, 23);
			this->topicSMTP->TabIndex = 0;
			this->topicSMTP->Text = L"Wysy³anie wiadomoœci SMTP (Zalogowany jako: ***@***.**)";
			// 
			// SMTP
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(955, 480);
			this->Controls->Add(this->tableLayoutPanel4);
			this->Controls->Add(this->tableLayoutPanel3);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"SMTP";
			this->Text = L"SMTP";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &SMTP::SMTP_FormClosed);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel3->ResumeLayout(false);
			this->tableLayoutPanel3->PerformLayout();
			this->tableLayoutPanel4->ResumeLayout(false);
			this->tableLayoutPanel4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		/** Wydarzenie (event) button_send_Click() wysyla wiadomosc email do danego uzytkownika za pomoca protokolu `SMTP` */
		private: System::Void button_send_Click(System::Object^ sender, System::EventArgs^ e) {
			string serverAddress = msclr::interop::marshal_as<string>(this->serverAddress->Text);
			string userName = msclr::interop::marshal_as<string>(this->userName->Text);
			string password = msclr::interop::marshal_as<string>(this->password->Text);
			string To = msclr::interop::marshal_as<string>(this->input_To->Text);
			string CC = msclr::interop::marshal_as<string>(this->input_CC->Text);
			string topic = msclr::interop::marshal_as<string>(this->input_topic->Text);
			string message = msclr::interop::marshal_as<string>(this->input_textArea->Text);

			if (!empty(To) && !empty(CC) && !empty(topic) && !empty(message)) {
				WriteMail wm(serverAddress, userName, password, this->port);
				if (wm.writeMail(To, topic, message) == "ok") {
					this->label_status->Text = L"Status: wys³ano poprawnie wiadomoœæ...";
					this->progressBar->Increment(100);
					MessageBox::Show("Sukcess! Poprawnie wys³ano email.", "Success!", MessageBoxButtons::OK, MessageBoxIcon::Information);

					auto confirmFile = MessageBox::Show("Czy potrzebujesz wyeksporowaæ treœæ maila?", "Eksport maila do pliku tekstowego", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
					if (confirmFile == System::Windows::Forms::DialogResult::Yes) {
						Files file("Kopia " + To + ".txt");

						if (file.ifFileExists()) {
							auto confirmExistFile = MessageBox::Show("Taki plik ju¿ istnieje. Czy chcesz go nadpisaæ?", "Eksport maila do pliku tekstowego", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
							if (confirmExistFile == System::Windows::Forms::DialogResult::Yes) {
								file.reWriteContentFile(message);
								MessageBox::Show("Poprawnie zapisano kopiê do pliku: \"Kopia " + this->input_To->Text + ".txt\"", "Success!", MessageBoxButtons::OK, MessageBoxIcon::Information);
							}
						} else {
							file.reWriteContentFile(message);
							MessageBox::Show("Poprawnie zapisano kopiê do pliku: \"Kopia " + this->input_To->Text + ".txt\"", "Success!", MessageBoxButtons::OK, MessageBoxIcon::Information);
						}

					}					

				} else {
					this->label_status->Text = L"Status: b³¹d podczas wysy³ania...";
					String^ getError = gcnew String(wm.writeMail(To, topic, message).c_str());
					MessageBox::Show("B³¹d! " + getError, "#[000003] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			} else {
				MessageBox::Show("B³¹d! Wype³nij wszystkie pola.", "#[000001] - Error!", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		
		/** Wydarzenie (event) SMTP_FormClosed() zamyka plik / program po pliknieciu w `X` */
		private: System::Void SMTP_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
			System::Windows::Forms::Application::Exit();
		}
	};
}
