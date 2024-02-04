#ifndef DATABASEMODULE_H
#define DATABASEMODULE_H


#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QSqlQuery>

enum class CLIENTS {
    ID = 0,
    PIB,
    ADDRESS,
    PHONE_NUMBER,
    IS_DELETE
};
typedef QHash <CLIENTS, QVariant> clientsObject_t;

enum class MANAGERS {
    ID = 0,
    PIB,
    ADDRESS,
    PHONE_NUMBER,
    IS_DELETE
};
typedef QHash <MANAGERS, QVariant> managersObject_t;

enum class SERVICES {
    ID = 0,
    TITLE,
    EQUIPMENT,
    DESCRIPTION,
    PRICE,
    IS_DELETE
};
typedef QHash <SERVICES, QVariant> servicesObject_t;

enum class ORDERS {
    NUMBER = 0,
    ID_CLIENT,
    ID_MANAGER,
    DATE,
    TOTAL_PRICE,
    STATUS_WORK,
    IS_DELETE
};
typedef QHash <ORDERS, QVariant> ordersObject_t;

enum class ORDERS_SERVICES {
    ID_ORDER = 0,
    ID_SERVICE,
    NUMBER
};
typedef QHash <ORDERS_SERVICES, QVariant> ordersServicesObject_t;

class DatabaseModule : public QObject
{
    Q_OBJECT

public:
    DatabaseModule(QObject *parent = nullptr);

    QSqlDatabase db;

    bool connect();
    void disconnect() { db.close(); }

    QSqlError lastError() { return db.lastError(); }

    void setDbName(QString name) { db.setDatabaseName(name); }
    void setHostAddress(QString address) { db.setHostName(address); }
    void setHostPort(int port) { db.setPort(port); }

    void selectTables();

    QSqlTableModel* clientsModel;
    QSqlTableModel* managersModel;
    QSqlTableModel* servicesModel;
    QSqlRelationalTableModel* ordersModel;
    QSqlRelationalTableModel* ordersServicesModel;

    QSqlQueryModel *reports_1_q;
    QSqlQuery reports_1_2_q;
    QSqlQueryModel *reports_2_q;
    QSqlQuery reports_2_2_q;
    QSqlQueryModel *reports_3_q;
};

#endif // DATABASEMODULE_H
