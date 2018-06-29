#ifndef CLJDIALOG_H
#define CLJDIALOG_H
#include <QDialog>
#include "cljshadowengine.h"

class CLJDialog : public QDialog
{
    Q_OBJECT

public:
    CLJDialog(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~CLJDialog();
    void setShadowColor(const QColor &color);
    void setShadowRadius(int radius);
    void setShadowWidth(int width);

protected:
    void paintEvent(QPaintEvent *event);

private:
    CLJShadowEngine m_shadowEngine;
};

#endif // CLJDIALOG_H
