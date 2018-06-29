#include "cljshadowwidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QTextEdit>

CLJShadowWidget::CLJShadowWidget(QWidget *parent, Qt::WindowFlags f)
    :QWidget(parent,f)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);

    this->setContentsMargins(5,5,5,5);
    this->setBaseSize(100,30);
}

CLJShadowWidget::~CLJShadowWidget()
{

}

void CLJShadowWidget::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    int r = m_radius;
//    painter.setPen(QPen(Qt::NoPen));
//    {
//        QRect rect(0,0,r,r);
//        painter.setBrush(getBrush(rect.bottomRight(),r));
//        painter.drawRect(rect);
//    }
//    {
//        QRect rect(0,this->height() - r,r,r);
//        painter.setBrush(getBrush(rect.topRight(),r));
//        painter.drawRect(rect);
//    }
//    {
//        QRect rect(this->width() - r,0,r,r);
//        painter.setBrush(getBrush(rect.bottomLeft(),r));
//        painter.drawRect(rect);
//    }
//    {
//        QRect rect(this->width() - r,this->height() - r,r,r);
//        painter.setBrush(getBrush(rect.topLeft(),r));
//        painter.drawRect(rect);
//    }
//    qreal dd = 1.8;
//    {
//        setLineGradientPainter(&painter,QPointF(r,0),QPointF(0-dd,0));
//        painter.drawRect(QRect(0,m_radius,m_radius,this->height() - 2 * r));
//    }
//    {
//        setLineGradientPainter(&painter,QPointF(this->width() - r,0),QPointF(this->width(),0));
//        painter.drawRect(QRect(this->width() - r,m_radius,m_radius,this->height() - 2 * r));
//    }
//    {
//        setLineGradientPainter(&painter,QPointF(m_radius,m_radius),QPointF(m_radius,-dd));
//        painter.drawRect(QRect(m_radius,0,this->width() - 2 * m_radius,m_radius));
//    }
//    {
//        setLineGradientPainter(&painter,QPointF(m_radius,this->height() - m_radius),QPointF(m_radius,this->height()));
//        painter.drawRect(QRect(m_radius,this->height() - m_radius,this->width() - 2 * m_radius,m_radius));
//    }
    m_shadowEngine.painterShadow(this);
    QWidget::paintEvent(event);
}

