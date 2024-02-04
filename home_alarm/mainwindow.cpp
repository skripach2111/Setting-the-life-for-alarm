#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DatabaseModule* db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dbm = db;

    ui->tableView_clients->setModel(dbm->clientsModel);
    ui->tableView_clients->setColumnHidden((int)CLIENTS::ID, true);
    ui->tableView_clients->setColumnHidden((int)CLIENTS::IS_DELETE, true);
    ui->tableView_clients->setSortingEnabled(true);
    ui->tableView_clients->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_managers->setModel(dbm->managersModel);
    ui->tableView_managers->setColumnHidden((int)MANAGERS::ID, true);
    ui->tableView_managers->setColumnHidden((int)MANAGERS::IS_DELETE, true);
    ui->tableView_managers->setSortingEnabled(true);
    ui->tableView_managers->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_services->setModel(dbm->servicesModel);
    ui->tableView_services->setColumnHidden((int)SERVICES::ID, true);
    ui->tableView_services->setColumnHidden((int)SERVICES::IS_DELETE, true);
    ui->tableView_services->setSortingEnabled(true);
    ui->tableView_services->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_orders->setModel(dbm->ordersModel);
    ui->tableView_orders->setColumnHidden((int)ORDERS::IS_DELETE, true);
    ui->tableView_orders->setSortingEnabled(true);
    ui->tableView_orders->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);

    ui->tableView_report_1_orders->setModel(dbm->reports_1_q);
    ui->tableView_report_1_orders->setColumnHidden((int)ORDERS::IS_DELETE, true);
    ui->tableView_report_1_orders->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_report_2_orders->setModel(dbm->reports_2_q);
    ui->tableView_report_2_orders->setColumnHidden((int)ORDERS::IS_DELETE, true);
    ui->tableView_report_2_orders->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->tableView_report_3_services->setModel(dbm->reports_3_q);
    ui->tableView_report_3_services->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui->dateEdit->setDate(QDate::currentDate());

    ui->stackedWidget->setCurrentIndex(CLIENTS);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clients_add_clicked()
{
    dbm->clientsModel->insertRow(dbm->clientsModel->rowCount());
    ui->tableView_clients->setCurrentIndex(dbm->clientsModel->index(dbm->clientsModel->rowCount()-1, 0));

    mapper->clearMapping();
    mapper->setModel(dbm->clientsModel);
    mapper->setCurrentIndex(ui->tableView_clients->currentIndex().row());

    ClientsAddEditDialog dialog(mapper);
    if(dialog.exec() == ClientsAddEditDialog::Accepted)
    {
        dbm->clientsModel->setData(dbm->clientsModel->index(ui->tableView_clients->currentIndex().row(), (int)CLIENTS::IS_DELETE), 0);
        dbm->clientsModel->submit();
    }
    else
        dbm->clientsModel->revert();
}


void MainWindow::on_pushButton_clients_edit_clicked()
{
    if(ui->tableView_clients->currentIndex().row() == -1)
        return;

    mapper->clearMapping();
    mapper->setModel(dbm->clientsModel);
    mapper->setCurrentIndex(ui->tableView_clients->currentIndex().row());

    ClientsAddEditDialog dialog(mapper);
    if(dialog.exec() == ClientsAddEditDialog::Accepted)
        dbm->clientsModel->submit();
}


void MainWindow::on_pushButton_clients_remove_clicked()
{
    dbm->clientsModel->setData(dbm->clientsModel->index(ui->tableView_clients->currentIndex().row(), (int)CLIENTS::IS_DELETE), 1);
    dbm->clientsModel->submit();
    dbm->clientsModel->select();
}


void MainWindow::on_pushButton_managers_add_clicked()
{
    dbm->managersModel->insertRow(dbm->managersModel->rowCount());
    ui->tableView_managers->setCurrentIndex(dbm->managersModel->index(dbm->managersModel->rowCount()-1, 0));

    mapper->clearMapping();
    mapper->setModel(dbm->managersModel);
    mapper->setCurrentIndex(ui->tableView_managers->currentIndex().row());

    ManagersAddEditDialog dialog(mapper);
    if(dialog.exec() == ManagersAddEditDialog::Accepted)
    {
        dbm->managersModel->setData(dbm->managersModel->index(ui->tableView_managers->currentIndex().row(), (int)MANAGERS::IS_DELETE), 0);
        dbm->managersModel->submit();
    }
    else
        dbm->managersModel->revert();
}


