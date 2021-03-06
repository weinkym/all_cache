#include "cljshadowengine.h"
#include <QPainter>
#include <QWidget>
#include <QBrush>
#include <QPen>

CLJShadowEngine::CLJShadowEngine()
{
    m_color = QColor(33,33,33,55);
    m_radius = 23;
    m_shawWidth = 6;
}

CLJShadowEngine::~CLJShadowEngine()
{

}

void CLJShadowEngine::setColor(const QColor &color)
{
    m_color = color;
}

void CLJShadowEngine::setRadius(int radius)
{
    if(radius >= 0)
    {
        m_radius = radius;
    }
}

void CLJShadowEngine::setShadowWidth(int width)
{
    if(width >= 0)
    {
        m_shawWidth = width;
    }
}

void CLJShadowEngine::painterShadow(QWidget *widget)
{
    if(m_radius <= 0 || m_shawWidth <= 0)
    {
        return;
    }
    QPainter painter(widget);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    int r = m_radius;
    painter.setPen(QPen(Qt::NoPen));
    {
        QRect rect(0,0,r,r);
        painter.setBrush(getBrush(rect.bottomRight(),r));
        painter.drawRect(rect);
    }
    {
        QRect rect(0,widget->height() - r,r,r);
        painter.setBrush(getBrush(rect.topRight(),r));
        painter.drawRect(rect);
    }
    {
        QRect rect(widget->width() - r,0,r,r);
        painter.setBrush(getBrush(rect.bottomLeft(),r));
        painter.drawRect(rect);
    }
    {
        QRect rect(widget->width() - r,widget->height() - r,r,r);
        painter.setBrush(getBrush(rect.topLeft(),r));
        painter.drawRect(rect);
    }
    qreal dd = 1.8;
    {
        setLineGradientPainter(&painter,QPointF(r,0),QPointF(0-dd,0));
        painter.drawRect(QRect(0,m_radius,m_radius,widget->height() - 2 * r));
    }
    {
        setLineGradientPainter(&painter,QPointF(widget->width() - r,0),QPointF(widget->width(),0));
        painter.drawRect(QRect(widget->width() - r,m_radius,m_radius,widget->height() - 2 * r));
    }
    {
        setLineGradientPainter(&painter,QPointF(m_radius,m_radius),QPointF(m_radius,-dd));
        painter.drawRect(QRect(m_radius,0,widget->width() - 2 * m_radius,m_radius));
    }
    {
        setLineGradientPainter(&painter,QPointF(m_radius,widget->height() - m_radius),QPointF(m_radius,widget->height()));
        painter.drawRect(QRect(m_radius,widget->height() - m_radius,widget->width() - 2 * m_radius,m_radius));
    }
}

qreal CLJShadowEngine::getShawPos()
{
    if(m_shawWidth >= m_radius)
    {
        return 1;
    }
    if(m_radius <= 0)
    {
        return 0;
    }
    return 1.0 * m_shawWidth / m_radius;
}

QBrush CLJShadowEngine::getBrush(const QPoint &center, int radius)
{
    qreal shawPos = getShawPos();
    QRadialGradient radialGradient(center,radius,center);
    radialGradient.setColorAt(0, m_color);
    radialGradient.setColorAt(1 - shawPos, m_color);
    radialGradient.setColorAt(1,QColor(m_color.red(),m_color.green(),m_color.blue(),0));
    return QBrush(radialGradient);
}

void CLJShadowEngine::setLineGradientPainter(QPainter *painter, const QPointF &startPoint, const QPointF &endPoint)
{
    qreal shawPos = getShawPos();
    QLinearGradient linearGradient(startPoint,endPoint);
    linearGradient.setColorAt(0,m_color);
    linearGradient.setColorAt(1- shawPos,m_color);
    linearGradient.setColorAt(1,QColor(m_color.red(),m_color.green(),m_color.blue(),0));
    painter->setBrush(QBrush(linearGradient));
}
