#include "frmHistory.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace SHWT;

frmHistory::frmHistory(Student^ student)
{
    currentStudent = student;
    dbHelper = gcnew DatabaseHelper();
    logList = gcnew List<HealthLog^>();
    InitializeComponent();
    LoadHistory();
}

void frmHistory::AddTile(Label^ lbl, String^ txt, Label^ val, int x)
{
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Drawing::Font^ fSumLbl = gcnew Drawing::Font("Segoe UI", 8.5f, FontStyle::Regular);
    Drawing::Font^ fSumVal = gcnew Drawing::Font("Segoe UI", 13.0f, FontStyle::Bold);

    lbl->AutoSize = true;
    lbl->Location = Point(x, 8);
    lbl->Text = txt;
    lbl->Font = fSumLbl;
    lbl->ForeColor = clrTextSecond;
    lbl->BackColor = Color::Transparent;

    val->AutoSize = true;
    val->Location = Point(x, 26);
    val->Text = L"—";
    val->Font = fSumVal;
    val->ForeColor = clrTextPrimary;
    val->BackColor = Color::Transparent;

    pnlSummaryBar->Controls->Add(lbl);
    pnlSummaryBar->Controls->Add(val);
}

void frmHistory::StyleGrid()
{
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrAltRow = Color::FromArgb(52, 52, 52);
    Color clrHeader = Color::FromArgb(35, 35, 35);

    dgvHistory->BackgroundColor = clrSurface;
    dgvHistory->GridColor = Color::FromArgb(58, 58, 58);
    dgvHistory->BorderStyle = BorderStyle::None;

    dgvHistory->RowHeadersVisible = false;
    dgvHistory->AllowUserToAddRows = false;
    dgvHistory->AllowUserToDeleteRows = false;
    dgvHistory->ReadOnly = true;
    dgvHistory->MultiSelect = false;
    dgvHistory->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
    dgvHistory->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

    dgvHistory->Font =
        gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);

    //Default cell style
    dgvHistory->DefaultCellStyle->BackColor = clrSurface;
    dgvHistory->DefaultCellStyle->ForeColor = clrTextPrimary;
    dgvHistory->DefaultCellStyle->SelectionBackColor = clrAccent;
    dgvHistory->DefaultCellStyle->SelectionForeColor = Color::White;
    dgvHistory->DefaultCellStyle->Padding =
        System::Windows::Forms::Padding(4, 0, 4, 0);

    //Alternating row
    dgvHistory->AlternatingRowsDefaultCellStyle->BackColor = clrAltRow;

    //Column headers
    dgvHistory->ColumnHeadersDefaultCellStyle->BackColor = clrHeader;
    dgvHistory->ColumnHeadersDefaultCellStyle->ForeColor = clrAccent;
    dgvHistory->ColumnHeadersDefaultCellStyle->Font =
        gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);
    dgvHistory->ColumnHeadersDefaultCellStyle->Padding =
        System::Windows::Forms::Padding(6, 0, 0, 0);
    dgvHistory->ColumnHeadersHeightSizeMode =
        DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
    dgvHistory->ColumnHeadersHeight = 34;
    dgvHistory->RowTemplate->Height = 28;

    dgvHistory->EnableHeadersVisualStyles = false;
}

