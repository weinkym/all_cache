#include "cljlotteryresultdialog.h"
#include "ui_cljlotteryresultdialog.h"
#include "cljlotteryanimationview.h"
#include "cljlotterymanager.h"
#include "cljlotteryresultview.h"
#include "cljlotterymanager.h"

CLJLotterResultDialog::CLJLotterResultDialog(QWidget *parent) :
    CLJDialog(parent),
    ui(new Ui::CLJLotterResultDialog)
{
    ui->setupUi(this);
    m_viewAnimation = new CLJLotteryAnimationView;
    ui->viewLayout->addWidget(m_viewAnimation);

    m_viewResult = new CLJLotteryResultView;
    ui->viewLayout->addWidget(m_viewResult);

    m_viewResult->setVisible(false);

    connect(CLJLotteryManager::getInstance(),SIGNAL(sigLotteryFinished(int)),this,SLOT(onLotteryFinished(int)));
    connect(CLJLotteryManager::getInstance(),SIGNAL(sigUserDataReady()),this,SLOT(onUserDataReady()));
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    this->setContentsMargins(5,5,5,5);

    showResult(false);
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

void CLJLotterResultDialog::on_pushButton_clicked()
{
    showResult(m_viewAnimation->isVisible());
}

void CLJLotterResultDialog::onUserDataReady()
{
    m_viewAnimation->start(CLJLotteryManager::getInstance()->getLotteryCount());
    showResult(false);
}


void CLJLotterResultDialog::showResult(bool show)
{
    ui->widgetTitle->setStyleSheet(QString("#widgetTitle{border-top-left-radius: 23px;border-top-right-radius: 23px;"
                                   "border-image: url(:/res/lottery/lottery_title%1.png) 0 0 0 0;}").arg(show ? "_win":""));
    ui->widgetStop->setVisible(!show);
    ui->pbStop->setEnabled(!show);
    m_viewAnimation->setVisible(!show);
    ui->pushButtonClose->setVisible(show);
    m_viewResult->setVisible(show);
}

void CLJLotterResultDialog::on_pbStop_clicked()
{
    ui->pbStop->setEnabled(false);
    CLJLotteryManager::getInstance()->stop();
}
