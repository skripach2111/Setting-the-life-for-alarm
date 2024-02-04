#ifndef ORDERSADDVIEWDIALOG_H
#define ORDERSADDVIEWDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "databasemodule.h"
#include "serviceselectdialog.h"

namespace Ui {
class OrdersAddViewDialog;
}

class OrdersAddViewDialog : public QDialog
{
    Q_OBJECT

    enum PAGES {
        EDIT = 0,
        VIEW
    };

    QDataWidgetMapper *mapper;
    QSqlTableModel *servicesModel;
    QSqlTableModel *ordersServicesModel;
    QList <ordersServicesObject_t> listOrdersServices;

    QSqlQueryModel *servicesView;

public:
    explicit OrdersAddViewDialog(QDataWidgetMapper *mapper, QSqlTableModel *clientsModel,
                                 QSqlTableModel *managersModel,
                                 QSqlRelationalTableModel *ordersServicesModel,
                                 QSqlTableModel *servicesModel, QWidget *parent = nullptr);

    explicit OrdersAddViewDialog(QDataWidgetMapper *mapper,
                                 QWidget *parent = nullptr);

    ~OrdersAddViewDialog();

private slots:
    void on_pushButton_services_add_clicked();

    void on_pushButton_clicked();

    void on_pushButton_services_remove_clicked();

    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::OrdersAddViewDialog *ui;

    void updateServicesTable();

    bool checkInput();
};

#endif // ORDERSADDVIEWDIALOG_H
