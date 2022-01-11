#ifndef WEBSOCKETTRANSPORT_H
#define WEBSOCKETTRANSPORT_H

#include <QObject>
#include <QWebChannelAbstractTransport>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

namespace LTDev {


class WebSocketTransport : public QWebChannelAbstractTransport
{
    Q_OBJECT

public:
    Q_INVOKABLE void sendMessage(const QJsonObject &message) override
    {
        QJsonDocument doc(message);
        emit messageChanged(QString::fromUtf8(doc.toJson(QJsonDocument::Compact)));
    }

    Q_INVOKABLE void textMessageReceive(const QString &messageData)
    {
        QJsonParseError error;
        QJsonDocument message = QJsonDocument::fromJson(messageData.toUtf8(), &error);
        if (error.error)
        {
            qWarning() << "Failed to parse text message as JSON object:" << messageData
                       << "Error is:" << error.errorString();
            return;
        } else if (!message.isObject())
        {
            qWarning() << "Received JSON message that is not an object: " << messageData;
            return;
        }
        emit messageReceived(message.object(), this);
    }

signals:
    void messageChanged(const QString & message);
};


}
#endif // WEBSOCKETTRANSPORT_H
