#ifndef CLJLOTTERYUSERITEM_H
#define CLJLOTTERYUSERITEM_H

#include <QGraphicsItem>
#include "cljlotterymanager.h"

class CLJLotteryUserItem : public QGraphicsPixmapItem
{

public:
    CLJLotteryUserItem(const QSharedPointer<CLJLotteryUser> &obj,CLJLotteryManager::ImageType &type,
                       bool isWinner,QGraphicsItem *parent = Q_NULLPTR);
    ~CLJLotteryUserItem();

private:
    void updateConttent();

private:
    QSharedPointer<CLJLotteryUser> m_userObj;
    bool m_isWinner;
    CLJLotteryManager::ImageType m_imageType;
};

#endif // CLJLOTTERYUSERITEM_H
