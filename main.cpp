
#include <QApplication>
#include "imageview.h"
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /////////////////////1//////////////////
    MainWindow w;
    w.show();
    /////////////////////2/////////////////

//    QWidget *w;
//    w = new QWidget;
//    ImageView img(w);
//    w->show();

    return a.exec();
}
