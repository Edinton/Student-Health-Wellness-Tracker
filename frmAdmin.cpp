#include "frmAdmin.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace SHWT;

frmAdmin::frmAdmin()
{
    dbHelper = gcnew DatabaseHelper();
    InitializeComponent();
    LoadData();
}

Panel^ frmAdmin::MakeStatCard(Color accent, String^ title,
    Label^% outTitle, Label^% outVal)
{
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);

    Panel^ card = gcnew Panel();
    card->Size = Drawing::Size(200, 80);
    card->BackColor = clrSurface;

    Panel^ stripe = gcnew Panel();
    stripe->Size = Drawing::Size(4, 80);
    stripe->Location = Point(0, 0);
    stripe->BackColor = accent;
    card->Controls->Add(stripe);

    Label^ lTitle = gcnew Label();
    lTitle->AutoSize = true;
    lTitle->Location = Point(12, 10);
    lTitle->Text = title;
    lTitle->Font = gcnew Drawing::Font("Segoe UI", 8.5f, FontStyle::Regular);
    lTitle->ForeColor = clrTextSecond;
    lTitle->BackColor = Color::Transparent;
    card->Controls->Add(lTitle);

    Label^ lVal = gcnew Label();
    lVal->AutoSize = true;
    lVal->Location = Point(12, 28);
    lVal->Text = L"—";
    lVal->Font = gcnew Drawing::Font("Segoe UI", 22.0f, FontStyle::Bold);
    lVal->ForeColor = clrTextPrimary;
    lVal->BackColor = Color::Transparent;
    card->Controls->Add(lVal);

    outTitle = lTitle;
    outVal = lVal;
    return card;
}

void frmAdmin::StyleGrid(DataGridView^ dgv)
{
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrAlt = Color::FromArgb(52, 52, 52);
    Color clrColHeader = Color::FromArgb(35, 35, 35);

    dgv->BackgroundColor = clrSurface;
    dgv->GridColor = Color::FromArgb(58, 58, 58);
    dgv->BorderStyle = BorderStyle::None;

    dgv->RowHeadersVisible = false;
    dgv->AllowUserToAddRows = false;
    dgv->AllowUserToDeleteRows = false;
    dgv->ReadOnly = true;
    dgv->MultiSelect = false;
    dgv->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
    dgv->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

    dgv->Font = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);

    dgv->DefaultCellStyle->BackColor = clrSurface;
    dgv->DefaultCellStyle->ForeColor = clrTextPrimary;
    dgv->DefaultCellStyle->SelectionBackColor = clrAccent;
    dgv->DefaultCellStyle->SelectionForeColor = Color::White;
    dgv->DefaultCellStyle->Padding =
        System::Windows::Forms::Padding(4, 0, 4, 0);

    dgv->AlternatingRowsDefaultCellStyle->BackColor = clrAlt;

    dgv->ColumnHeadersDefaultCellStyle->BackColor = clrColHeader;
    dgv->ColumnHeadersDefaultCellStyle->ForeColor = clrAccent;
    dgv->ColumnHeadersDefaultCellStyle->Font =
        gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Bold);
    dgv->ColumnHeadersDefaultCellStyle->Padding =
        System::Windows::Forms::Padding(6, 0, 0, 0);
    dgv->ColumnHeadersHeightSizeMode =
        DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
    dgv->ColumnHeadersHeight = 32;
    dgv->RowTemplate->Height = 26;
    dgv->EnableHeadersVisualStyles = false;
}

