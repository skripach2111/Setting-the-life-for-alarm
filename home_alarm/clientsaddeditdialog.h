#ifndef CLIENTSADDEDITDIALOG_H
#define CLIENTSADDEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "databasemodule.h"

namespace Ui {
class ClientsAddEditDialog;
}

class ClientsAddEditDialog : public QDialog
{
    Q_OBJECT
    QDataWidgetMapper *mapper;

    bool checkInput();

public:
    explicit ClientsAddEditDialog(QDataWidgetMapper *mapper, QWidget *parent = nullptr);
    ~ClientsAddEditDialog();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ClientsAddEditDialog *ui;
};

#endif // CLIENTSADDEDITDIALOG_H
