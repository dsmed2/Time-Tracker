#include "dialog.h"
#include "ui_dialog.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog), countA(0), countP(0), countD(0), countJ(0)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ui->addButt, SIGNAL(clicked()), this, SLOT(addMin()));
    connect(ui->loadButt, SIGNAL(clicked()), this, SLOT(loadMin()));
    connect(ui->saveButt, SIGNAL(clicked()), this, SLOT(saveMin()));
}

void Dialog::addMin()
{
    ui->textEdit->append(ui->lineEdit_2->text());
    ui->textEdit->append(tr("Attendance:"));
    if (ui->dariusC->isChecked())
    {
        countD++;
    }
    QString charNum = QString::number(countD);
    ui->textEdit->append(tr("%1: %2").arg(ui->dariusL->text(), charNum));

    if (ui->parkerC->isChecked())
    {
        countP++;
    }
    charNum = QString::number(countP);
    ui->textEdit->append(tr("%1: %2").arg(ui->parkerL->text(), charNum));

    if (ui->jakeC->isChecked())
    {
        countJ++;
    }
    charNum = QString::number(countJ);
    ui->textEdit->append(tr("%1: %2").arg(ui->jakeL->text(), charNum));

    if (ui->alexC->isChecked())
    {
        countA++;
    }
    charNum = QString::number(countA);
    ui->textEdit->append(tr("%1: %2").arg(ui->alexL->text(), charNum));

    ui->textEdit->append(tr("Number of minutes: %1 \n").arg(ui->lineEdit->text()));
}

void Dialog::loadMin()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Grades"), "", tr("Homework Grades (*.abk);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_4_5);
        QString tempStr;
        QString tempNum;

        in >> tempStr;
        int size = tempStr.size();

        if (tempStr.isEmpty())
        {
            QMessageBox::information(this, tr("No Minutes in file"), tr("The file you are attempting to open contains no minutes"));
        }
        else
        {
            tempNum = tempStr[size-1];
            countA = tempNum.toInt();
            tempNum = tempStr[size-2];
            countJ = tempNum.toInt();
            tempNum = tempStr[size-3];
            countP = tempNum.toInt();
            tempNum = tempStr[size-4];
            countD = tempNum.toInt();
            tempStr.remove(size-4, size-1);
            ui->textEdit->setText(tempStr);
        }
    }
}

void Dialog::saveMin()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Grades"), "", tr("Timer Tracker (*.abk);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Unable to open file"), file.errorString());
            return;
        }

        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_4_5);

        QString temp(ui->textEdit->toPlainText());
        QString charNum = QString::number(countD);
        temp.push_back(charNum);
        charNum = QString::number(countP);
        temp.push_back(charNum);
        charNum = QString::number(countJ);
        temp.push_back(charNum);
        charNum = QString::number(countA);
        temp.push_back(charNum);
        out << temp;
    }
}

Dialog::~Dialog()
{
    delete ui;
}
