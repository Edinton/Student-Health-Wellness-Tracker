#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

namespace SHWT {

    
        public ref class frmDashboard : public Form {
        public:
            frmDashboard(Student^ student);

        private:
            Student^ currentStudent;
            DatabaseHelper^ dbHelper;

            Panel^ pnlHeader;
            Label^ lblWelcome;
            Label^ lblStudentInfo;
            Label^ lblLastLogin;

            // Four stat cards
            Panel^ pnlCardSleep;
            Label^ lblCardSleepTitle;
            Label^ lblCardSleepVal;
            Panel^ pnlCardWater;
            Label^ lblCardWaterTitle;
            Label^ lblCardWaterVal;
            Panel^ pnlCardExercise;
            Label^ lblCardExerciseTitle;
            Label^ lblCardExerciseVal;
            Panel^ pnlCardStress;
            Label^ lblCardStressTitle;
            Label^ lblCardStressVal;

            // Reminders
            GroupBox^ grpReminders;
            Label^ lblReminders;

            // Navigation buttons
            Button^ btnLogEntry;
            Button^ btnHistory;
            Button^ btnReport;
            Button^ btnAdmin;

            // Account management buttons
            Button^ btnLogout;
            Button^ btnDeleteAccount;

            // Status bar
            Panel^ pnlStatusBar;
            Label^ lblStatusBar;

            void InitializeComponent();
            void LoadLatestStats();
            Panel^ MakeStatCard(Color accent, String^ title,
                Label^% outTitle, Label^% outVal);
            Button^ MakeNavBtn(String^ text, Color bg, Color fg, int y);

            System::Void btnLogEntry_Click(Object^ sender, EventArgs^ e);
            System::Void btnHistory_Click(Object^ sender, EventArgs^ e);
            System::Void btnReport_Click(Object^ sender, EventArgs^ e);
            System::Void btnAdmin_Click(Object^ sender, EventArgs^ e);
            System::Void btnLogout_Click(Object^ sender, EventArgs^ e);
            System::Void btnDeleteAccount_Click(Object^ sender, EventArgs^ e);
    };
    

}