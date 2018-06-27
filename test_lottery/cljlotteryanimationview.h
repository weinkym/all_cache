#ifndef CLJLOTTERYANIMATIONVIEW_H
#define CLJLOTTERYANIMATIONVIEW_H
#include <QGraphicsView>
#include <QTimer>

class QGraphicsScene;
class CLJLotteryUserItem;
class CLJLotteryAnimationView : public QGraphicsView
{
    Q_OBJECT

public:
    CLJLotteryAnimationView(QWidget *parent = Q_NULLPTR);
    ~CLJLotteryAnimationView();
    void stop();

private slots:
    void onTimeout();
    void onUserDataReady(int count);

private:
    void startShow();

private:
    QGraphicsScene *m_scene;
    int m_row;
    int m_col;
    int m_margin;
    QSize m_itemSize;
    QTimer m_timer;
    QList<CLJLotteryUserItem*> m_itemList;
};

#endif // CLJLOTTERYANIMATIONVIEW_H
