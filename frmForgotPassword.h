#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SHWT {

    
        public ref class frmForgotPassword : public Form {
        public:
            frmForgotPassword();

        private:
            DatabaseHelper^ dbHelper;

            // Step tracking: 1=enter email, 2=answer question, 3=new password
            int currentStep;

            Panel^ pnlHeader;
            Label^ lblTitle;
            Label^ lblSubtitle;

            // Step 1
            GroupBox^ grpStep1;
            Label^ lblEmailPrompt;
            TextBox^ txtEmail;
            Button^ btnFindAccount;
            Label^ lblStep1Status;

            // Step 2
            GroupBox^ grpStep2;
            Label^ lblQuestionDisplay;
            Label^ lblAnswerPrompt;
            TextBox^ txtAnswer;
            Button^ btnVerifyAnswer;
            Label^ lblStep2Status;

            // Step 3
            GroupBox^ grpStep3;
            Label^ lblNewPassPrompt;
            TextBox^ txtNewPassword;
            Label^ lblConfirmPrompt;
            TextBox^ txtConfirmPassword;
            Button^ btnResetPassword;
            Label^ lblStep3Status;

            // Common
            Button^ btnCancel;

            void InitializeComponent();
            void ShowStep(int step);

            System::Void btnFindAccount_Click(Object^ sender, EventArgs^ e);
            System::Void btnVerifyAnswer_Click(Object^ sender, EventArgs^ e);
            System::Void btnResetPassword_Click(Object^ sender, EventArgs^ e);
            System::Void btnCancel_Click(Object^ sender, EventArgs^ e);
    };
    

}