void frmAdmin::InitializeComponent()
{
    Color clrFormBg = Color::FromArgb(30, 30, 30);
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrHeader = Color::FromArgb(28, 28, 28);
    Color clrBorder = Color::FromArgb(75, 75, 75);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrDangerBg = Color::FromArgb(110, 35, 35);
    Color clrDangerFg = Color::FromArgb(255, 190, 190);
    Color clrDangerBdr = Color::FromArgb(170, 55, 55);

    Drawing::Font^ fTitle = gcnew Drawing::Font("Segoe UI", 13.0f, FontStyle::Bold);
    Drawing::Font^ fSub = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);
    Drawing::Font^ fGroup = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Bold);
    Drawing::Font^ fBase = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);
    Drawing::Font^ fStatus = gcnew Drawing::Font("Segoe UI", 8.5f, FontStyle::Regular);

    pnlHeader = gcnew Panel();
    lblTitle = gcnew Label();
    lblSubtitle = gcnew Label();

    grpStudents = gcnew GroupBox();
    dgvStudents = gcnew DataGridView();
    btnDeleteStudent = gcnew Button();
    lblStudentStatus = gcnew Label();

    grpLogs = gcnew GroupBox();
    dgvLogs = gcnew DataGridView();
    btnDeleteAdminLog = gcnew Button();
    lblLogStatus = gcnew Label();

    pnlActionBar = gcnew Panel();
    btnRefresh = gcnew Button();
    btnClose = gcnew Button();

    this->SuspendLayout();
    pnlHeader->SuspendLayout();
    grpStudents->SuspendLayout();
    grpLogs->SuspendLayout();
    pnlActionBar->SuspendLayout();
    ((System::ComponentModel::ISupportInitialize^)(dgvStudents))->BeginInit();
    ((System::ComponentModel::ISupportInitialize^)(dgvLogs))->BeginInit();

    //Header
    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(1100, 72);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblSubtitle);

    lblTitle->AutoSize = true;
    lblTitle->Location = Point(20, 12);
    lblTitle->Text = L"Admin Monitor  —  Student Wellness Overview";
    lblTitle->Font = fTitle;
    lblTitle->ForeColor = clrAccent;
    lblTitle->BackColor = Color::Transparent;

    lblSubtitle->AutoSize = true;
    lblSubtitle->Location = Point(22, 44);
    lblSubtitle->Text =
        L"Select a student to view their logs. Use Delete to remove records permanently.";
    lblSubtitle->Font = fSub;
    lblSubtitle->ForeColor = clrTextSecond;
    lblSubtitle->BackColor = Color::Transparent;

    //Stat cards
    pnlCardStudents = MakeStatCard(
        Color::FromArgb(100, 149, 237), L"Registered Students",
        lblCardStudentsTitle, lblCardStudentsVal);
    pnlCardStudents->Location = Point(20, 86);

    pnlCardLogs = MakeStatCard(
        Color::FromArgb(90, 185, 120), L"Total Wellness Logs",
        lblCardLogsTitle, lblCardLogsVal);
    pnlCardLogs->Location = Point(234, 86);

    //Students GroupBox
    grpStudents->Location = Point(16, 180);
    grpStudents->Size = Drawing::Size(360, 446);
    grpStudents->Text = L"Registered Students";
    grpStudents->Font = fGroup;
    grpStudents->ForeColor = clrAccent;
    grpStudents->BackColor = clrSurface;

    dgvStudents->Location = Point(12, 28);
    dgvStudents->Size = Drawing::Size(334, 352);
    StyleGrid(dgvStudents);
    dgvStudents->SelectionChanged += gcnew EventHandler(
        this, &frmAdmin::dgvStudents_SelectionChanged);

    lblStudentStatus->AutoSize = false;
    lblStudentStatus->Size = Drawing::Size(334, 22);
    lblStudentStatus->Location = Point(12, 388);
    lblStudentStatus->Text = L"Select a student to view their logs.";
    lblStudentStatus->Font = fStatus;
    lblStudentStatus->ForeColor = clrTextSecond;
    lblStudentStatus->BackColor = Color::Transparent;

    btnDeleteStudent->Location = Point(12, 412);
    btnDeleteStudent->Size = Drawing::Size(334, 30);
    btnDeleteStudent->Text = L"Delete Selected Student & All Their Logs";
    btnDeleteStudent->Font = fBtn;
    btnDeleteStudent->BackColor = clrDangerBg;
    btnDeleteStudent->ForeColor = clrDangerFg;
    btnDeleteStudent->FlatStyle = FlatStyle::Flat;
    btnDeleteStudent->FlatAppearance->BorderSize = 1;
    btnDeleteStudent->FlatAppearance->BorderColor = clrDangerBdr;
    btnDeleteStudent->Cursor = Cursors::Hand;
    btnDeleteStudent->Enabled = false;
    btnDeleteStudent->Click += gcnew EventHandler(
        this, &frmAdmin::btnDeleteStudent_Click);

    grpStudents->Controls->Add(dgvStudents);
    grpStudents->Controls->Add(lblStudentStatus);
    grpStudents->Controls->Add(btnDeleteStudent);

    //Logs GroupBox
    grpLogs->Location = Point(392, 180);
    grpLogs->Size = Drawing::Size(692, 446);
    grpLogs->Text = L"Wellness Logs  —  Select a student on the left";
    grpLogs->Font = fGroup;
    grpLogs->ForeColor = clrAccent;
    grpLogs->BackColor = clrSurface;

    dgvLogs->Location = Point(12, 28);
    dgvLogs->Size = Drawing::Size(664, 352);
    StyleGrid(dgvLogs);
    dgvLogs->SelectionChanged += gcnew EventHandler(
        this, &frmAdmin::dgvLogs_SelectionChanged);

    lblLogStatus->AutoSize = false;
    lblLogStatus->Size = Drawing::Size(664, 22);
    lblLogStatus->Location = Point(12, 388);
    lblLogStatus->Text = L"Select a log entry to enable deletion.";
    lblLogStatus->Font = fStatus;
    lblLogStatus->ForeColor = clrTextSecond;
    lblLogStatus->BackColor = Color::Transparent;

    btnDeleteAdminLog->Location = Point(12, 412);
    btnDeleteAdminLog->Size = Drawing::Size(664, 30);
    btnDeleteAdminLog->Text = L"Delete Selected Log Entry";
    btnDeleteAdminLog->Font = fBtn;
    btnDeleteAdminLog->BackColor = clrDangerBg;
    btnDeleteAdminLog->ForeColor = clrDangerFg;
    btnDeleteAdminLog->FlatStyle = FlatStyle::Flat;
    btnDeleteAdminLog->FlatAppearance->BorderSize = 1;
    btnDeleteAdminLog->FlatAppearance->BorderColor = clrDangerBdr;
    btnDeleteAdminLog->Cursor = Cursors::Hand;
    btnDeleteAdminLog->Enabled = false;
    btnDeleteAdminLog->Click += gcnew EventHandler(
        this, &frmAdmin::btnDeleteAdminLog_Click);

    grpLogs->Controls->Add(dgvLogs);
    grpLogs->Controls->Add(lblLogStatus);
    grpLogs->Controls->Add(btnDeleteAdminLog);

    //Action bar
    pnlActionBar->Location = Point(0, 640);
    pnlActionBar->Size = Drawing::Size(1100, 52);
    pnlActionBar->BackColor = Color::FromArgb(38, 38, 38);
    pnlActionBar->Controls->Add(btnRefresh);
    pnlActionBar->Controls->Add(btnClose);

    btnRefresh->Location = Point(16, 8);
    btnRefresh->Size = Drawing::Size(130, 36);
    btnRefresh->Text = L"Refresh All";
    btnRefresh->Font = fBtn;
    btnRefresh->BackColor = Color::FromArgb(55, 75, 110);
    btnRefresh->ForeColor = Color::White;
    btnRefresh->FlatStyle = FlatStyle::Flat;
    btnRefresh->FlatAppearance->BorderSize = 0;
    btnRefresh->Cursor = Cursors::Hand;
    btnRefresh->Click += gcnew EventHandler(
        this, &frmAdmin::btnRefresh_Click);

    btnClose->Location = Point(952, 8);
    btnClose->Size = Drawing::Size(130, 36);
    btnClose->Text = L"Close";
    btnClose->Font = fBtn;
    btnClose->BackColor = Color::FromArgb(55, 55, 55);
    btnClose->ForeColor = clrTextSecond;
    btnClose->FlatStyle = FlatStyle::Flat;
    btnClose->FlatAppearance->BorderSize = 1;
    btnClose->FlatAppearance->BorderColor = clrBorder;
    btnClose->Cursor = Cursors::Hand;
    btnClose->Click += gcnew EventHandler(
        this, &frmAdmin::btnClose_Click);

    // ── Form ──────────────────────────────────────────────────
    this->AutoScaleDimensions = Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(1100, 692);
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->StartPosition = FormStartPosition::CenterParent;
    this->Text = L"SHWT – Admin Monitor";
    this->Controls->Add(pnlHeader);
    this->Controls->Add(pnlCardStudents);
    this->Controls->Add(pnlCardLogs);
    this->Controls->Add(grpStudents);
    this->Controls->Add(grpLogs);
    this->Controls->Add(pnlActionBar);

    ((System::ComponentModel::ISupportInitialize^)(dgvStudents))->EndInit();
    ((System::ComponentModel::ISupportInitialize^)(dgvLogs))->EndInit();
    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    grpStudents->ResumeLayout(false);
    grpLogs->ResumeLayout(false);
    pnlActionBar->ResumeLayout(false);
    this->ResumeLayout(false);
}

