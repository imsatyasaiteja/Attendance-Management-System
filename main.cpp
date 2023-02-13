#include "home.h"
#include <fstream>
#include <sstream>
#include <string.h>
#include <QApplication>

CascadeClassifier face_cascade;
string faceFolder;
string xmlPath = "/home/teja/OpenCV/opencv/data/haarcascades/haarcascade_frontalface_alt.xml";

AddStudent::AddStudent(QString classFolder, QSpinBox *rollEdit)
{
    filenumber = 10;
    this->cf = classFolder.toStdString();
    this->ff = (classFolder + "faces/").toStdString();
    this->ef = (classFolder + "eigenface.yml").toStdString();
    this->roll = rollEdit->text().toStdString();
}

void AddStudent::detectAndDisplay(Mat frame)
{
    vector<Rect> faces;
    Mat frame_gray;
    Mat crop;
    Mat res;
    Mat gray;
    String folder;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    Rect roi_b;
    Rect roi_c;

    size_t ic = 0;
    size_t ib = 0;

    for (ic = 0; ic < faces.size(); ic++)
    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        crop = frame(roi_b);
        resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR);
        cvtColor(crop, gray, COLOR_BGR2GRAY);
        stringstream ssfn;

        folder = this->ff;
        String name = this->roll;

        ssfn << folder.c_str() << name << this->filenumber << ".jpg";

        folder = ssfn.str();
        imwrite(folder, res);

        this->filenumber++;

        if (filenumber > 99)
        {
            filenumber = 10;
            break;
        }

        Point pt1(faces[ic].x, faces[ic].y);
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        rectangle(frame, pt1, pt2, Scalar(0, 0, 255), 2, 8, 0);
    }

    if (!crop.empty())
    {
        imshow("Detected", crop);
    }
    else
    {
        destroyWindow("Detected");
    }
}

void AddStudent::addFace(int i, QString vidPath)
{
    this->videoPath = vidPath.toStdString();

    if (i == 1)
    {
        VideoCapture capture(videoPath);

        if (!capture.isOpened())
        {
            return;
        }

        if (!face_cascade.load(xmlPath))
        {
            cout << "error" << endl;
            return;
        };

        int frame_counter = 0;
        Mat frame;

        while (frame_counter < 80)
        {
            capture >> frame;

            if (frame.empty())
            {
                break;
            }

            this->detectAndDisplay(frame);

            frame_counter++;
            sleep(0.1);
        }

        this->eigenFaceTrainer();
        return;
    }
    else
    {
        int i = 0;
        VideoCapture capture(0);

        if (!capture.isOpened())
        {
            return;
        }

        Mat frame;

        if (!face_cascade.load(xmlPath))
        {
            cout << "error" << endl;
            return;
        }

        for (;;)
        {
            capture >> frame;

            this->detectAndDisplay(frame);
            i++;

            if (i == 80)
            {
                cout << "\n Face Added";
                break;
            }

            int c = waitKey(10);

            if (27 == char(c))
            {
                break;
            }
        }

        this->eigenFaceTrainer();
        return;
    }
}

static void dbread(vector<Mat> &images, vector<int> &labels)
{
    vector<cv::String> fn;

    glob(faceFolder, fn, false);

    size_t count = fn.size();

    for (size_t i = 2; i < count; i++)
    {
        string itsname = "";

        char sep = '/';

        size_t j = fn[i].rfind(sep, fn[i].length());

        if (j != string::npos)
        {
            itsname = (fn[i].substr(j + 1, fn[i].length() - j - 6));
        }

        images.push_back(imread(fn[i], 0));
        labels.push_back(atoi(itsname.c_str()));
    }
}

void AddStudent::eigenFaceTrainer()
{
    vector<Mat> images;
    vector<int> labels;

    faceFolder = this->ff;

    dbread(images, labels);

    if (images.size() <= 1)
    {
        return;
    }

    cout << " Size of the Images is " << images.size() << endl;
    cout << " Size of the Labels is " << labels.size() << endl;
    cout << " Training Begins.... " << endl;

    Ptr<EigenFaceRecognizer> model = EigenFaceRecognizer::create();

    model->train(images, labels);
    model->save(this->ef);

    cout << " Training Finished.... " << endl;

    waitKey(10000);
}

