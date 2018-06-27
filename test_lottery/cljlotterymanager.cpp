#include "cljlotterymanager.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QApplication>

CLJLotteryManager *CLJLotteryManager::m_instance = NULL;
CLJLotteryManager *CLJLotteryManager::getInstance()
{
    if(!m_instance)
    {
        m_instance = new CLJLotteryManager;
    }
    return m_instance;
}

QPixmap CLJLotteryManager::getUserPixmap(const QSize &size, int devicePixelRatio)
{
    if(!m_unDownloadUserList.isEmpty())
    {
        request();
    }
    if(!m_finishedUserList.isEmpty())
    {
        QSharedPointer<CLJLotteryUser> obj = m_finishedUserList.takeFirst();
        m_loadUserList.append(obj);
        return createUserPixmap(obj,size,devicePixelRatio);
    }
    else if(!m_loadUserList.isEmpty())
    {
        m_repeatIndex = m_repeatIndex % m_loadUserList.count();
        return createUserPixmap(m_loadUserList.at(m_repeatIndex++),size,devicePixelRatio);
    }
    return QPixmap();

//    QSize size(ssize * devicePixelRatio);
//    QPixmap pixmap = QPixmap("/Users/miaozw/Pictures/test.jpeg")
//            .scaled(size,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
//    QPixmap userPixmap(size);
//    userPixmap.fill(QColor(77,77,77,50));
//    QPainter painter(&userPixmap);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing
//                           | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);


////    painter.setBrush(QBrush(pixmap));
////    QPen pen(Qt::white);
////    pen.setWidth(3);
////    painter.setPen(pen);
////    painter.drawEllipse(QRect(0,0,size.width(),size.height()));

//    {
//        static int index = 1;
//        QFont font;
//        font.setPixelSize(64);
//        painter.setFont(font);
//        QString text = QString::number(index++);
//        QPen pen(Qt::red);
//        painter.setPen(pen);
//        QFontMetrics fontMetrics(font);
//        QRect rect = fontMetrics.boundingRect(text);
//        painter.drawText(QRect((size.width() - rect.width()) / 2,(size.height() - rect.height()) / 2
//                               ,rect.width(),rect.height()),text);
//    }
//    userPixmap.setDevicePixelRatio(devicePixelRatio);
    //    return userPixmap;
}

QPixmap CLJLotteryManager::createUserPixmap(const QSharedPointer<CLJLotteryUser> &user, const QSize &size, int devicePixelRatio)
{
    QString key = createKey(user.data()->getId(),size,devicePixelRatio);
    if(m_cechePixmapMap.contains(key))
    {
        return m_cechePixmapMap.value(key);
    }

    if(src.isNull())
    {
        return QPixmap();
    }

    int devicePixelRatio = 2;
    QSize ssize(50,50);
    QSize size(ssize * devicePixelRatio);
    QPixmap pixmap = src.scaled(size,Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    QPixmap userPixmap(size);
    userPixmap.fill(QColor(77,77,77,50));
    QPainter painter(&userPixmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing
                           | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);


    painter.setBrush(QBrush(pixmap));
    QPen pen(Qt::white);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawEllipse(QRect(0,0,size.width(),size.height()));

    {
        static int index = 1;
        QFont font;
        font.setPixelSize(64);
        painter.setFont(font);
//        QString text = QString::number(index++);
        QString text = name;
        QPen pen(Qt::red);
        painter.setPen(pen);
        QFontMetrics fontMetrics(font);
        QRect rect = fontMetrics.boundingRect(text);
        painter.drawText(QRect((size.width() - rect.width()) / 2,(size.height() - rect.height()) / 2
                               ,rect.width(),rect.height()),text);
    }
    userPixmap.setDevicePixelRatio(devicePixelRatio);
    return userPixmap;
}

int CLJLotteryManager::getUserReadyCount()
{
    return m_finishedUserList.count();
}

int CLJLotteryManager::getLotteryCount()
{
    return m_lotteryCount;
}

QString CLJLotteryManager::getLotteryTitle()
{
    return m_lotteryTitle;
}

void CLJLotteryManager::setItemSize(const QSize &size)
{
    m_itemSize = size;
}

void CLJLotteryManager::setCacheCount(int count)
{
    m_cacheCount = count;
}

QList<QSharedPointer<CLJLotteryUser> > CLJLotteryManager::getSelectedUsers()
{
    return m_selectedUserList;
}

void CLJLotteryManager::testAll()
{
    if(m_unDownloadUserList.isEmpty())
    {
        appendUser("");
    }
}

void CLJLotteryManager::testStop()
{
    int count = qMin(6,m_allUserMap.count());
    int index = 0;

    m_selectedUserList.clear();
    for(int i = 0; i < count; ++i)
    {
        QString id = QString::number(i+10);
        if(m_allUserMap.contains(id))
        {
            m_selectedUserList.append(m_allUserMap.value(id));
        }
    }
    emit sigLotteryFinished(0);
//    while(index < count)
//    {
//        int id = qrand() % 100;

//    }
}

void CLJLotteryManager::onUserDownloadFinished(const QString &id, int error)
{
    if(!m_downloadingUserMap.contains(id))
    {
        return;
    }
//    qDebug()<<Q_FUNC_INFO<<m_downloadingUserMap.count();

    QSharedPointer<CLJLotteryUser> obj = m_downloadingUserMap.take(id);
//    qDebug()<<Q_FUNC_INFO<<"AA"<<m_downloadingUserMap.count();

    if(error == 0)
    {
        m_finishedUserList.append(obj);
        emit sigUserDataReady(m_finishedUserList.count());
    }
    else
    {
        request();
        //TODO 错误了是否还需要重新下载
//        m_unDownloadUserList.append(obj);
    }
}

void CLJLotteryManager::request()
{
    qDebug()<<Q_FUNC_INFO<<__LINE__;
    int downCount = m_cacheCount - m_downloadingUserMap.count();
    for(int i = 0; i < downCount;++i)
    {
        if(m_unDownloadUserList.isEmpty())
        {
            break;
        }
        QSharedPointer<CLJLotteryUser> obj = m_unDownloadUserList.takeFirst();
        m_downloadingUserMap.insert(obj.data()->getId(),obj);
        connect(obj.data(),SIGNAL(sigDownloadFinished(QString,int)),this,SLOT(onUserDownloadFinished(QString,int)));
        obj.data()->loadImage();
    }
}

void CLJLotteryManager::appendUser(const QString &json)
{
    for(int i = 0; i < 100; ++i)
    {
        QString id = QString::number(i);
        QString name = QString::number(i);
        QString url = QString("/Users/miaozw/Pictures/test/%1.png").arg(i);
        QSharedPointer<CLJLotteryUser> obj(new CLJLotteryUser(id,name,url));
        m_unDownloadUserList.append(obj);
        m_allUserMap.insert(id,obj);
    }
    request();
}

QString CLJLotteryManager::createKey(const QString &id, const QSize &size, int devicePixelRatio)
{
    return QString("id:=%1w=%2h=%3radio=%4").arg(id).arg(size.width()).arg(size.height()).arg(devicePixelRatio);
}

CLJLotteryManager::CLJLotteryManager()
    :m_status(LOTTERY_STATUS_NORMAL)
{

}