// ─────────────────────────────────────────────────────────────
void frmAdmin::LoadData()
{
    lblCardStudentsVal->Text = dbHelper->GetTotalStudents().ToString();
    lblCardLogsVal->Text = dbHelper->GetTotalLogs().ToString();

    dgvStudents->Rows->Clear();
    dgvStudents->Columns->Clear();
    dgvStudents->Columns->Add("sid", "ID");
    dgvStudents->Columns->Add("name", "Full Name");
    dgvStudents->Columns->Add("email", "Email");

    DataTable^ dt = dbHelper->GetAllStudents();
    for each(DataRow ^ row in dt->Rows)
    {
        array<Object^>^ r = {
            row["student_id"]->ToString(),
            row["first_name"]->ToString() + " " + row["last_name"]->ToString(),
            row["email"]->ToString()
        };
        dgvStudents->Rows->Add(r);
    }

    dgvLogs->Rows->Clear();
    dgvLogs->Columns->Clear();
    btnDeleteStudent->Enabled = false;
    btnDeleteAdminLog->Enabled = false;
    lblStudentStatus->Text = "Select a student to view their logs.";
    lblLogStatus->Text = "Select a log entry to enable deletion.";
    grpLogs->Text = L"Wellness Logs  —  Select a student on the left";
}

