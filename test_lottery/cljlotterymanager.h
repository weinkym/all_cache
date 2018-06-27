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

    static CLJLotteryManager* getInstance();
    QPixmap getUserPixmap(const QSize &size,int devicePixelRatio = 1);

    QPixmap createUserPixmap(const QSharedPointer<CLJLotteryUser> &user,const QSize &size,int devicePixelRatio);

    int getUserReadyCount();
    int getLotteryCount();
    QString getLotteryTitle();
    void setItemSize(const QSize &size);
    void setCacheCount(int count);
    QList<QSharedPointer<CLJLotteryUser> > getSelectedUsers();

    void testAll();
    void testStop();

private slots:
    void onUserDownloadFinished(const QString &id,int error);

private:
    void request();
    void appendUser(const QString &json);
    static QString createKey(const QString &id,const QSize &size,int devicePixelRatio);

signals:
    void sigUserDataReady(int count);
    void sigLotteryFinished(int error);

protected:
    CLJLotteryManager();
    static CLJLotteryManager* m_instance;
    LotteryStatus m_status;
    int m_lotteryId = 0;
    int m_cacheCount = 30;
    int m_repeatIndex = 0;
    int m_lotteryCount = 3;
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