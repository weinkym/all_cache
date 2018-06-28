#include "cljlotteryresultdialog.h"
#include "ui_cljlotteryresultdialog.h"
#include "cljlotteryanimationview.h"
#include "cljlotterymanager.h"
#include "cljlotteryresultview.h"
#include "cljlotterymanager.h"

CLJLotterResultDialog::CLJLotterResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CLJLotterResultDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    m_viewAnimation = new CLJLotteryAnimationView;
    ui->viewLayout->addWidget(m_viewAnimation);

    m_viewResult = new CLJLotteryResultView;
    ui->viewLayout->addWidget(m_viewResult);

    m_viewResult->setVisible(false);

    connect(CLJLotteryManager::getInstance(),SIGNAL(sigLotteryFinished(int)),this,SLOT(onLotteryFinished(int)));
    connect(CLJLotteryManager::getInstance(),SIGNAL(sigUserDataReady()),this,SLOT(onUserDataReady()));
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    this->setContentsMargins(5,-5,5,5);
}

CLJLotterResultDialog::~CLJLotterResultDialog()
{
    delete ui;
}

void CLJLotterResultDialog::on_pushButtonClose_clicked()
{
    this->close();
}

void CLJLotterResultDialog::on_pushButton_2_clicked()
{
    showResult(false);
    CLJLotteryManager::getInstance()->testAll();
}

void CLJLotterResultDialog::on_pushButtonResult_clicked()
{
    showResult(true);
}

void CLJLotterResultDialog::onLotteryFinished(int error)
{
    qDebug()<<Q_FUNC_INFO<<error;
    m_viewAnimation->stop();
    m_viewResult->updateResult(CLJLotteryManager::getInstance()->getSelectedUsers());
    showResult(true);
}

void CLJLotterResultDialog::on_pushButtonStop_clicked()
{
    CLJLotteryManager::getInstance()->testStop();
}

void CLJLotterResultDialog::on_pushButton_clicked()
{
    showResult(m_viewAnimation->isVisible());

    //    ui->stackedWidget->setCurrentIndex((ui->stackedWidget->currentIndex() + 1) % ui->stackedWidget->count());
}

void CLJLotterResultDialog::onUserDataReady()
{
    m_viewAnimation->start(CLJLotteryManager::getInstance()->getLotteryCount());
    showResult(false);
}

void CLJLotterResultDialog::paintEvent(QPaintEvent *event)
{
    //通过绘制透明度渐变的多个圆角矩形来实现阴影
    int width = this->width();
    int height = this->height();
    static double shadow = 0.5;   //阴影的最大不透明度
    static quint64 size = 6;     //阴影宽度
    QPainter painter(this);
//    for(unsigned int i = 0; i < size; i++)
//    {
//        painter.setOpacity(shadow / size * i);
////        painter.drawRoundedRect(i, i + size, width - i * 2, height - i * 2 - size, size - i, size - i);
//        painter.drawRoundedRect(i, i + size, width - i * 2, height - i * 2 - size, size - i + 23, size - i + 23);
//    }
//    painter.
    {
        int size = 23;
        QPoint center(size,size);

        QRadialGradient gradient(center, size,center);
        //    QRadialGradient gradient(0, 50, 50, 50, 50);
        gradient.setColorAt(0, QColor::fromRgbF(0, 1, 0, 1));
        gradient.setColorAt(0.05, QColor::fromRgbF(0, 0, 1, 1));
        gradient.setColorAt(0.91, QColor::fromRgbF(1, 0, 1, 1));
        gradient.setColorAt(1, QColor::fromRgbF(1, 1, 0, 1));
        QBrush brush(gradient);
        painter.setBrush(brush);
//        painter.drawRoundedRect(0,0,size,size,size / 2,size /2);
        painter.drawRect(0,0,size,size);

    }

//    painter.drawRoundedRect(0,0,size,size,23,23);
    QDialog::paintEvent(event);
}

void CLJLotterResultDialog::showResult(bool show)
{
    m_viewAnimation->setVisible(!show);
    m_viewResult->setVisible(show);
}
