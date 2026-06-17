#include "frmDashboard.h"
#include "frmLogEntry.h"
#include "frmHistory.h"
#include "frmReport.h"
#include "frmAdmin.h"
#include "frmLogin.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace SHWT;

frmDashboard::frmDashboard(Student^ student)
{
    currentStudent = student;
    dbHelper = gcnew DatabaseHelper();
    InitializeComponent();
    LoadLatestStats();
}

Button^ frmDashboard::MakeNavBtn(String^ text, Color bg, Color fg, int y)
{
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);
    const int navX = 526;
    const int navW = 272;
    const int navH = 40;

    Button^ b = gcnew Button();
    b->Location = Point(navX, y);
    b->Size = Drawing::Size(navW, navH);
    b->Text = text;
    b->Font = fBtn;
    b->BackColor = bg;
    b->ForeColor = fg;
    b->FlatStyle = FlatStyle::Flat;
    b->FlatAppearance->BorderSize = 0;
    b->Cursor = Cursors::Hand;
    b->TextAlign = ContentAlignment::MiddleLeft;
    b->Padding = System::Windows::Forms::Padding(12, 0, 0, 0);
    return b;
}

Panel^ frmDashboard::MakeStatCard(Color accent, String^ title,
    Label^% outTitle, Label^% outVal)
{
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);

    Panel^ card = gcnew Panel();
    card->Size = Drawing::Size(162, 88);
    card->BackColor = clrSurface;

    Panel^ stripe = gcnew Panel();
    stripe->Size = Drawing::Size(4, 88);
    stripe->Location = Point(0, 0);
    stripe->BackColor = accent;
    card->Controls->Add(stripe);

    Label^ lTitle = gcnew Label();
    lTitle->AutoSize = true;
    lTitle->Location = Point(12, 12);
    lTitle->Text = title;
    lTitle->Font = gcnew Drawing::Font("Segoe UI", 8.5f, FontStyle::Regular);
    lTitle->ForeColor = clrTextSecond;
    lTitle->BackColor = Color::Transparent;
    card->Controls->Add(lTitle);

    Label^ lVal = gcnew Label();
    lVal->AutoSize = true;
    lVal->Location = Point(12, 32);
    lVal->Text = L"—";
    lVal->Font = gcnew Drawing::Font("Segoe UI", 24.0f, FontStyle::Bold);
    lVal->ForeColor = clrTextPrimary;
    lVal->BackColor = Color::Transparent;
    card->Controls->Add(lVal);

    outTitle = lTitle;
    outVal = lVal;
    return card;
}

