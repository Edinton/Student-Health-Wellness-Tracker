#include "frmLogEntry.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace SHWT;

frmLogEntry::frmLogEntry(Student^ student)
{
    currentStudent = student;
    dbHelper = gcnew DatabaseHelper();
    InitializeComponent();
}

void frmLogEntry::BuildMetricRow(
    int rowY, int groupW,
    String^ name, String^ hint,
    int minV, int maxV, int defV,
    Label^% outLbl, TrackBar^% outTrk,
    Label^% outVal, Label^% outHint,
    EventHandler^ onChange)
{
    Color clrTextSecond = Color::FromArgb(170, 170, 170);
    Color clrTextPrimary = Color::FromArgb(240, 240, 240);
    Color clrAccent = Color::FromArgb(100, 149, 237);
    Color clrSurface = Color::FromArgb(45, 45, 45);

    
    Drawing::Font^ fLabel = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);
    Drawing::Font^ fVal = gcnew Drawing::Font("Segoe UI", 12.0f, FontStyle::Bold);
    Drawing::Font^ fHint = gcnew Drawing::Font("Segoe UI", 8.0f, FontStyle::Regular);

    const int iX = 16;          
    const int trkW = groupW - iX - 80;   
    const int badgeX = iX + trkW + 6;    

    Label^ lbl = gcnew Label();
    lbl->AutoSize = true;
    lbl->Location = Point(iX, rowY);
    lbl->Text = name;
    lbl->Font = fLabel;
    lbl->ForeColor = clrTextPrimary;
    lbl->BackColor = Color::Transparent;

  
    Label^ val = gcnew Label();
    val->AutoSize = false;
    val->Size = Drawing::Size(58, 28);
    val->Location = Point(badgeX, rowY + 16);
    val->Text = defV.ToString();
    val->Font = fVal;
    val->ForeColor = clrAccent;
    val->BackColor = Color::FromArgb(38, 38, 48);
    val->TextAlign = ContentAlignment::MiddleCenter;

    // TrackBar
    TrackBar^ trk = gcnew TrackBar();
    trk->Minimum = minV;
    trk->Maximum = maxV;
    trk->Value = defV;
    trk->Location = Point(iX, rowY + 18);
    trk->Size = Drawing::Size(trkW, 28);
    trk->TickStyle = TickStyle::None;
    trk->BackColor = clrSurface;
    trk->ValueChanged += onChange;

    // Hint text
    Label^ hnt = gcnew Label();
    hnt->AutoSize = true;
    hnt->Location = Point(iX, rowY + 50);
    hnt->Text = hint;
    hnt->Font = fHint;
    hnt->ForeColor = clrTextSecond;
    hnt->BackColor = Color::Transparent;

    outLbl = lbl;
    outTrk = trk;
    outVal = val;
    outHint = hnt;
    

}

