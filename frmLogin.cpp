#include "frmLogin.h"
#include "frmRegister.h"
#include "frmDashboard.h"
#include "frmForgotPassword.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace SHWT;

frmLogin::frmLogin()
{
    dbHelper = gcnew DatabaseHelper();
    LoggedInStudent = nullptr;
    dbHelper->InitialiseDatabase();
    InitializeComponent();
}

void frmLogin::InitializeComponent()
{
    // ── Colour palette ───────────────────────────────────────────────────────
    Color clrFormBg = Color::FromArgb(30, 30, 30);
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrHeader = Color::FromArgb(28, 28, 28);
    Color clrInputBg = Color::FromArgb(55, 55, 55);
    Color clrBorder = Color::FromArgb(75, 75, 75);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrDanger = Color::FromArgb(210, 80, 80);
    Color clrFooter = Color::FromArgb(38, 38, 38);

    // ── Fonts ────────────────────────────────────────────────────────────────
    Drawing::Font^ fAppName = gcnew Drawing::Font("Segoe UI", 16.0f, FontStyle::Bold);
    Drawing::Font^ fTagline = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);
    Drawing::Font^ fGroup = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Bold);
    Drawing::Font^ fLabel = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBase = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);
    Drawing::Font^ fLink = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);

    // ── Control instantiation ────────────────────────────────────────────────
    pnlHeader = gcnew Panel();
    lblAppName = gcnew Label();
    lblAppTagline = gcnew Label();
    grpLogin = gcnew GroupBox();
    lblEmail = gcnew Label();
    txtEmail = gcnew TextBox();
    lblPassword = gcnew Label();
    txtPassword = gcnew TextBox();
    btnLogin = gcnew Button();
    lnkForgotPassword = gcnew LinkLabel();
    lblStatus = gcnew Label();
    pnlFooter = gcnew Panel();
    lblNoAccount = gcnew Label();
    btnGoRegister = gcnew Button();

    // ── Suspend layouts before setting properties ────────────────────────────
    this->SuspendLayout();
    pnlHeader->SuspendLayout();
    grpLogin->SuspendLayout();
    pnlFooter->SuspendLayout();

    // ════════════════════════════════════════════════════════════════════════
    // Header panel  (460 × 90)
    // ════════════════════════════════════════════════════════════════════════
    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(460, 90);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblAppName);
    pnlHeader->Controls->Add(lblAppTagline);

    lblAppName->AutoSize = true;
    lblAppName->Location = Point(20, 16);
    lblAppName->Text = L"Student Health and Wellness Tracker";
    lblAppName->Font = fAppName;
    lblAppName->ForeColor = clrAccent;
    lblAppName->BackColor = Color::Transparent;

    lblAppTagline->AutoSize = true;
    lblAppTagline->Location = Point(22, 52);
    lblAppTagline->Text = L"Track your wellbeing \x2014 sleep, hydration, exercise and more.";
    lblAppTagline->Font = fTagline;
    lblAppTagline->ForeColor = clrTextSecond;
    lblAppTagline->BackColor = Color::Transparent;

    // ════════════════════════════════════════════════════════════════════════
    // Login GroupBox  (418 × 278)
    // FIX: height increased from 252 → 278 so lblStatus (Y=252) is not clipped
    // ════════════════════════════════════════════════════════════════════════
    grpLogin->Location = Point(20, 108);
    grpLogin->Size = Drawing::Size(418, 278);   // ← was 252, now 278
    grpLogin->Text = L"Sign In to Your Account";
    grpLogin->Font = fGroup;
    grpLogin->ForeColor = clrAccent;
    grpLogin->BackColor = clrSurface;

    const int iX = 16;   // left margin inside group
    const int iW = 382;  // control width inside group

    // Email label & textbox
    lblEmail->AutoSize = true;
    lblEmail->Location = Point(iX, 32);
    lblEmail->Text = L"Email Address";
    lblEmail->Font = fLabel;
    lblEmail->ForeColor = clrTextSecond;
    lblEmail->BackColor = Color::Transparent;

    txtEmail->Location = Point(iX, 52);
    txtEmail->Size = Drawing::Size(iW, 26);
    txtEmail->Font = fBase;
    txtEmail->BackColor = clrInputBg;
    txtEmail->ForeColor = clrTextPrimary;
    txtEmail->BorderStyle = BorderStyle::FixedSingle;

    // Password label & textbox
    lblPassword->AutoSize = true;
    lblPassword->Location = Point(iX, 94);
    lblPassword->Text = L"Password";
    lblPassword->Font = fLabel;
    lblPassword->ForeColor = clrTextSecond;
    lblPassword->BackColor = Color::Transparent;

    txtPassword->Location = Point(iX, 114);
    txtPassword->Size = Drawing::Size(iW, 26);
    txtPassword->Font = fBase;
    txtPassword->BackColor = clrInputBg;
    txtPassword->ForeColor = clrTextPrimary;
    txtPassword->BorderStyle = BorderStyle::FixedSingle;
    txtPassword->PasswordChar = '*';
    txtPassword->KeyPress += gcnew KeyPressEventHandler(
        this, &frmLogin::txtPassword_KeyPress);

    // Sign In button  (Y=158, H=38 → bottom at 196)
    btnLogin->Location = Point(iX, 158);
    btnLogin->Size = Drawing::Size(iW, 38);
    btnLogin->Text = L"Sign In";
    btnLogin->Font = fBtn;
    btnLogin->BackColor = clrAccent;
    btnLogin->ForeColor = Color::White;
    btnLogin->FlatStyle = FlatStyle::Flat;
    btnLogin->FlatAppearance->BorderSize = 0;
    btnLogin->Cursor = Cursors::Hand;
    btnLogin->Click += gcnew EventHandler(
        this, &frmLogin::btnLogin_Click);

    // FIX: lnkForgotPassword moved to Y=204 (was 208, gave no breathing room)
    lnkForgotPassword->AutoSize = true;
    lnkForgotPassword->Location = Point(iX, 204);
    lnkForgotPassword->Text = L"Forgot your password?";
    lnkForgotPassword->Font = fLink;
    lnkForgotPassword->LinkColor = clrAccent;
    lnkForgotPassword->BackColor = Color::Transparent;
    lnkForgotPassword->LinkClicked += gcnew LinkLabelLinkClickedEventHandler(
        this, &frmLogin::lnkForgotPassword_Click);

    // FIX: lblStatus moved to Y=228 (below lnkForgotPassword ~204+16=220)
    //      GroupBox height 278 comfortably contains Y=228 + H=22 = 250
    lblStatus->AutoSize = false;
    lblStatus->Size = Drawing::Size(iW, 22);
    lblStatus->Location = Point(iX, 228);
    lblStatus->Text = L"";
    lblStatus->Font = fLabel;
    lblStatus->ForeColor = clrDanger;
    lblStatus->BackColor = Color::Transparent;
    lblStatus->TextAlign = ContentAlignment::MiddleLeft;

    // Add controls to GroupBox
    grpLogin->Controls->Add(lblEmail);
    grpLogin->Controls->Add(txtEmail);
    grpLogin->Controls->Add(lblPassword);
    grpLogin->Controls->Add(txtPassword);
    grpLogin->Controls->Add(btnLogin);
    grpLogin->Controls->Add(lnkForgotPassword);
    grpLogin->Controls->Add(lblStatus);

    // ════════════════════════════════════════════════════════════════════════
    // Footer panel
    // FIX: Y recalculated → header(90) + gap(8) + grpLogin(108+278=386) + gap(8) = 402
    //      Form ClientHeight adjusted to 402 + 60 (footer) = 462
    // ════════════════════════════════════════════════════════════════════════
    pnlFooter->Location = Point(0, 402);          // ← was 376, now 402
    pnlFooter->Size = Drawing::Size(460, 60);
    pnlFooter->BackColor = clrFooter;
    pnlFooter->Controls->Add(lblNoAccount);
    pnlFooter->Controls->Add(btnGoRegister);

    lblNoAccount->AutoSize = true;
    lblNoAccount->Location = Point(20, 20);
    lblNoAccount->Text = L"Don't have an account?";
    lblNoAccount->Font = fLabel;
    lblNoAccount->ForeColor = clrTextSecond;
    lblNoAccount->BackColor = Color::Transparent;

    btnGoRegister->Location = Point(210, 14);
    btnGoRegister->Size = Drawing::Size(228, 32);
    btnGoRegister->Text = L"Create a New Account";
    btnGoRegister->Font = fBtn;
    btnGoRegister->BackColor = Color::FromArgb(60, 60, 60);
    btnGoRegister->ForeColor = clrTextPrimary;
    btnGoRegister->FlatStyle = FlatStyle::Flat;
    btnGoRegister->FlatAppearance->BorderSize = 1;
    btnGoRegister->FlatAppearance->BorderColor = clrBorder;
    btnGoRegister->Cursor = Cursors::Hand;
    btnGoRegister->Click += gcnew EventHandler(
        this, &frmLogin::btnGoRegister_Click);

    // ════════════════════════════════════════════════════════════════════════
    // Form properties
    // FIX: AutoScaleDimensions uses float literals (6.0f, 13.0f) not integers
    // FIX: ClientSize height 462 (was 436) to accommodate taller GroupBox + footer
    // ════════════════════════════════════════════════════════════════════════
    this->AutoScaleDimensions = Drawing::SizeF(6.0f, 13.0f);   // ← was (6, 13)
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(460, 462);        // ← was 436, now 462
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->MinimizeBox = true;
    this->StartPosition = FormStartPosition::CenterScreen;
    this->Text = L"SHWT \x2013 Login";
    this->Name = L"frmLogin";       // ← added: good practice in C++/CLI

    // Add top-level controls to form
    this->Controls->Add(pnlHeader);
    this->Controls->Add(grpLogin);
    this->Controls->Add(pnlFooter);

    // ── Resume layouts ───────────────────────────────────────────────────────
    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    grpLogin->ResumeLayout(false);
    grpLogin->PerformLayout();
    pnlFooter->ResumeLayout(false);
    pnlFooter->PerformLayout();
    this->ResumeLayout(false);
}