void frmAdmin::LoadLogsForStudent(int studentId, String^ studentName)
{
    dgvLogs->Rows->Clear();
    dgvLogs->Columns->Clear();
    btnDeleteAdminLog->Enabled = false;
    lblLogStatus->Text = "Select a log entry to enable deletion.";
    lblLogStatus->ForeColor = Color::FromArgb(170, 170, 170);
    grpLogs->Text = L"Wellness Logs  —  " + studentName;

    dgvLogs->Columns->Add("logid", "Log ID");
    dgvLogs->Columns->Add("date", "Date");
    dgvLogs->Columns->Add("sleep", "Sleep (hrs)");
    dgvLogs->Columns->Add("water", "Water (gl)");
    dgvLogs->Columns->Add("exercise", "Exercise (mins)");
    dgvLogs->Columns->Add("stress", "Stress");
    dgvLogs->Columns->Add("mood", "Mood");
    dgvLogs->Columns->Add("rating", "Rating");

    List<HealthLog^>^ logs = dbHelper->GetLogsForStudent(studentId);
    for each(HealthLog ^ log in logs)
    {
        array<Object^>^ row = {
            log->LogId.ToString(),
            log->EntryDate.ToString("dd MMM yyyy"),
            log->SleepHours.ToString(),
            log->WaterGlasses.ToString(),
            log->ExerciseMins.ToString(),
            log->StressLevel.ToString(),
            log->MoodRating.ToString(),
            log->GetWellnessSummary()
        };
        dgvLogs->Rows->Add(row);
    }

    if (dgvLogs->Columns->Contains("logid"))
        dgvLogs->Columns["logid"]->Visible = false;
}