void frmLogEntry::InitializeComponent()
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
    Drawing::Font^ fNote = gcnew Drawing::Font("Segoe UI", 8.5f, FontStyle::Regular);

    pnlHeader = gcnew Panel();
    lblTitle = gcnew Label();
    lblSubtitle = gcnew Label();

    grpDate = gcnew GroupBox();
    lblDatePrompt = gcnew Label();
    dtpDate = gcnew DateTimePicker();
    lblDateNote = gcnew Label();

    grpMetrics = gcnew GroupBox();

    pnlActionBar = gcnew Panel();
    btnSave = gcnew Button();
    btnCancel = gcnew Button();
    lblStatus = gcnew Label();

    this->SuspendLayout();
    pnlHeader->SuspendLayout();
    grpDate->SuspendLayout();
    grpMetrics->SuspendLayout();
    pnlActionBar->SuspendLayout();

    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(560, 72);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblSubtitle);

    lblTitle->AutoSize = true;
    lblTitle->Location = Point(20, 12);
    lblTitle->Text = L"Log Today's Wellness";
    lblTitle->Font = fTitle;
    lblTitle->ForeColor = clrAccent;
    lblTitle->BackColor = Color::Transparent;

    lblSubtitle->AutoSize = true;
    lblSubtitle->Location = Point(22, 44);
    lblSubtitle->Text = L"Use the sliders to record each metric, then click Save Entry.";
    lblSubtitle->Font = fSub;
    lblSubtitle->ForeColor = clrTextSecond;
    lblSubtitle->BackColor = Color::Transparent;

    grpDate->Location = Point(20, 86);
    grpDate->Size = Drawing::Size(518, 80);
    grpDate->Text = L"Entry Date";
    grpDate->Font = fGroup;
    grpDate->ForeColor = clrAccent;
    grpDate->BackColor = clrSurface;

    lblDatePrompt->AutoSize = true;
    lblDatePrompt->Location = Point(16, 28);
    lblDatePrompt->Text = L"Select the date this entry is for:";
    lblDatePrompt->Font = fLabel;
    lblDatePrompt->ForeColor = clrTextSecond;
    lblDatePrompt->BackColor = Color::Transparent;

    dtpDate->Location = Point(16, 46);
    dtpDate->Size = Drawing::Size(220, 24);
    dtpDate->Format = DateTimePickerFormat::Long;
    dtpDate->Font = fBase;
    dtpDate->BackColor = clrInputBg;
    dtpDate->ForeColor = clrTextPrimary;
    dtpDate->MaxDate = DateTime::Today;

    lblDateNote->AutoSize = true;
    lblDateNote->Location = Point(248, 50);
    lblDateNote->Text = L"Note: only one entry per day is allowed.";
    lblDateNote->Font = fNote;
    lblDateNote->ForeColor = Color::FromArgb(130, 130, 130);
    lblDateNote->BackColor = Color::Transparent;

    grpDate->Controls->Add(lblDatePrompt);
    grpDate->Controls->Add(dtpDate);
    grpDate->Controls->Add(lblDateNote);

    const int grpW = 518;
    grpMetrics->Location = Point(20, 178);
    grpMetrics->Size = Drawing::Size(grpW, 436);
    grpMetrics->Text = L"Daily Wellness Metrics";
    grpMetrics->Font = fGroup;
    grpMetrics->ForeColor = clrAccent;
    grpMetrics->BackColor = clrSurface;

    const int rowH = 80;   
    int ry = 28;            

    BuildMetricRow(ry, grpW,
        L"Sleep Hours",
        L"Recommended: 7–9 hours per night.   Range: 0–24",
        0, 24, 7,
        lblSleep, trkSleep, lblSleepVal, lblSleepHint,
        gcnew EventHandler(this, &frmLogEntry::trkSleep_ValueChanged));
    ry += rowH;

    Panel^ sep1 = gcnew Panel();
    sep1->Location = Point(16, ry - 4);
    sep1->Size = Drawing::Size(grpW - 32, 1);
    sep1->BackColor = Color::FromArgb(60, 60, 60);
    grpMetrics->Controls->Add(sep1);

    BuildMetricRow(ry, grpW,
        L"Water Intake (glasses)",
        L"Recommended: at least 8 glasses per day.   Range: 0–20",
        0, 20, 8,
        lblWater, trkWater, lblWaterVal, lblWaterHint,
        gcnew EventHandler(this, &frmLogEntry::trkWater_ValueChanged));
    ry += rowH;

    Panel^ sep2 = gcnew Panel();
    sep2->Location = Point(16, ry - 4);
    sep2->Size = Drawing::Size(grpW - 32, 1);
    sep2->BackColor = Color::FromArgb(60, 60, 60);
    grpMetrics->Controls->Add(sep2);

    BuildMetricRow(ry, grpW,
        L"Exercise Duration (minutes)",
        L"Recommended: at least 30 minutes per day.   Range: 0–180",
        0, 180, 30,
        lblExercise, trkExercise, lblExerciseVal, lblExerciseHint,
        gcnew EventHandler(this, &frmLogEntry::trkExercise_ValueChanged));
    ry += rowH;

    Panel^ sep3 = gcnew Panel();
    sep3->Location = Point(16, ry - 4);
    sep3->Size = Drawing::Size(grpW - 32, 1);
    sep3->BackColor = Color::FromArgb(60, 60, 60);
    grpMetrics->Controls->Add(sep3);

    BuildMetricRow(ry, grpW,
        L"Stress Level",
        L"1 = very calm,   10 = extremely stressed.   Aim to stay below 5.",
        1, 10, 5,
        lblStress, trkStress, lblStressVal, lblStressHint,
        gcnew EventHandler(this, &frmLogEntry::trkStress_ValueChanged));
    ry += rowH;

    Panel^ sep4 = gcnew Panel();
    sep4->Location = Point(16, ry - 4);
    sep4->Size = Drawing::Size(grpW - 32, 1);
    sep4->BackColor = Color::FromArgb(60, 60, 60);
    grpMetrics->Controls->Add(sep4);

    BuildMetricRow(ry, grpW,
        L"Mood Rating",
        L"1 = very low,   5 = excellent.   Try to keep above 3.",
        1, 5, 3,
        lblMood, trkMood, lblMoodVal, lblMoodHint,
        gcnew EventHandler(this, &frmLogEntry::trkMood_ValueChanged));

    grpMetrics->Controls->Add(lblSleep);
    grpMetrics->Controls->Add(trkSleep);
    grpMetrics->Controls->Add(lblSleepVal);
    grpMetrics->Controls->Add(lblSleepHint);
    grpMetrics->Controls->Add(lblWater);
    grpMetrics->Controls->Add(trkWater);
    grpMetrics->Controls->Add(lblWaterVal);
    grpMetrics->Controls->Add(lblWaterHint);
    grpMetrics->Controls->Add(lblExercise);
    grpMetrics->Controls->Add(trkExercise);
    grpMetrics->Controls->Add(lblExerciseVal);
    grpMetrics->Controls->Add(lblExerciseHint);
    grpMetrics->Controls->Add(lblStress);
    grpMetrics->Controls->Add(trkStress);
    grpMetrics->Controls->Add(lblStressVal);
    grpMetrics->Controls->Add(lblStressHint);
    grpMetrics->Controls->Add(lblMood);
    grpMetrics->Controls->Add(trkMood);
    grpMetrics->Controls->Add(lblMoodVal);
    grpMetrics->Controls->Add(lblMoodHint);

    pnlActionBar->Location = Point(0, 628);
    pnlActionBar->Size = Drawing::Size(560, 60);
    pnlActionBar->BackColor = Color::FromArgb(38, 38, 38);
    pnlActionBar->Controls->Add(lblStatus);
    pnlActionBar->Controls->Add(btnSave);
    pnlActionBar->Controls->Add(btnCancel);

    lblStatus->AutoSize = false;
    lblStatus->Size = Drawing::Size(230, 24);
    lblStatus->Location = Point(20, 18);
    lblStatus->Text = L"";
    lblStatus->Font = fLabel;
    lblStatus->ForeColor = clrDanger;
    lblStatus->BackColor = Color::Transparent;
    lblStatus->TextAlign = ContentAlignment::MiddleLeft;

    btnSave->Location = Point(268, 12);
    btnSave->Size = Drawing::Size(140, 36);
    btnSave->Text = L"Save Entry";
    btnSave->Font = fBtn;
    btnSave->BackColor = clrAccent;
    btnSave->ForeColor = Color::White;
    btnSave->FlatStyle = FlatStyle::Flat;
    btnSave->FlatAppearance->BorderSize = 0;
    btnSave->Cursor = Cursors::Hand;
    btnSave->Click += gcnew EventHandler(
        this, &frmLogEntry::btnSave_Click);

    btnCancel->Location = Point(418, 12);
    btnCancel->Size = Drawing::Size(120, 36);
    btnCancel->Text = L"Cancel";
    btnCancel->Font = fBtn;
    btnCancel->BackColor = Color::FromArgb(55, 55, 55);
    btnCancel->ForeColor = clrTextSecond;
    btnCancel->FlatStyle = FlatStyle::Flat;
    btnCancel->FlatAppearance->BorderSize = 1;
    btnCancel->FlatAppearance->BorderColor = clrBorder;
    btnCancel->Cursor = Cursors::Hand;
    btnCancel->Click += gcnew EventHandler(
        this, &frmLogEntry::btnCancel_Click);

    this->AutoScaleDimensions = Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(560, 688);
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->StartPosition = FormStartPosition::CenterParent;
    this->Text = L"SHWT – Log Wellness Entry";
    this->Controls->Add(pnlHeader);
    this->Controls->Add(grpDate);
    this->Controls->Add(grpMetrics);
    this->Controls->Add(pnlActionBar);

    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    grpDate->ResumeLayout(false);
    grpDate->PerformLayout();
    grpMetrics->ResumeLayout(false);
    pnlActionBar->ResumeLayout(false);
    this->ResumeLayout(false);
    

}

