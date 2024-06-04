#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QPixmap ic;
    ic.load(":/stonks.png");
    w.setWindowIcon(ic);
    w.show();
    return a.exec();
}
