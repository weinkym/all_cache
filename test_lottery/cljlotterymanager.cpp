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

QPixmap CLJLotteryManager::createEllipsePixmap(const QPixmap &pixmap)
{
    if(pixmap.isNull())
    {
        return pixmap;
    }
    QPixmap resultPixmap(pixmap.width(),pixmap.height());
    resultPixmap.fill(QColor(0,0,0,0));
    QPainter p(&resultPixmap);
    p.setBrush(pixmap);
    QPen pen(Qt::NoPen);
    p.setPen(pen);
    p.drawEllipse(0,0,resultPixmap.width(),resultPixmap.height());
    return resultPixmap;
}

QString CLJLotteryManager::getImageTypeString(CLJLotteryManager::ImageType type)
{
    if(type == IMAGE_TYPE_ONE)
    {
        return "one";
    }
    else if(type == IMAGE_TYPE_THREE)
    {
        return "two";
    }
    else
    {
        return "three";
    }
}

QPixmap CLJLotteryManager::getUserLablePixmap(CLJLotteryManager::ImageType type, bool isWinner, int devicePixelRatio)
{
    static QMap<QString,QPixmap> s_cacheLablePixmapMap;
    QString key = createKey("",type,isWinner,devicePixelRatio);
    if(s_cacheLablePixmapMap.contains(key))
    {
        return s_cacheLablePixmapMap.value(key);
    }
    UserAvatarParam param(type,isWinner);

    QPixmap pixmap(QString(":/res/lottery/lottery_%1user_%2.png").arg(isWinner?"win_":"").arg(getImageTypeString(type)));
    qDebug()<<"QPixmap pixmap"<<(pixmap.isNull() ? "Y":"N");
    if(!pixmap.isNull())
    {
        pixmap = pixmap.scaled(param.labelRect.size()* devicePixelRatio,
                               Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    }
    else
    {
        pixmap = QPixmap(param.labelRect.size()* devicePixelRatio);
        pixmap.fill(QColor(128,128,128));
    }
    s_cacheLablePixmapMap.insert(key,pixmap);
    return pixmap;
}

QPixmap CLJLotteryManager::getWinnerLablePixmap(CLJLotteryManager::ImageType type, int devicePixelRatio)
{
    static QMap<QString,QPixmap> s_cacheLablePixmapMap;
    QString key = createKey("",type,true,devicePixelRatio);
    if(s_cacheLablePixmapMap.contains(key))
    {
        return s_cacheLablePixmapMap.value(key);
    }
    UserAvatarParam param(type,true);

    QPixmap pixmap(QString(":/res/lottery/lottery_win_label_%1.png").arg(getImageTypeString(type)));

    if(!pixmap.isNull())
    {
        pixmap = pixmap.scaled(param.winnerLableRect.size()* devicePixelRatio,
                                         Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    }
    else
    {
        pixmap = QPixmap(param.winnerLableRect.size()* devicePixelRatio);
        pixmap.fill(QColor(128,128,128));
    }
    s_cacheLablePixmapMap.insert(key,pixmap);
    return pixmap;
}

QPixmap CLJLotteryManager::getUserPixmap(ImageType type, bool isWinner, int devicePixelRatio)
{
    bool needRquest = true;
    QPixmap pixmap;
    if(!m_finishedUserList.isEmpty())
    {
        QSharedPointer<CLJLotteryUser> obj = m_finishedUserList.takeFirst();
        m_loadUserList.append(obj);
        pixmap = createUserPixmap(obj,type,isWinner,devicePixelRatio);
    }
    else if(!m_unDownloadUserList.isEmpty())
    {
        needRquest = false;
        QSharedPointer<CLJLotteryUser> obj = loadOneImage();
        pixmap = createUserPixmap(obj,type,isWinner,devicePixelRatio);
    }
    else if(!m_loadUserList.isEmpty())
    {
        m_repeatIndex = m_repeatIndex % m_loadUserList.count();
        pixmap = createUserPixmap(m_loadUserList.at(m_repeatIndex++),type,isWinner,devicePixelRatio);
    }
    if(needRquest)
    {
        loadOneImage();;
    }
    return pixmap;
}

QPixmap CLJLotteryManager::createUserPixmap(const QSharedPointer<CLJLotteryUser> &user, ImageType type, bool isWinner, int devicePixelRatio)
{
    if(user.isNull())
    {
        return m_defaultAvatar;
    }

    QString key = createKey(user.data()->getId(),type,isWinner,devicePixelRatio);
    if(m_cechePixmapMap.contains(key))
    {
        return m_cechePixmapMap.value(key);
    }
    QPixmap avatar = user.data()->getPixmap();
    QPixmap userPixmap = createUserPixmap(avatar,type,isWinner,devicePixelRatio,user.data()->getName());

    if(!avatar.isNull())
    {
        m_cechePixmapMap.insert(key,userPixmap);
    }
    return userPixmap;
}

QPixmap CLJLotteryManager::createUserPixmap(const QSharedPointer<CLJLotteryUser> &user, CLJLotteryManager::ImageType type, bool isWinner)
{
    return createUserPixmap(user,type,isWinner,getApplicationDevicePixelRatio());
}

QPixmap CLJLotteryManager::createUserPixmap(const QPixmap &avatarPixmap, CLJLotteryManager::ImageType type, bool isWinner, int devicePixelRatio, const QString &name)
{
    QPixmap avatarTemp = avatarPixmap;
    if(avatarTemp.isNull())
    {
        avatarTemp = m_defaultAvatar;
    }

    UserAvatarParam param(type,isWinner);
    QSize pixmapSize(param.itemSize * devicePixelRatio);

    avatarTemp = avatarTemp.scaled(param.avatarRect.size() * devicePixelRatio,
                                     Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation);
    avatarTemp = createEllipsePixmap(avatarTemp);

    QPixmap userPixmap(pixmapSize);
    userPixmap.fill(QColor(77,77,77,0));
    QPainter painter(&userPixmap);
//    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing
//                           | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    {
        painter.save();
        QPen pen(Qt::NoPen);
        painter.setPen(pen);
        painter.drawPixmap(param.avatarRect.x() * devicePixelRatio,param.avatarRect.y() *devicePixelRatio,avatarTemp);
        painter.restore();
    }
    {
        painter.save();
        QPen pen(Qt::white);
        pen.setWidth(6);
        painter.setPen(pen);
        painter.drawEllipse(QRectF(pen.widthF() / 2 + param.avatarRect.x() * devicePixelRatio,
                                   pen.widthF() / 2 + param.avatarRect.y() * devicePixelRatio,
                                   avatarTemp.width() - pen.widthF(),avatarTemp.height() - pen.widthF()));
        painter.restore();
    }
//    {
//        painter.save();
//        QPen pen(QColor(0,0,255,55));
//        pen.setWidth(6);
//        painter.setPen(pen);
//        painter.drawRect(QRect(0,0,pixmapSize.width(),pixmapSize.height()));
//        painter.restore();
//    }

    {
        QPixmap pixmap = getUserLablePixmap(type,isWinner,devicePixelRatio);
        painter.drawPixmap(param.labelRect.x() * devicePixelRatio,param.labelRect.y() * devicePixelRatio,pixmap);
    }
    {
        painter.save();
        QPen pen(QColor(255,255,255,255));
        painter.setPen(pen);
        QRect textRangeRect(param.nameRect.x() * devicePixelRatio,
                            param.nameRect.y() * devicePixelRatio,
                            param.nameRect.width() * devicePixelRatio,
                            param.nameRect.height() * devicePixelRatio);
        QFont font;
        font.setPointSizeF(param.fontPixelSizeF);
        painter.setFont(font);
        painter.drawText(textRangeRect,name,QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));
        painter.restore();
    }

    if(isWinner)
    {
        QPixmap pixmap = getWinnerLablePixmap(type,devicePixelRatio);
        painter.drawPixmap(param.winnerLableRect.x() * devicePixelRatio,param.winnerLableRect.y() * devicePixelRatio,pixmap);
    }

    userPixmap.setDevicePixelRatio(devicePixelRatio);
    return userPixmap;
}