System::Void frmLogEntry::trkSleep_ValueChanged(Object^ sender, EventArgs^ e)
{
    lblSleepVal->Text = trkSleep->Value.ToString();
}
System::Void frmLogEntry::trkWater_ValueChanged(Object^ sender, EventArgs^ e)
{
    lblWaterVal->Text = trkWater->Value.ToString();
}
System::Void frmLogEntry::trkExercise_ValueChanged(Object^ sender, EventArgs^ e)
{
    lblExerciseVal->Text = trkExercise->Value.ToString();
}
System::Void frmLogEntry::trkStress_ValueChanged(Object^ sender, EventArgs^ e)
{
    int v = trkStress->Value;
    lblStressVal->Text = v.ToString();
   
    if (v <= 4) lblStressVal->ForeColor = Color::FromArgb(90, 185, 120);
    else if (v <= 7) lblStressVal->ForeColor = Color::FromArgb(220, 160, 50);
    else             lblStressVal->ForeColor = Color::FromArgb(210, 80, 80);
}
System::Void frmLogEntry::trkMood_ValueChanged(Object^ sender, EventArgs^ e)
{
    int v = trkMood->Value;
    lblMoodVal->Text = v.ToString();
   
    if (v >= 4) lblMoodVal->ForeColor = Color::FromArgb(90, 185, 120);
    else if (v >= 3) lblMoodVal->ForeColor = Color::FromArgb(220, 160, 50);
    else             lblMoodVal->ForeColor = Color::FromArgb(210, 80, 80);
}

