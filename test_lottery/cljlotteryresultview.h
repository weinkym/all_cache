#ifndef CLJLOTTERYRESULTVIEW_H
#define CLJLOTTERYRESULTVIEW_H

#include <QGraphicsView>
#include <QGraphicsView>
#include "cljlotteryuser.h"

class QGraphicsScene;

class CLJLotteryResultView : public QGraphicsView
{
    Q_OBJECT

public:
    CLJLotteryResultView(QWidget *parent = Q_NULLPTR);
    ~CLJLotteryResultView();
    void updateResult(const QList<QSharedPointer<CLJLotteryUser> > &userList);

protected:
    void wheelEvent(QWheelEvent *event);

private:
    QGraphicsScene *m_scene;

};

#endif // CLJLOTTERYRESULTVIEW_H