int CLJLotteryManager::getApplicationDevicePixelRatio()
{
    return ((QApplication*)QApplication::instance())->devicePixelRatio();
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
    m_status = LOTTERY_STATUS_STARTING;
    if(m_unDownloadUserList.isEmpty())
    {
        appendUser("");
    }
}

void CLJLotteryManager::stop()
{
    if(m_status != LOTTERY_STATUS_STARTING)
    {
        return;
    }

    int count = qMin(m_lotteryCount,m_allUserMap.count());
    int index = 0;

    m_selectedUserList.clear();
    for(int i = 0; i < count; ++i)
    {
        QString id = QString::number(qrand() % m_allUserMap.count());
        if(m_allUserMap.contains(id))
        {
            QSharedPointer<CLJLotteryUser> obj = m_allUserMap.value(id);
            obj.data()->loadImage();
            m_selectedUserList.append(obj);
        }
    }
    m_status = LOTTERY_STATUS_FINISHED;
    emit sigLotteryFinished(0);
}

void CLJLotteryManager::onUserDownloadFinished(const QString &id, int error)
{
    if(!m_downloadingUserMap.contains(id))
    {
        return;
    }
    QSharedPointer<CLJLotteryUser> obj = m_downloadingUserMap.take(id);

    if(error == 0)
    {
        m_finishedUserList.append(obj);
    }
    else
    {
        request();
        //TODO 错误了是否还需要重新下载
//        m_unDownloadUserList.append(obj);
    }
    if(/*m_finishedUserList.count() >= m_lotteryCount && */m_status == LOTTERY_STATUS_STARTING)
    {
//        m_status = LOTTERY_STATUS_STARTING;
        emit sigUserDataReady();
    }

}

