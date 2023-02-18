# Attendance Marker Using Facial Recognition

A C++ program that uses facial recognition technology to mark attendance for events, classes, or meetings. 

The program is equipped with a graphical user interface (GUI) for easy usage.

## Requirements

OpenCV library for facial recognition.

Qt for GUI design and development.

## Features 

Ability to add new faces to the database for recognition.

Automatic recognition of registered faces.

GUI for easy attendance marking and management.

Records attendance in a text file for later analysis.

## Windows

- Install OpenCV, OpenCV contrib and QT on your system
  
- Clone or download this repository to your local system.
  
- Open the project in Qt, modify the necessary paths, and build the project.
  
- Run the executable file to start the program.
  
## Linux

- [QT installation](https://web.stanford.edu/dept/cs_edu/resources/qt/install-linux)
  
- [OpenCV and OpenCV Contrib installation](https://www.skynats.com/blog/installing-opencv-on-ubuntu-20-04/#)
    
- Clone or download this repository to your local system
    
- Open the project in Qt, modify the necessary paths and build the project
  
- Run the executable file to start the program 
    
## Usage    
    
- Start the program and navigate to the "Add Student" tab.

- Add student data to the database and then add face data by clicking the "Add face" button and capturing images of the individual by using any of the two options present:

    1. WebCam

    2. Video (In case of the this option video should be already present in database folder and it's relative path should be entered when prompted)

- Navigate to the "Mark attendance" tab to start the facial recognition process.

- Registered faces will be automatically recognized, and attendance will be marked in real-time.

- The attendance records can be viewed in the text file created in the folder of the batch entered automatically.

## Preview

![ams(1)](https://user-images.githubusercontent.com/85508314/219870048-682b438f-e9c5-40e1-9d5a-8e73c0b0da9d.jpg)
![ams(2)](https://user-images.githubusercontent.com/85508314/219870051-a9238672-e775-47a8-9902-46d9be5cc7c7.jpg)

## Limitations 

The program may not work as expected with low-quality images or poorly lit environments. 

Additionally, the program may not be able to recognize faces with significant changes such as facial hair, glasses, masks, etc.

## Team Members

- [Shivam Litoria](https://github.com/Litoriashiv)

- [Holesh Sharma](https://github.com/holesh01)
    
- [M Satya Sai Teja](https://github.com/imsatyasaiteja) (Myself)

## Contribute

If you would like to contribute to the development of this program, please feel free to submit a pull request.

## Note 

This Program has been written and tested on Ubuntu 22.04 LTS, using : 

- QT Creator 6.4.2

- Opencv 4.7.0

- Opencv Contrib 

To run the program, you need to make necessary changes to the code according to your system.

## License

This program is licensed under the MIT License.
