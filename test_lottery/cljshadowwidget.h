#ifndef CLJSHADOWWIDGET_H
#define CLJSHADOWWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QDoubleSpinBox>
#include "cljshadowengine.h"

class CLJShadowWidget : public QWidget
{
    Q_OBJECT
public:
    CLJShadowWidget(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~CLJShadowWidget();

protected:
    void paintEvent(QPaintEvent *event);

private:
   CLJShadowEngine m_shadowEngine;
};

#endif // CLJSHADOWWIDGET_H
