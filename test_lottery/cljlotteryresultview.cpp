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
    int row = 0;
    int col = 0;
    int count = userList.count();
    count=6;
    if(count <= 3)
    {
        row = 1;
        col = count;
    }
    else if(count <= 6)
    {
        row = 2;
        col = 3;
    }
    else
    {
        return;
    }
    int viewWidth = 354;
    QSize m_itemSize = QSize(150 / col,150 / col);
    if(col == 1)
    {
        m_itemSize = QSize(124,124);
    }
    else if(col == 2)
    {
        m_itemSize = QSize(82,82);
    }
    else
    {
        m_itemSize = QSize(72,72);
    }
    int margin_h = (viewWidth - col * m_itemSize.width()) / (col + 1);
    int x = margin_h;
    int margin_v = 10;
    int y = margin_v / 2;
    int margin = 5;
    for(int i = 0; i < row; ++i)
    {
        x = margin_h;
        for(int j = 0; j < col; ++j)
        {
//            int x = m_itemSize.width() * j + (2 * j + 1) * m_margin;
            CLJLotteryUserItem *item = new CLJLotteryUserItem(m_itemSize);
            item->setPos(x,y);
//            item->setSize(QSize(40,40));
            m_scene->addItem(item);
//            m_itemList.append(item);
            x = x + m_itemSize.width() + margin_h;
        }
        y = y + margin_v + m_itemSize.height();
    }
    QRect rect(0,0,viewWidth,y - margin_v / 2);
    {
        m_scene->addRect(rect,QPen(Qt::red));
    }
    this->setMinimumHeight(rect.height());
    this->setMaximumHeight(rect.height());
    //    this->adjustSize();
}

void CLJLotteryResultView::wheelEvent(QWheelEvent *event)
{
    event->accept();
}
