#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

public slots:
    void addMin();
    void loadMin();
    void saveMin();

private:
    int countD, countP, countJ, countA;
    Ui::Dialog *ui;
};

#endif // DIALOG_H
