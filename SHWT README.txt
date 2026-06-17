  SHWT — Student Health and Wellness Tracker
  Version 1.0  |  C++/CLI  |  Windows Forms  |  Visual Studio 2022


OVERVIEW:

SHWT (Student Health and Wellness Tracker) is a Windows desktop application
built with C++/CLI and Windows Forms. It provides students with a structured
way to log, monitor, and review their daily health and wellness metrics —
including sleep, hydration, exercise, stress, and mood — and gives
administrators visibility into overall system usage.



FEATURES:

Student Features

  - Account registration with email, password, and a security question
  - Secure login with password masking and Enter-key support
  - 3-step forgot password flow: email lookup > security question > reset
  - Personal dashboard showing the latest wellness stats at a glance
  - Daily wellness log entry using sliders (one entry per day enforced)
  - Full wellness history view with data grid and entry deletion
  - Health report generation with date-range presets (7, 30, 90 days)
  - Account self-deletion with two-step confirmation

Admin Features

  - Admin monitor panel accessible from the dashboard
  - View all registered students (ID, name, email)
  - Select any student to inspect their full wellness log history
  - Delete individual log entries or entire student accounts
  - Live stat cards: total registered students and total wellness logs


APPLICATION SCREENS

  Screen              File                      Description

  Login               frmLogin.cpp              Entry point. Email + password
                                                sign-in, links to registration
                                                and password recovery.

  Register            frmRegister.cpp           New account creation with
                                                personal details, password, and
                                                a security question.

  Forgot Password     frmForgotPassword.cpp     3-step recovery: find account >
                                                verify security answer > set new
                                                password.

  Dashboard           frmDashBoard.cpp          Main hub. Shows latest stats,
                                                wellness reminders, and
                                                navigation to all features.

  Log Entry           frmLogEntry.cpp           Slider-based daily wellness
                                                entry (sleep, water, exercise,
                                                stress, mood).

  History             frmHistory.cpp            Full log history in a data grid
                                                with summary stats, refresh,
                                                and delete support.

  Report              frmReport.h / .cpp        Aggregated health report over a
                                                selectable date range with an
                                                overall wellness rating.

  Admin Monitor       frmAdmin.cpp              Admin panel showing all students
                                                and their logs, with deletion
                                                capabilities.



DATA MODEL:

HealthLog (HealthLog.h)

Each daily entry captures the following fields:

  Property        Type        Range / Notes

  LogId           int         Auto-assigned database ID
  StudentId       int         Foreign key linking log to student
  EntryDate       DateTime    Date of entry (no future dates allowed)
  SleepHours      int         0 – 24 hours
  WaterGlasses    int         0 – 20 glasses
  ExerciseMins    int         0 – 180 minutes
  StressLevel     int         1 – 10  (1 = very calm, 10 = extremely stressed)
  MoodRating      int         1 – 5   (1 = very low, 5 = excellent)

Wellness Summary Rating

Each log is automatically rated based on how many of 5 health targets are met:

  Criteria          Target

  Sleep             7 or more hours
  Water intake      8 or more glasses
  Exercise          30 or more minutes
  Stress level      4 or below
  Mood rating       4 or above

  Score     Rating
  
  5 / 5     Excellent
  3 – 4     Good
  2         Fair
  0 – 1     Needs Improvement


TECHNOLOGY STACK:

  Component         Technology

  Language          C++/CLI (Managed C++)
  UI Framework      Windows Forms (.NET)
  IDE               Visual Studio 2022 (v17.14)
  Project Type      Visual C++ Windows Forms Application (.vcxproj)
  Platforms         x86 (Win32) and x64
  Build Configs     Debug and Release
  Database          DatabaseHelper class (abstracted CRUD layer)
  Font              Segoe UI throughout


GETTING STARTED

Prerequisites

  - Windows 10 or later
  - Visual Studio 2022 with the "Desktop development with C++" workload
  - .NET Framework support for C++/CLI

Building the Project

  1. Open SHWT.sln in Visual Studio 2022
  2. Select your target platform (x64 recommended) and configuration
  3. Build with Build > Build Solution (Ctrl+Shift+B)
  4. Run the application with F5 or the Start button

First Launch

  1. The application opens at the Login screen
  2. Click "Create a New Account" to register
  3. Fill in your name, email, password, and a security question
  4. Sign in and start logging daily wellness entries from the Dashboard


PROJECT STRUCTURE


  File                      Purpose

  SHWT.sln                  Visual Studio solution file
  SHWT.vcxproj              C++ project file (build settings, file list)
  frmLogin.cpp/h            Login form
  frmRegister.cpp/h         Registration form
  frmForgotPassword.cpp/h   Password recovery wizard
  frmDashBoard.cpp/h        Main dashboard
  frmLogEntry.cpp/h         Daily wellness log entry form
  frmHistory.cpp/h          Wellness history viewer
  frmReport.cpp/h           Health report generator
  frmAdmin.cpp/h            Admin monitor panel
  HealthLog.h               HealthLog data model and validation logic
  DatabaseHelper.h/.cpp     Database abstraction layer (CRUD operations)


NOTES

  - Only one wellness log entry is permitted per student per day.
  - Security question answers are not case-sensitive.
  - Passwords must be a minimum of 6 characters.
  - Account and log deletion is permanent and cannot be undone.
  - The Admin Monitor is accessible to any logged-in user from the Dashboard.
    Consider restricting access in a production deployment.


  SHWT v1.0  —  All data is stored securely.