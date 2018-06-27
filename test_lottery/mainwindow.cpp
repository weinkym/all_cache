#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cljlotteryuseritem.h"
#include "cljlotterymanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    m_scene = new QGraphicsScene;
//    CLJLotteryUserItem *item = new CLJLotteryUserItem();
//    m_scene->addItem(item);
//    ui->graphicsView->setScene(m_scene);
    m_view = new CLJLotteryAnimationView;
    ui->vLayout->addWidget(m_view);
//    m_view->startShow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
//    QString path("/Users/miaozw/Pictures/test");
//    for(int i = 0; i < 100; ++i)
//    {
//        QPixmap pixmap = CLJLotteryUserManager::getInstance()->getUserPixmap(QSize(50,50),2);
//        pixmap.save(QString("%1/%2.png").arg(path).arg(i));
//    }
}
