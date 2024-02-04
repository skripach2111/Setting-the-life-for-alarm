#include "ordersaddviewdialog.h"
#include "ui_ordersaddviewdialog.h"

OrdersAddViewDialog::OrdersAddViewDialog(QDataWidgetMapper *mapper, QSqlTableModel *clientsModel, QSqlTableModel *managersModel, QSqlRelationalTableModel *ordersServicesModel, QSqlTableModel *servicesModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrdersAddViewDialog)
{
    ui->setupUi(this);

    ui->label_error_listServices->setVisible(false);

    ui->stackedWidget->setCurrentIndex(EDIT);

    ui->dateEdit_date->setDate(QDate::currentDate());

    this->ordersServicesModel = ordersServicesModel;
    this->servicesModel = servicesModel;

    ui->comboBox_clients->setModel(clientsModel);
    ui->comboBox_clients->setModelColumn((int)CLIENTS::PIB);
    ui->comboBox_managers->setModel(managersModel);
    ui->comboBox_managers->setModelColumn((int)MANAGERS::PIB);

    this->mapper = mapper;
    mapper->addMapping(ui->comboBox_clients, (int)ORDERS::ID_CLIENT, "currentText");
    mapper->addMapping(ui->comboBox_managers, (int)ORDERS::ID_MANAGER, "currentText");
    mapper->addMapping(ui->dateEdit_date, (int)ORDERS::DATE);
    mapper->addMapping(ui->doubleSpinBox_totalCost, (int)ORDERS::TOTAL_PRICE);
    mapper->addMapping(ui->comboBox_status, (int)ORDERS::STATUS_WORK, "currentText");
    mapper->setCurrentIndex(mapper->currentIndex());

    ui->tableWidget_services->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

OrdersAddViewDialog::OrdersAddViewDialog(QDataWidgetMapper *mapper, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OrdersAddViewDialog)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(VIEW);
    mapper->addMapping(ui->label_number, (int)ORDERS::NUMBER, "text");
    mapper->addMapping(ui->label_client, (int)ORDERS::ID_CLIENT, "text");
    mapper->addMapping(ui->label_manager, (int)ORDERS::ID_MANAGER, "text");
    mapper->addMapping(ui->label_date, (int)ORDERS::DATE, "text");
    mapper->addMapping(ui->label_totalCost, (int)ORDERS::TOTAL_PRICE, "text");
    mapper->addMapping(ui->label_status, (int)ORDERS::STATUS_WORK, "text");
    mapper->setCurrentIndex(mapper->currentIndex());
    ui->label_totalCost->setText(mapper->model()->index(mapper->currentIndex(), (int)ORDERS::TOTAL_PRICE).data().toString());

    servicesView = new QSqlQueryModel(this);
    servicesView->setQuery("SELECT\
                               services.title AS \"Назва послуги\",\
                               os.number AS \"Кількість\",\
                               os.number * services.price AS \"Вартість\"\
                           FROM\
                                 orders_services os, services\
                           WHERE\
                           os.idOrder = " + mapper->model()->index(mapper->currentIndex(), (int)ORDERS::NUMBER).data().toString()
                             + " AND services.id = os.idService;");
    ui->tableView_services->setModel(servicesView);
    ui->tableView_services->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

OrdersAddViewDialog::~OrdersAddViewDialog()
{
    delete ui;
}

void OrdersAddViewDialog::on_pushButton_services_add_clicked()
{
    ServiceSelectDialog dialog(servicesModel);
    if(dialog.exec() == ServiceSelectDialog::Accepted)
    {
        listOrdersServices.push_back(dialog.getService());
        updateServicesTable();
    }
}

void OrdersAddViewDialog::updateServicesTable()
{
    float totalCost = 0;
    ui->tableWidget_services->setRowCount(0);

    for(int i = 0; i < listOrdersServices.size(); i++)
    {
        ui->tableWidget_services->insertRow(i);
        ui->tableWidget_services->setItem(i, 0, new QTableWidgetItem(servicesModel->index(listOrdersServices[i][ORDERS_SERVICES::ID_SERVICE].toInt(), (int)SERVICES::TITLE).data().toString()));
        ui->tableWidget_services->setItem(i, 1, new QTableWidgetItem(listOrdersServices[i][ORDERS_SERVICES::NUMBER].toString()));
        ui->tableWidget_services->setItem(i, 2, new QTableWidgetItem(QVariant(servicesModel->index(listOrdersServices[i][ORDERS_SERVICES::ID_SERVICE].toInt(), (int)SERVICES::PRICE).data().toFloat() * listOrdersServices[i][ORDERS_SERVICES::NUMBER].toFloat()).toString()));

        totalCost += servicesModel->index(listOrdersServices[i][ORDERS_SERVICES::ID_SERVICE].toInt(), (int)SERVICES::PRICE).data().toFloat() * listOrdersServices[i][ORDERS_SERVICES::NUMBER].toFloat();
    }

    ui->doubleSpinBox_totalCost->setValue(totalCost);
}

bool OrdersAddViewDialog::checkInput()
{
    bool flag = true;

    if(listOrdersServices.isEmpty())
    {
        ui->label_error_listServices->setText("Помилка! Немає жодної послуги!");
        ui->label_error_listServices->setVisible(true);
        flag = false;
    }
    else
        ui->label_error_listServices->setVisible(false);

    return flag;
}


void OrdersAddViewDialog::on_pushButton_clicked()
{
    close();
}


void OrdersAddViewDialog::on_pushButton_services_remove_clicked()
{
    if(ui->tableWidget_services->currentIndex().row() == -1)
        return;

    listOrdersServices.removeAt(ui->tableWidget_services->currentIndex().row());
    updateServicesTable();
}


void OrdersAddViewDialog::on_pushButton_save_clicked()
{
    if(!checkInput())
        return;

    mapper->model()->setData(mapper->model()->index(mapper->currentIndex(), (int)ORDERS::ID_CLIENT),
                             ui->comboBox_clients->model()->index(ui->comboBox_clients->currentIndex(), (int)CLIENTS::ID).data());
    mapper->model()->setData(mapper->model()->index(mapper->currentIndex(), (int)ORDERS::ID_MANAGER),
                             ui->comboBox_managers->model()->index(ui->comboBox_managers->currentIndex(), (int)MANAGERS::ID).data());
    mapper->model()->setData(mapper->model()->index(mapper->currentIndex(), (int)ORDERS::ID_MANAGER), ui->comboBox_status->currentText());
    mapper->model()->setData(mapper->model()->index(mapper->currentIndex(), (int)ORDERS::IS_DELETE), 0);
    mapper->submit();
    mapper->model()->submit();

    for(int i = 0; i < listOrdersServices.size(); i++)
    {
        ordersServicesModel->insertRow(ordersServicesModel->rowCount());
        ordersServicesModel->setData(ordersServicesModel->index(ordersServicesModel->rowCount()-1, (int)ORDERS_SERVICES::ID_ORDER),
                                     mapper->model()->index(mapper->currentIndex(), (int)ORDERS::NUMBER).data());
        ordersServicesModel->setData(ordersServicesModel->index(ordersServicesModel->rowCount()-1, (int)ORDERS_SERVICES::ID_SERVICE),
                                     servicesModel->index(listOrdersServices[i][ORDERS_SERVICES::ID_SERVICE].toInt(), (int)SERVICES::ID).data());
        ordersServicesModel->setData(ordersServicesModel->index(ordersServicesModel->rowCount()-1, (int)ORDERS_SERVICES::NUMBER),
                                     listOrdersServices[i][ORDERS_SERVICES::NUMBER]);
        ordersServicesModel->submit();
    }
    accept();
    close();
}


void OrdersAddViewDialog::on_pushButton_cancel_clicked()
{
    mapper->revert();
    close();
}

