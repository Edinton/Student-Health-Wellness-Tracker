#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SHWT {

    
        public ref class frmRegister : public Form {
        public:
            frmRegister();

        private:
            DatabaseHelper^ dbHelper;

            Panel^ pnlHeader;
            Label^ lblTitle;
            Label^ lblSubtitle;

            GroupBox^ grpPersonal;
            Label^ lblFirstName;
            TextBox^ txtFirstName;
            Label^ lblLastName;
            TextBox^ txtLastName;
            Label^ lblEmail;
            TextBox^ txtEmail;

            GroupBox^ grpSecurity;
            Label^ lblPassword;
            TextBox^ txtPassword;
            Label^ lblConfirm;
            TextBox^ txtConfirm;
            Label^ lblSecQuestion;
            ComboBox^ cmbSecQuestion;
            Label^ lblSecAnswer;
            TextBox^ txtSecAnswer;

            Button^ btnRegister;
            Button^ btnBack;
            Label^ lblStatus;

            void InitializeComponent();
            bool ValidateInput();

            System::Void btnRegister_Click(Object^ sender, EventArgs^ e);
            System::Void btnBack_Click(Object^ sender, EventArgs^ e);
    };
    

}