#ifndef CLJSHADOWWIDGET_H
#define CLJSHADOWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDoubleSpinBox>

class CLJShadowWidget : public QWidget
{
    Q_OBJECT
public:
    CLJShadowWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~CLJShadowWidget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QBrush getBrush(const QPoint &center,int radius);
    void setLineGradientPainter(QPainter *painter,const QPointF &startPoint,const QPointF &endPoint);

private slots:
    void onValueChanged();

private:
    QColor m_color;
    int m_radius;
    qreal m_shawPos;
    QDoubleSpinBox *m_doubleSpinBox;
};

#endif // CLJSHADOWWIDGET_H
