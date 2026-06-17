#include "frmReport.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace SHWT;

frmReport::frmReport(Student^ student)
{
    currentStudent = student;
    dbHelper = gcnew DatabaseHelper();
    InitializeComponent();
}

void frmReport::ResetLabel(Label^ l)
{
    l->Text = L"—";
}

Button^ frmReport::MakePreset(String^ text, int x, EventHandler^ click)
{
    Drawing::Font^ fBtn = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Bold);
    Button^ b = gcnew Button();
    b->Location = Point(x, 80);
    b->Size = Drawing::Size(80, 26);
    b->Text = text;
    b->Font = fBtn;
    b->BackColor = Color::FromArgb(55, 75, 110);
    b->ForeColor = Color::White;
    b->FlatStyle = FlatStyle::Flat;
    b->FlatAppearance->BorderSize = 0;
    b->Cursor = Cursors::Hand;
    b->Click += click;
    return b;
}

void frmReport::AddStatRow(GroupBox^ grp, Label^ lbl, String^ text,
    Label^ val, int y,
    Drawing::Font^ vFont, Color vColor)
{
    Color clrTextSecond = Color::FromArgb(170, 170, 170);

    Drawing::Font^ fLabel = gcnew Drawing::Font("Segoe UI", 9.5f, FontStyle::Regular);

    lbl->AutoSize = true;
    lbl->Location = Point(16, y);
    lbl->Text = text;
    lbl->Font = fLabel;
    lbl->ForeColor = clrTextSecond;
    lbl->BackColor = Color::Transparent;

    val->AutoSize = false;
    val->Size = Drawing::Size(200, 24);
    val->Location = Point(358, y - 2);
    val->Text = L"—";
    val->Font = vFont;
    val->ForeColor = vColor;
    val->BackColor = Color::Transparent;
    val->TextAlign = ContentAlignment::MiddleRight;

    grp->Controls->Add(lbl);
    grp->Controls->Add(val);
}

