#include "Login.h"

using namespace System;
using namespace System::Windows::Forms;

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Projekt::Login formLogin;
	Application::Run(% formLogin);
}