void frmDashboard::InitializeComponent()
{
    Color clrFormBg = Color::FromArgb(30, 30, 30);
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrHeader = Color::FromArgb(28, 28, 28);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrDanger = Color::FromArgb(190, 60, 60);
    Color clrStatusBar = Color::FromArgb(22, 22, 22);

    Drawing::Font^ fWelcome = gcnew Drawing::Font("Segoe UI", 15.0f, FontStyle::Bold);
    Drawing::Font^ fInfo = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);
    Drawing::Font^ fGroup = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Bold);
    Drawing::Font^ fBase = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);
    Drawing::Font^ fStatus = gcnew Drawing::Font("Segoe UI", 8.5f, FontStyle::Regular);

    //Header 
    pnlHeader = gcnew Panel();
    lblWelcome = gcnew Label();
    lblStudentInfo = gcnew Label();
    lblLastLogin = gcnew Label();

    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(820, 80);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblWelcome);
    pnlHeader->Controls->Add(lblStudentInfo);
    pnlHeader->Controls->Add(lblLastLogin);

    lblWelcome->AutoSize = true;
    lblWelcome->Location = Point(20, 10);
    lblWelcome->Text = L"Welcome back, " + currentStudent->FirstName + L"!";
    lblWelcome->Font = fWelcome;
    lblWelcome->ForeColor = clrTextPrimary;
    lblWelcome->BackColor = Color::Transparent;

    lblStudentInfo->AutoSize = true;
    lblStudentInfo->Location = Point(22, 44);
    lblStudentInfo->Text = currentStudent->FullName + L"   ·   " + currentStudent->Email;
    lblStudentInfo->Font = fInfo;
    lblStudentInfo->ForeColor = clrTextSecond;
    lblStudentInfo->BackColor = Color::Transparent;

    lblLastLogin->AutoSize = true;
    lblLastLogin->Location = Point(22, 60);
    lblLastLogin->Text = L"Session started: " + DateTime::Now.ToString("dd MMM yyyy  HH:mm");
    lblLastLogin->Font = fInfo;
    lblLastLogin->ForeColor = Color::FromArgb(130, 130, 130);
    lblLastLogin->BackColor = Color::Transparent;

    // Stat cards
    int cardY = 96;
    int cardGap = 12;
    int cardStartX = 20;

    pnlCardSleep = MakeStatCard(Color::FromArgb(100, 149, 237),
        L"Sleep (hrs)",
        lblCardSleepTitle, lblCardSleepVal);
    pnlCardWater = MakeStatCard(Color::FromArgb(70, 180, 200),
        L"Water (glasses)",
        lblCardWaterTitle, lblCardWaterVal);
    pnlCardExercise = MakeStatCard(Color::FromArgb(90, 185, 120),
        L"Exercise (mins)",
        lblCardExerciseTitle, lblCardExerciseVal);
    pnlCardStress = MakeStatCard(Color::FromArgb(200, 90, 90),
        L"Stress (1–10)",
        lblCardStressTitle, lblCardStressVal);

    pnlCardSleep->Location = Point(cardStartX, cardY);
    pnlCardWater->Location = Point(cardStartX + 162 + cardGap, cardY);
    pnlCardExercise->Location = Point(cardStartX + (162 + cardGap) * 2, cardY);
    pnlCardStress->Location = Point(cardStartX + (162 + cardGap) * 3, cardY);

    //Reminders group
    grpReminders = gcnew GroupBox();
    lblReminders = gcnew Label();

    grpReminders->Location = Point(20, 200);
    grpReminders->Size = Drawing::Size(492, 138);
    grpReminders->Text = L"Today's Wellness Reminders";
    grpReminders->Font = fGroup;
    grpReminders->ForeColor = clrAccent;
    grpReminders->BackColor = clrSurface;

    lblReminders->Location = Point(14, 26);
    lblReminders->Size = Drawing::Size(462, 100);
    lblReminders->Font = fBase;
    lblReminders->ForeColor = clrTextSecond;
    lblReminders->BackColor = Color::Transparent;
    lblReminders->Text =
        L"  Drink at least 8 glasses of water today.\r\n\r\n"
        L"  Aim for at least 30 minutes of physical activity.\r\n\r\n"
        L"  Get 7 to 9 hours of sleep tonight.\r\n\r\n"
        L"  Take a short break if you are feeling stressed.";

    grpReminders->Controls->Add(lblReminders);

    const int navH = 40;
    const int navG = 10;

    int ny = 200;
    btnLogEntry = MakeNavBtn(L"   + Log Today's Wellness",
        Color::FromArgb(100, 149, 237), Color::White, ny);
    ny += navH + navG;
    btnHistory = MakeNavBtn(L"   View Wellness History",
        Color::FromArgb(60, 90, 155), Color::White, ny);
    ny += navH + navG;
    btnReport = MakeNavBtn(L"   Generate Health Report",
        Color::FromArgb(60, 120, 80), Color::White, ny);
    ny += navH + navG;
    btnAdmin = MakeNavBtn(L"   Admin Monitor",
        Color::FromArgb(80, 60, 120), Color::White, ny);

    btnLogEntry->Click += gcnew EventHandler(this, &frmDashboard::btnLogEntry_Click);
    btnHistory->Click += gcnew EventHandler(this, &frmDashboard::btnHistory_Click);
    btnReport->Click += gcnew EventHandler(this, &frmDashboard::btnReport_Click);
    btnAdmin->Click += gcnew EventHandler(this, &frmDashboard::btnAdmin_Click);

    //Account management buttons
    const int navX = 526;
    const int navW = 272;
    int bottomY = 360;

    btnLogout = gcnew Button();
    btnLogout->Location = Point(navX, bottomY);
    btnLogout->Size = Drawing::Size(navW, 34);
    btnLogout->Text = L"   Sign Out";
    btnLogout->Font = fBtn;
    btnLogout->BackColor = Color::FromArgb(55, 55, 55);
    btnLogout->ForeColor = clrTextSecond;
    btnLogout->FlatStyle = FlatStyle::Flat;
    btnLogout->FlatAppearance->BorderSize = 1;
    btnLogout->FlatAppearance->BorderColor = Color::FromArgb(80, 80, 80);
    btnLogout->Cursor = Cursors::Hand;
    btnLogout->TextAlign = ContentAlignment::MiddleLeft;
    btnLogout->Padding = System::Windows::Forms::Padding(12, 0, 0, 0);
    btnLogout->Click += gcnew EventHandler(
        this, &frmDashboard::btnLogout_Click);

    btnDeleteAccount = gcnew Button();
    btnDeleteAccount->Location = Point(navX, bottomY + 44);
    btnDeleteAccount->Size = Drawing::Size(navW, 34);
    btnDeleteAccount->Text = L"   Delete My Account";
    btnDeleteAccount->Font = fBtn;
    btnDeleteAccount->BackColor = Color::FromArgb(100, 35, 35);
    btnDeleteAccount->ForeColor = Color::FromArgb(240, 160, 160);
    btnDeleteAccount->FlatStyle = FlatStyle::Flat;
    btnDeleteAccount->FlatAppearance->BorderSize = 1;
    btnDeleteAccount->FlatAppearance->BorderColor = Color::FromArgb(160, 50, 50);
    btnDeleteAccount->Cursor = Cursors::Hand;
    btnDeleteAccount->TextAlign = ContentAlignment::MiddleLeft;
    btnDeleteAccount->Padding = System::Windows::Forms::Padding(12, 0, 0, 0);
    btnDeleteAccount->Click += gcnew EventHandler(
        this, &frmDashboard::btnDeleteAccount_Click);

    // Status bar
    pnlStatusBar = gcnew Panel();
    lblStatusBar = gcnew Label();

    pnlStatusBar->Location = Point(0, 452);
    pnlStatusBar->Size = Drawing::Size(820, 24);
    pnlStatusBar->BackColor = clrStatusBar;
    pnlStatusBar->Controls->Add(lblStatusBar);

    lblStatusBar->AutoSize = false;
    lblStatusBar->Size = Drawing::Size(800, 24);
    lblStatusBar->Location = Point(12, 0);
    lblStatusBar->Text = L"Student Health & Wellness Tracker  v1.0   |   All data is stored securely.";
    lblStatusBar->Font = fStatus;
    lblStatusBar->ForeColor = Color::FromArgb(100, 100, 100);
    lblStatusBar->BackColor = Color::Transparent;
    lblStatusBar->TextAlign = ContentAlignment::MiddleLeft;

    this->AutoScaleDimensions = Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(820, 476);
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->StartPosition = FormStartPosition::CenterScreen;
    this->Text = L"SHWT – Dashboard";

    pnlHeader->SuspendLayout();
    grpReminders->SuspendLayout();
    pnlStatusBar->SuspendLayout();

    this->Controls->Add(pnlHeader);
    this->Controls->Add(pnlCardSleep);
    this->Controls->Add(pnlCardWater);
    this->Controls->Add(pnlCardExercise);
    this->Controls->Add(pnlCardStress);
    this->Controls->Add(grpReminders);
    this->Controls->Add(btnLogEntry);
    this->Controls->Add(btnHistory);
    this->Controls->Add(btnReport);
    this->Controls->Add(btnAdmin);
    this->Controls->Add(btnLogout);
    this->Controls->Add(btnDeleteAccount);
    this->Controls->Add(pnlStatusBar);

    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    grpReminders->ResumeLayout(false);
    pnlStatusBar->ResumeLayout(false);
    this->ResumeLayout(false);
}

