#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SHWT {

    
        public ref class frmLogEntry : public Form {
        public:
            frmLogEntry(Student^ student);

        private:
            Student^ currentStudent;
            DatabaseHelper^ dbHelper;

            Panel^ pnlHeader;
            Label^ lblTitle;
            Label^ lblSubtitle;

            GroupBox^ grpDate;
            Label^ lblDatePrompt;
            DateTimePicker^ dtpDate;
            Label^ lblDateNote;

            GroupBox^ grpMetrics;

            // Each metric row: label | trackbar | value badge
            Label^ lblSleep;
            TrackBar^ trkSleep;
            Label^ lblSleepVal;
            Label^ lblSleepHint;

            Label^ lblWater;
            TrackBar^ trkWater;
            Label^ lblWaterVal;
            Label^ lblWaterHint;

            Label^ lblExercise;
            TrackBar^ trkExercise;
            Label^ lblExerciseVal;
            Label^ lblExerciseHint;

            Label^ lblStress;
            TrackBar^ trkStress;
            Label^ lblStressVal;
            Label^ lblStressHint;

            Label^ lblMood;
            TrackBar^ trkMood;
            Label^ lblMoodVal;
            Label^ lblMoodHint;

            Panel^ pnlActionBar;
            Button^ btnSave;
            Button^ btnCancel;
            Label^ lblStatus;

            void InitializeComponent();
            void BuildMetricRow(int rowY, int groupW,
                String^ name, String^ hint,
                int minV, int maxV, int defV,
                Label^% outLbl, TrackBar^% outTrk,
                Label^% outVal, Label^% outHint,
                EventHandler^ onChange);

            System::Void btnSave_Click(Object^ sender, EventArgs^ e);
            System::Void btnCancel_Click(Object^ sender, EventArgs^ e);
            System::Void trkSleep_ValueChanged(Object^ sender, EventArgs^ e);
            System::Void trkWater_ValueChanged(Object^ sender, EventArgs^ e);
            System::Void trkExercise_ValueChanged(Object^ sender, EventArgs^ e);
            System::Void trkStress_ValueChanged(Object^ sender, EventArgs^ e);
            System::Void trkMood_ValueChanged(Object^ sender, EventArgs^ e);
    };
    

}