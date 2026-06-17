#include "frmRegister.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace SHWT;

frmRegister::frmRegister()
{
    dbHelper = gcnew DatabaseHelper();
    InitializeComponent();
}

void frmRegister::InitializeComponent()
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

    
    Drawing::Font^ fTitle = gcnew Drawing::Font("Segoe UI", 13.0f, FontStyle::Bold);
    Drawing::Font^ fSub = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);
    Drawing::Font^ fGroup = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Bold);
    Drawing::Font^ fLabel = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBase = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);

    pnlHeader = gcnew Panel();
    lblTitle = gcnew Label();
    lblSubtitle = gcnew Label();

    grpPersonal = gcnew GroupBox();
    lblFirstName = gcnew Label();
    txtFirstName = gcnew TextBox();
    lblLastName = gcnew Label();
    txtLastName = gcnew TextBox();
    lblEmail = gcnew Label();
    txtEmail = gcnew TextBox();

    grpSecurity = gcnew GroupBox();
    lblPassword = gcnew Label();
    txtPassword = gcnew TextBox();
    lblConfirm = gcnew Label();
    txtConfirm = gcnew TextBox();
    lblSecQuestion = gcnew Label();
    cmbSecQuestion = gcnew ComboBox();
    lblSecAnswer = gcnew Label();
    txtSecAnswer = gcnew TextBox();

    btnRegister = gcnew Button();
    btnBack = gcnew Button();
    lblStatus = gcnew Label();

    this->SuspendLayout();
    pnlHeader->SuspendLayout();
    grpPersonal->SuspendLayout();
    grpSecurity->SuspendLayout();

    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(500, 72);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblSubtitle);

    lblTitle->AutoSize = true;
    lblTitle->Location = Point(20, 12);
    lblTitle->Text = L"Create Your Account";
    lblTitle->Font = fTitle;
    lblTitle->ForeColor = clrAccent;
    lblTitle->BackColor = Color::Transparent;

    lblSubtitle->AutoSize = true;
    lblSubtitle->Location = Point(22, 44);
    lblSubtitle->Text = L"All fields are required. Your security question helps you recover access.";
    lblSubtitle->Font = fSub;
    lblSubtitle->ForeColor = clrTextSecond;
    lblSubtitle->BackColor = Color::Transparent;

    const int gX = 20;
    const int gW = 458;
    const int iX = 16;
    const int iW = 422;

    //Personal Details group 
    grpPersonal->Location = Point(gX, 86);
    grpPersonal->Size = Drawing::Size(gW, 176);
    grpPersonal->Text = L"Personal Details";
    grpPersonal->Font = fGroup;
    grpPersonal->ForeColor = clrAccent;
    grpPersonal->BackColor = clrSurface;

    // First Name + Last Name 
    int halfW = (iW - 12) / 2;

    lblFirstName->AutoSize = true;
    lblFirstName->Location = Point(iX, 28);
    lblFirstName->Text = L"First Name";
    lblFirstName->Font = fLabel;
    lblFirstName->ForeColor = clrTextSecond;
    lblFirstName->BackColor = Color::Transparent;
    txtFirstName->Location = Point(iX, 46);
    txtFirstName->Size = Drawing::Size(halfW, 26);
    txtFirstName->Font = fBase;
    txtFirstName->BackColor = clrInputBg;
    txtFirstName->ForeColor = clrTextPrimary;
    txtFirstName->BorderStyle = BorderStyle::FixedSingle;

    lblLastName->AutoSize = true;
    lblLastName->Location = Point(iX + halfW + 12, 28);
    lblLastName->Text = L"Last Name";
    lblLastName->Font = fLabel;
    lblLastName->ForeColor = clrTextSecond;
    lblLastName->BackColor = Color::Transparent;
    txtLastName->Location = Point(iX + halfW + 12, 46);
    txtLastName->Size = Drawing::Size(halfW, 26);
    txtLastName->Font = fBase;
    txtLastName->BackColor = clrInputBg;
    txtLastName->ForeColor = clrTextPrimary;
    txtLastName->BorderStyle = BorderStyle::FixedSingle;

    // Email
    lblEmail->AutoSize = true;
    lblEmail->Location = Point(iX, 88);
    lblEmail->Text = L"Email Address";
    lblEmail->Font = fLabel;
    lblEmail->ForeColor = clrTextSecond;
    lblEmail->BackColor = Color::Transparent;
    txtEmail->Location = Point(iX, 106);
    txtEmail->Size = Drawing::Size(iW, 26);
    txtEmail->Font = fBase;
    txtEmail->BackColor = clrInputBg;
    txtEmail->ForeColor = clrTextPrimary;
    txtEmail->BorderStyle = BorderStyle::FixedSingle;

    grpPersonal->Controls->Add(lblFirstName);
    grpPersonal->Controls->Add(txtFirstName);
    grpPersonal->Controls->Add(lblLastName);
    grpPersonal->Controls->Add(txtLastName);
    grpPersonal->Controls->Add(lblEmail);
    grpPersonal->Controls->Add(txtEmail);

    //Security group
    grpSecurity->Location = Point(gX, 274);
    grpSecurity->Size = Drawing::Size(gW, 268);
    grpSecurity->Text = L"Password & Security";
    grpSecurity->Font = fGroup;
    grpSecurity->ForeColor = clrAccent;
    grpSecurity->BackColor = clrSurface;

    // Password + Confirm
    lblPassword->AutoSize = true;
    lblPassword->Location = Point(iX, 28);
    lblPassword->Text = L"Password  (min. 6 characters)";
    lblPassword->Font = fLabel;
    lblPassword->ForeColor = clrTextSecond;
    lblPassword->BackColor = Color::Transparent;
    txtPassword->Location = Point(iX, 46);
    txtPassword->Size = Drawing::Size(halfW, 26);
    txtPassword->Font = fBase;
    txtPassword->BackColor = clrInputBg;
    txtPassword->ForeColor = clrTextPrimary;
    txtPassword->BorderStyle = BorderStyle::FixedSingle;
    txtPassword->PasswordChar = '*';

    lblConfirm->AutoSize = true;
    lblConfirm->Location = Point(iX + halfW + 12, 28);
    lblConfirm->Text = L"Confirm Password";
    lblConfirm->Font = fLabel;
    lblConfirm->ForeColor = clrTextSecond;
    lblConfirm->BackColor = Color::Transparent;
    txtConfirm->Location = Point(iX + halfW + 12, 46);
    txtConfirm->Size = Drawing::Size(halfW, 26);
    txtConfirm->Font = fBase;
    txtConfirm->BackColor = clrInputBg;
    txtConfirm->ForeColor = clrTextPrimary;
    txtConfirm->BorderStyle = BorderStyle::FixedSingle;
    txtConfirm->PasswordChar = '*';

    // Security question dropdown
    lblSecQuestion->AutoSize = true;
    lblSecQuestion->Location = Point(iX, 90);
    lblSecQuestion->Text = L"Security Question  (used to recover your password)";
    lblSecQuestion->Font = fLabel;
    lblSecQuestion->ForeColor = clrTextSecond;
    lblSecQuestion->BackColor = Color::Transparent;

    cmbSecQuestion->Location = Point(iX, 110);
    cmbSecQuestion->Size = Drawing::Size(iW, 26);
    cmbSecQuestion->Font = fBase;
    cmbSecQuestion->BackColor = clrInputBg;
    cmbSecQuestion->ForeColor = clrTextPrimary;
    cmbSecQuestion->FlatStyle = FlatStyle::Flat;
    cmbSecQuestion->DropDownStyle = ComboBoxStyle::DropDownList;
    cmbSecQuestion->Items->Add("What was the name of your first pet?");
    cmbSecQuestion->Items->Add("What is your mother's maiden name?");
    cmbSecQuestion->Items->Add("What city were you born in?");
    cmbSecQuestion->Items->Add("What was the name of your primary school?");
    cmbSecQuestion->Items->Add("What is your oldest sibling's middle name?");
    cmbSecQuestion->Items->Add("What street did you grow up on?");
    cmbSecQuestion->SelectedIndex = 0;

    // Security answer
    lblSecAnswer->AutoSize = true;
    lblSecAnswer->Location = Point(iX, 152);
    lblSecAnswer->Text = L"Your Answer  (not case-sensitive)";
    lblSecAnswer->Font = fLabel;
    lblSecAnswer->ForeColor = clrTextSecond;
    lblSecAnswer->BackColor = Color::Transparent;
    txtSecAnswer->Location = Point(iX, 170);
    txtSecAnswer->Size = Drawing::Size(iW, 26);
    txtSecAnswer->Font = fBase;
    txtSecAnswer->BackColor = clrInputBg;
    txtSecAnswer->ForeColor = clrTextPrimary;
    txtSecAnswer->BorderStyle = BorderStyle::FixedSingle;

    grpSecurity->Controls->Add(lblPassword);
    grpSecurity->Controls->Add(txtPassword);
    grpSecurity->Controls->Add(lblConfirm);
    grpSecurity->Controls->Add(txtConfirm);
    grpSecurity->Controls->Add(lblSecQuestion);
    grpSecurity->Controls->Add(cmbSecQuestion);
    grpSecurity->Controls->Add(lblSecAnswer);
    grpSecurity->Controls->Add(txtSecAnswer);

    lblStatus->AutoSize = false;
    lblStatus->Size = Drawing::Size(gW, 22);
    lblStatus->Location = Point(gX, 554);
    lblStatus->Text = L"";
    lblStatus->Font = fLabel;
    lblStatus->ForeColor = clrDanger;
    lblStatus->BackColor = Color::Transparent;
    lblStatus->TextAlign = ContentAlignment::MiddleLeft;

    btnRegister->Location = Point(gX, 582);
    btnRegister->Size = Drawing::Size(gW, 38);
    btnRegister->Text = L"Create Account";
    btnRegister->Font = fBtn;
    btnRegister->BackColor = clrAccent;
    btnRegister->ForeColor = Color::White;
    btnRegister->FlatStyle = FlatStyle::Flat;
    btnRegister->FlatAppearance->BorderSize = 0;
    btnRegister->Cursor = Cursors::Hand;
    btnRegister->Click += gcnew EventHandler(
        this, &frmRegister::btnRegister_Click);

    btnBack->Location = Point(gX, 630);
    btnBack->Size = Drawing::Size(gW, 32);
    btnBack->Text = L"← Back to Login";
    btnBack->Font = fBtn;
    btnBack->BackColor = Color::FromArgb(55, 55, 55);
    btnBack->ForeColor = clrTextSecond;
    btnBack->FlatStyle = FlatStyle::Flat;
    btnBack->FlatAppearance->BorderSize = 1;
    btnBack->FlatAppearance->BorderColor = clrBorder;
    btnBack->Cursor = Cursors::Hand;
    btnBack->Click += gcnew EventHandler(
        this, &frmRegister::btnBack_Click);

    this->AutoScaleDimensions = Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(500, 678);
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->StartPosition = FormStartPosition::CenterParent;
    this->Text = L"SHWT – Register";
    this->Controls->Add(pnlHeader);
    this->Controls->Add(grpPersonal);
    this->Controls->Add(grpSecurity);
    this->Controls->Add(lblStatus);
    this->Controls->Add(btnRegister);
    this->Controls->Add(btnBack);

    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    grpPersonal->ResumeLayout(false);
    grpPersonal->PerformLayout();
    grpSecurity->ResumeLayout(false);
    grpSecurity->PerformLayout();
    this->ResumeLayout(false);
    

}

