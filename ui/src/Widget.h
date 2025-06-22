#pragma once
#include <QWidget>
#include <QListWidgetItem>

#include <QTimer>
#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QDebug>
#include <winver.h>
#include <QProcess>
#include <regex>
#include <sstream>

#include "stdafx.h"
#include "hostQtUi.h"


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
	void launchModel();
signals:
  void signal1();
private:
	void addInsightItem(const QString& title, const QString& code);
	void launchProcess(QString name, QStringList arguments, QString working_dir);
	void runModelNextCommand(const QString& seed_text);
	void runModelBlockPredicted(const QString& seed_text);
	void runModelMacrosPredicted(const QString& seed_text);
	QString getPathToNanoCADLogFolder();
	QString readLogs();
	QString formatTextToStandard(const QString& text);
	QString readFileToString(const QString& filePath);

	QMap<QListWidgetItem*, QWidget*> expandedItems;
	Ui::Widget* ui;

	QString comandPredicted;
	QString macrosPredicted;
	QString blockPredicted;
	QString pathToLogs;

	QString predictedText;
};

