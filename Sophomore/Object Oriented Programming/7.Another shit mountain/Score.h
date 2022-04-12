#include "Base class.h"

class Score
{
private:
    long studentID;
    string courseID;
    int score;

public:
    void SetStudentID(long n);
    void SetCourseID(string s);
    void SetScore(int n);
    long GetStudentID();
    string GetCourseID();
    int GetScore();
};

void Score::SetStudentID(long n)
{
    studentID = n;
    return;
}

void Score::SetCourseID(string s)
{
    courseID = s;
    return;
}

void Score::SetScore(int n)
{
    score = n;
    return;
}

long Score::GetStudentID()
{
    return studentID;
}

string Score::GetCourseID()
{
    return courseID;
}

int Score::GetScore()
{
    return score;
}