#pragma once

using namespace System;

namespace SHWT {


    public ref class Student {
    public:
        property int     StudentId;
        property String^ FirstName;
        property String^ LastName;
        property String^ Email;
        property String^ Password;
        property String^ SecurityQuestion;
        property String^ SecurityAnswer;

        Student() {}

        Student(int id, String^ first, String^ last,
            String^ email, String^ password) {
            StudentId = id;
            FirstName = first;
            LastName = last;
            Email = email;
            Password = password;
        }

        property String^ FullName{
            String ^ get() { return FirstName + " " + LastName; }
        }

            bool ValidateData() {
            if (String::IsNullOrWhiteSpace(FirstName))       return false;
            if (String::IsNullOrWhiteSpace(LastName))        return false;
            if (String::IsNullOrWhiteSpace(Email))           return false;
            if (!Email->Contains("@"))                       return false;
            if (String::IsNullOrWhiteSpace(Password))        return false;
            if (Password->Length < 6)                        return false;
            if (String::IsNullOrWhiteSpace(SecurityQuestion))return false;
            if (String::IsNullOrWhiteSpace(SecurityAnswer))  return false;
            return true;
        }
    };


}