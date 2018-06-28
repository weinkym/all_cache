#include "cljshadowwidget.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QTextEdit>

CLJShadowWidget::CLJShadowWidget(QWidget *parent, Qt::WindowFlags f)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    m_color = QColor(128,128,128,22);
    m_radius = 10;
    m_shawPos = 1;
    this->setContentsMargins(m_radius,m_radius,m_radius,m_radius);

    QVBoxLayout *vlayout = new QVBoxLayout;
    QTextEdit *textEdit = new QTextEdit;
    vlayout->addWidget(textEdit);
    this->setLayout(vlayout);
    vlayout->setSpacing(0);
    vlayout->setMargin(0);
    m_doubleSpinBox = new QDoubleSpinBox;
    m_doubleSpinBox->setMinimum(0.0);
    m_doubleSpinBox->setMaximum(5);
    m_doubleSpinBox->setSingleStep(0.01);
    m_doubleSpinBox->setValue(2);
    vlayout->addWidget(m_doubleSpinBox);
    connect(m_doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(onValueChanged()));
}

CLJShadowWidget::~CLJShadowWidget()
{

}

void CLJShadowWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    int r = m_radius;
    painter.setPen(QPen(Qt::NoPen));
    {
        QRect rect(0,0,r,r);
        painter.setBrush(getBrush(rect.bottomRight(),r));
        painter.drawRect(rect);
    }
    {
        QRect rect(0,this->height() - r,r,r);
        painter.setBrush(getBrush(rect.topRight(),r));
        painter.drawRect(rect);
    }
    {
        QRect rect(this->width() - r,0,r,r);
        painter.setBrush(getBrush(rect.bottomLeft(),r));
        painter.drawRect(rect);
    }
    {
        QRect rect(this->width() - r,this->height() - r,r,r);
        painter.setBrush(getBrush(rect.topLeft(),r));
        painter.drawRect(rect);
    }
    qreal dd = 1.8;
    {
        setLineGradientPainter(&painter,QPointF(r,0),QPointF(0-dd,0));
        painter.drawRect(QRect(0,m_radius,m_radius,this->height() - 2 * r));
    }
    {
        setLineGradientPainter(&painter,QPointF(this->width() - r,0),QPointF(this->width(),0));
        painter.drawRect(QRect(this->width() - r,m_radius,m_radius,this->height() - 2 * r));
    }
    {
        setLineGradientPainter(&painter,QPointF(m_radius,m_radius),QPointF(m_radius,-dd));
        painter.drawRect(QRect(m_radius,0,this->width() - 2 * m_radius,m_radius));
    }
    {
        setLineGradientPainter(&painter,QPointF(m_radius,this->height() - m_radius),QPointF(m_radius,this->height()));
        painter.drawRect(QRect(m_radius,this->height() - m_radius,this->width() - 2 * m_radius,m_radius));
    }
    QWidget::paintEvent(event);
}

QBrush CLJShadowWidget::getBrush(const QPoint &center, int radius)
{
    QRadialGradient radialGradient(center,radius,center);
    radialGradient.setColorAt(0, m_color);
    radialGradient.setColorAt(1 - m_shawPos, m_color);
    radialGradient.setColorAt(1,QColor(m_color.red(),m_color.green(),m_color.blue(),0));
    return QBrush(radialGradient);
}

void CLJShadowWidget::setLineGradientPainter(QPainter *painter, const QPointF &startPoint, const QPointF &endPoint)
{
    QLinearGradient linearGradient(startPoint,endPoint);
    linearGradient.setColorAt(0,m_color);
    linearGradient.setColorAt(1- m_shawPos,m_color);
    linearGradient.setColorAt(1,QColor(m_color.red(),m_color.green(),m_color.blue(),0));
    painter->setBrush(QBrush(linearGradient));
}

void CLJShadowWidget::onValueChanged()
{
    this->update();

}