void frmHistory::InitializeComponent()
{
    Color clrFormBg = Color::FromArgb(30, 30, 30);
    Color clrSurface = Color::FromArgb(45, 45, 45);
    Color clrHeader = Color::FromArgb(28, 28, 28);
    Color clrSummary = Color::FromArgb(38, 38, 38);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrDanger = Color::FromArgb(190, 60, 60);
    Color clrBorder = Color::FromArgb(75, 75, 75);

    Drawing::Font^ fTitle = gcnew Drawing::Font("Segoe UI", 13.0f, FontStyle::Bold);
    Drawing::Font^ fSub = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);
    Drawing::Font^ fGroup = gcnew Drawing::Font("Segoe UI", 10.0f, FontStyle::Bold);
    Drawing::Font^ fBase = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);

    pnlHeader = gcnew Panel();
    lblTitle = gcnew Label();
    lblSubtitle = gcnew Label();

    pnlSummaryBar = gcnew Panel();
    lblTotalEntries = gcnew Label();
    lblTotalEntriesVal = gcnew Label();
    lblAvgSleep = gcnew Label();
    lblAvgSleepVal = gcnew Label();
    lblAvgMood = gcnew Label();
    lblAvgMoodVal = gcnew Label();

    grpHistory = gcnew GroupBox();
    dgvHistory = gcnew DataGridView();

    pnlActionBar = gcnew Panel();
    btnDeleteLog = gcnew Button();
    btnRefresh = gcnew Button();
    btnClose = gcnew Button();
    lblActionStatus = gcnew Label();

    this->SuspendLayout();
    pnlHeader->SuspendLayout();
    pnlSummaryBar->SuspendLayout();
    grpHistory->SuspendLayout();
    pnlActionBar->SuspendLayout();
    ((System::ComponentModel::ISupportInitialize^)(dgvHistory))->BeginInit();

    //Header 
    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(860, 72);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblSubtitle);

    lblTitle->AutoSize = true;
    lblTitle->Location = Point(20, 12);
    lblTitle->Text = L"Wellness History  —  " + currentStudent->FullName;
    lblTitle->Font = fTitle;
    lblTitle->ForeColor = clrAccent;
    lblTitle->BackColor = Color::Transparent;

    lblSubtitle->AutoSize = true;
    lblSubtitle->Location = Point(22, 44);
    lblSubtitle->Text = L"All recorded wellness entries, newest first. Select a row and click Delete to remove it.";
    lblSubtitle->Font = fSub;
    lblSubtitle->ForeColor = clrTextSecond;
    lblSubtitle->BackColor = Color::Transparent;

    //Summary bar
    pnlSummaryBar->Location = Point(0, 72);
    pnlSummaryBar->Size = Drawing::Size(860, 56);
    pnlSummaryBar->BackColor = clrSummary;

    AddTile(lblTotalEntries, L"Total Entries", lblTotalEntriesVal, 24);
    AddTile(lblAvgSleep, L"Avg Sleep (hrs)", lblAvgSleepVal, 180);
    AddTile(lblAvgMood, L"Avg Mood (1–5)", lblAvgMoodVal, 340);

    //History group
    grpHistory->Location = Point(16, 140);
    grpHistory->Size = Drawing::Size(826, 440);
    grpHistory->Text = L"Wellness Log";
    grpHistory->Font = fGroup;
    grpHistory->ForeColor = clrAccent;
    grpHistory->BackColor = clrSurface;

    dgvHistory->Location = Point(12, 28);
    dgvHistory->Size = Drawing::Size(800, 400);
    StyleGrid();
    dgvHistory->SelectionChanged += gcnew EventHandler(
        this, &frmHistory::dgvHistory_SelectionChanged);

    grpHistory->Controls->Add(dgvHistory);

    pnlActionBar->Location = Point(0, 594);
    pnlActionBar->Size = Drawing::Size(860, 56);
    pnlActionBar->BackColor = Color::FromArgb(38, 38, 38);

    lblActionStatus->AutoSize = false;
    lblActionStatus->Size = Drawing::Size(340, 24);
    lblActionStatus->Location = Point(20, 16);
    lblActionStatus->Text = L"Select a row to enable deletion.";
    lblActionStatus->Font = fBase;
    lblActionStatus->ForeColor = clrTextSecond;
    lblActionStatus->BackColor = Color::Transparent;
    lblActionStatus->TextAlign = ContentAlignment::MiddleLeft;

    btnDeleteLog->Location = Point(380, 10);
    btnDeleteLog->Size = Drawing::Size(160, 36);
    btnDeleteLog->Text = L"Delete Selected Log";
    btnDeleteLog->Font = fBtn;
    btnDeleteLog->BackColor = Color::FromArgb(130, 40, 40);
    btnDeleteLog->ForeColor = Color::FromArgb(255, 200, 200);
    btnDeleteLog->FlatStyle = FlatStyle::Flat;
    btnDeleteLog->FlatAppearance->BorderSize = 1;
    btnDeleteLog->FlatAppearance->BorderColor = Color::FromArgb(180, 60, 60);
    btnDeleteLog->Cursor = Cursors::Hand;
    btnDeleteLog->Enabled = false;
    btnDeleteLog->Click += gcnew EventHandler(
        this, &frmHistory::btnDeleteLog_Click);

    btnRefresh->Location = Point(552, 10);
    btnRefresh->Size = Drawing::Size(120, 36);
    btnRefresh->Text = L"Refresh";
    btnRefresh->Font = fBtn;
    btnRefresh->BackColor = Color::FromArgb(55, 75, 110);
    btnRefresh->ForeColor = Color::White;
    btnRefresh->FlatStyle = FlatStyle::Flat;
    btnRefresh->FlatAppearance->BorderSize = 0;
    btnRefresh->Cursor = Cursors::Hand;
    btnRefresh->Click += gcnew EventHandler(
        this, &frmHistory::btnRefresh_Click);

    btnClose->Location = Point(684, 10);
    btnClose->Size = Drawing::Size(156, 36);
    btnClose->Text = L"Close";
    btnClose->Font = fBtn;
    btnClose->BackColor = Color::FromArgb(55, 55, 55);
    btnClose->ForeColor = clrTextSecond;
    btnClose->FlatStyle = FlatStyle::Flat;
    btnClose->FlatAppearance->BorderSize = 1;
    btnClose->FlatAppearance->BorderColor = clrBorder;
    btnClose->Cursor = Cursors::Hand;
    btnClose->Click += gcnew EventHandler(
        this, &frmHistory::btnClose_Click);

    pnlActionBar->Controls->Add(lblActionStatus);
    pnlActionBar->Controls->Add(btnDeleteLog);
    pnlActionBar->Controls->Add(btnRefresh);
    pnlActionBar->Controls->Add(btnClose);

    this->AutoScaleDimensions = Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(860, 650);
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->StartPosition = FormStartPosition::CenterParent;
    this->Text = L"SHWT – Wellness History";
    this->Controls->Add(pnlHeader);
    this->Controls->Add(pnlSummaryBar);
    this->Controls->Add(grpHistory);
    this->Controls->Add(pnlActionBar);

    ((System::ComponentModel::ISupportInitialize^)(dgvHistory))->EndInit();
    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    pnlSummaryBar->ResumeLayout(false);
    pnlSummaryBar->PerformLayout();
    grpHistory->ResumeLayout(false);
    pnlActionBar->ResumeLayout(false);
    this->ResumeLayout(false);
}

