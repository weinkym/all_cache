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
    setAttribute(Qt::WA_TranslucentBackground);

    m_viewAnimation = new CLJLotteryAnimationView;
    ui->viewLayout->addWidget(m_viewAnimation);

    m_viewResult = new CLJLotteryResultView;
    ui->viewLayout->addWidget(m_viewResult);

    m_viewResult->setBackgroundBrush(QBrush(Qt::darkBlue));
    m_viewResult->setVisible(false);


//    CLJLotteryManager::getInstance()
    connect(CLJLotteryManager::getInstance(),SIGNAL(sigLotteryFinished(int)),this,SLOT(onLotteryFinished(int)));
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
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

void CLJLotterResultDialog::showResult(bool show)
{
    m_viewAnimation->setVisible(!show);
    m_viewResult->setVisible(show);
}
