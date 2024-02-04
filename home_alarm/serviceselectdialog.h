#ifndef SERVICESELECTDIALOG_H
#define SERVICESELECTDIALOG_H

#include <QDialog>

#include "databasemodule.h"

namespace Ui {
class ServiceSelectDialog;
}

class ServiceSelectDialog : public QDialog
{
    Q_OBJECT
    ordersServicesObject_t service;

public:
    explicit ServiceSelectDialog(QSqlTableModel *servicesModel, QWidget *parent = nullptr);
    ~ServiceSelectDialog();

    ordersServicesObject_t getService();

private slots:
    void on_pushButton_select_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ServiceSelectDialog *ui;

    bool checkInput();
};

#endif // SERVICESELECTDIALOG_H