void frmReport::InitializeComponent()
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
    Drawing::Font^ fValMed = gcnew Drawing::Font("Segoe UI", 11.0f, FontStyle::Bold);
    Drawing::Font^ fValBig = gcnew Drawing::Font("Segoe UI", 26.0f, FontStyle::Bold);
    Drawing::Font^ fRatDesc = gcnew Drawing::Font("Segoe UI", 9.0f, FontStyle::Regular);

    pnlHeader = gcnew Panel();
    lblTitle = gcnew Label();
    lblSubtitle = gcnew Label();

    grpRange = gcnew GroupBox();
    lblFromPrompt = gcnew Label();
    dtpFrom = gcnew DateTimePicker();
    lblToPrompt = gcnew Label();
    dtpTo = gcnew DateTimePicker();
    lblPresetPrompt = gcnew Label();
    btnPreset7 = gcnew Button();
    btnPreset30 = gcnew Button();
    btnPreset90 = gcnew Button();
    btnGenerate = gcnew Button();

    grpResults = gcnew GroupBox();
    lblAvgSleep = gcnew Label();  lblAvgSleepVal = gcnew Label();
    lblAvgWater = gcnew Label();  lblAvgWaterVal = gcnew Label();
    lblAvgExercise = gcnew Label();  lblAvgExerciseVal = gcnew Label();
    lblAvgStress = gcnew Label();  lblAvgStressVal = gcnew Label();
    lblAvgMood = gcnew Label();  lblAvgMoodVal = gcnew Label();
    lblEntries = gcnew Label();  lblEntriesVal = gcnew Label();
    lblDateRange = gcnew Label();  lblDateRangeVal = gcnew Label();

    pnlRating = gcnew Panel();
    lblRatingTitle = gcnew Label();
    lblRatingVal = gcnew Label();
    lblRatingDesc = gcnew Label();

    pnlActionBar = gcnew Panel();
    btnClose = gcnew Button();
    lblResultStatus = gcnew Label();

    this->SuspendLayout();
    pnlHeader->SuspendLayout();
    grpRange->SuspendLayout();
    grpResults->SuspendLayout();
    pnlRating->SuspendLayout();
    pnlActionBar->SuspendLayout();

    //Header
    pnlHeader->Location = Point(0, 0);
    pnlHeader->Size = Drawing::Size(640, 72);
    pnlHeader->BackColor = clrHeader;
    pnlHeader->Controls->Add(lblTitle);
    pnlHeader->Controls->Add(lblSubtitle);

    lblTitle->AutoSize = true;
    lblTitle->Location = Point(20, 12);
    lblTitle->Text = L"Health Report  —  " + currentStudent->FullName;
    lblTitle->Font = fTitle;
    lblTitle->ForeColor = clrAccent;
    lblTitle->BackColor = Color::Transparent;

    lblSubtitle->AutoSize = true;
    lblSubtitle->Location = Point(22, 44);
    lblSubtitle->Text = L"Select a date range and generate your personalised wellness summary.";
    lblSubtitle->Font = fSub;
    lblSubtitle->ForeColor = clrTextSecond;
    lblSubtitle->BackColor = Color::Transparent;

    //Date range group
    grpRange->Location = Point(16, 86);
    grpRange->Size = Drawing::Size(606, 122);
    grpRange->Text = L"Report Period";
    grpRange->Font = fGroup;
    grpRange->ForeColor = clrAccent;
    grpRange->BackColor = clrSurface;

    lblFromPrompt->AutoSize = true;
    lblFromPrompt->Location = Point(16, 28);
    lblFromPrompt->Text = L"From";
    lblFromPrompt->Font = fLabel;
    lblFromPrompt->ForeColor = clrTextSecond;
    lblFromPrompt->BackColor = Color::Transparent;

    dtpFrom->Location = Point(16, 46);
    dtpFrom->Size = Drawing::Size(190, 24);
    dtpFrom->Format = DateTimePickerFormat::Short;
    dtpFrom->Font = fBase;
    dtpFrom->BackColor = clrInputBg;
    dtpFrom->ForeColor = clrTextPrimary;
    dtpFrom->MaxDate = DateTime::Today;
    dtpFrom->Value = DateTime::Today.AddDays(-30);

    lblToPrompt->AutoSize = true;
    lblToPrompt->Location = Point(222, 28);
    lblToPrompt->Text = L"To";
    lblToPrompt->Font = fLabel;
    lblToPrompt->ForeColor = clrTextSecond;
    lblToPrompt->BackColor = Color::Transparent;

    dtpTo->Location = Point(222, 46);
    dtpTo->Size = Drawing::Size(190, 24);
    dtpTo->Format = DateTimePickerFormat::Short;
    dtpTo->Font = fBase;
    dtpTo->BackColor = clrInputBg;
    dtpTo->ForeColor = clrTextPrimary;
    dtpTo->MaxDate = DateTime::Today;
    dtpTo->Value = DateTime::Today;

    // Generate button
    btnGenerate->Location = Point(430, 42);
    btnGenerate->Size = Drawing::Size(162, 32);
    btnGenerate->Text = L"Generate Report";
    btnGenerate->Font = fBtn;
    btnGenerate->BackColor = clrAccent;
    btnGenerate->ForeColor = Color::White;
    btnGenerate->FlatStyle = FlatStyle::Flat;
    btnGenerate->FlatAppearance->BorderSize = 0;
    btnGenerate->Cursor = Cursors::Hand;
    btnGenerate->Click += gcnew EventHandler(
        this, &frmReport::btnGenerate_Click);

    // Quick-preset buttons
    lblPresetPrompt->AutoSize = true;
    lblPresetPrompt->Location = Point(16, 84);
    lblPresetPrompt->Text = L"Quick presets:";
    lblPresetPrompt->Font = fLabel;
    lblPresetPrompt->ForeColor = clrTextSecond;
    lblPresetPrompt->BackColor = Color::Transparent;

    btnPreset7 = MakePreset(L"Last 7 days", 110,
        gcnew EventHandler(this, &frmReport::btnPreset7_Click));
    btnPreset30 = MakePreset(L"Last 30 days", 200,
        gcnew EventHandler(this, &frmReport::btnPreset30_Click));
    btnPreset90 = MakePreset(L"Last 90 days", 290,
        gcnew EventHandler(this, &frmReport::btnPreset90_Click));

    grpRange->Controls->Add(lblFromPrompt);
    grpRange->Controls->Add(dtpFrom);
    grpRange->Controls->Add(lblToPrompt);
    grpRange->Controls->Add(dtpTo);
    grpRange->Controls->Add(btnGenerate);
    grpRange->Controls->Add(lblPresetPrompt);
    grpRange->Controls->Add(btnPreset7);
    grpRange->Controls->Add(btnPreset30);
    grpRange->Controls->Add(btnPreset90);

    //Results group
    grpResults->Location = Point(16, 222);
    grpResults->Size = Drawing::Size(606, 290);
    grpResults->Text = L"Wellness Summary";
    grpResults->Font = fGroup;
    grpResults->ForeColor = clrAccent;
    grpResults->BackColor = clrSurface;

    int ry = 28;
    const int rowStep = 34;
    Color cNeutral = Color::FromArgb(200, 200, 200);
    Color cGreen = Color::FromArgb(90, 185, 120);
    Color cRed = Color::FromArgb(210, 80, 80);
    Color cBlue = Color::FromArgb(100, 149, 237);

    AddStatRow(grpResults, lblDateRange, L"Period Covered:", lblDateRangeVal, ry, fValMed, cBlue);    ry += rowStep;
    AddStatRow(grpResults, lblEntries, L"Total Log Entries:", lblEntriesVal, ry, fValMed, cNeutral); ry += rowStep;

    Panel^ sep = gcnew Panel();
    sep->Location = Point(16, ry + 4);
    sep->Size = Drawing::Size(570, 1);
    sep->BackColor = Color::FromArgb(62, 62, 62);
    grpResults->Controls->Add(sep);
    ry += 14;

    AddStatRow(grpResults, lblAvgSleep, L"Average Sleep:", lblAvgSleepVal, ry, fValMed, cNeutral); ry += rowStep;
    AddStatRow(grpResults, lblAvgWater, L"Average Water:", lblAvgWaterVal, ry, fValMed, cNeutral); ry += rowStep;
    AddStatRow(grpResults, lblAvgExercise, L"Average Exercise:", lblAvgExerciseVal, ry, fValMed, cNeutral); ry += rowStep;
    AddStatRow(grpResults, lblAvgStress, L"Average Stress:", lblAvgStressVal, ry, fValMed, cRed);     ry += rowStep;
    AddStatRow(grpResults, lblAvgMood, L"Average Mood:", lblAvgMoodVal, ry, fValMed, cGreen);

    //Rating panel
    pnlRating->Location = Point(16, 526);
    pnlRating->Size = Drawing::Size(606, 72);
    pnlRating->BackColor = Color::FromArgb(38, 48, 68);
    pnlRating->Controls->Add(lblRatingTitle);
    pnlRating->Controls->Add(lblRatingVal);
    pnlRating->Controls->Add(lblRatingDesc);

    lblRatingTitle->AutoSize = true;
    lblRatingTitle->Location = Point(16, 8);
    lblRatingTitle->Text = L"Overall Wellness Rating";
    lblRatingTitle->Font = fLabel;
    lblRatingTitle->ForeColor = clrTextSecond;
    lblRatingTitle->BackColor = Color::Transparent;

    lblRatingVal->AutoSize = true;
    lblRatingVal->Location = Point(16, 26);
    lblRatingVal->Text = L"Generate a report to see your rating.";
    lblRatingVal->Font = fValMed;
    lblRatingVal->ForeColor = clrAccent;
    lblRatingVal->BackColor = Color::Transparent;

    lblRatingDesc->AutoSize = true;
    lblRatingDesc->Location = Point(320, 30);
    lblRatingDesc->Text = L"";
    lblRatingDesc->Font = fRatDesc;
    lblRatingDesc->ForeColor = clrTextSecond;
    lblRatingDesc->BackColor = Color::Transparent;

    pnlActionBar->Location = Point(0, 612);
    pnlActionBar->Size = Drawing::Size(640, 52);
    pnlActionBar->BackColor = Color::FromArgb(38, 38, 38);
    pnlActionBar->Controls->Add(lblResultStatus);
    pnlActionBar->Controls->Add(btnClose);

    lblResultStatus->AutoSize = false;
    lblResultStatus->Size = Drawing::Size(440, 24);
    lblResultStatus->Location = Point(16, 14);
    lblResultStatus->Text = L"";
    lblResultStatus->Font = fBase;
    lblResultStatus->ForeColor = clrDanger;
    lblResultStatus->BackColor = Color::Transparent;
    lblResultStatus->TextAlign = ContentAlignment::MiddleLeft;

    btnClose->Location = Point(488, 8);
    btnClose->Size = Drawing::Size(130, 36);
    btnClose->Text = L"Close";
    btnClose->Font = fBtn;
    btnClose->BackColor = Color::FromArgb(55, 55, 55);
    btnClose->ForeColor = clrTextSecond;
    btnClose->FlatStyle = FlatStyle::Flat;
    btnClose->FlatAppearance->BorderSize = 1;
    btnClose->FlatAppearance->BorderColor = Color::FromArgb(75, 75, 75);
    btnClose->Cursor = Cursors::Hand;
    btnClose->Click += gcnew EventHandler(
        this, &frmReport::btnClose_Click);

    this->AutoScaleDimensions = Drawing::SizeF(6, 13);
    this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
    this->ClientSize = Drawing::Size(640, 664);
    this->BackColor = clrFormBg;
    this->ForeColor = clrTextPrimary;
    this->Font = fBase;
    this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
    this->MaximizeBox = false;
    this->StartPosition = FormStartPosition::CenterParent;
    this->Text = L"SHWT – Health Report";
    this->Controls->Add(pnlHeader);
    this->Controls->Add(grpRange);
    this->Controls->Add(grpResults);
    this->Controls->Add(pnlRating);
    this->Controls->Add(pnlActionBar);

    pnlHeader->ResumeLayout(false);
    pnlHeader->PerformLayout();
    grpRange->ResumeLayout(false);
    grpResults->ResumeLayout(false);
    pnlRating->ResumeLayout(false);
    pnlActionBar->ResumeLayout(false);
    this->ResumeLayout(false);
}

