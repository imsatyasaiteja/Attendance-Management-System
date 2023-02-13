#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QtWidgets>
#include <QString>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <iostream>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/core.hpp"
#include <opencv2/core/core.hpp>

#include <fstream>
#include <sstream>

class Home;
class MarkAttendance;

using namespace std;
using namespace cv;
using namespace cv::face;

class AddStudent
{
private:
    string cf;
    string ff;
    string ef;
    string sf;
    string videoPath;
    string roll;
    int filenumber;

public:
    AddStudent(QString classFolder, QSpinBox *rollEdit);
    void detectAndDisplay(Mat frame);
    void addFace(int i, QString vidPath);
    void eigenFaceTrainer();
};

class Student
{
private:
    QString name;
    string roll;
    QString Label;
    QString date;
    bool present;
    bool marked;

public:
    Student(int label);
    string Mark(MarkAttendance *M);
};

class MarkAttendance
{
private:
    string cf;
    string ef;
    string sf;
    string af;
    QString SF;
    QString AF;
    int label;
    bool marked = false;
    int array_hash[200] = {0};

public:
    MarkAttendance(QString cf, QComboBox *subBox, QComboBox *comboBox, QSpinBox *batchEdit, QString today);
    void faceRecognition();
    friend string Student::Mark(MarkAttendance *M);
};

class Home : public QMainWindow
{
    Q_OBJECT
private:
    QMainWindow *menu;
    QWidget *addStudentPage;
    QMainWindow *addFacePage;
    QString today;
    bool isFaceAdded;
    bool isFaceDeleted;
    QString dir = "/home/teja/Mark/Database/";

public:
    Home();
    ~Home();

private slots:
    void showMenu();
    void addFaceButton(QString classFolder, QString faceFolder, QSpinBox *rollEdit);
    void recognizeFaceButton();
    void showMessage(const QString &message);
    void addStudentButton();
    void deleteStudentButton();
    void webCamButton(AddStudent &S);
    void videoButton(QString classFolder, QSpinBox *rollEdit);
};

#endif // HOME_H
