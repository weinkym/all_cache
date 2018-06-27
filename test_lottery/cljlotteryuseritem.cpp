#include "cljlotteryuseritem.h"
#include "cljlotterymanager.h"

CLJLotteryUserItem::CLJLotteryUserItem(const QSize &size, QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
    ,m_size(size)
{
    updateConttent();
}


CLJLotteryUserItem::~CLJLotteryUserItem()
{

}

//void CLJLotteryUserItem::setSize(const QSize &size)
//{
//    if(m_size == size || size.isValid() || size.isEmpty() || size.isNull())
//    {
//        return;
//    }
//    m_size = size;
//    updateConttent();
////    this->setPixmap(m_pixmap.scaled(size,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));
//}

void CLJLotteryUserItem::updateConttent()
{
    QPixmap pixmap = CLJLotteryManager::getInstance()->getUserPixmap(m_size,2);
    if(pixmap.isNull())
    {
        return;
    }
    this->setPixmap(pixmap);
    //
}

//void CLJLotteryUserItem::start()
//{
//    updateConttent();
//}