#include "cljlotteryanimationview.h"
#include <QGraphicsScene>
#include "cljlotteryuseritem.h"
#include "cljlotterymanager.h"
#include <QScrollBar>
#include <QWheelEvent>

CLJLotteryAnimationView::CLJLotteryAnimationView(QWidget *parent)
    :QGraphicsView(parent)
    ,m_scene(NULL)
    ,param(6,false)
{

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setMouseTracking(false);

    m_timer.setInterval(20);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
}

CLJLotteryAnimationView::~CLJLotteryAnimationView()
{
    this->setScene(NULL);
    if(m_scene)
    {
        m_scene->deleteLater();
        m_scene = NULL;
    }
}

void CLJLotteryAnimationView::stop()
{
    qDebug()<<Q_FUNC_INFO;
    m_timer.stop();
    m_itemList.clear();
    m_scene->clear();
    this->horizontalScrollBar()->setValue(0);
    this->horizontalScrollBar()->setMaximum(0);
    this->verticalScrollBar()->setValue(0);
    this->verticalScrollBar()->setMaximum(0);
}

void CLJLotteryAnimationView::start(int lotteryCount)
{
    if(m_timer.isActive())
    {
        return;
    }
    if(!m_scene)
    {
        m_scene = new QGraphicsScene;
        this->setScene(m_scene);
    }
    else
    {
        m_scene->clear();
        m_itemList.clear();
    }
    param = CLJLotteryManager::ViewParam(lotteryCount,false);

    int row = param.row + 1;
    int x = param.margin_h;
    int y = param.margin_v / 2;
    qDebug()<<"param.avatarParam.itemSize.width()"<<param.avatarParam.itemSize.width()<<param.margin_h;
    for(int i = 0; i < row; ++i)
    {
        x = param.margin_h;
        for(int j = 0; j < param.col; ++j)
        {
            CLJLotteryUserItem *item = new CLJLotteryUserItem(param.imageType,false);
            item->setPos(x,y);
            m_scene->addItem(item);
            x = x + param.avatarParam.itemSize.width() + param.margin_h;
//            qDebug()<<"boundingRect.width()"<<item->boundingRect().width();
            m_itemList.append(item);
        }
        y = y + param.margin_v + param.avatarParam.itemSize.height();
    }
    QRect rect(0,0,(param.avatarParam.itemSize.width() + param.margin_h) * param.col + param.margin_h,
               y - param.margin_v / 2 - param.margin_v - param.avatarParam.itemSize.height());
    {
        m_scene->addRect(rect,QPen(Qt::red),QBrush(QColor(12,0,0,77)));
    }
    this->setMinimumHeight(rect.height());
    this->setMaximumHeight(rect.height());
//    m_timer.start();
}

void CLJLotteryAnimationView::wheelEvent(QWheelEvent *event)
{
    return QGraphicsView::wheelEvent(event);
    event->accept();
}

void CLJLotteryAnimationView::onTimeout()
{
    int dy = 4;
    int row = param.row + 1;
    int itemHeight = param.avatarParam.itemSize.height() + param.margin_v;
    int contentHeight = itemHeight * row;
    for(auto obj:m_itemList)
    {
        QPointF pos = obj->pos();
        int y = pos.y() - dy;
        if(y + param.avatarParam.itemSize.height() < param.margin_v / 2)
        {
            y += contentHeight;
            obj->updateConttent();
        }
        obj->setPos(pos.x(),y);
    }
}
