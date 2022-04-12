#include "Student.h"
#include "Teacher.h"
#include "Course.h"
#include "Score.h"
#include <fstream>
#include <sstream>

class TableManager
{
private:
    Student *St;
    Teacher *T;
    Course *C;
    Score *Sc;
    int num_of_student;
    int num_of_teacher;
    int num_of_course;
    int num_of_score;

public:
    void InitializeStudent(ifstream readfile);
    void InitializeTeacher(ifstream readfile);
    void InitializeCourse(ifstream readfile);
    void InitializeScore(ifstream readfile);
    string GetTeacherFromCourse(string course);
    int GetScoreFromCourse(string course, long stuID);
    string GetInfoFromID(long stuID);
    void SetScoreToCourse(long stuID, string course, int score);
};

void TableManager::InitializeStudent(ifstream readfile)
{
    ostringstream ss;
    ss << readfile.rdbuf();
    string s = ss.str();
    int index;
    for (int i = 0; (index = s.find("\n")) != -1; i++)
    {
        string temp = s.substr(0, index);
        s.erase(0, index + 1);

        index = temp.find(" ");
        St[i].SetName(temp.substr(0, index));
        temp.erase(0, index + 1);
        index = temp.find(" ");
        St[i].SetGender(temp.substr(0, index));
        temp.erase(0, index + 1);
        index = temp.find(" ");
        St[i].SetBirth(stod(temp.substr(0, index)));
        temp.erase(0, index + 1);
        St[i].SetID(stoi(temp));
    }

    return;
}

void TableManager::InitializeTeacher(ifstream readfile)
{
    ostringstream ss;
    ss << readfile.rdbuf();
    string s = ss.str();
    int index;
    for (int i = 0; (index = s.find("\n")) != -1; i++)
    {
        string temp = s.substr(0, index);
        s.erase(0, index + 1);

        index = temp.find(" ");
        T[i].SetName(temp.substr(0, index));
        temp.erase(0, index + 1);
        index = temp.find(" ");
        T[i].SetGender(temp.substr(0, index));
        temp.erase(0, index + 1);
        index = temp.find(" ");
        T[i].SetBirth(stod(temp.substr(0, index)));
        temp.erase(0, index + 1);
        T[i].SetID(temp);
    }

    return;
}

void TableManager::InitializeCourse(ifstream readfile)
{
    ostringstream ss;
    ss << readfile.rdbuf();
    string s = ss.str();
    int index;
    for (int i = 0; (index = s.find("\n")) != -1; i++)
    {
        string temp = s.substr(0, index);
        s.erase(0, index + 1);

        index = temp.find(" ");
        C[i].SetCourseCode(temp.substr(0, index));
        temp.erase(0, index + 1);
        index = temp.find(" ");
        C[i].SetCourseName(temp.substr(0, index));
        temp.erase(0, index + 1);
        C[i].SetTeacherID(temp);
    }

    return;
}

void TableManager::InitializeScore(ifstream readfile)
{
    ostringstream ss;
    ss << readfile.rdbuf();
    string s = ss.str();
    int index;
    for (int i = 0; (index = s.find("\n")) != -1; i++)
    {
        string temp = s.substr(0, index);
        s.erase(0, index + 1);

        index = temp.find(" ");
        Sc[i].SetStudentID(stoi(temp.substr(0, index)));
        temp.erase(0, index + 1);
        index = temp.find(" ");
        Sc[i].SetCourseID(temp.substr(0, index));
        temp.erase(0, index + 1);
        Sc[i].SetScore(stoi(temp));
    }

    return;
}

string TableManager::GetTeacherFromCourse(string course)
{
    for (int i = 0; i < num_of_course; i++)
    {
        if (C[i].GetCourseName() == course)
        {
            for (int j = 0; j < num_of_teacher; j++)
            {
                if (T[j].GetID() == C[i].GetTeacherID())
                    return T[j].GetName();
            }
        }
    }

    return "Not Found.";
}

int TableManager::GetScoreFromCourse(string course, long stuID)
{
    for (int i = 0; i < num_of_course; i++)
    {
        if (C[i].GetCourseName() == course)
        {
            for (int j = 0; j < num_of_score; j++)
            {
                if (Sc[j].GetCourseID() == C[i].GetCourseCode() && Sc[j].GetStudentID() == stuID)
                    return Sc[j].GetScore();
            }
        }
    }

    return -1;
}

string TableManager::GetInfoFromID(long stuID)
{
    for (int i = 0; i < num_of_student; i++)
    {
        if (St[i].GetID() == stuID)
        {
            int age = 2021.4 - St[i].Getbirth();
            return St[i].GetName() + " " + St[i].Getgender() + " " + to_string(age);
        }
    }

    return "Not Found.";
}

void TableManager::SetScoreToCourse(long stuID, string course, int score)
{
    int i = 0;
    for (; i < num_of_course; i++)
        if (C[i].GetCourseName() == course)
            break;

    Sc = (Score *)realloc(Sc, (++num_of_score) * sizeof(Score));
    Sc[num_of_score - 1].SetStudentID(stuID);
    Sc[num_of_score - 1].SetCourseID(C[i].GetCourseCode());
    Sc[num_of_score - 1].SetScore(score);
}