void CLJLotteryManager::request()
{
    int downCount = m_cacheCount - m_downloadingUserMap.count();
    for(int i = 0; i < downCount;++i)
    {
        if(m_unDownloadUserList.isEmpty())
        {
            break;
        }
        loadOneImage();
    }
}

void CLJLotteryManager::appendUser(const QString &json)
{
    if(m_status != LOTTERY_STATUS_STARTING)
    {
        return;
    }
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

QString CLJLotteryManager::createKey(const QString &id, ImageType type, bool isWinner, int devicePixelRatio)
{
    return QString("id:=%1type=%2isWinner=%3radio=%4").arg(id).arg(type).arg(isWinner?"Y":"N").arg(devicePixelRatio);
}

QSharedPointer<CLJLotteryUser> CLJLotteryManager::loadOneImage()
{
    if(m_unDownloadUserList.isEmpty())
    {
        return QSharedPointer<CLJLotteryUser>();
    }
    QSharedPointer<CLJLotteryUser> obj = m_unDownloadUserList.takeFirst();
    m_downloadingUserMap.insert(obj.data()->getId(),obj);
    connect(obj.data(),SIGNAL(sigDownloadFinished(QString,int)),this,SLOT(onUserDownloadFinished(QString,int)));
    obj.data()->loadImage();
    return obj;
}

CLJLotteryManager::CLJLotteryManager()
    :m_status(LOTTERY_STATUS_NORMAL)
    ,m_lotteryCount(6)
{
    m_defaultAvatar = QPixmap(":/res/lottery/lottery_default_avatar.png");
    if(m_defaultAvatar.isNull())
    {
        m_defaultAvatar = QPixmap(256,256);
        m_defaultAvatar.fill(QColor(128,128,128));
    }
    m_lotteryTitle = "TDJ";

}

CLJLotteryManager::ViewParam::ViewParam(int lotteryCount, bool isWinner)
    :avatarParam(IMAGE_TYPE_ONE,isWinner)
{
    row = 0;
    col = 0;
//    int selecteCount = selectCount;
//    selecteCount=6;
    if(lotteryCount <= 3)
    {
        row = 1;
        col = lotteryCount;
    }
    else if(lotteryCount <= 6)
    {
        row = 2;
        col = 3;
    }
    else
    {
        row = 2;
        col = 3;
    }
    int viewWidth = 354;
//    QSize m_itemSize = QSize(50,50);
    if(col == 1)
    {
        imageType = IMAGE_TYPE_ONE;
    }
    else if(col == 2)
    {
        imageType = IMAGE_TYPE_TWO;
    }
    else
    {
        imageType = IMAGE_TYPE_TWO;
    }
    avatarParam = UserAvatarParam(imageType,isWinner);
    margin_h = (viewWidth - col * avatarParam.itemSize.width()) / (col + 1);
    margin_v = 10;
}

CLJLotteryManager::UserAvatarParam::UserAvatarParam(CLJLotteryManager::ImageType type, bool isWinner)
{

    qreal base_fontPixelSizeF = 36;
    int base_avatartY = isWinner ? 5:0;
    int base_avatartX = 14;
    int base_winnerLableW = 38;
    int base_winnerLableH = 26;
    int base_winUserLableH = 45;
    int base_nameDH = base_winUserLableH * 15 / 54;
    QSize base_avatarSize(124,124);

    qreal radio = 1;


    if(type == IMAGE_TYPE_ONE)
    {
        radio = 1;
    }
    else if(type == IMAGE_TYPE_TWO)
    {
        radio = 1.0 * 84 / 124;
    }
    else
    {
        radio = 1.0 * 71 / 124;
    }

    int avatartY = base_avatartY * radio;
    int avatartX = base_avatartX * radio;
    int winnerLableW = base_winnerLableW * radio;
    int winnerLableH = base_winnerLableH * radio;
    int winUserLableH = base_winUserLableH * radio;
    int nameDH = base_nameDH * radio;
    QSize avatarSize = base_avatarSize * radio;

    penWidth = 10;
    avatarRect = QRect(avatartX,avatartY,avatarSize.width(),avatarSize.height());
    itemSize = QSize(avatarRect.width() + avatartX * 2,avatarRect.bottom());
    labelRect = QRect(0,avatarRect.center().y(),itemSize.width(),winUserLableH);
    winnerLableRect = QRect((itemSize.width() - winnerLableW) / 2,0,winnerLableW,winnerLableH);
    nameRect = QRect(labelRect.x(),labelRect.y() + nameDH,labelRect.width(),labelRect.height() - nameDH);
    fontPixelSizeF = base_fontPixelSizeF * radio;
}
