#pragma once
#include <QWidget>
#include <QListWidgetItem>


QT_BEGIN_NAMESPACE
namespace Ui
{
	class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
  Q_OBJECT
public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

private slots:
	void onItemClicked(QListWidgetItem* item);
	void onTryButtonClicked();
 // void showDialog();
signals:
  void signal1();
private:
	void addInsightItem(const QString& title, const QString& code);

//    // Для хранения данных о развернутых элементах
	QMap<QListWidgetItem*, QWidget*> expandedItems;
	Ui::Widget* ui;
  //struct WidgetImpl;
  //WidgetImpl* impl;
};


//#include <QtWidgets>
//
//class Widget : public QWidget
//{
//    Q_OBJECT
//
//public:
//    Widget(QWidget* parent = nullptr);
//
//private slots:
//    void onItemClicked(QListWidgetItem* item);
//    void onSaveButtonClicked();
//    void onTryButtonClicked();
//
//private:
//    void setupUI();
//    void addInsightItem(const QString& title, const QString& description, const QString& code);
//
//    QTabWidget* tabWidget;
//    QListWidget* insightList;
//    QListWidget* savedList;
//
//    // Для хранения данных о развернутых элементах
//    QMap<QListWidgetItem*, QWidget*> expandedItems;
//
//private:
//  struct WidgetImpl;
//  WidgetImpl* impl;
//};