// ════════════════════════════════════════════════════════════════════════════
// Event handlers
// ════════════════════════════════════════════════════════════════════════════

System::Void frmLogin::btnLogin_Click(Object^ sender, EventArgs^ e)
{
    lblStatus->Text = L"";

    if (String::IsNullOrWhiteSpace(txtEmail->Text) ||
        String::IsNullOrWhiteSpace(txtPassword->Text))
    {
        lblStatus->Text = L"Please enter your email and password.";
        return;
    }

    Student^ s = dbHelper->LoginStudent(
        txtEmail->Text->Trim(), txtPassword->Text);

    if (s == nullptr)
    {
        lblStatus->Text = L"Incorrect email or password. Please try again.";
        txtPassword->Clear();
        txtPassword->Focus();
        return;
    }

    LoggedInStudent = s;
    frmDashboard^ dash = gcnew frmDashboard(s);
    dash->Show();
    this->Hide();
}

System::Void frmLogin::btnGoRegister_Click(Object^ sender, EventArgs^ e)
{
    frmRegister^ reg = gcnew frmRegister();
    reg->ShowDialog(this);
}

System::Void frmLogin::lnkForgotPassword_Click(
    Object^ sender, LinkLabelLinkClickedEventArgs^ e)
{
    frmForgotPassword^ fp = gcnew frmForgotPassword();
    fp->ShowDialog(this);
}

System::Void frmLogin::txtPassword_KeyPress(Object^ sender, KeyPressEventArgs^ e)
{
    if (e->KeyChar == (char)Keys::Return)
        btnLogin_Click(sender, e);
}