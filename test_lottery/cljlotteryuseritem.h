#ifndef CLJLOTTERYUSERITEM_H
#define CLJLOTTERYUSERITEM_H

#include <QGraphicsItem>

class CLJLotteryUserItem : public QGraphicsPixmapItem
{
//    Q_OBJECT
public:
    CLJLotteryUserItem(const QSize &size,QGraphicsItem *parent = Q_NULLPTR);
    ~CLJLotteryUserItem();
//    void setSize(const QSize &size);

    void updateConttent();
//    void start();

private:
    QPixmap m_pixmap;
    QSize m_size;
};

#endif // CLJLOTTERYUSERITEM_H
