#include "cljdialog.h"
#include <QVBoxLayout>
#include <QLineEdit>
CLJDialog::CLJDialog(QWidget *parent, Qt::WindowFlags f)
    :QDialog(parent,f)
{
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::Dialog);
//    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setShadowColor(QColor(55,55,55,11));
    setShadowRadius(29);
    setShadowWidth(3);
}

CLJDialog::~CLJDialog()
{

}

void CLJDialog::setShadowColor(const QColor &color)
{
    m_shadowEngine.setColor(color);
    this->update();
}

void CLJDialog::setShadowRadius(int radius)
{
    m_shadowEngine.setRadius(radius);
    this->update();
}

void CLJDialog::setShadowWidth(int width)
{
    m_shadowEngine.setShadowWidth(width);
    this->update();
}

void CLJDialog::paintEvent(QPaintEvent *event)
{
    m_shadowEngine.painterShadow(this);
    return QDialog::paintEvent(event);
}
