#ifndef CLJLOTTERYUSERITEM_H
#define CLJLOTTERYUSERITEM_H

#include <QGraphicsItem>
#include "cljlotterymanager.h"

class CLJLotteryUserItem : public QGraphicsPixmapItem
{
//    Q_OBJECT
public:
    CLJLotteryUserItem(CLJLotteryManager::ImageType &type,bool isWinner,QGraphicsItem *parent = Q_NULLPTR);
    ~CLJLotteryUserItem();
//    void setSize(const QSize &size);

    void updateConttent();
//    void start();

private:
    QPixmap m_pixmap;
    bool m_isWinner;
    CLJLotteryManager::ImageType m_imageType;
};

#endif // CLJLOTTERYUSERITEM_H
