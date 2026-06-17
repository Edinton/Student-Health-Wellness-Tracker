#pragma once

using namespace System;

namespace SHWT {

    
        public ref class HealthLog {
        public:
            property int      LogId;
            property int      StudentId;
            property DateTime EntryDate;
            property int      SleepHours;
            property int      WaterGlasses;
            property int      ExerciseMins;
            property int      StressLevel;
            property int      MoodRating;

            HealthLog() {
                EntryDate = DateTime::Today;
                SleepHours = 0;
                WaterGlasses = 0;
                ExerciseMins = 0;
                StressLevel = 5;
                MoodRating = 3;
            }

            HealthLog(int studentId, DateTime date,
                int sleep, int water, int exercise,
                int stress, int mood) {
                StudentId = studentId;
                EntryDate = date;
                SleepHours = sleep;
                WaterGlasses = water;
                ExerciseMins = exercise;
                StressLevel = stress;
                MoodRating = mood;
            }

            String^ GetWellnessSummary() {
                int score = 0;
                if (SleepHours >= 7)  score++;
                if (WaterGlasses >= 8)  score++;
                if (ExerciseMins >= 30) score++;
                if (StressLevel <= 4)  score++;
                if (MoodRating >= 4)  score++;
                if (score == 5) return "Excellent";
                if (score >= 3) return "Good";
                if (score >= 2) return "Fair";
                return "Needs Improvement";
            }

            bool ValidateData() {
                if (SleepHours < 0 || SleepHours   > 24)  return false;
                if (WaterGlasses < 0 || WaterGlasses > 30)  return false;
                if (ExerciseMins < 0 || ExerciseMins > 600) return false;
                if (StressLevel < 1 || StressLevel  > 10)  return false;
                if (MoodRating < 1 || MoodRating   > 5)   return false;
                if (EntryDate > DateTime::Today)             return false;
                return true;
            }
    };
    

}