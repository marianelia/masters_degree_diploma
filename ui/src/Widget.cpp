#include "stdafx.h"
#include "Widget.h"
#include "hostQtUi.h"
#include "ui_Widget.h"

Widget::Widget(QWidget *parent)
  : QWidget(parent), ui(new Ui::Widget)//, impl(new WidgetImpl())
{
    ui->setupUi(this);
  //connect(impl->pushButtonWithSlot, &QPushButton::released, this, &Widget::showDialog);
  //connect(impl->pushButtonWithSignal, &QPushButton::released, this, &Widget::signal1);


    connect(ui->insightList, &QListWidget::itemClicked, this, &Widget::onItemClicked);

}


Widget::~Widget()
{
    //delete impl;
}

void Widget::addInsightItem(const QString& title, const QString& code)
{
    QListWidgetItem* item = new QListWidgetItem(title, ui->insightList);
    item->setData(Qt::UserRole, QVariant::fromValue<QString>(""));
    item->setData(Qt::UserRole +1, QVariant::fromValue<QString>(code));
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // ��������� ��������������
   // item->setCheckState(Qt::Unchecked); // �������� � ���������� ����������
}

void Widget::onItemClicked(QListWidgetItem* item)
{
    QMessageBox e;
    e.setText("TEST");
    e.exec();
//{
//    if (expandedItems.contains(item))
//    {
//        // ���� ������� ��� ���������, �������� ���
//        delete expandedItems[item];
//        expandedItems.remove(item);
//        item->setCheckState(Qt::Unchecked);
//    }
//    else
//    {
//        // ������� ����������� ���
//        QWidget* expandedWidget = new QWidget();
//        QVBoxLayout* layout = new QVBoxLayout(expandedWidget);
//
//        // ��������� ���� � ���������
//        QLabel* descriptionLabel = new QLabel(item->data(Qt::UserRole).toString(), expandedWidget);
//        layout->addWidget(descriptionLabel);
//
//        // ���� � �����
//        QLineEdit* codeEdit = new QLineEdit(item->data(Qt::UserRole + 1).toString(), expandedWidget);
//        codeEdit->setReadOnly(true);
//        layout->addWidget(codeEdit);
//
//        // ������ Save � Try
//       QPushButton* saveButton = new QPushButton("Save", expandedWidget);
//        QPushButton* tryButton = new QPushButton("Try", expandedWidget);
//
//        layout->addWidget(saveButton);
//        layout->addWidget(tryButton);
//
//        // ���������� ������� ������
//       // connect(saveButton, &QPushButton::clicked, this, &Widget::onSaveButtonClicked);
//        connect(tryButton, &QPushButton::clicked, this, &Widget::onTryButtonClicked);
//
//        expandedWidget->setLayout(layout);
//
//        // ��������� ����������� ���
//        expandedItems[item] = expandedWidget;
//
//        // ��������� ����������� ��� ��� ���������
//        insightList->setItemWidget(item, expandedWidget);
//
//        // ������������� ��������� ������������ ��������
//        item->setCheckState(Qt::Checked);
//    }
}

void Widget::onTryButtonClicked()
{
    QListWidgetItem* currentItem = ui->insightList->currentItem();
    if (currentItem)
    {
        QMessageBox e;
        e.setText("TEST");
        e.exec();
        // ����� ����� �������� ������ ��� �������� "Try"
       // qDebug() << "Try action for:" << currentItem->text();
    }
}
