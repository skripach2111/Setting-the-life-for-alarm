#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDataWidgetMapper>

#include "databasemodule.h"

#include "clientsaddeditdialog.h"
#include "managersaddeditdialog.h"
#include "servicesaddeditdialog.h"
#include "ordersaddviewdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DatabaseModule* dbm;
    QDataWidgetMapper *mapper;

    enum PAGES {
        CLIENTS,
        MANAGERS,
        SERVICES,
        ORDERS,
        REPORTS
    };

public:
    MainWindow(DatabaseModule* db, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clients_add_clicked();

    void on_pushButton_clients_edit_clicked();

    void on_pushButton_clients_remove_clicked();

    void on_pushButton_managers_add_clicked();

    void on_pushButton_managers_edit_clicked();

    void on_pushButton_managers_remove_clicked();

    void on_pushButton_services_add_clicked();

    void on_pushButton_services_edit_clicked();

    void on_pushButton_services_remove_clicked();

    void on_pushButton_orders_add_clicked();

    void on_pushButton_orders_remove_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_orders_doubleClicked(const QModelIndex &index);

    void on_pushButton_report_1_calc_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
