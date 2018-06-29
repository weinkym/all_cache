#ifndef CLJLotterResultDialog_H
#define CLJLotterResultDialog_H

#include <QDialog>
#include "cljdialog.h"

namespace Ui {
class CLJLotterResultDialog;
}

class CLJLotteryAnimationView;
class CLJLotteryResultView;

class CLJLotterResultDialog : public CLJDialog
{
    Q_OBJECT

public:
    explicit CLJLotterResultDialog(QWidget *parent = 0);
    ~CLJLotterResultDialog();

private slots:
    void on_pushButtonClose_clicked();

    void on_pushButton_2_clicked();

    void on_pushButtonResult_clicked();

    void onLotteryFinished(int error);

    void on_pushButtonStop_clicked();

    void on_pushButton_clicked();

    void onUserDataReady();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void showResult(bool show);

private:
    Ui::CLJLotterResultDialog *ui;
    CLJLotteryAnimationView *m_viewAnimation;
    CLJLotteryResultView *m_viewResult;
};

#endif // CLJLotterResultDialog_H
