#pragma once
#include "ReadMails.h";
#include "Files.h";

#include <msclr\marshal_cppstd.h>

namespace Projekt {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/** Klasa POP3 odpowiedzialna za wyswietlanie wiadomosci, dzialajaca za pomoca protokolu `POP3` */
	public ref class POP3 : public System::Windows::Forms::Form {

	public:
		/** Funckja `Replace_All` zamienia dana litere na inna 
		* @param s - Cale slowo
		* @param search - Szukana litera
		* @param replace - Litera na ktora ma zostac zmieniona powyzsza litera `serach`
		* @result - Funkcja zwraca zamienione slowo, uwzgledniajac powyzsze warunki poszczegolnych liter.
		*/
		void ReplaceAll(string& s, const string& search, const string& replace) {
			for (size_t pos = 0; ; pos += replace.length()) {
				pos = s.find(search, pos);
				if (pos == string::npos) {
					break;
				}
				s.erase(pos, search.length());
				s.insert(pos, replace);
			}
		}

		/** Funckja `toPolishWords` zamienia wartosci ktore sa nie czytelne do programu na polskie znaki
		* @param myWord - Slowo ktore bedzie zmieniane
		* @result - Funkcja zwraca zamienione slowo
		*/
		string toPolishWords(string myWord) {
			ReplaceAll(myWord, "Ä…", "¹");
			ReplaceAll(myWord, "Ä‡", "æ");
			ReplaceAll(myWord, "Ä™", "ê");
			ReplaceAll(myWord, "Å‚", "³");
			ReplaceAll(myWord, "Å„", "ñ");
			ReplaceAll(myWord, "Ã³", "ó");
			ReplaceAll(myWord, "Å›", "œ");
			ReplaceAll(myWord, "Åº", "Ÿ");
			ReplaceAll(myWord, "Å¼", "¿");
			ReplaceAll(myWord, "Ä„", "¥");
			ReplaceAll(myWord, "Ä†", "Æ");
			ReplaceAll(myWord, "Ä", "Ê");
			ReplaceAll(myWord, "Åƒ", "Ñ");
			ReplaceAll(myWord, "Ã“", "Ó");
			ReplaceAll(myWord, "Åš", "Œ");
			ReplaceAll(myWord, "Å¹", "");
			ReplaceAll(myWord, "Å»", "¯");
			ReplaceAll(myWord, "â€ž", "„");
			ReplaceAll(myWord, "â€", "”");
			ReplaceAll(myWord, "â€˜", "‘");
			ReplaceAll(myWord, "â€™", "’");
			ReplaceAll(myWord, "â€“", "-");
			return myWord;
		}

		/** Funckja `convertBtokB` zamienia wartosci podane w bajtach [B] na kilobajty [kB]
		* @param value - Wartosc podana w bajtach [B]
		* @result - Funkcja zwraca wartosc przekonwertowana na kilobajty [kB]
		*/
		int convertBtokB(const int &value) {
			return round(value / 1024);
		}

	public:
		/// `Textbox` adresu serwera POP3
		TextBox^ serverAddress;
		/// `Textbox` nazwy uzytkownika
		TextBox^ userName;
		/// `Textbox` hasla uzytkownika
		TextBox^ password;
		/// Port serwera POP3
		int port;

	private: System::Windows::Forms::ListBox^ listEmailsHidden;
	private: System::Windows::Forms::Button^ buttonExport;
	private: System::Windows::Forms::ListBox^ listEmails;

	public:
		/** Konstruktor dla klasy `POP3`, ktory inicjuje wszystkie niezbedne komponenty oraz zapisuje odczytanie wiadomosci do listy */
		POP3(TextBox^ serverAddress, TextBox^ userName, TextBox^ password, int port) : serverAddress(serverAddress), userName(userName), password(password), port(port) {
			InitializeComponent();
			this->topicPOP3->Text = L"Odbieranie wiadomoœci POP3 (Zalogowany jako: " + this->userName->Text + ")";
			this->listEmails->Items->Add("ID / Tytu³ / Od / Rozmiar [kB]");
			this->listEmails->Items->Add("");
			this->listEmailsHidden->Items->Add("");
			this->listEmailsHidden->Items->Add("");

			//Logowanie do POP3:
			string addressPOP3 = msclr::interop::marshal_as<string>(this->serverAddress->Text);
			string userNamePOP3 = msclr::interop::marshal_as<string>(this->userName->Text);
			string passwordPOP3 = msclr::interop::marshal_as<string>(this->password->Text);
			ReadMails rm(addressPOP3, userNamePOP3, passwordPOP3, this->port);
			const vector <ReadMails::Mail>& mails = rm.downloadLastMails(100);

			string getContentFromMail;
			int counter = 1;
			for (const auto& m : mails) {
				if (m.getContentType.find("text") != string::npos) {
					getContentFromMail = toPolishWords(m.content);
				}
				else {
					getContentFromMail = "<Nie uda³o siê odczytaæ przed program>";
				}

				string time = ctime(&m.receivedTime);
				string dataEmail = to_string(counter) + " | \"" + toPolishWords(m.subject) + "\" (" + m.sender + ") [" + to_string(convertBtokB(m.sizeInBytes)) + " kB]";
				string fullContent = "Od:" + m.sender + "\n" + "Do: " + userNamePOP3 + "\n" + "Data: " + time + "\n" + getContentFromMail;

				String^ getData = gcnew String(dataEmail.c_str());
				String^ getContent = gcnew String(fullContent.c_str());

				this->listEmails->Items->Add(getData);
				this->listEmailsHidden->Items->Add(getContent);
				counter++;
			}
			this->listEmails->SelectedIndexChanged += gcnew System::EventHandler(this, &POP3::listEmails_SelectedIndexChanged);
		}

	protected:
		/** Destruktor dla klasy `POP3`, ktory usuwa wszystkie utworzone wczesniej komponenty */
		~POP3() {
			if (components) {
				delete components;
			}
		}

	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel2;
	private: System::Windows::Forms::Label^ topicPOP3;
	private: System::Windows::Forms::TableLayoutPanel^ tablelistEmails;
	private: System::Windows::Forms::RichTextBox^ Textemail;
	private: System::ComponentModel::Container ^components;

		/** Metoda `InitializeComponent()` inicjalizuje niezbedne komponenty */
		void InitializeComponent(void) {
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(POP3::typeid));
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->topicPOP3 = (gcnew System::Windows::Forms::Label());
			this->tablelistEmails = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->listEmails = (gcnew System::Windows::Forms::ListBox());
			this->Textemail = (gcnew System::Windows::Forms::RichTextBox());
			this->listEmailsHidden = (gcnew System::Windows::Forms::ListBox());
			this->buttonExport = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1->SuspendLayout();
			this->tableLayoutPanel2->SuspendLayout();
			this->tablelistEmails->SuspendLayout();
			this->SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel1->ColumnCount = 1;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(12, 12);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 1;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 36)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(902, 36);
			this->tableLayoutPanel1->TabIndex = 4;
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tableLayoutPanel2->BackColor = System::Drawing::SystemColors::ControlDark;
			this->tableLayoutPanel2->ColumnCount = 1;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->Controls->Add(this->topicPOP3, 0, 0);
			this->tableLayoutPanel2->Location = System::Drawing::Point(3, 3);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 1;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(896, 30);
			this->tableLayoutPanel2->TabIndex = 4;
			// 
			// topicPOP3
			// 
			this->topicPOP3->Anchor = System::Windows::Forms::AnchorStyles::Left;
			this->topicPOP3->AutoSize = true;
			this->topicPOP3->Font = (gcnew System::Drawing::Font(L"Arial Narrow", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(238)));
			this->topicPOP3->Location = System::Drawing::Point(3, 3);
			this->topicPOP3->Name = L"topicPOP3";
			this->topicPOP3->Size = System::Drawing::Size(452, 23);
			this->topicPOP3->TabIndex = 0;
			this->topicPOP3->Text = L"Odbieranie wiadomoœci POP3 (Zalogowany jako: ***@***.**)";
			// 
			// tablelistEmails
			// 
			this->tablelistEmails->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->tablelistEmails->ColumnCount = 1;
			this->tablelistEmails->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tablelistEmails->Controls->Add(this->listEmails, 0, 0);
			this->tablelistEmails->Location = System::Drawing::Point(12, 54);
			this->tablelistEmails->Name = L"tablelistEmails";
			this->tablelistEmails->RowCount = 1;
			this->tablelistEmails->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tablelistEmails->Size = System::Drawing::Size(902, 301);
			this->tablelistEmails->TabIndex = 5;
			// 
			// listEmails
			// 
			this->listEmails->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listEmails->FormattingEnabled = true;
			this->listEmails->Location = System::Drawing::Point(3, 3);
			this->listEmails->Name = L"listEmails";
			this->listEmails->Size = System::Drawing::Size(896, 290);
			this->listEmails->TabIndex = 0;
			// 
			// Textemail
			// 
			this->Textemail->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->Textemail->Location = System::Drawing::Point(12, 361);
			this->Textemail->Name = L"Textemail";
			this->Textemail->Size = System::Drawing::Size(903, 213);
			this->Textemail->TabIndex = 0;
			this->Textemail->Text = L"";
			// 
			// listEmailsHidden
			// 
			this->listEmailsHidden->FormattingEnabled = true;
			this->listEmailsHidden->Location = System::Drawing::Point(0, 0);
			this->listEmailsHidden->Name = L"listEmailsHidden";
			this->listEmailsHidden->Size = System::Drawing::Size(86, 17);
			this->listEmailsHidden->TabIndex = 6;
			this->listEmailsHidden->Visible = false;
			// 
			// buttonExport
			// 
			this->buttonExport->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->buttonExport->Enabled = false;
			this->buttonExport->Location = System::Drawing::Point(12, 580);
			this->buttonExport->Name = L"buttonExport";
			this->buttonExport->Size = System::Drawing::Size(903, 23);
			this->buttonExport->TabIndex = 7;
			this->buttonExport->Text = L"Export do pliku";
			this->buttonExport->UseVisualStyleBackColor = true;
			this->buttonExport->Click += gcnew System::EventHandler(this, &POP3::buttonExportEvent);
			// 
			// POP3
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(927, 615);
			this->Controls->Add(this->buttonExport);
			this->Controls->Add(this->listEmailsHidden);
			this->Controls->Add(this->Textemail);
			this->Controls->Add(this->tablelistEmails);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"POP3";
			this->Text = L"POP3";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &POP3::POP3_FormClosed);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel2->ResumeLayout(false);
			this->tableLayoutPanel2->PerformLayout();
			this->tablelistEmails->ResumeLayout(false);
			this->ResumeLayout(false);

		}

		/** Wydarzenie (event) listEmails_SelectedIndexChanged() zamienia glowna liste z listy ukrytej odpowiednim kontentem */
		private: System::Void listEmails_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
			int id = this->listEmails->SelectedIndex;
			this->Textemail->Text = this->listEmailsHidden->Items[id]->ToString();
			this->buttonExport->Enabled = true;
		}

		/** Wydarzenie (event) buttonExportEvent() proba zapisu do pliku tekstowego odpowiedniego kontentu */
		private: System::Void buttonExportEvent(System::Object^ sender, System::EventArgs^ e) {
			auto confirmFile = MessageBox::Show("Czy potrzebujesz wyeksporowaæ treœæ maila?", "Eksport maila do pliku tekstowego", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
			if (confirmFile == System::Windows::Forms::DialogResult::Yes) {
				Files file("Kopia POP3.txt");

				int id = this->listEmails->SelectedIndex;
				string content = msclr::interop::marshal_as<string>(this->listEmailsHidden->Items[id]->ToString());

				if (file.ifFileExists()) {
					auto confirmExistFile = MessageBox::Show("Taki plik ju¿ istnieje. Czy chcesz go nadpisaæ?", "Eksport maila do pliku tekstowego", MessageBoxButtons::YesNo, MessageBoxIcon::Question);
					if (confirmExistFile == System::Windows::Forms::DialogResult::Yes) {
						file.reWriteContentFile(content);
						MessageBox::Show("Poprawnie zapisano kopiê do pliku: \"Kopia POP3.txt\"", "Success!", MessageBoxButtons::OK, MessageBoxIcon::Information);
					}
				}
				else {
					file.reWriteContentFile(content);
					MessageBox::Show("Poprawnie zapisano kopiê do pliku: \"Kopia POP3.txt\"", "Success!", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}

			}
		}

		/** Wydarzenie (event) POP3_FormClosed() zamyka plik / program po pliknieciu w `X` */
		private: System::Void POP3_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
			System::Windows::Forms::Application::Exit();
		}

	};
}
