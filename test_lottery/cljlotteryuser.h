#ifndef CLJLOTTERYUSER_H
#define CLJLOTTERYUSER_H

#include <QObject>
#include <QPixmap>
class CLJLotteryUser : public QObject
{
    Q_OBJECT

public:
    enum RequestStatus{
        REQUEST_STATUS_NORMAL,
        REQUEST_STATUS_STARTING,
        REQUEST_STATUS_FINISHED,
        REQUEST_STATUS_FAIL,
    };
    CLJLotteryUser(QObject *parent = Q_NULLPTR);
    CLJLotteryUser(const QString &id,const QString &name,const QString &url,QObject *parent = Q_NULLPTR);
    ~CLJLotteryUser();
    void loadImage();
    bool isLoading();
    QPixmap getPixmap();
    QString getId();

signals:
    void sigDownloadFinished(const QString &id,int error);

private:
    RequestStatus m_status;
    QString m_id;
    QString m_name;
    QString m_url;
    QPixmap m_pixmap;
};

//Q_DECLARE_METATYPE(CLJLotteryUser)

#endif // CLJLOTTERYUSER_H
