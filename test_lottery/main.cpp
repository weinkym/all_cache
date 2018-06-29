#include "mainwindow.h"
#include <QApplication>
#include "cljlotteryresultdialog.h"
#include "cljshadowwidget.h"
#include "cljdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

//    CLJShadowWidget w;
//    w.show();

//    CLJDialog dlg;
//    dlg.show();

    CLJLotterResultDialog dlg;
    dlg.show();

    return a.exec();
}
