#include "Base class.h"

class Course
{
private:
    string courseCode;
    string courseName;
    string teacherID;

public:
    void SetCourseCode(string s);
    void SetCourseName(string s);
    void SetTeacherID(string s);
    string GetCourseCode();
    string GetCourseName();
    string GetTeacherID();
};

void Course::SetCourseCode(string s)
{
    courseCode = s;
    return;
}

void Course::SetCourseName(string s)
{
    courseName = s;
    return;
}

void Course::SetTeacherID(string s)
{
    teacherID = s;
    return;
}

string Course::GetCourseCode()
{
    return courseCode;
}

string Course::GetCourseName()
{
    return courseName;
}

string Course::GetTeacherID()
{
    return teacherID;
}