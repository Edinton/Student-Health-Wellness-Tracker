
#include "frmLogin.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace SHWT;

[STAThread]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew frmLogin());
	return 0;
}