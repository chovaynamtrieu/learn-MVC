#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "to_do_list.h"
#include <QStandardItem>
#include <QItemDelegate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ToDoList *model1 = new ToDoList;

    model = new QStandardItemModel(5,1, this);
    for (int row = 0; row < 5; row++){
        QModelIndex index = model->index(row, 0, QModelIndex());
        model->setData(index, row + 2);
    }

    delegate = new MyDelegate;
    ui->listView->setItemDelegate(delegate);
    ui->listView->setModel(model);

    //    QStandardItemModel* model = new QStandardItemModel;
    //    QStandardItem* item1 = new QStandardItem("Item 1");
    //    item1->setCheckable(true);
    //    model->appendRow(item1);
    //    QStandardItem* item2 = new QStandardItem("Item 2");
    //    item2->setCheckable(true);
    //    model->appendRow(item2);

    // Set the model to the list view
    //    ui->listView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete model;
    delete delegate;
}

