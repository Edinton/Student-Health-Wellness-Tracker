#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SHWT {

    
        public ref class frmReport : public Form {
        public:
            frmReport(Student^ student);

        private:
            Student^ currentStudent;
            DatabaseHelper^ dbHelper;

            Panel^ pnlHeader;
            Label^ lblTitle;
            Label^ lblSubtitle;

            GroupBox^ grpRange;
            Label^ lblFromPrompt;
            DateTimePicker^ dtpFrom;
            Label^ lblToPrompt;
            DateTimePicker^ dtpTo;
            Label^ lblPresetPrompt;
            Button^ btnPreset7;
            Button^ btnPreset30;
            Button^ btnPreset90;
            Button^ btnGenerate;

            GroupBox^ grpResults;

            // Stat rows
            Label^ lblAvgSleep;      Label^ lblAvgSleepVal;
            Label^ lblAvgWater;      Label^ lblAvgWaterVal;
            Label^ lblAvgExercise;   Label^ lblAvgExerciseVal;
            Label^ lblAvgStress;     Label^ lblAvgStressVal;
            Label^ lblAvgMood;       Label^ lblAvgMoodVal;
            Label^ lblEntries;       Label^ lblEntriesVal;
            Label^ lblDateRange;     Label^ lblDateRangeVal;

            Panel^ pnlRating;
            Label^ lblRatingTitle;
            Label^ lblRatingVal;
            Label^ lblRatingDesc;

            Panel^ pnlActionBar;
            Button^ btnClose;
            Label^ lblResultStatus;
            Button^ MakePreset(String^ text, int x, EventHandler^ click);
            void    ResetLabel(Label^ l);

            void InitializeComponent();
            void SetDatePreset(int days);
            void GenerateReport();
            String^ GetOverallRating(double avgSleep, double avgWater,
                double avgExercise, double avgStress,
                double avgMood, String^% outDesc);
            void AddStatRow(GroupBox^ grp, Label^ lbl, String^ text,
                Label^ val, int y,
                Drawing::Font^ vFont, Color vColor);

            System::Void btnGenerate_Click(Object^ sender, EventArgs^ e);
            System::Void btnPreset7_Click(Object^ sender, EventArgs^ e);
            System::Void btnPreset30_Click(Object^ sender, EventArgs^ e);
            System::Void btnPreset90_Click(Object^ sender, EventArgs^ e);
            System::Void btnClose_Click(Object^ sender, EventArgs^ e);
    };
    

}