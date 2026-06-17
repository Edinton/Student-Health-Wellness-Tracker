#include "frmForgotPassword.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace SHWT;

frmForgotPassword::frmForgotPassword()
{
    dbHelper = gcnew DatabaseHelper();
    currentStep = 1;
    InitializeComponent();
    ShowStep(1);
}

void frmForgotPassword::InitializeComponent()
{
    Color clrFormBg = Color::FromArgb(30, 30, 30);
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrHeader = Color::FromArgb(28, 28, 28);
    Color clrInputBg = Color::FromArgb(55, 55, 55);
    Color clrBorder = Color::FromArgb(75, 75, 75);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrDanger = Color::FromArgb(210, 80, 80);
    Color clrSuccess = Color::FromArgb(80, 190, 120);

    
    Drawing::Font^ fTitle = gcnew Drawing::Font("Segoe UI", 13.0f, FontStyle::Bold);
    Drawing::Font^ fSub = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);
    Drawing::Font^ fGroup = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Bold);
    Drawing::Font^ fLabel = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBase = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);
    Drawing::Font^ fQuestion = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Italic);

    pnlHeader = gcnew Panel();
    lblTitle = gcnew Label();
    lblSubtitle = gcnew Label();

    grpStep1 = gcnew GroupBox();
    lblEmailPrompt = gcnew Label();
    txtEmail = gcnew TextBox();
    btnFindAccount = gcnew Button();
    lblStep1Status = gcnew Label();

    grpStep2 = gcnew GroupBox();
    lblQuestionDisplay = gcnew Label();
    lblAnswerPrompt = gcnew Label();
    txtAnswer = gcnew TextBox();
    btnVerifyAnswer = gcnew Button();
    lblStep2Status = gcnew Label();

    grpStep3 = gcnew GroupBox();
    lblNewPassPrompt = gcnew Label();
    txtNewPassword = gcnew TextBox();
    lblConfirmPrompt = gcnew Label();
    txtConfirmPassword = gcnew TextBox();
    btnResetPassword = gcnew Button();
    lblStep3Status = gcnew Label();

    btnCancel = gcnew Button();

    this->SuspendLayout();
    pnlHeader->SuspendLayout();

    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(480, 72);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblSubtitle);

    lblTitle->AutoSize = true;
    lblTitle->Location = Point(20, 12);
    lblTitle->Text = L"Reset Your Password";
    lblTitle->Font = fTitle;
    lblTitle->ForeColor = clrAccent;
    lblTitle->BackColor = Color::Transparent;

    lblSubtitle->AutoSize = true;
    lblSubtitle->Location = Point(22, 44);
    lblSubtitle->Text = L"Follow the steps below to recover your account.";
    lblSubtitle->Font = fSub;
    lblSubtitle->ForeColor = clrTextSecond;
    lblSubtitle->BackColor = Color::Transparent;

    const int gX = 20;
    const int gW = 438;
    const int iX = 16;
    const int iW = 402;

    grpStep1->Location = Point(gX, 86);
    grpStep1->Size = Drawing::Size(gW, 150);
    grpStep1->Text = L"Step 1 of 3  —  Enter Your Registered Email";
    grpStep1->Font = fGroup;
    grpStep1->ForeColor = clrAccent;
    grpStep1->BackColor = clrSurface;

    lblEmailPrompt->AutoSize = true;
    lblEmailPrompt->Location = Point(iX, 30);
    lblEmailPrompt->Text = L"Email Address";
    lblEmailPrompt->Font = fLabel;
    lblEmailPrompt->ForeColor = clrTextSecond;
    lblEmailPrompt->BackColor = Color::Transparent;

    txtEmail->Location = Point(iX, 50);
    txtEmail->Size = Drawing::Size(iW, 26);
    txtEmail->Font = fBase;
    txtEmail->BackColor = clrInputBg;
    txtEmail->ForeColor = clrTextPrimary;
    txtEmail->BorderStyle = BorderStyle::FixedSingle;

    btnFindAccount->Location = Point(iX, 92);
    btnFindAccount->Size = Drawing::Size(iW, 34);
    btnFindAccount->Text = L"Find My Account";
    btnFindAccount->Font = fBtn;
    btnFindAccount->BackColor = clrAccent;
    btnFindAccount->ForeColor = Color::White;
    btnFindAccount->FlatStyle = FlatStyle::Flat;
    btnFindAccount->FlatAppearance->BorderSize = 0;
    btnFindAccount->Cursor = Cursors::Hand;
    btnFindAccount->Click += gcnew EventHandler(
        this, &frmForgotPassword::btnFindAccount_Click);

    lblStep1Status->AutoSize = false;
    lblStep1Status->Size = Drawing::Size(iW, 20);
    lblStep1Status->Location = Point(iX, 132);
    lblStep1Status->Text = L"";
    lblStep1Status->Font = fLabel;
    lblStep1Status->ForeColor = clrDanger;
    lblStep1Status->BackColor = Color::Transparent;

    grpStep1->Controls->Add(lblEmailPrompt);
    grpStep1->Controls->Add(txtEmail);
    grpStep1->Controls->Add(btnFindAccount);
    grpStep1->Controls->Add(lblStep1Status);

    grpStep2->Location = Point(gX, 86);
    grpStep2->Size = Drawing::Size(gW, 190);
    grpStep2->Text = L"Step 2 of 3  —  Answer Your Security Question";
    grpStep2->Font = fGroup;
    grpStep2->ForeColor = clrAccent;
    grpStep2->BackColor = clrSurface;

    lblQuestionDisplay->AutoSize = false;
    lblQuestionDisplay->Size = Drawing::Size(iW, 44);
    lblQuestionDisplay->Location = Point(iX, 28);
    lblQuestionDisplay->Text = L"";
    lblQuestionDisplay->Font = fQuestion;
    lblQuestionDisplay->ForeColor = clrTextPrimary;
    lblQuestionDisplay->BackColor = Color::FromArgb(38, 38, 48);
    lblQuestionDisplay->TextAlign = ContentAlignment::MiddleLeft;
    lblQuestionDisplay->Padding = System::Windows::Forms::Padding(8, 0, 0, 0);

    lblAnswerPrompt->AutoSize = true;
    lblAnswerPrompt->Location = Point(iX, 84);
    lblAnswerPrompt->Text = L"Your Answer";
    lblAnswerPrompt->Font = fLabel;
    lblAnswerPrompt->ForeColor = clrTextSecond;
    lblAnswerPrompt->BackColor = Color::Transparent;

    txtAnswer->Location = Point(iX, 104);
    txtAnswer->Size = Drawing::Size(iW, 26);
    txtAnswer->Font = fBase;
    txtAnswer->BackColor = clrInputBg;
    txtAnswer->ForeColor = clrTextPrimary;
    txtAnswer->BorderStyle = BorderStyle::FixedSingle;

    btnVerifyAnswer->Location = Point(iX, 144);
    btnVerifyAnswer->Size = Drawing::Size(iW, 34);
    btnVerifyAnswer->Text = L"Verify Answer";
    btnVerifyAnswer->Font = fBtn;
    btnVerifyAnswer->BackColor = clrAccent;
    btnVerifyAnswer->ForeColor = Color::White;
    btnVerifyAnswer->FlatStyle = FlatStyle::Flat;
    btnVerifyAnswer->FlatAppearance->BorderSize = 0;
    btnVerifyAnswer->Cursor = Cursors::Hand;
    btnVerifyAnswer->Click += gcnew EventHandler(
        this, &frmForgotPassword::btnVerifyAnswer_Click);

    lblStep2Status->AutoSize = false;
    lblStep2Status->Size = Drawing::Size(iW, 20);
    lblStep2Status->Location = Point(iX, 168);
    lblStep2Status->Text = L"";
    lblStep2Status->Font = fLabel;
    lblStep2Status->ForeColor = clrDanger;
    lblStep2Status->BackColor = Color::Transparent;

    grpStep2->Controls->Add(lblQuestionDisplay);
    grpStep2->Controls->Add(lblAnswerPrompt);
    grpStep2->Controls->Add(txtAnswer);
    grpStep2->Controls->Add(btnVerifyAnswer);
    grpStep2->Controls->Add(lblStep2Status);

    grpStep3->Location = Point(gX, 86);
    grpStep3->Size = Drawing::Size(gW, 210);
    grpStep3->Text = L"Step 3 of 3  —  Set a New Password";
    grpStep3->Font = fGroup;
    grpStep3->ForeColor = clrAccent;
    grpStep3->BackColor = clrSurface;

    lblNewPassPrompt->AutoSize = true;
    lblNewPassPrompt->Location = Point(iX, 30);
    lblNewPassPrompt->Text = L"New Password  (min. 6 characters)";
    lblNewPassPrompt->Font = fLabel;
    lblNewPassPrompt->ForeColor = clrTextSecond;
    lblNewPassPrompt->BackColor = Color::Transparent;

    txtNewPassword->Location = Point(iX, 50);
    txtNewPassword->Size = Drawing::Size(iW, 26);
    txtNewPassword->Font = fBase;
    txtNewPassword->BackColor = clrInputBg;
    txtNewPassword->ForeColor = clrTextPrimary;
    txtNewPassword->BorderStyle = BorderStyle::FixedSingle;
    txtNewPassword->PasswordChar = '*';

    lblConfirmPrompt->AutoSize = true;
    lblConfirmPrompt->Location = Point(iX, 92);
    lblConfirmPrompt->Text = L"Confirm New Password";
    lblConfirmPrompt->Font = fLabel;
    lblConfirmPrompt->ForeColor = clrTextSecond;
    lblConfirmPrompt->BackColor = Color::Transparent;

    txtConfirmPassword->Location = Point(iX, 112);
    txtConfirmPassword->Size = Drawing::Size(iW, 26);
    txtConfirmPassword->Font = fBase;
    txtConfirmPassword->BackColor = clrInputBg;
    txtConfirmPassword->ForeColor = clrTextPrimary;
    txtConfirmPassword->BorderStyle = BorderStyle::FixedSingle;
    txtConfirmPassword->PasswordChar = '*';

    btnResetPassword->Location = Point(iX, 154);
    btnResetPassword->Size = Drawing::Size(iW, 34);
    btnResetPassword->Text = L"Reset Password";
    btnResetPassword->Font = fBtn;
    btnResetPassword->BackColor = Color::FromArgb(70, 140, 90);
    btnResetPassword->ForeColor = Color::White;
    btnResetPassword->FlatStyle = FlatStyle::Flat;
    btnResetPassword->FlatAppearance->BorderSize = 0;
    btnResetPassword->Cursor = Cursors::Hand;
    btnResetPassword->Click += gcnew EventHandler(
        this, &frmForgotPassword::btnResetPassword_Click);

    lblStep3Status->AutoSize = false;
    lblStep3Status->Size = Drawing::Size(iW, 20);
    lblStep3Status->Location = Point(iX, 185);
    lblStep3Status->Text = L"";
    lblStep3Status->Font = fLabel;
    lblStep3Status->ForeColor = clrDanger;
    lblStep3Status->BackColor = Color::Transparent;

    grpStep3->Controls->Add(lblNewPassPrompt);
    grpStep3->Controls->Add(txtNewPassword);
    grpStep3->Controls->Add(lblConfirmPrompt);
    grpStep3->Controls->Add(txtConfirmPassword);
    grpStep3->Controls->Add(btnResetPassword);
    grpStep3->Controls->Add(lblStep3Status);

    btnCancel->Location = Point(gX, 316);
    btnCancel->Size = Drawing::Size(gW, 32);
    btnCancel->Text = L"Cancel — Return to Login";
    btnCancel->Font = fBtn;
    btnCancel->BackColor = Color::FromArgb(55, 55, 55);
    btnCancel->ForeColor = clrTextSecond;
    btnCancel->FlatStyle = FlatStyle::Flat;
    btnCancel->FlatAppearance->BorderSize = 1;
    btnCancel->FlatAppearance->BorderColor = clrBorder;
    btnCancel->Cursor = Cursors::Hand;
    btnCancel->Click += gcnew EventHandler(
        this, &frmForgotPassword::btnCancel_Click);

    this->AutoScaleDimensions = Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(480, 362);
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->StartPosition = FormStartPosition::CenterParent;
    this->Text = L"SHWT – Forgot Password";
    this->Controls->Add(pnlHeader);
    this->Controls->Add(grpStep1);
    this->Controls->Add(grpStep2);
    this->Controls->Add(grpStep3);
    this->Controls->Add(btnCancel);

    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    this->ResumeLayout(false);
    

}

