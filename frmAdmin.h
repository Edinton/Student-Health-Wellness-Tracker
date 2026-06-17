#pragma once
#include "DatabaseHelper.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data;

namespace SHWT {

    
        public ref class frmAdmin : public Form {
        public:
            frmAdmin();

        private:
            DatabaseHelper^ dbHelper;

            Panel^ pnlHeader;
            Label^ lblTitle;
            Label^ lblSubtitle;

            // Stat cards
            Panel^ pnlCardStudents;
            Label^ lblCardStudentsTitle;
            Label^ lblCardStudentsVal;
            Panel^ pnlCardLogs;
            Label^ lblCardLogsTitle;
            Label^ lblCardLogsVal;

            //student list
            GroupBox^ grpStudents;
            DataGridView^ dgvStudents;
            Button^ btnDeleteStudent;
            Label^ lblStudentStatus;

            //log viewer
            GroupBox^ grpLogs;
            DataGridView^ dgvLogs;
            Button^ btnDeleteAdminLog;
            Label^ lblLogStatus;

            // Bottom bar
            Panel^ pnlActionBar;
            Button^ btnRefresh;
            Button^ btnClose;

            void InitializeComponent();
            void LoadData();
            void LoadLogsForStudent(int studentId, String^ studentName);
            void StyleGrid(DataGridView^ dgv);
            Panel^ MakeStatCard(Color accent, String^ title,
                Label^% outTitle, Label^% outVal);

            System::Void btnDeleteStudent_Click(Object^ sender, EventArgs^ e);
            System::Void btnDeleteAdminLog_Click(Object^ sender, EventArgs^ e);
            System::Void btnRefresh_Click(Object^ sender, EventArgs^ e);
            System::Void btnClose_Click(Object^ sender, EventArgs^ e);
            System::Void dgvStudents_SelectionChanged(Object^ sender, EventArgs^ e);
            System::Void dgvLogs_SelectionChanged(Object^ sender, EventArgs^ e);
    };
    

}