void frmDashboard::LoadLatestStats()
{
    List<HealthLog^>^ logs =
        dbHelper->GetLogsForStudent(currentStudent->StudentId);

    if (logs->Count == 0)
    {
        lblCardSleepVal->Text = L"—";
        lblCardWaterVal->Text = L"—";
        lblCardExerciseVal->Text = L"—";
        lblCardStressVal->Text = L"—";
        return;
    }

    HealthLog^ latest = logs[0];
    lblCardSleepVal->Text = latest->SleepHours.ToString();
    lblCardWaterVal->Text = latest->WaterGlasses.ToString();
    lblCardExerciseVal->Text = latest->ExerciseMins.ToString();
    lblCardStressVal->Text = latest->StressLevel.ToString();
}

System::Void frmDashboard::btnLogEntry_Click(Object^ sender, EventArgs^ e)
{
    frmLogEntry^ f = gcnew frmLogEntry(currentStudent);
    if (f->ShowDialog(this) == System::Windows::Forms::DialogResult::OK)
        LoadLatestStats();
}

System::Void frmDashboard::btnHistory_Click(Object^ sender, EventArgs^ e)
{
    frmHistory^ f = gcnew frmHistory(currentStudent);
    f->ShowDialog(this);
}

System::Void frmDashboard::btnReport_Click(Object^ sender, EventArgs^ e)
{
    frmReport^ f = gcnew frmReport(currentStudent);
    f->ShowDialog(this);
}

