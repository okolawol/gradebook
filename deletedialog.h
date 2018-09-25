#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteDialog;
}

class DeleteDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DeleteDialog(QWidget *parent = 0);
    ~DeleteDialog();
    bool getChoice();
    
private slots:
    void on_yesPushButton_clicked();

    void on_noPushButton_clicked();

private:
    Ui::DeleteDialog *ui;
    bool choice;
};

#endif // DELETEDIALOG_H