bool frmRegister::ValidateInput()
{
    if (String::IsNullOrWhiteSpace(txtFirstName->Text))
    {
        lblStatus->Text = L"First name is required."; return false;
    }
    if (String::IsNullOrWhiteSpace(txtLastName->Text))
    {
        lblStatus->Text = L"Last name is required."; return false;
    }
    if (String::IsNullOrWhiteSpace(txtEmail->Text) ||
        !txtEmail->Text->Contains("@"))
    {
        lblStatus->Text = L"Please enter a valid email address."; return false;
    }
    if (txtPassword->Text->Length < 6)
    {
        lblStatus->Text = L"Password must be at least 6 characters."; return false;
    }
    if (txtPassword->Text != txtConfirm->Text)
    {
        lblStatus->Text = L"Passwords do not match."; return false;
    }
    if (String::IsNullOrWhiteSpace(txtSecAnswer->Text))
    {
        lblStatus->Text = L"Please provide an answer to your security question."; return false;
    }
    return true;
}

System::Void frmRegister::btnRegister_Click(Object^ sender, EventArgs^ e)
{
    lblStatus->Text = L"";
    if (!ValidateInput()) return;

    
        if (dbHelper->EmailExists(txtEmail->Text->Trim()))
        {
            lblStatus->Text = L"An account with that email already exists.";
            return;
        }

    Student^ s = gcnew Student();
    s->FirstName = txtFirstName->Text->Trim();
    s->LastName = txtLastName->Text->Trim();
    s->Email = txtEmail->Text->Trim();
    s->Password = txtPassword->Text;
    s->SecurityQuestion = cmbSecQuestion->SelectedItem->ToString();
    s->SecurityAnswer = txtSecAnswer->Text->Trim();

    if (dbHelper->RegisterStudent(s))
    {
        MessageBox::Show(
            "Account created successfully!\n"
            "You can now sign in with your email and password.",
            "Registration Complete",
            MessageBoxButtons::OK,
            MessageBoxIcon::Information);
        this->Close();
    }
    else
    {
        lblStatus->Text = L"Registration failed. Please try again.";
    }
    

}

System::Void frmRegister::btnBack_Click(Object^ sender, EventArgs^ e)
{
    this->Close();
}