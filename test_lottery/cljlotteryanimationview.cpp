#include "cljlotteryanimationview.h"
#include <QGraphicsScene>
#include "cljlotteryuseritem.h"
#include "cljlotterymanager.h"
#include <QScrollBar>

CLJLotteryAnimationView::CLJLotteryAnimationView(QWidget *parent)
    :QGraphicsView(parent)
    ,m_scene(NULL)
    ,m_row(2)
    ,m_col(3)
    ,m_margin(5)
    ,m_itemSize(50,50)
{
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_timer.setInterval(20);
    connect(&m_timer,SIGNAL(timeout()),this,SLOT(onTimeout()));
    connect(CLJLotteryManager::getInstance(),SIGNAL(sigUserDataReady(int)),this,SLOT(onUserDataReady(int)));
    onUserDataReady(CLJLotteryManager::getInstance()->getUserReadyCount());
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

void CLJLotteryAnimationView::startShow()
{
    if(!m_scene)
    {
        m_scene = new QGraphicsScene;
        this->setScene(m_scene);
    }
    QSize size(m_itemSize.width() + 2 * m_margin,m_itemSize.height() + 2 * m_margin);
    for(int row = 0; row < m_row; ++row)
    {
        int y = m_itemSize.height() * row + (2 * row + 1) * m_margin;
        for(int col = 0; col < m_col; ++col)
        {
            int x = m_itemSize.width() * col + (2 * col + 1) * m_margin;
            CLJLotteryUserItem *item = new CLJLotteryUserItem(m_itemSize);
            item->setPos(x,y);
            m_scene->addItem(item);
            m_itemList.append(item);

        }
    }
    {
        m_scene->addRect(QRect(0,0,size.width() * m_col,size.height() * m_row));
    }
    m_timer.start();
    this->setMinimumHeight(size.height() * m_row);
    this->setMaximumHeight(size.height() * m_row);
}

void CLJLotteryAnimationView::onTimeout()
{
    int dy = 4;
    int contentHeight = (m_itemSize.height() + 2 * m_margin) * m_row;
    for(auto obj:m_itemList)
    {
        QPointF pos = obj->pos();
        int y = pos.y() - dy;
        if(y + m_itemSize.height() < 0)
        {
//            obj->setToolTip(QString("posy=%1,y=%2").arg(pos.y()).arg(y));
            y += contentHeight;
            obj->updateConttent();
        }
        obj->setPos(pos.x(),y);
//        break;
    }
}

void CLJLotteryAnimationView::onUserDataReady(int count)
{
    if(m_timer.isActive())
    {
        return;
    }

    qDebug()<<"count"<<count;
    if(count > m_row * m_col)
    {
        startShow();
    }
}