void frmReport::SetDatePreset(int days)
{
    dtpFrom->Value = DateTime::Today.AddDays(-days);
    dtpTo->Value = DateTime::Today;
}

String^ frmReport::GetOverallRating(double avgSleep, double avgWater,
    double avgExercise, double avgStress,
    double avgMood, String^% outDesc)
{
    int score = 0;
    if (avgSleep >= 7)  score++;
    if (avgWater >= 8)  score++;
    if (avgExercise >= 30) score++;
    if (avgStress <= 4)  score++;
    if (avgMood >= 4)  score++;

    if (score == 5)
    {
        outDesc = L"All 5 metrics meet recommended targets. Keep it up!";
        return L"Excellent";
    }
    if (score >= 3)
    {
        outDesc = L"Most metrics are on track. Small improvements will help.";
        return L"Good";
    }
    if (score >= 2)
    {
        outDesc = L"Some metrics need attention. Focus on sleep and hydration first.";
        return L"Fair";
    }
    outDesc = L"Several metrics are below target. Consider speaking to a wellness advisor.";
    return L"Needs Improvement";
}

void frmReport::GenerateReport()
{
    lblResultStatus->Text = L"";

    if (dtpFrom->Value.Date > dtpTo->Value.Date)
    {
        lblResultStatus->Text = L"'From' date must be on or before 'To' date.";
        return;
    }

    List<HealthLog^>^ logs = dbHelper->GetLogsInRange(
        currentStudent->StudentId,
        dtpFrom->Value, dtpTo->Value);

    // Reset all value labels
    ResetLabel(lblAvgSleepVal); ResetLabel(lblAvgWaterVal);
    ResetLabel(lblAvgExerciseVal); ResetLabel(lblAvgStressVal);
    ResetLabel(lblAvgMoodVal); ResetLabel(lblEntriesVal);
    ResetLabel(lblDateRangeVal);
    lblRatingVal->Text = L"No data available for this period.";
    lblRatingDesc->Text = L"";

    if (logs->Count == 0)
    {
        lblResultStatus->Text = L"No entries found for the selected period.";
        return;
    }

    double tSleep = 0, tWater = 0, tEx = 0, tStr = 0, tMood = 0;
    for each (HealthLog ^ l in logs)
    {
        tSleep += l->SleepHours;
        tWater += l->WaterGlasses;
        tEx += l->ExerciseMins;
        tStr += l->StressLevel;
        tMood += l->MoodRating;
    }

    int    n = logs->Count;
    double as_ = tSleep / n;
    double aw = tWater / n;
    double ae = tEx / n;
    double astr = tStr / n;
    double am = tMood / n;

    lblDateRangeVal->Text = dtpFrom->Value.ToString("dd MMM yyyy") +
        L"  to  " +
        dtpTo->Value.ToString("dd MMM yyyy");
    lblEntriesVal->Text = n.ToString() + " entries";
    lblAvgSleepVal->Text = String::Format("{0:F1} hrs", as_);
    lblAvgWaterVal->Text = String::Format("{0:F1} glasses", aw);
    lblAvgExerciseVal->Text = String::Format("{0:F0} mins", ae);
    lblAvgStressVal->Text = String::Format("{0:F1} / 10", astr);
    lblAvgMoodVal->Text = String::Format("{0:F1} / 5", am);

    lblAvgStressVal->ForeColor = (astr <= 4)
        ? Color::FromArgb(90, 185, 120)
        : (astr <= 7)
        ? Color::FromArgb(220, 160, 50)
        : Color::FromArgb(210, 80, 80);

    lblAvgMoodVal->ForeColor = (am >= 4)
        ? Color::FromArgb(90, 185, 120)
        : (am >= 3)
        ? Color::FromArgb(220, 160, 50)
        : Color::FromArgb(210, 80, 80);

    String^ desc = L"";
    String^ rating = GetOverallRating(as_, aw, ae, astr, am, desc);
    lblRatingVal->Text = rating;
    lblRatingDesc->Text = desc;

    // Rating colour
    Color ratingColor;
    if (rating == "Excellent") ratingColor = Color::FromArgb(90, 185, 120);
    else if (rating == "Good")      ratingColor = Color::FromArgb(100, 149, 237);
    else if (rating == "Fair")      ratingColor = Color::FromArgb(220, 160, 50);
    else                            ratingColor = Color::FromArgb(210, 80, 80);
    lblRatingVal->ForeColor = ratingColor;

    lblResultStatus->ForeColor = Color::FromArgb(90, 185, 120);
    lblResultStatus->Text = L"Report generated for " + n.ToString() + " entries.";
}

System::Void frmReport::btnGenerate_Click(Object^ sender, EventArgs^ e)
{
    GenerateReport();
}
System::Void frmReport::btnPreset7_Click(Object^ sender, EventArgs^ e)
{
    SetDatePreset(7);  GenerateReport();
}
System::Void frmReport::btnPreset30_Click(Object^ sender, EventArgs^ e)
{
    SetDatePreset(30); GenerateReport();
}
System::Void frmReport::btnPreset90_Click(Object^ sender, EventArgs^ e)
{
    SetDatePreset(90); GenerateReport();
}
System::Void frmReport::btnClose_Click(Object^ sender, EventArgs^ e)
{
    this->Close();
}