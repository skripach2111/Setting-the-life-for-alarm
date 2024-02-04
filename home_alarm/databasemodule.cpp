#include "databasemodule.h"

#include <QDebug>

DatabaseModule::DatabaseModule(QObject *parent)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("home_alarm");
    db.setUserName("home_alarm_user");
    db.setPassword("home_alarm_user");
}

bool DatabaseModule::connect()
{
    if(db.open())
    {
        clientsModel = new QSqlTableModel(this);
        clientsModel->setTable("clients");
        clientsModel->setHeaderData((int)CLIENTS::PIB, Qt::Horizontal, "ПІБ");
        clientsModel->setHeaderData((int)CLIENTS::ADDRESS, Qt::Horizontal, "Адреса");
        clientsModel->setHeaderData((int)CLIENTS::PHONE_NUMBER, Qt::Horizontal, "Номер телефону");
        clientsModel->setFilter("isDelete != 1");
        clientsModel->select();

        managersModel = new QSqlTableModel(this);
        managersModel->setTable("managers");
        managersModel->setHeaderData((int)MANAGERS::PIB, Qt::Horizontal, "ПІБ");
        managersModel->setHeaderData((int)MANAGERS::ADDRESS, Qt::Horizontal, "Адреса");
        managersModel->setHeaderData((int)MANAGERS::PHONE_NUMBER, Qt::Horizontal, "Номер телефону");
        managersModel->setFilter("isDelete != 1");
        managersModel->select();

        servicesModel = new QSqlTableModel(this);
        servicesModel->setTable("services");
        servicesModel->setHeaderData((int)SERVICES::TITLE, Qt::Horizontal, "Назва");
        servicesModel->setHeaderData((int)SERVICES::EQUIPMENT, Qt::Horizontal, "Обладнання");
        servicesModel->setHeaderData((int)SERVICES::DESCRIPTION, Qt::Horizontal, "Опис");
        servicesModel->setHeaderData((int)SERVICES::PRICE, Qt::Horizontal, "Вартість");
        servicesModel->setFilter("isDelete != 1");
        servicesModel->select();

        ordersModel = new QSqlRelationalTableModel(this);
        ordersModel->setTable("orders");
        ordersModel->setRelation(1, QSqlRelation("clients", "id", "pib"));
        ordersModel->setRelation(2, QSqlRelation("managers", "id", "pib"));
        ordersModel->setHeaderData((int)ORDERS::NUMBER, Qt::Horizontal, "№");
        ordersModel->setHeaderData((int)ORDERS::ID_CLIENT, Qt::Horizontal, "Клієнт");
        ordersModel->setHeaderData((int)ORDERS::ID_MANAGER, Qt::Horizontal, "Менеджер");
        ordersModel->setHeaderData((int)ORDERS::DATE, Qt::Horizontal, "Дата");
        ordersModel->setHeaderData((int)ORDERS::TOTAL_PRICE, Qt::Horizontal, "Загальна вартість");
        ordersModel->setHeaderData((int)ORDERS::STATUS_WORK, Qt::Horizontal, "Статус");
        ordersModel->setFilter("orders.isDelete != 1");
        ordersModel->select();

        ordersServicesModel = new QSqlRelationalTableModel(this);
        ordersServicesModel->setTable("orders_services");
        ordersServicesModel->setRelation(1, QSqlRelation("services", "id", "title"));
        ordersServicesModel->setHeaderData((int)ORDERS_SERVICES::ID_ORDER, Qt::Horizontal, "№");
        ordersServicesModel->setHeaderData((int)ORDERS_SERVICES::ID_SERVICE, Qt::Horizontal, "Послуга");
        ordersServicesModel->setHeaderData((int)ORDERS_SERVICES::NUMBER, Qt::Horizontal, "Кількість");
        ordersServicesModel->setFilter("idOrder = orders.id AND orders.isDelete != 1");
        ordersServicesModel->select();

        reports_1_q = new QSqlQueryModel(this);
        reports_1_q->setHeaderData((int)ORDERS::NUMBER, Qt::Horizontal, "№");
        reports_1_q->setHeaderData((int)ORDERS::ID_CLIENT, Qt::Horizontal, "Клієнт");
        reports_1_q->setHeaderData((int)ORDERS::ID_MANAGER, Qt::Horizontal, "Менеджер");
        reports_1_q->setHeaderData((int)ORDERS::DATE, Qt::Horizontal, "Дата");
        reports_1_q->setHeaderData((int)ORDERS::TOTAL_PRICE, Qt::Horizontal, "Загальна вартість");
        reports_1_q->setHeaderData((int)ORDERS::STATUS_WORK, Qt::Horizontal, "Статус");
        reports_2_q = new QSqlQueryModel(this);
        reports_2_q->setHeaderData((int)ORDERS::NUMBER, Qt::Horizontal, "№");
        reports_2_q->setHeaderData((int)ORDERS::ID_CLIENT, Qt::Horizontal, "Клієнт");
        reports_2_q->setHeaderData((int)ORDERS::ID_MANAGER, Qt::Horizontal, "Менеджер");
        reports_2_q->setHeaderData((int)ORDERS::DATE, Qt::Horizontal, "Дата");
        reports_2_q->setHeaderData((int)ORDERS::TOTAL_PRICE, Qt::Horizontal, "Загальна вартість");
        reports_2_q->setHeaderData((int)ORDERS::STATUS_WORK, Qt::Horizontal, "Статус");
        reports_3_q = new QSqlQueryModel(this);

        reports_2_2_q = QSqlQuery();
        reports_1_2_q = QSqlQuery();

        return true;
    }
    else
        return false;
}

void DatabaseModule::selectTables()
{
    clientsModel->select();
    managersModel->select();
    servicesModel->select();
    ordersModel->select();
    ordersServicesModel->select();
}