System::Void frmDashboard::btnAdmin_Click(Object^ sender, EventArgs^ e)
{
    frmAdmin^ f = gcnew frmAdmin();
    f->ShowDialog(this);
}

System::Void frmDashboard::btnLogout_Click(Object^ sender, EventArgs^ e)
{
    System::Windows::Forms::DialogResult res = MessageBox::Show(
        "Are you sure you want to sign out?",
        "Confirm Sign Out",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Question);

    if (res == System::Windows::Forms::DialogResult::Yes)
    {
        frmLogin^ login = gcnew frmLogin();
        login->Show();
        this->Close();
    }
}

System::Void frmDashboard::btnDeleteAccount_Click(Object^ sender, EventArgs^ e)
{
    System::Windows::Forms::DialogResult res1 = MessageBox::Show(
        "This will permanently delete your account\n"
        "and ALL wellness logs associated with it.\n\n"
        "This action cannot be undone. Continue?",
        "Delete Account — Step 1 of 2",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Warning);

    if (res1 != System::Windows::Forms::DialogResult::Yes) return;

    System::Windows::Forms::DialogResult res2 = MessageBox::Show(
        "Final confirmation:\n\n"
        "Delete account for  " + currentStudent->FullName + "?\n\n"
        "Click Yes to permanently delete everything.",
        "Delete Account — Step 2 of 2",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Stop);

    if (res2 != System::Windows::Forms::DialogResult::Yes) return;

    if (dbHelper->DeleteStudent(currentStudent->StudentId))
    {
        MessageBox::Show(
            "Your account has been deleted.\n"
            "Thank you for using SHWT.",
            "Account Deleted",
            MessageBoxButtons::OK,
            MessageBoxIcon::Information);

        frmLogin^ login = gcnew frmLogin();
        login->Show();
        this->Close();
    }
    else
    {
        MessageBox::Show(
            "An error occurred while deleting your account.\n"
            "Please try again or contact support.",
            "Delete Failed",
            MessageBoxButtons::OK,
            MessageBoxIcon::Error);
    }
}