System::Void frmAdmin::dgvStudents_SelectionChanged(Object^ sender, EventArgs^ e)
{
    if (dgvStudents->SelectedRows->Count == 0)
    {
        btnDeleteStudent->Enabled = false;
        return;
    }

    btnDeleteStudent->Enabled = true;
    int    rowIdx = dgvStudents->SelectedRows[0]->Index;
    int    studentId = Int32::Parse(
        dgvStudents->Rows[rowIdx]->Cells["sid"]->Value->ToString());
    String^ name = dgvStudents->Rows[rowIdx]->Cells["name"]->Value->ToString();

    lblStudentStatus->Text = "Viewing logs for: " + name;
    lblStudentStatus->ForeColor = Color::FromArgb(100, 149, 237);
    LoadLogsForStudent(studentId, name);
}

System::Void frmAdmin::dgvLogs_SelectionChanged(Object^ sender, EventArgs^ e)
{
    bool has = (dgvLogs->SelectedRows->Count > 0);
    btnDeleteAdminLog->Enabled = has;
    lblLogStatus->Text = has
        ? "Log selected. Click Delete to remove it."
        : "Select a log entry to enable deletion.";
    lblLogStatus->ForeColor = has
        ? Color::FromArgb(220, 160, 80)
        : Color::FromArgb(170, 170, 170);
}

System::Void frmAdmin::btnDeleteStudent_Click(Object^ sender, EventArgs^ e)
{
    if (dgvStudents->SelectedRows->Count == 0) return;

    int    rowIdx = dgvStudents->SelectedRows[0]->Index;
    int    studentId = Int32::Parse(
        dgvStudents->Rows[rowIdx]->Cells["sid"]->Value->ToString());
    String^ name = dgvStudents->Rows[rowIdx]->Cells["name"]->Value->ToString();

    auto res = MessageBox::Show(
        "Permanently delete the account for:\n\n  " + name + "\n\n"
        "This will also delete ALL their wellness logs.\n"
        "This action cannot be undone.",
        "Confirm Delete Student",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Warning);

    if (res != System::Windows::Forms::DialogResult::Yes) return;

    if (dbHelper->DeleteStudent(studentId))
    {
        lblStudentStatus->Text = "Student '" + name + "' deleted successfully.";
        lblStudentStatus->ForeColor = Color::FromArgb(90, 185, 120);
        LoadData();
    }
    else
    {
        lblStudentStatus->Text = "Failed to delete student. Please try again.";
        lblStudentStatus->ForeColor = Color::FromArgb(210, 80, 80);
    }
}

System::Void frmAdmin::btnDeleteAdminLog_Click(Object^ sender, EventArgs^ e)
{
    if (dgvLogs->SelectedRows->Count == 0) return;

    int rowIdx = dgvLogs->SelectedRows[0]->Index;

    Object^ logIdObj = dgvLogs->Rows[rowIdx]->Cells["logid"]->Value;
    if (logIdObj == nullptr) return;

    int     logId = Int32::Parse(logIdObj->ToString());
    String^ dateStr = dgvLogs->Rows[rowIdx]->Cells["date"]->Value->ToString();

    auto res = MessageBox::Show(
        "Delete the wellness log entry for  " + dateStr + "?\n\n"
        "This entry will be permanently removed.",
        "Confirm Delete Log",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Warning);

    if (res != System::Windows::Forms::DialogResult::Yes) return;

    if (dbHelper->DeleteLog(logId))
    {
        lblLogStatus->Text = "Log entry for " + dateStr + " deleted.";
        lblLogStatus->ForeColor = Color::FromArgb(90, 185, 120);

        lblCardLogsVal->Text = dbHelper->GetTotalLogs().ToString();

        if (dgvStudents->SelectedRows->Count > 0)
        {
            int    sIdx = dgvStudents->SelectedRows[0]->Index;
            int    sid = Int32::Parse(
                dgvStudents->Rows[sIdx]->Cells["sid"]->Value->ToString());
            String^ sName = dgvStudents->Rows[sIdx]->Cells["name"]->Value->ToString();
            LoadLogsForStudent(sid, sName);
        }
    }
    else
    {
        lblLogStatus->Text = "Failed to delete log. Please try again.";
        lblLogStatus->ForeColor = Color::FromArgb(210, 80, 80);
    }
}

System::Void frmAdmin::btnRefresh_Click(Object^ sender, EventArgs^ e)
{
    LoadData();
}

System::Void frmAdmin::btnClose_Click(Object^ sender, EventArgs^ e)
{
    this->Close();
}