#-------------------------------------------------
#
# Project created by QtCreator 2013-06-16T23:02:09
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GradeBook
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    mainwindow.cpp \
    gradewindow.cpp \
    coursedialog.cpp \
    criteriadialog.cpp \
    curvesdialog.cpp \
    databaseif.cpp \
    User.cpp \
    Account.cpp \
    Semester.cpp \
    Student.cpp \
    Instructor.cpp \
    TA.cpp \
    Activity.cpp \
    Grade.cpp \
    Course.cpp \
    Admin.cpp \
    Class.cpp \
    GradeBook.cpp \
    semesterdialog.cpp \
    deletedialog.cpp

HEADERS  += loginwindow.h \
    mainwindow.h \
    gradewindow.h \
    coursedialog.h \
    criteriadialog.h \
    curvesdialog.h \
    databaseif.h \
    User.h \
    Account.h \
    Semester.h \
    Student.h \
    Instructor.h \
    TA.h \
    Activity.h \
    Grade.h \
    Course.h \
    Admin.h \
    Class.h \
    GradeBook.h \
    GradeBook.h \
    semesterdialog.h \
    deletedialog.h

FORMS    += loginwindow.ui \
    mainwindow.ui \
    gradewindow.ui \
    coursedialog.ui \
    criteriadialog.ui \
    curvesdialog.ui \
    semesterdialog.ui \
    deletedialog.ui