System::Void frmLogEntry::btnSave_Click(Object^ sender, EventArgs^ e)
{
    lblStatus->Text = L"";

    
        if (dbHelper->LogExistsForDate(
            currentStudent->StudentId, dtpDate->Value))
        {
            lblStatus->Text = L"A log already exists for this date.";
            return;
        }

    HealthLog^ log = gcnew HealthLog();
    log->StudentId = currentStudent->StudentId;
    log->EntryDate = dtpDate->Value;
    log->SleepHours = trkSleep->Value;
    log->WaterGlasses = trkWater->Value;
    log->ExerciseMins = trkExercise->Value;
    log->StressLevel = trkStress->Value;
    log->MoodRating = trkMood->Value;

    if (!log->ValidateData())
    {
        lblStatus->Text = L"Invalid data detected. Please check your entries.";
        return;
    }

    if (dbHelper->AddHealthLog(log))
    {
        MessageBox::Show(
            "Wellness entry saved successfully!\n\n"
            "Overall Wellness: " + log->GetWellnessSummary(),
            "Entry Saved",
            MessageBoxButtons::OK,
            MessageBoxIcon::Information);

        this->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Close();
    }
    else
    {
        lblStatus->Text = L"Failed to save entry. Please try again.";
    }
    

}

System::Void frmLogEntry::btnCancel_Click(Object^ sender, EventArgs^ e)
{
    this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
    this->Close();
}