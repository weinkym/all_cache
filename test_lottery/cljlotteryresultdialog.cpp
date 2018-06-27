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
    m_viewAnimation = new CLJLotteryAnimationView;
    ui->vLayoutAnimation->addWidget(m_viewAnimation);

    m_viewResult = new CLJLotteryResultView;
    ui->vLayoutResult->addWidget(m_viewResult);

//    CLJLotteryManager::getInstance()
    connect(CLJLotteryManager::getInstance(),SIGNAL(sigLotteryFinished(int)),this,SLOT(onLotteryFinished(int)));
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
    ui->stackedWidget->setCurrentWidget(ui->pageAnimation);
    CLJLotteryManager::getInstance()->testAll();
}

void CLJLotterResultDialog::on_pushButtonResult_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageResult);
}

void CLJLotterResultDialog::onLotteryFinished(int error)
{
    m_viewAnimation->stop();
    m_viewResult->updateResult(CLJLotteryManager::getInstance()->getSelectedUsers());
    ui->stackedWidget->setCurrentWidget(ui->pageResult);
}

void CLJLotterResultDialog::on_pushButtonStop_clicked()
{
    CLJLotteryManager::getInstance()->testStop();
}