void frmForgotPassword::ShowStep(int step)
{
    grpStep1->Visible = (step == 1);
    grpStep2->Visible = (step == 2);
    grpStep3->Visible = (step == 3);
    currentStep = step;

    
    int groupBottom = 86;
    if (step == 1) groupBottom += grpStep1->Height;
    if (step == 2) groupBottom += grpStep2->Height;
    if (step == 3) groupBottom += grpStep3->Height;

    btnCancel->Location = Point(btnCancel->Location.X, groupBottom + 12);
    this->ClientSize = Drawing::Size(
        this->ClientSize.Width,
        btnCancel->Bottom + 16);
    

}

System::Void frmForgotPassword::btnFindAccount_Click(Object^ sender, EventArgs^ e)
{
    lblStep1Status->Text = L"";
    String^ email = txtEmail->Text->Trim();

    
        if (String::IsNullOrWhiteSpace(email) || !email->Contains("@"))
        {
            lblStep1Status->Text = L"Please enter a valid email address.";
            return;
        }

    String^ question = dbHelper->GetSecurityQuestion(email);
    if (question == nullptr || String::IsNullOrWhiteSpace(question))
    {
        lblStep1Status->Text = L"No account found with that email address.";
        return;
    }

    lblQuestionDisplay->Text = question;
    txtAnswer->Clear();
    lblStep2Status->Text = L"";
    ShowStep(2);
    txtAnswer->Focus();
    

}

