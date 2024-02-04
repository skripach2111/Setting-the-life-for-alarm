#ifndef MANAGERSADDEDITDIALOG_H
#define MANAGERSADDEDITDIALOG_H

#include <QDialog>
#include <QDataWidgetMapper>

#include "databasemodule.h"

namespace Ui {
class ManagersAddEditDialog;
}

class ManagersAddEditDialog : public QDialog
{
    Q_OBJECT
    QDataWidgetMapper *mapper;

    bool checkInput();

public:
    explicit ManagersAddEditDialog(QDataWidgetMapper *mapper, QWidget *parent = nullptr);
    ~ManagersAddEditDialog();

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::ManagersAddEditDialog *ui;
};

#endif // MANAGERSADDEDITDIALOG_H
