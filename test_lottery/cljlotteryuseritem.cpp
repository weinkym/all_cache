#include "cljlotteryuseritem.h"
#include "cljlotterymanager.h"

CLJLotteryUserItem::CLJLotteryUserItem(const QSharedPointer<CLJLotteryUser> &obj, CLJLotteryManager::ImageType &type,
                                       bool isWinner, QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
    ,m_userObj(obj)
    ,m_isWinner(isWinner)
    ,m_imageType(type)
{
    if(!m_userObj.isNull())
    {
         updateConttent();
         QObject::connect(obj.data(),&CLJLotteryUser::sigDownloadFinished,[this]{
            updateConttent();
         });
    }
}

CLJLotteryUserItem::~CLJLotteryUserItem()
{

}

void CLJLotteryUserItem::updateConttent()
{
    if(m_userObj.isNull())
    {
        return;
    }
    QPixmap pixmap = CLJLotteryManager::getInstance()->createUserPixmap(m_userObj,m_imageType,m_isWinner);
    if(pixmap.isNull())
    {
        return;
    }
    this->setPixmap(pixmap);
}

