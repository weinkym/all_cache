#include "cljlotteryuser.h"
#include "cljlotterymanager.h"
#include <QTimer>

CLJLotteryUser::CLJLotteryUser(QObject *parent)
    :QObject(parent)
{

}

CLJLotteryUser::CLJLotteryUser(const QString &id, const QString &name, const QString &url,QObject *parent)
    :QObject(parent)
    ,m_status(REQUEST_STATUS_NORMAL)
    ,m_id(id)
    ,m_name(name)
    ,m_url(url)
{

}

CLJLotteryUser::~CLJLotteryUser()
{

}

void CLJLotteryUser::loadImage()
{
    if(isLoading())
    {
        return;
    }
    m_status = REQUEST_STATUS_STARTING;
    QTimer::singleShot(3500, [this]{
//        qDebug()<<"url="<<m_url;
//        m_pixmap = CLJLotteryManager::createUserPixmap(QPixmap(m_url),m_name);
        m_pixmap = QPixmap(m_url);
        emit sigDownloadFinished(m_id,m_pixmap.isNull() ? 1:0);
    });
}

bool CLJLotteryUser::isLoading()
{
    return m_status == REQUEST_STATUS_STARTING;
}

QPixmap CLJLotteryUser::getPixmap()
{
    return m_pixmap;
}

QString CLJLotteryUser::getId()
{
    return m_id;
}

QString CLJLotteryUser::getName()
{
    return m_name;
}