void MainWindow::on_pushButton_managers_edit_clicked()
{
    if(!ui->tableView_managers->currentIndex().isValid())
        return;

    mapper->clearMapping();
    mapper->setModel(dbm->managersModel);
    mapper->setCurrentIndex(ui->tableView_managers->currentIndex().row());

    ManagersAddEditDialog dialog(mapper);
    if(dialog.exec() == ManagersAddEditDialog::Accepted)
        dbm->managersModel->submit();
}


void MainWindow::on_pushButton_managers_remove_clicked()
{
    dbm->managersModel->setData(dbm->managersModel->index(ui->tableView_managers->currentIndex().row(), (int)MANAGERS::IS_DELETE), 1);
    dbm->managersModel->submit();
    dbm->managersModel->select();
}


void MainWindow::on_pushButton_services_add_clicked()
{
    dbm->servicesModel->insertRow(dbm->servicesModel->rowCount());
    ui->tableView_services->setCurrentIndex(dbm->servicesModel->index(dbm->servicesModel->rowCount()-1, 0));

    mapper->clearMapping();
    mapper->setModel(dbm->servicesModel);
    mapper->setCurrentIndex(ui->tableView_services->currentIndex().row());

    ServicesAddEditDialog dialog(mapper);
    if(dialog.exec() == ManagersAddEditDialog::Accepted)
    {
        dbm->servicesModel->setData(dbm->servicesModel->index(ui->tableView_services->currentIndex().row(), (int)SERVICES::IS_DELETE), 0);
        dbm->servicesModel->submit();
    }
    else
        dbm->servicesModel->revert();
}


void MainWindow::on_pushButton_services_edit_clicked()
{
    if(!ui->tableView_services->currentIndex().isValid())
        return;

    mapper->clearMapping();
    mapper->setModel(dbm->servicesModel);
    mapper->setCurrentIndex(ui->tableView_services->currentIndex().row());

    ServicesAddEditDialog dialog(mapper);
    if(dialog.exec() == ServicesAddEditDialog::Accepted)
        dbm->servicesModel->submit();
}


void MainWindow::on_pushButton_services_remove_clicked()
{
    dbm->servicesModel->setData(dbm->servicesModel->index(ui->tableView_services->currentIndex().row(), (int)SERVICES::IS_DELETE), 1);
    dbm->servicesModel->submit();
    dbm->servicesModel->select();
}


void MainWindow::on_pushButton_orders_add_clicked()
{
    dbm->ordersModel->insertRow(dbm->ordersModel->rowCount());
    ui->tableView_orders->setCurrentIndex(dbm->ordersModel->index(dbm->ordersModel->rowCount()-1, 0));

    mapper->clearMapping();
    mapper->setModel(dbm->ordersModel);
    mapper->setCurrentIndex(ui->tableView_orders->currentIndex().row());

    OrdersAddViewDialog dialog(mapper, dbm->clientsModel, dbm->managersModel, dbm->ordersServicesModel, dbm->servicesModel);

    if(dialog.exec() != OrdersAddViewDialog::Accepted)
        dbm->ordersModel->revert();
}


void MainWindow::on_pushButton_orders_remove_clicked()
{
    dbm->ordersModel->setData(dbm->ordersModel->index(ui->tableView_orders->currentIndex().row(), (int)ORDERS::IS_DELETE), 1);
    dbm->ordersModel->submit();
    dbm->ordersModel->select();
}


void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(CLIENTS);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(MANAGERS);
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(SERVICES);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(ORDERS);
}


