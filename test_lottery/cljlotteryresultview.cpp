#include "cljlotteryresultview.h"
#include "cljlotteryuseritem.h"
#include <QWheelEvent>

CLJLotteryResultView::CLJLotteryResultView(QWidget *parent)
    :QGraphicsView(parent)
    ,m_scene(NULL)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

CLJLotteryResultView::~CLJLotteryResultView()
{
    this->setScene(NULL);
    if(m_scene)
    {
        m_scene->deleteLater();
        m_scene = NULL;
    }
}

void CLJLotteryResultView::updateResult(const QList<QSharedPointer<CLJLotteryUser> > &userList)
{
    if(!m_scene)
    {
        m_scene = new QGraphicsScene;
        this->setScene(m_scene);
    }
    else
    {
        m_scene->clear();
    }
    CLJLotteryManager::ViewParam param = CLJLotteryManager::ViewParam(userList.count(),false);

    int row = param.row + 1;
    int x = param.margin_h;
    int y = param.margin_v / 2;
    qDebug()<<"param.avatarParam.itemSize.width()"<<param.avatarParam.itemSize.width()<<param.margin_h;
    int index = 0;
    for(int i = 0; i < row; ++i)
    {
        x = param.margin_h;
        for(int j = 0; j < param.col; ++j)
        {
            if(index < userList.count())
            {
                CLJLotteryUserItem *item = new CLJLotteryUserItem(userList.at(index),param.imageType,true);
                index++;
                item->setPos(x,y);
                m_scene->addItem(item);
            }
            x = x + param.avatarParam.itemSize.width() + param.margin_h;
        }
        y = y + param.margin_v + param.avatarParam.itemSize.height();
    }
    QRect rect(0,0,(param.avatarParam.itemSize.width() + param.margin_h) * param.col + param.margin_h,
               y - param.margin_v / 2 - param.margin_v - param.avatarParam.itemSize.height());
    {
//        m_scene->addRect(rect,QPen(Qt::red),QBrush(QColor(12,0,0,77)));
    }
    this->setMinimumHeight(rect.height());
    this->setMaximumHeight(rect.height());
}

void CLJLotteryResultView::wheelEvent(QWheelEvent *event)
{
    event->accept();
}
