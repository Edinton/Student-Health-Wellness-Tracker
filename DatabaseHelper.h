#pragma once
#include "Student.h"
#include "HealthLog.h"

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Collections::Generic;

namespace SHWT {

    
        public ref class DatabaseHelper {
        private:
            String^ connectionString;

            SqlConnection^ GetConnection() {
                return gcnew SqlConnection(connectionString);
            }

        public:
            DatabaseHelper() {
                connectionString =
                    "Server=.\\SQLEXPRESS;Database=SHWT_DB;Trusted_Connection=True;";
            }

            void InitialiseDatabase() {
                // Students table — includes security_question / security_answer
                String^ createStudents =
                    "IF NOT EXISTS (SELECT * FROM sysobjects "
                    "               WHERE name='Students' AND xtype='U') "
                    "CREATE TABLE Students ("
                    "  student_id        INT IDENTITY(1,1) PRIMARY KEY,"
                    "  first_name        NVARCHAR(100) NOT NULL,"
                    "  last_name         NVARCHAR(100) NOT NULL,"
                    "  email             NVARCHAR(200) NOT NULL UNIQUE,"
                    "  password          NVARCHAR(200) NOT NULL,"
                    "  security_question NVARCHAR(300) NOT NULL DEFAULT '',"
                    "  security_answer   NVARCHAR(300) NOT NULL DEFAULT ''"
                    ");";

                // Add security columns if the table already exists without them
                String^ addSecQ =
                    "IF NOT EXISTS (SELECT * FROM sys.columns "
                    "               WHERE object_id=OBJECT_ID('Students') "
                    "               AND name='security_question') "
                    "ALTER TABLE Students ADD security_question NVARCHAR(300) NOT NULL DEFAULT '';";

                String^ addSecA =
                    "IF NOT EXISTS (SELECT * FROM sys.columns "
                    "               WHERE object_id=OBJECT_ID('Students') "
                    "               AND name='security_answer') "
                    "ALTER TABLE Students ADD security_answer NVARCHAR(300) NOT NULL DEFAULT '';";

                String^ createLogs =
                    "IF NOT EXISTS (SELECT * FROM sysobjects "
                    "               WHERE name='Health_Log' AND xtype='U') "
                    "CREATE TABLE Health_Log ("
                    "  log_id        INT IDENTITY(1,1) PRIMARY KEY,"
                    "  student_id    INT NOT NULL "
                    "    FOREIGN KEY REFERENCES Students(student_id) ON DELETE CASCADE,"
                    "  entry_date    DATE NOT NULL,"
                    "  sleep_hours   INT  NOT NULL,"
                    "  water_glasses INT  NOT NULL,"
                    "  exercise_mins INT  NOT NULL,"
                    "  stress_level  INT  NOT NULL,"
                    "  mood_rating   INT  NOT NULL"
                    ");";

                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    (gcnew SqlCommand(createStudents, conn))->ExecuteNonQuery();
                    (gcnew SqlCommand(addSecQ, conn))->ExecuteNonQuery();
                    (gcnew SqlCommand(addSecA, conn))->ExecuteNonQuery();
                    (gcnew SqlCommand(createLogs, conn))->ExecuteNonQuery();
                }
                finally { conn->Close(); }
            }

            bool RegisterStudent(Student^ s) {
                String^ sql =
                    "INSERT INTO Students "
                    "(first_name,last_name,email,password,"
                    " security_question,security_answer) "
                    "VALUES (@fn,@ln,@em,@pw,@sq,@sa)";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@fn", s->FirstName);
                    cmd->Parameters->AddWithValue("@ln", s->LastName);
                    cmd->Parameters->AddWithValue("@em", s->Email);
                    cmd->Parameters->AddWithValue("@pw", s->Password);
                    cmd->Parameters->AddWithValue("@sq", s->SecurityQuestion);
                    cmd->Parameters->AddWithValue("@sa", s->SecurityAnswer->ToLower()->Trim());
                    return cmd->ExecuteNonQuery() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            Student^ LoginStudent(String^ email, String^ password) {
                String^ sql =
                    "SELECT * FROM Students WHERE email=@em AND password=@pw";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@em", email);
                    cmd->Parameters->AddWithValue("@pw", password);
                    SqlDataReader^ r = cmd->ExecuteReader();
                    if (r->Read()) {
                        Student^ s = gcnew Student();
                        s->StudentId = r->GetInt32(r->GetOrdinal("student_id"));
                        s->FirstName = r->GetString(r->GetOrdinal("first_name"));
                        s->LastName = r->GetString(r->GetOrdinal("last_name"));
                        s->Email = r->GetString(r->GetOrdinal("email"));
                        s->Password = r->GetString(r->GetOrdinal("password"));
                        s->SecurityQuestion = r->GetString(r->GetOrdinal("security_question"));
                        s->SecurityAnswer = r->GetString(r->GetOrdinal("security_answer"));
                        return s;
                    }
                    return nullptr;
                }
                catch (Exception^) { return nullptr; }
                finally { conn->Close(); }
            }