void frmHistory::LoadHistory()
{
    dgvHistory->Rows->Clear();
    dgvHistory->Columns->Clear();
    logList->Clear();
    btnDeleteLog->Enabled = false;
    lblActionStatus->Text = L"Select a row to enable deletion.";
    lblActionStatus->ForeColor = Color::FromArgb(170, 170, 170);

    dgvHistory->Columns->Add("date", "Date");
    dgvHistory->Columns->Add("sleep", "Sleep (hrs)");
    dgvHistory->Columns->Add("water", "Water (glasses)");
    dgvHistory->Columns->Add("exercise", "Exercise (mins)");
    dgvHistory->Columns->Add("stress", "Stress (1–10)");
    dgvHistory->Columns->Add("mood", "Mood (1–5)");
    dgvHistory->Columns->Add("summary", "Wellness Rating");

    List<HealthLog^>^ logs =
        dbHelper->GetLogsForStudent(currentStudent->StudentId);

    for each (HealthLog ^ log in logs)
    {
        logList->Add(log);
        array<Object^>^ row = {
            log->EntryDate.ToString("dd MMM yyyy"),
            log->SleepHours.ToString(),
            log->WaterGlasses.ToString(),
            log->ExerciseMins.ToString(),
            log->StressLevel.ToString(),
            log->MoodRating.ToString(),
            log->GetWellnessSummary()
        };
        dgvHistory->Rows->Add(row);
    }

    UpdateSummaryBar();
}

void frmHistory::UpdateSummaryBar()
{
    int n = logList->Count;
    lblTotalEntriesVal->Text = n.ToString();

    if (n == 0)
    {
        lblAvgSleepVal->Text = L"—";
        lblAvgMoodVal->Text = L"—";
        return;
    }

    double totalSleep = 0, totalMood = 0;
    for each (HealthLog ^ log in logList)
    {
        totalSleep += log->SleepHours;
        totalMood += log->MoodRating;
    }

    lblAvgSleepVal->Text = String::Format("{0:F1}", totalSleep / n);
    lblAvgMoodVal->Text = String::Format("{0:F1}", totalMood / n);
}

System::Void frmHistory::dgvHistory_SelectionChanged(Object^ sender, EventArgs^ e)
{
    bool hasSelection = (dgvHistory->SelectedRows->Count > 0);
    btnDeleteLog->Enabled = hasSelection;
    lblActionStatus->Text = hasSelection
        ? L"Row selected. Click 'Delete Selected Log' to remove it."
        : L"Select a row to enable deletion.";
    lblActionStatus->ForeColor = hasSelection
        ? Color::FromArgb(220, 160, 80)
        : Color::FromArgb(170, 170, 170);
}

System::Void frmHistory::btnDeleteLog_Click(Object^ sender, EventArgs^ e)
{
    if (dgvHistory->SelectedRows->Count == 0) return;

    int rowIdx = dgvHistory->SelectedRows[0]->Index;
    if (rowIdx < 0 || rowIdx >= logList->Count) return;

    HealthLog^ selected = logList[rowIdx];
    String^ dateStr = selected->EntryDate.ToString("dd MMM yyyy");

    System::Windows::Forms::DialogResult res = MessageBox::Show(
        "Delete the wellness log for  " + dateStr + "?\n\n"
        "This entry will be permanently removed and cannot be recovered.",
        "Confirm Delete Log",
        MessageBoxButtons::YesNo,
        MessageBoxIcon::Warning);

    if (res != System::Windows::Forms::DialogResult::Yes) return;

    if (dbHelper->DeleteLog(selected->LogId))
    {
        lblActionStatus->Text = L"Log entry for " + dateStr + " deleted successfully.";
        lblActionStatus->ForeColor = Color::FromArgb(90, 185, 120);
        LoadHistory();
    }
    else
    {
        lblActionStatus->Text = L"Failed to delete the log. Please try again.";
        lblActionStatus->ForeColor = Color::FromArgb(210, 80, 80);
    }
}

System::Void frmHistory::btnRefresh_Click(Object^ sender, EventArgs^ e)
{
    LoadHistory();
    lblActionStatus->Text = L"Data refreshed.";
    lblActionStatus->ForeColor = Color::FromArgb(90, 185, 120);
}

System::Void frmHistory::btnClose_Click(Object^ sender, EventArgs^ e)
{
    this->Close();
}