#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>

class MainWindow;
class GradeBook;
namespace Ui {
class LogInWindow;
}

class LogInWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit LogInWindow(QWidget *parent = 0);
    ~LogInWindow();
    
private slots:
    void on_logInButton_clicked();

private:
    Ui::LogInWindow *ui;
    MainWindow *w;
    GradeBook *gradeBook;
};

#endif // LOGINWINDOW_H
