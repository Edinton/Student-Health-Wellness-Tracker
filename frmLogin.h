#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SHWT {

    
        ref class frmDashboard;      // forward declaration

    public ref class frmLogin : public Form {
    public:
        frmLogin();
        property Student^ LoggedInStudent;

    private:
        DatabaseHelper^ dbHelper;

        Panel^ pnlHeader;
        Label^ lblAppName;
        Label^ lblAppTagline;

        GroupBox^ grpLogin;
        Label^ lblEmail;
        TextBox^ txtEmail;
        Label^ lblPassword;
        TextBox^ txtPassword;
        Button^ btnLogin;
        LinkLabel^ lnkForgotPassword;
        Label^ lblStatus;

        Panel^ pnlFooter;
        Label^ lblNoAccount;
        Button^ btnGoRegister;

        void InitializeComponent();

        System::Void btnLogin_Click(Object^ sender, EventArgs^ e);
        System::Void btnGoRegister_Click(Object^ sender, EventArgs^ e);
        System::Void lnkForgotPassword_Click(Object^ sender, LinkLabelLinkClickedEventArgs^ e);
        System::Void txtPassword_KeyPress(Object^ sender, KeyPressEventArgs^ e);
    };
    

}