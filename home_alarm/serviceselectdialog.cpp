#include "serviceselectdialog.h"
#include "ui_serviceselectdialog.h"

ServiceSelectDialog::ServiceSelectDialog(QSqlTableModel *servicesModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServiceSelectDialog)
{
    ui->setupUi(this);

    ui->label_error_listServices->setVisible(false);

    ui->tableView_services->setModel(servicesModel);
    ui->tableView_services->setColumnHidden((int)SERVICES::ID, true);
    ui->tableView_services->setColumnHidden((int)SERVICES::IS_DELETE, true);

    ui->tableView_services->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

ServiceSelectDialog::~ServiceSelectDialog()
{
    delete ui;
}

ordersServicesObject_t ServiceSelectDialog::getService()
{
    return service;
}

void ServiceSelectDialog::on_pushButton_select_clicked()
{
    if(!checkInput())
        return;

    service[ORDERS_SERVICES::ID_SERVICE] = ui->tableView_services->currentIndex().row();
    service[ORDERS_SERVICES::NUMBER] = ui->spinBox_number->value();
    this->accept();
    this->close();
}


void ServiceSelectDialog::on_pushButton_cancel_clicked()
{
    this->close();
}

bool ServiceSelectDialog::checkInput()
{
    bool flag = true;

    if(ui->tableView_services->currentIndex().row() == -1)
    {
        ui->label_error_listServices->setText("Помилка! Послугу не обрано!");
        ui->label_error_listServices->setVisible(true);
        flag = false;
    }
    ui->label_error_listServices->setVisible(false);

    return flag;
}