void MainWindow::on_pushButton_5_clicked()
{
    dbm->reports_2_q->setQuery("SELECT\
                                    o.number AS order_number,\
                                    c.pib AS client_name,\
                                    m.pib AS manager_name,\
                                    o.date_сreate AS order_date,\
                                    o.total_price AS total_order_price,\
                                    o.status_work,\
                                    o.isDelete\
                                FROM\
                                    orders o\
                                JOIN\
                                    clients c ON o.idClient = c.id\
                                JOIN\
                                    managers m ON o.idManager = m.id\
                                WHERE\
                                    o.isDelete != 1;", dbm->db);
    qDebug() << dbm->reports_2_q->lastError();
    dbm->reports_2_2_q.exec("SELECT\
                                        COUNT(*) AS number_of_contracts,\
                                        SUM(total_price) AS total_contract_price\
                                    FROM\
                                        orders\
                                    WHERE\
                                        isDelete != 1;\
                                    ");
    if(dbm->reports_2_2_q.next())
    {
    ui->label_report_2_total_number->setText(dbm->reports_2_2_q.value(0).toString());
    ui->label_report_2_total_cost->setText(dbm->reports_2_2_q.value(1).toString());
    }
    else
    {
        ui->label_report_2_total_number->setText("0");
        ui->label_report_2_total_cost->setText("0");
    }

    dbm->reports_3_q->setQuery("SELECT\
                                    s.title AS \"Назва послуги\",\
                                    SUM(os.number) AS \"Кількість\"\
                                FROM\
                                    orders_services os\
                                JOIN\
                                    services s ON os.idService = s.id\
                                JOIN\
                                    orders o ON os.idOrder = o.number\
                                WHERE\
                                    o.isDelete = false\
                                GROUP BY\
                                    os.idService\
                                ORDER BY\
                                    SUM(os.number) DESC;", dbm->db);

    dbm->reports_2_q->setHeaderData((int)ORDERS::NUMBER, Qt::Horizontal, "№");
    dbm->reports_2_q->setHeaderData((int)ORDERS::ID_CLIENT, Qt::Horizontal, "Клієнт");
    dbm->reports_2_q->setHeaderData((int)ORDERS::ID_MANAGER, Qt::Horizontal, "Менеджер");
    dbm->reports_2_q->setHeaderData((int)ORDERS::DATE, Qt::Horizontal, "Дата");
    dbm->reports_2_q->setHeaderData((int)ORDERS::TOTAL_PRICE, Qt::Horizontal, "Загальна вартість");
    dbm->reports_2_q->setHeaderData((int)ORDERS::STATUS_WORK, Qt::Horizontal, "Статус");

    ui->tableView_report_2_orders->setColumnHidden((int)ORDERS::IS_DELETE, true);
    ui->stackedWidget->setCurrentIndex(REPORTS);
}


void MainWindow::on_tableView_orders_doubleClicked(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    mapper->clearMapping();
    mapper->setModel(dbm->ordersModel);
    mapper->setCurrentIndex(ui->tableView_orders->currentIndex().row());

    OrdersAddViewDialog dialog(mapper);
    dialog.exec();
}


void MainWindow::on_pushButton_report_1_calc_clicked()
{
    dbm->reports_1_q->setQuery("SELECT\
                                    o.number AS order_number,\
                                    c.pib AS client_name,\
                                    m.pib AS manager_name,\
                                    o.date_сreate AS order_date,\
                                    o.total_price AS total_order_price,\
                                    o.status_work,\
                                    o.isDelete\
                                FROM\
                                    orders o\
                                JOIN\
                                    clients c ON o.idClient = c.id\
                                JOIN\
                                    managers m ON o.idManager = m.id\
                                WHERE\
                                    o.date_сreate = '" + ui->dateEdit->date().toString("yyyy-MM-dd") + "' AND o.isDelete != 1;", dbm->db);
    qDebug() << dbm->reports_1_q->lastError();
    dbm->reports_1_2_q.exec("SELECT\
                                        COUNT(*) AS number_of_contracts,\
                                        SUM(total_price) AS total_contract_price\
                                    FROM\
                                        orders\
                                    WHERE\
                                        date_сreate = '" + ui->dateEdit->date().toString("yyyy-MM-dd") + "' AND isDelete != 1;\
                                    ");
    qDebug() << ui->dateEdit->date().toString("yyyy-MM-dd");
    if(dbm->reports_1_2_q.next())
    {
    ui->label_report_1_total_number->setText(dbm->reports_1_2_q.value(0).toString());
    ui->label_report_1_total_cost->setText(dbm->reports_1_2_q.value(1).toString());
    }
    else
    {
        ui->label_report_1_total_number->setText("0");
        ui->label_report_1_total_cost->setText("0");
    }

    dbm->reports_1_q->setHeaderData((int)ORDERS::NUMBER, Qt::Horizontal, "№");
    dbm->reports_1_q->setHeaderData((int)ORDERS::ID_CLIENT, Qt::Horizontal, "Клієнт");
    dbm->reports_1_q->setHeaderData((int)ORDERS::ID_MANAGER, Qt::Horizontal, "Менеджер");
    dbm->reports_1_q->setHeaderData((int)ORDERS::DATE, Qt::Horizontal, "Дата");
    dbm->reports_1_q->setHeaderData((int)ORDERS::TOTAL_PRICE, Qt::Horizontal, "Загальна вартість");
    dbm->reports_1_q->setHeaderData((int)ORDERS::STATUS_WORK, Qt::Horizontal, "Статус");

    ui->tableView_report_1_orders->setColumnHidden((int)ORDERS::IS_DELETE, true);
}