System::Void frmForgotPassword::btnVerifyAnswer_Click(Object^ sender, EventArgs^ e)
{
    lblStep2Status->Text = L"";

    
        if (String::IsNullOrWhiteSpace(txtAnswer->Text))
        {
            lblStep2Status->Text = L"Please enter your answer.";
            return;
        }

    bool ok = dbHelper->VerifySecurityAnswer(
        txtEmail->Text->Trim(), txtAnswer->Text);

    if (!ok)
    {
        lblStep2Status->Text = L"Incorrect answer. Please try again.";
        txtAnswer->Clear();
        txtAnswer->Focus();
        return;
    }

    txtNewPassword->Clear();
    txtConfirmPassword->Clear();
    lblStep3Status->Text = L"";
    ShowStep(3);
    txtNewPassword->Focus();
    

}

System::Void frmForgotPassword::btnResetPassword_Click(Object^ sender, EventArgs^ e)
{
    lblStep3Status->Text = L"";

    
        if (txtNewPassword->Text->Length < 6)
        {
            lblStep3Status->Text = L"Password must be at least 6 characters.";
            return;
        }

    if (txtNewPassword->Text != txtConfirmPassword->Text)
    {
        lblStep3Status->Text = L"Passwords do not match.";
        txtConfirmPassword->Clear();
        txtConfirmPassword->Focus();
        return;
    }

    if (dbHelper->UpdatePassword(txtEmail->Text->Trim(), txtNewPassword->Text))
    {
        MessageBox::Show(
            "Your password has been reset successfully.\n"
            "You may now sign in with your new password.",
            "Password Reset Successful",
            MessageBoxButtons::OK,
            MessageBoxIcon::Information);
        this->Close();
    }
    else
    {
        lblStep3Status->Text = L"An error occurred. Please try again.";
    }
    

}

System::Void frmForgotPassword::btnCancel_Click(Object^ sender, EventArgs^ e)
{
    this->Close();
}