#include "cljlotteryresultview.h"
#include "cljlotteryuseritem.h"

CLJLotteryResultView::CLJLotteryResultView(QWidget *parent)
    :QGraphicsView(parent)
    ,m_scene(NULL)
{

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
    count=1;
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
    QSize m_itemSize = QSize(150 / col,150 / col);

    int m_margin = 5;
    QSize size(m_itemSize.width() + 2 * m_margin,m_itemSize.height() + 2 * m_margin);
    for(int i = 0; i < row; ++i)
    {
        int y = m_itemSize.height() * i + (2 * i + 1) * m_margin;
        for(int j = 0; j < col; ++j)
        {
            int x = m_itemSize.width() * j + (2 * j + 1) * m_margin;
            CLJLotteryUserItem *item = new CLJLotteryUserItem(m_itemSize);
            item->setPos(x,y);
//            item->setSize(QSize(40,40));
            m_scene->addItem(item);
//            m_itemList.append(item);

        }
    }
    {
        m_scene->addRect(QRect(0,0,size.width() * col,size.height() * row));
    }

}
