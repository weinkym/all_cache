#ifndef CLJLOTTERYANIMATIONVIEW_H
#define CLJLOTTERYANIMATIONVIEW_H
#include <QGraphicsView>
#include <QTimer>
#include "cljlotterymanager.h"

class QGraphicsScene;
class CLJLotteryUserItem;
class CLJLotteryAnimationView : public QGraphicsView
{
    Q_OBJECT

public:
    CLJLotteryAnimationView(QWidget *parent = Q_NULLPTR);
    ~CLJLotteryAnimationView();
    void stop();
    void start(int selectCount);

protected:
    void wheelEvent(QWheelEvent *event);

private slots:
    void onTimeout();

private:
    QGraphicsScene *m_scene;
    CLJLotteryManager::ViewParam param;
    QTimer m_timer;
    QList<CLJLotteryUserItem*> m_itemList;
};

#endif // CLJLOTTERYANIMATIONVIEW_H
