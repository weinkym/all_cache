#include "mainwindow.h"
#include <QApplication>
#include "cljlotteryresultdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    CLJLotterResultDialog dlg;
    dlg.show();

    return a.exec();
}
