#ifndef CLJLOTTERYMANAGER_H
#define CLJLOTTERYMANAGER_H

#include <QObject>
#include <QPixmap>
#include <QSharedPointer>
#include "cljlotteryuser.h"
#include <QDebug>

class CLJLotteryManager : public QObject
{
    Q_OBJECT

public:
    enum LotteryStatus{
        LOTTERY_STATUS_NORMAL,
        LOTTERY_STATUS_STARTING,
        LOTTERY_STATUS_FINISHED,
    };
    enum ImageType{
        IMAGE_TYPE_ONE,
        IMAGE_TYPE_TWO,
        IMAGE_TYPE_THREE,
    };

    struct UserAvatarParam{
        UserAvatarParam(ImageType type,bool isWinner);
        int penWidth;
        qreal fontPixelSizeF;
        QSize itemSize;
        QRect avatarRect;
        QRect labelRect;
        QRect winnerLableRect;
        QRect nameRect;
    };

    struct ViewParam{
        ViewParam(int lotteryCount,bool isWinner);
        UserAvatarParam avatarParam;
        ImageType imageType;
        int col;
        int row;
        int margin_h;
        int margin_v;
    };

    static CLJLotteryManager* getInstance();

    static QPixmap createEllipsePixmap(const QPixmap &pixmap);

    static QString getImageTypeString(ImageType type);

    static QPixmap getUserLablePixmap(ImageType type,bool isWinner,int devicePixelRatio);
    static QPixmap getWinnerLablePixmap(ImageType type,int devicePixelRatio);

    QPixmap getUserPixmap(ImageType type,bool isWinner,int devicePixelRatio = 1);

    QPixmap createUserPixmap(const QSharedPointer<CLJLotteryUser> &user,ImageType type,bool isWinner,int devicePixelRatio);
    QPixmap createUserPixmap(const QSharedPointer<CLJLotteryUser> &user,ImageType type,bool isWinner);

    QPixmap createUserPixmap(const QPixmap &avatarPixmap,ImageType type,bool isWinner,int devicePixelRatio,const QString &name);


    int getApplicationDevicePixelRatio();

    int getUserReadyCount();
    int getLotteryCount();
    QString getLotteryTitle();
    void setItemSize(const QSize &size);
    void setCacheCount(int count);
    QList<QSharedPointer<CLJLotteryUser> > getSelectedUsers();

    void testAll();
    void stop();

private slots:
    void onUserDownloadFinished(const QString &id,int error);

private:
    void request();
    void appendUser(const QString &json);
    static QString createKey(const QString &id,ImageType type,bool isWinner,int devicePixelRatio);
    QSharedPointer<CLJLotteryUser> loadOneImage();


signals:
    void sigUserDataReady();
    void sigLotteryFinished(int error);
    void sigUserAvatarUpdate(const QString &id);

protected:
    CLJLotteryManager();
    static CLJLotteryManager* m_instance;
    LotteryStatus m_status;
    int m_lotteryId = 0;
    int m_cacheCount = 30;
    int m_repeatIndex = 0;
    int m_lotteryCount = 3;
    QPixmap m_defaultAvatar;
    QString m_lotteryTitle;
    QSize m_itemSize;

    QList<QSharedPointer<CLJLotteryUser> >m_finishedUserList;
    QList<QSharedPointer<CLJLotteryUser> > m_loadUserList;

    QList<QSharedPointer<CLJLotteryUser> > m_unDownloadUserList;
    QHash<QString,QSharedPointer<CLJLotteryUser> > m_downloadingUserMap;

    QList<QSharedPointer<CLJLotteryUser> > m_selectedUserList;
    QHash<QString,QSharedPointer<CLJLotteryUser> > m_allUserMap;
    QHash<QString,QPixmap> m_cechePixmapMap;
};

#endif // CLJLOTTERYMANAGER_H
