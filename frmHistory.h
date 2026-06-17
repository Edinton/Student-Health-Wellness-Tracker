#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

namespace SHWT {

    
        public ref class frmHistory : public Form {
        public:
            frmHistory(Student^ student);

        private:
            Student^ currentStudent;
            DatabaseHelper^ dbHelper;
            List<HealthLog^>^ logList;   

            Panel^ pnlHeader;
            Label^ lblTitle;
            Label^ lblSubtitle;

            Panel^ pnlSummaryBar;
            Label^ lblTotalEntries;
            Label^ lblTotalEntriesVal;
            Label^ lblAvgSleep;
            Label^ lblAvgSleepVal;
            Label^ lblAvgMood;
            Label^ lblAvgMoodVal;

            GroupBox^ grpHistory;
            DataGridView^ dgvHistory;

            Panel^ pnlActionBar;
            Button^ btnDeleteLog;
            Button^ btnRefresh;
            Button^ btnClose;
            Label^ lblActionStatus;

            void InitializeComponent();
            void LoadHistory();
            void StyleGrid();
            void UpdateSummaryBar();
            void AddTile(Label^ lbl, String^ txt, Label^ val, int x);

            System::Void btnDeleteLog_Click(Object^ sender, EventArgs^ e);
            System::Void btnRefresh_Click(Object^ sender, EventArgs^ e);
            System::Void btnClose_Click(Object^ sender, EventArgs^ e);
            System::Void dgvHistory_SelectionChanged(Object^ sender, EventArgs^ e);
    };
    

}