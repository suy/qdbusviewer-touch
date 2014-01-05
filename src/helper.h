#ifndef HELPER_H
#define HELPER_H

#include <QObject>

class QDBusModel;
class DBusObjectModel;

class Helper : public QObject
{
    Q_OBJECT
    public:
        explicit Helper(QObject* parent = 0);
        ~Helper();

        Q_INVOKABLE DBusObjectModel* makeModel(bool session, QString service, QString objectPath);

    private:
        QDBusModel* m_model;
};

#endif // HELPER_H