            bool EmailExists(String^ email) {
                String^ sql = "SELECT COUNT(*) FROM Students WHERE email=@em";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@em", email);
                    return (int)cmd->ExecuteScalar() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            // Returns the security question for a given email (for forgot-password)
            String^ GetSecurityQuestion(String^ email) {
                String^ sql =
                    "SELECT security_question FROM Students WHERE email=@em";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@em", email);
                    Object^ result = cmd->ExecuteScalar();
                    if (result != nullptr && result != System::DBNull::Value)
                        return result->ToString();
                    return nullptr;
                }
                catch (Exception^) { return nullptr; }
                finally { conn->Close(); }
            }

            // Verifies email + security answer (case-insensitive)
            bool VerifySecurityAnswer(String^ email, String^ answer) {
                String^ sql =
                    "SELECT COUNT(*) FROM Students "
                    "WHERE email=@em AND security_answer=@sa";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@em", email);
                    cmd->Parameters->AddWithValue("@sa", answer->ToLower()->Trim());
                    return (int)cmd->ExecuteScalar() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            // Resets password after successful security verification
            bool UpdatePassword(String^ email, String^ newPassword) {
                String^ sql =
                    "UPDATE Students SET password=@pw WHERE email=@em";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@pw", newPassword);
                    cmd->Parameters->AddWithValue("@em", email);
                    return cmd->ExecuteNonQuery() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            // Deletes a student and all their logs 
            bool DeleteStudent(int studentId) {
                String^ sql = "DELETE FROM Students WHERE student_id=@sid";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@sid", studentId);
                    return cmd->ExecuteNonQuery() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            // Returns all students for the admin panel
            DataTable^ GetAllStudents() {
                String^ sql =
                    "SELECT student_id, first_name, last_name, email "
                    "FROM Students ORDER BY last_name, first_name";
                SqlConnection^ conn = GetConnection();
                DataTable^ dt = gcnew DataTable();
                try {
                    conn->Open();
                    SqlDataAdapter^ da = gcnew SqlDataAdapter(sql, conn);
                    da->Fill(dt);
                    return dt;
                }
                catch (Exception^) { return dt; }
                finally { conn->Close(); }
            }

            bool AddHealthLog(HealthLog^ log) {
                String^ sql =
                    "INSERT INTO Health_Log "
                    "(student_id,entry_date,sleep_hours,water_glasses,"
                    " exercise_mins,stress_level,mood_rating) "
                    "VALUES (@sid,@dt,@sl,@wa,@ex,@st,@mo)";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@sid", log->StudentId);
                    cmd->Parameters->AddWithValue("@dt", log->EntryDate.Date);
                    cmd->Parameters->AddWithValue("@sl", log->SleepHours);
                    cmd->Parameters->AddWithValue("@wa", log->WaterGlasses);
                    cmd->Parameters->AddWithValue("@ex", log->ExerciseMins);
                    cmd->Parameters->AddWithValue("@st", log->StressLevel);
                    cmd->Parameters->AddWithValue("@mo", log->MoodRating);
                    return cmd->ExecuteNonQuery() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            bool DeleteLog(int logId) {
                String^ sql = "DELETE FROM Health_Log WHERE log_id=@lid";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@lid", logId);
                    return cmd->ExecuteNonQuery() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            List<HealthLog^>^ GetLogsForStudent(int studentId) {
                String^ sql =
                    "SELECT * FROM Health_Log "
                    "WHERE student_id=@sid ORDER BY entry_date DESC";
                SqlConnection^ conn = GetConnection();
                List<HealthLog^>^ list = gcnew List<HealthLog^>();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@sid", studentId);
                    SqlDataReader^ r = cmd->ExecuteReader();
                    while (r->Read()) {
                        HealthLog^ l = gcnew HealthLog();
                        l->LogId = r->GetInt32(r->GetOrdinal("log_id"));
                        l->StudentId = r->GetInt32(r->GetOrdinal("student_id"));
                        l->EntryDate = r->GetDateTime(r->GetOrdinal("entry_date"));
                        l->SleepHours = r->GetInt32(r->GetOrdinal("sleep_hours"));
                        l->WaterGlasses = r->GetInt32(r->GetOrdinal("water_glasses"));
                        l->ExerciseMins = r->GetInt32(r->GetOrdinal("exercise_mins"));
                        l->StressLevel = r->GetInt32(r->GetOrdinal("stress_level"));
                        l->MoodRating = r->GetInt32(r->GetOrdinal("mood_rating"));
                        list->Add(l);
                    }
                    return list;
                }
                catch (Exception^) { return list; }
                finally { conn->Close(); }
            }

            List<HealthLog^>^ GetLogsInRange(int studentId,
                DateTime from, DateTime to) {
                String^ sql =
                    "SELECT * FROM Health_Log "
                    "WHERE student_id=@sid "
                    "  AND entry_date BETWEEN @from AND @to "
                    "ORDER BY entry_date ASC";
                SqlConnection^ conn = GetConnection();
                List<HealthLog^>^ list = gcnew List<HealthLog^>();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@sid", studentId);
                    cmd->Parameters->AddWithValue("@from", from.Date);
                    cmd->Parameters->AddWithValue("@to", to.Date);
                    SqlDataReader^ r = cmd->ExecuteReader();
                    while (r->Read()) {
                        HealthLog^ l = gcnew HealthLog();
                        l->LogId = r->GetInt32(r->GetOrdinal("log_id"));
                        l->StudentId = r->GetInt32(r->GetOrdinal("student_id"));
                        l->EntryDate = r->GetDateTime(r->GetOrdinal("entry_date"));
                        l->SleepHours = r->GetInt32(r->GetOrdinal("sleep_hours"));
                        l->WaterGlasses = r->GetInt32(r->GetOrdinal("water_glasses"));
                        l->ExerciseMins = r->GetInt32(r->GetOrdinal("exercise_mins"));
                        l->StressLevel = r->GetInt32(r->GetOrdinal("stress_level"));
                        l->MoodRating = r->GetInt32(r->GetOrdinal("mood_rating"));
                        list->Add(l);
                    }
                    return list;
                }
                catch (Exception^) { return list; }
                finally { conn->Close(); }
            }

            bool LogExistsForDate(int studentId, DateTime date) {
                String^ sql =
                    "SELECT COUNT(*) FROM Health_Log "
                    "WHERE student_id=@sid AND entry_date=@dt";
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    SqlCommand^ cmd = gcnew SqlCommand(sql, conn);
                    cmd->Parameters->AddWithValue("@sid", studentId);
                    cmd->Parameters->AddWithValue("@dt", date.Date);
                    return (int)cmd->ExecuteScalar() > 0;
                }
                catch (Exception^) { return false; }
                finally { conn->Close(); }
            }

            DataTable^ GetAllLogsAsTable() {
                String^ sql =
                    "SELECT s.student_id,"
                    "       s.first_name + ' ' + s.last_name AS student_name,"
                    "       hl.log_id,"
                    "       CONVERT(VARCHAR,hl.entry_date,103) AS entry_date,"
                    "       hl.sleep_hours, hl.water_glasses,"
                    "       hl.exercise_mins, hl.stress_level, hl.mood_rating "
                    "FROM Health_Log hl "
                    "JOIN Students s ON s.student_id = hl.student_id "
                    "ORDER BY hl.entry_date DESC";
                SqlConnection^ conn = GetConnection();
                DataTable^ dt = gcnew DataTable();
                try {
                    conn->Open();
                    SqlDataAdapter^ da = gcnew SqlDataAdapter(sql, conn);
                    da->Fill(dt);
                    return dt;
                }
                catch (Exception^) { return dt; }
                finally { conn->Close(); }
            }

            int GetTotalStudents() {
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    return (int)(gcnew SqlCommand(
                        "SELECT COUNT(*) FROM Students", conn))->ExecuteScalar();
                }
                catch (Exception^) { return 0; }
                finally { conn->Close(); }
            }

            int GetTotalLogs() {
                SqlConnection^ conn = GetConnection();
                try {
                    conn->Open();
                    return (int)(gcnew SqlCommand(
                        "SELECT COUNT(*) FROM Health_Log", conn))->ExecuteScalar();
                }
                catch (Exception^) { return 0; }
                finally { conn->Close(); }
            }
    };
    

}