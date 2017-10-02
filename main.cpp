#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setWindowFlags(Qt::Window);
    w.setFixedHeight(450);
    w.show();

    return a.exec();
}
