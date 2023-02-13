#include "home.h"

using namespace std;

void Home::showMessage(const QString &message)
{
    QWidget *messagePage = new QWidget;
    messagePage->setWindowTitle("Message");
    messagePage->setFixedSize(432, 768);

    QLabel *bg = new QLabel(messagePage);
    bg->setPixmap(QPixmap("bgs/4.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label = new QLabel(message);
    QFont font = label->font();
    font.setPointSize(16);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);

    QPushButton *backButton = new QPushButton("Back");
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, [this, messagePage]()
    {
        this->hide();
        menu->show();
        messagePage->hide();
    });

    messagePage->setLayout(layout);
    messagePage->show();
    menu->hide();
}

void Home::videoButton(QString classFolder, QSpinBox *rollEdit)
{
    QWidget *videoPathPage = new QWidget;
    videoPathPage->setWindowTitle("Add Video");
    videoPathPage->setFixedSize(432, 768);

    QLabel *bg = new QLabel(videoPathPage);
    bg->setPixmap(QPixmap("bgs/6.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *videoLabel = new QLabel("Enter video name with extension");
    QLineEdit *vidname = new QLineEdit;
    QFont font = videoLabel->font();
    font.setPointSize(16);
    videoLabel->setFont(font);
    videoLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(vidname);
    layout->addWidget(videoLabel);

    QPushButton *submitButton = new QPushButton("Submit");
    layout->addWidget(submitButton);

    QPushButton *back = new QPushButton("Back");
    layout->addWidget(back);

    connect(back, &QPushButton::clicked, [this, videoPathPage]()
    {
        this->hide();
        addStudentPage->show();
        videoPathPage->close();
    });

    connect(submitButton, &QPushButton::clicked, [this, vidname, classFolder, videoPathPage, rollEdit]()
    {
        AddStudent S(classFolder, rollEdit);

        QString vidFolder = classFolder + "video";
        QString full = vidFolder + "/" + vidname->text();

        QFile vidFile(full);

        QDir vdir;

        if(vdir.exists(vidFolder))
        {
            if(vidFile.exists())
            {
                qDebug() << full;
                isFaceAdded = true;
                S.addFace(1, full);
            }
            else
            {
                videoPathPage->close();
                this->showMessage("Video Does'nt Exist");
            }
        }
        else
        {
            videoPathPage->close();
            this->showMessage("Directory Does'nt Exist");
        }
    });

    videoPathPage->setLayout(layout);
    videoPathPage->show();
}

void Home::webCamButton(AddStudent &S)
{
    S.addFace(2, "webcam");
}

void Home::addFaceButton(QString classFolder, QString faceFolder, QSpinBox *rollEdit)
{
    addFacePage = new QMainWindow;
    addFacePage->setWindowTitle("Add Face");
    addFacePage->setFixedSize(432, 768);

    QLabel *bg = new QLabel(addFacePage);
    bg->setPixmap(QPixmap("bgs/6.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    int roll = rollEdit->value();

    if (roll >= 1 && roll < 10)
    {
        rollEdit->setPrefix("0");
    }

    QDir cdir, fdir;

    if (!cdir.exists(classFolder))
    {
        cdir.mkpath(classFolder);

        if (!fdir.exists(faceFolder))
        {
            fdir.mkpath(faceFolder);
        }

        classFolder += "/";
    }
    else
    {
        if (!fdir.exists(faceFolder))
        {
            fdir.mkpath(faceFolder);
        }

        classFolder += "/";
    }

    QPushButton *video = new QPushButton("Video", addFacePage);
    video->setGeometry(166, 250, 120, 40);

    QPushButton *webCam = new QPushButton("Web Cam", addFacePage);
    webCam->setGeometry(166, 350, 120, 40);

    QPushButton *back = new QPushButton("Back", addFacePage);
    back->setGeometry(166, 450, 120, 40);

    connect(video, &QPushButton::clicked, [this, rollEdit, classFolder](bool)
    {
        addFacePage->hide();
        this->videoButton(classFolder, rollEdit);
    });

    connect(webCam, &QPushButton::clicked, [this, rollEdit, classFolder](bool)
    {
        AddStudent S(classFolder, rollEdit);

        isFaceAdded = true;
        this->webCamButton(S);
    });

    connect(back, &QPushButton::clicked, [this]()
    {
        this->hide();
        addStudentPage->show();
        addFacePage->close();
    });

    addFacePage->show();
    menu->close();
}

void Home::recognizeFaceButton()
{
    QWidget *recognizeFacePage = new QWidget;
    recognizeFacePage->setWindowTitle("Attendance");
    recognizeFacePage->setFixedSize(432, 768);

    QLabel *bg = new QLabel(recognizeFacePage);
    bg->setPixmap(QPixmap("bgs/10.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label1 = new QLabel("Branch");
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem("CSE");
    comboBox->addItem("ECE");
    layout->addWidget(label1);
    layout->addWidget(comboBox);

    QLabel *label2 = new QLabel("Subject");
    QComboBox *subBox = new QComboBox;
    subBox->addItem("OOPS");
    subBox->addItem("OS");
    subBox->addItem("ML");
    subBox->addItem("DIP");
    subBox->addItem("BIO INFO");
    layout->addWidget(label2);
    layout->addWidget(subBox);

    QLabel *label3 = new QLabel("Batch");
    QSpinBox *batchEdit = new QSpinBox;
    batchEdit->setRange(2018, 2099);
    layout->addWidget(label3);
    layout->addWidget(batchEdit);

    QLabel *dateLabel = new QLabel();
    QDateEdit *dateEdit = new QDateEdit;
    dateEdit->setDisplayFormat("dd-MM-yyyy");
    dateEdit->setDate(QDate::currentDate());
    dateEdit->setCalendarPopup(true);

    layout->addWidget(new QLabel("Enter date : "));
    layout->addWidget(dateEdit);
    layout->addWidget(dateLabel);

    QPushButton *markButton = new QPushButton("Mark");
    layout->addWidget(markButton);

    QPushButton *back = new QPushButton("Back");
    layout->addWidget(back);

    connect(markButton, &QPushButton::clicked, [this, comboBox, subBox, batchEdit, dateEdit, recognizeFacePage](bool)
    {
        QString classFolder =  dir + comboBox->currentText() + batchEdit->text();
        QString faceFolder = classFolder + "/faces";

        QString date = dateEdit->text();

        QDir cdir(classFolder);
        QDir fdir(faceFolder);

        if(cdir.exists())
        {
            classFolder += "/";

            if(fdir.exists())
            {
                if(fdir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries).empty())
                {
                    this->showMessage("No Images Added Yet");
                    recognizeFacePage->hide();
                }
            }
            else
            {
                this->showMessage("Faces Directory Does'nt Exist");
                recognizeFacePage->hide();
            }

            QString filename = classFolder + "eigenface.yml";
            QFile file(filename);

            QString subFolder = classFolder + subBox->currentText();
            QDir sdir(subFolder);

            if(!sdir.exists())
            {
                cdir.mkpath(subFolder);
                subFolder += "/";
            }
            else
            {
               subFolder += "/";
            }

            if(!file.exists())
            {
                this->showMessage("Data Not Trained Yet");
                recognizeFacePage->hide();
            }
            else
            {
                MarkAttendance M(classFolder, subBox, comboBox, batchEdit, date);
                M.faceRecognition();
            }
        }
        else
        {
            this->showMessage("Directory Does'nt Exist");
            recognizeFacePage->hide();
        }
    });

    connect(back, &QPushButton::clicked, [this, recognizeFacePage]()
    {
        this->hide();
        menu->show();
        recognizeFacePage->close();
    });

    recognizeFacePage->setLayout(layout);
    recognizeFacePage->show();
    menu->close();
}

void Home::addStudentButton()
{
    addStudentPage = new QWidget;
    addStudentPage->setWindowTitle("Add Student");
    addStudentPage->setFixedSize(432, 768);

    QLabel *bg = new QLabel(addStudentPage);
    bg->setPixmap(QPixmap("bgs/6.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label1 = new QLabel("Student Name");
    QLineEdit *nameEdit = new QLineEdit;
    layout->addWidget(label1);
    layout->addWidget(nameEdit);

    QLabel *label2 = new QLabel("Roll Number");
    QSpinBox *rollEdit = new QSpinBox;
    rollEdit->setRange(1, 99);
    layout->addWidget(label2);
    layout->addWidget(rollEdit);

    QLabel *label3 = new QLabel("Branch");
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem("CSE");
    comboBox->addItem("ECE");
    layout->addWidget(label3);
    layout->addWidget(comboBox);

    QLabel *label4 = new QLabel("Batch");
    QSpinBox *batchEdit = new QSpinBox;
    batchEdit->setRange(2018, 2099);
    layout->addWidget(label4);
    layout->addWidget(batchEdit);

    QPushButton *addFace = new QPushButton("Add Face");
    layout->addWidget(addFace);

    QPushButton *submitButton = new QPushButton("Submit");
    layout->addWidget(submitButton);

    QPushButton *backButton = new QPushButton("Back");
    layout->addWidget(backButton);

    connect(addFace, &QPushButton::clicked, [this, comboBox, batchEdit, rollEdit](bool)
    {
        isFaceAdded = false;

        QString classFolder = dir + comboBox->currentText() + batchEdit->text();
        QString faceFolder = classFolder + "/faces";

        addStudentPage->close();
        this->addFaceButton(classFolder, faceFolder, rollEdit); 
    });

    connect(submitButton, &QPushButton::clicked, [this, comboBox, batchEdit, nameEdit, rollEdit]()
    {
        if(isFaceAdded)
        {
            QString classFolder = dir + comboBox->currentText() + batchEdit->text() + "/";
            QString sf = classFolder + comboBox->currentText() + batchEdit->text() + ".txt";

            QFile file(sf);

            if (file.open(QIODevice::Append | QIODevice::Text))
            {
                QTextStream stream(&file);
                stream << nameEdit->text() << " " << rollEdit->text() << " " << batchEdit->text() << " " << comboBox->currentText() << "\n";

                file.close();

                addStudentPage->close();
                this->showMessage("Data Entered Successfully!!");
            }

            isFaceAdded = false;
        }
        else
        {
            addStudentPage->close();
            this->showMessage("Add Face To Save The Data!!");
        } 
        });

    connect(backButton, &QPushButton::clicked, [this]()
    {
        this->hide();
        menu->show();
        addStudentPage->close(); 
    });

    addStudentPage->setLayout(layout);
    addStudentPage->show();
    menu->close();
}

void Home::deleteStudentButton()
{
    QWidget *deleteStudentPage = new QWidget;
    deleteStudentPage->setWindowTitle("Delete Student");
    deleteStudentPage->setFixedSize(432, 768);

    QLabel *bg = new QLabel(deleteStudentPage);
    bg->setPixmap(QPixmap("bgs/8.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    QVBoxLayout *layout = new QVBoxLayout;

    QLabel *label1 = new QLabel("Roll Number");
    QSpinBox *rollEdit = new QSpinBox;
    rollEdit->setRange(1, 99);
    layout->addWidget(label1);
    layout->addWidget(rollEdit);

    QLabel *label2 = new QLabel("Branch");
    QComboBox *comboBox = new QComboBox;
    comboBox->addItem("CSE");
    comboBox->addItem("ECE");
    layout->addWidget(label2);
    layout->addWidget(comboBox);

    QLabel *label3 = new QLabel("Batch");
    QSpinBox *batchEdit = new QSpinBox;
    batchEdit->setRange(2018, 2099);
    layout->addWidget(label3);
    layout->addWidget(batchEdit);

    QPushButton *deleteButton = new QPushButton("Delete");
    layout->addWidget(deleteButton);

    QPushButton *back = new QPushButton("Back", deleteStudentPage);
    layout->addWidget(back);

    connect(deleteButton, &QPushButton::clicked, [this, comboBox, batchEdit, rollEdit, deleteStudentPage]()
    {
        isFaceDeleted = false;

        QString classFolder = dir + comboBox->currentText() + batchEdit->text();
        QDir cdir(classFolder);

        if (cdir.exists())
        {
            classFolder += "/";

            int roll = rollEdit->value();
            if (roll >= 1 && roll < 10)
            {
                rollEdit->setPrefix("0");
            }

            // Code to remove student details from text file

            QString filename = classFolder + comboBox->currentText() + batchEdit->text() + ".txt";
            QFile file(filename);

            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QStringList students;
                QTextStream stream(&file);
                while (!stream.atEnd())
                {
                    students << stream.readLine();
                }

                for (int i = 0; i < students.size(); i++)
                {
                    QStringList fields = students[i].split(" ");
                    int j = 0;

                    while (j < fields.size())
                    {
                        if (fields[j] == rollEdit->text())
                        {
                            students.removeAt(i);
                            break;
                        }
                        else
                        {
                            j++;
                        }
                    }
                }

                file.close();

                if (file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QTextStream stream(&file);
                    for (const QString &student : students)
                    {
                        stream << student << "\n";
                    }
                }

                file.close();
            }
            else
            {
                this->showMessage("Data File Does'nt Exist");
                deleteStudentPage->close();
            }

            // Code to delete Images in faces folder

            QString faceFolder = classFolder + "faces";
            QDir fdir(faceFolder);

            if (fdir.exists())
            {
                QStringList filters;
                filters << rollEdit->text() + "*.jpg";

                fdir.setNameFilters(filters);

                QStringList imageFiles = fdir.entryList();

                if(fdir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries).empty())
                {
                    isFaceDeleted = true;
                    this->showMessage("No Images to delete");
                    deleteStudentPage->close();
                }

                for (int i = 0; i < imageFiles.size(); i++)
                {
                    QFile file(fdir.path() + "/" + imageFiles.at(i));
                    file.remove();
                }

                QDir kdir(faceFolder);

                if(!isFaceDeleted)
                {
                    if(kdir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries).empty())
                    {
                        deleteStudentPage->close();
                        this->showMessage("Images deleted, no more Images");
                    }
                    else
                    {
                        AddStudent S(classFolder, rollEdit);
                        S.eigenFaceTrainer();

                        deleteStudentPage->close();
                        this->showMessage("Data Deleted Successfully");
                    }
                }

            }
            else
            {
                deleteStudentPage->close();
                this->showMessage("Face directory does'nt exist");
            }
        }
        else
        {
            deleteStudentPage->close();
            this->showMessage("Directory doesn't exist");
        }
    });

    connect(back, &QPushButton::clicked, [this, deleteStudentPage]()
    {
        this->hide();
        menu->show();
        deleteStudentPage->close();
    });

    deleteStudentPage->setLayout(layout);
    deleteStudentPage->show();
    menu->close();
}

void Home::showMenu()
{
    menu = new QMainWindow;
    menu->setWindowTitle("AMS");
    menu->setFixedSize(432, 768);

    QLabel *bg = new QLabel(menu);
    bg->setPixmap(QPixmap("bgs/3.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    QPushButton *recognizeFace = new QPushButton("Attendance", menu);
    recognizeFace->setGeometry(166, 240, 120, 40);

    QPushButton *addStudent = new QPushButton("Add Student", menu);
    addStudent->setGeometry(166, 340, 120, 40);

    QPushButton *deleteStudent = new QPushButton("Delete Student", menu);
    deleteStudent->setGeometry(166, 440, 120, 40);

    QPushButton *back = new QPushButton("Back", menu);
    back->setGeometry(166, 540, 120, 40);

    connect(recognizeFace, &QPushButton::clicked, this, &Home::recognizeFaceButton);

    connect(back, &QPushButton::clicked, [this]()
    {
        this->show();
        menu->close();
    });

    connect(addStudent, &QPushButton::clicked, this, &Home::addStudentButton);

    connect(deleteStudent, &QPushButton::clicked, this, &Home::deleteStudentButton);

    this->hide();
    menu->show();
}

Home::Home()
{
    setWindowTitle("AMS");
    setFixedSize(432, 768);

    QLabel *bg = new QLabel(this);
    bg->setPixmap(QPixmap("bgs/1.jpg"));
    bg->setScaledContents(true);
    bg->resize(432, 768);

    QPushButton *enter = new QPushButton("Enter", this);
    enter->setGeometry(166, 240, 100, 40);

    connect(enter, &QPushButton::clicked, this, &Home::showMenu);
}

Home::~Home()
{
}
