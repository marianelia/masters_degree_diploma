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
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); // Разрешаем разворачивание
   // item->setCheckState(Qt::Unchecked); // Начинаем с неактивным состоянием
}

void Widget::onItemClicked(QListWidgetItem* item)
{
    QMessageBox e;
    e.setText("TEST");
    e.exec();
//{
//    if (expandedItems.contains(item))
//    {
//        // Если элемент уже развернут, скрываем его
//        delete expandedItems[item];
//        expandedItems.remove(item);
//        item->setCheckState(Qt::Unchecked);
//    }
//    else
//    {
//        // Создаем развернутый вид
//        QWidget* expandedWidget = new QWidget();
//        QVBoxLayout* layout = new QVBoxLayout(expandedWidget);
//
//        // Текстовое поле с описанием
//        QLabel* descriptionLabel = new QLabel(item->data(Qt::UserRole).toString(), expandedWidget);
//        layout->addWidget(descriptionLabel);
//
//        // Поле с кодом
//        QLineEdit* codeEdit = new QLineEdit(item->data(Qt::UserRole + 1).toString(), expandedWidget);
//        codeEdit->setReadOnly(true);
//        layout->addWidget(codeEdit);
//
//        // Кнопки Save и Try
//       QPushButton* saveButton = new QPushButton("Save", expandedWidget);
//        QPushButton* tryButton = new QPushButton("Try", expandedWidget);
//
//        layout->addWidget(saveButton);
//        layout->addWidget(tryButton);
//
//        // Подключаем сигналы кнопок
//       // connect(saveButton, &QPushButton::clicked, this, &Widget::onSaveButtonClicked);
//        connect(tryButton, &QPushButton::clicked, this, &Widget::onTryButtonClicked);
//
//        expandedWidget->setLayout(layout);
//
//        // Сохраняем развернутый вид
//        expandedItems[item] = expandedWidget;
//
//        // Добавляем развернутый вид под элементом
//        insightList->setItemWidget(item, expandedWidget);
//
//        // Устанавливаем состояние развернутого элемента
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
        // Здесь можно добавить логику для действия "Try"
       // qDebug() << "Try action for:" << currentItem->text();
    }
}