Student::Student(int label)
{
    roll = to_string(label);
    this->Label = QString::fromStdString(roll);

    present = false;
    marked = false;
}

string Student::Mark(MarkAttendance *M)
{
    QFile file(M->SF);
    QFile attendanceFile(M->AF);

    name = "Unknown";

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList studentslist;
        QTextStream stream(&file);

        while (!stream.atEnd())
        {
            studentslist << stream.readLine();
        }

        int temp;
        QStringList tokens;

        for (int i = 0; i < studentslist.size(); i++)
        {
            tokens = studentslist[i].split(" ");

            int j = 0;

            while (j < tokens.size())
            {
                if ((tokens[j] == this->Label) && !marked)
                {
                    present = true;
                    marked = true;
                    temp = j;

                    break;
                }
                else
                {
                    j++;
                }
            }

            if (present)
            {
                name = " ";
                for (int k = 0; k < temp; k++)
                {
                    name += tokens[k] + " ";
                }

                break;
            }
        }

        file.close();

        if (attendanceFile.open(QIODevice::Append | QIODevice::Text))
        {
            if (M->array_hash[M->label] == 20)
            {
                QTextStream stream(&attendanceFile);
                stream << name << " " << Label << " Present"
                       << "\n";
                marked = true;
            }
        }

        attendanceFile.close();
    }

    return name.toStdString();
}

MarkAttendance::MarkAttendance(QString classFolder, QComboBox *subBox, QComboBox *comboBox, QSpinBox *batchEdit, QString today)
{
    this->cf = classFolder.toStdString();
    this->ef = (classFolder + "eigenface.yml").toStdString();
    this->SF = classFolder + comboBox->currentText() + batchEdit->text() + ".txt";
    this->sf = SF.toStdString();
    this->AF = classFolder + subBox->currentText() + "/" + today + ".txt";
    this->af = AF.toStdString();
}

void MarkAttendance::faceRecognition()
{
    cout << " Start Recognizing... " << endl;

    Ptr<FaceRecognizer> model = FisherFaceRecognizer::create();

    model->read(this->ef);

    string window = "Mark Attendance";
    int img_width = 128;
    int img_height = 128;

    string text;

    if (!face_cascade.load(xmlPath))
    {
        cout << " Error Loading File" << endl;
        return;
    }

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "exit" << endl;
        return;
    }

    namedWindow(window, 1);
    long count = 0;

    while (1)
    {
        vector<Rect> faces;
        Mat frame;
        Mat grayScaleFrame;
        Mat original;

        cap >> frame;
        count = count + 1;

        if (!frame.empty())
        {
            original = frame.clone();

            cvtColor(original, grayScaleFrame, COLOR_BGR2GRAY);

            face_cascade.detectMultiScale(grayScaleFrame, faces, 1.1, 3, 0, cv::Size(90, 90));
            string frameset = to_string(count);

            for (int i = 0; i < faces.size(); i++)
            {
                Rect face_i = faces[i];
                Mat face = grayScaleFrame(face_i);

                Mat face_resized;
                resize(face, face_resized, Size(img_width, img_height), 1.0, 1.0, INTER_CUBIC);

                label = -1;
                double confidence = 0;

                model->predict(face_resized, label, confidence);
                label = label / 10;

                array_hash[label]++;

                if (array_hash[label] == 20)
                {
                    Student st(label);
                    text = st.Mark(this);
                    marked = true;
                }

                cout << " Confidence " << confidence << " Label : " << label << endl;

                rectangle(original, face_i, CV_RGB(0, 0, 255), 1);

                int pos_x = max(face_i.tl().x - 10, 0);
                int pos_y = max(face_i.tl().y - 10, 0);

                putText(original, text , Point(pos_x, pos_y), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            }

            putText(original, "Frames : " + frameset, Point(30, 60), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);
            putText(original, "Persons detected: " + to_string(faces.size()), Point(30, 90), FONT_HERSHEY_COMPLEX_SMALL, 1.0, CV_RGB(0, 255, 0), 1.0);

            cv::imshow(window, original);
        }
        if (waitKey(30) == 27)
        {
            break;
        }

        if (marked)
        {
            sleep(4);
            destroyWindow(window);
            break;
        }
    }

    return;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Home home;
    home.show();

    return a.exec();
}
