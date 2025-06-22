#include "Widget.h"
#include "ui_Widget.h"



Widget::Widget(QWidget *parent)
  : QWidget(parent), ui(new Ui::Widget)//, impl(new WidgetImpl())
{
    ui->setupUi(this);
  //connect(impl->pushButtonWithSlot, &QPushButton::released, this, &Widget::showDialog);
  //connect(impl->pushButtonWithSignal, &QPushButton::released, this, &Widget::signal1);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::launchModel);


   pathToLogs = getPathToNanoCADLogFolder();

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
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable); 
}


QString Widget::getPathToNanoCADLogFolder()
{
    // Получаем путь к папке, где находится текущее приложение
    QString pathExeNanoCAD = QCoreApplication::applicationDirPath() + "/nCad.exe";

    // Получаем версию файла
    QFileInfo fileInfo(pathExeNanoCAD);
    if (!fileInfo.exists())
    {
        qWarning() << "Файл nCad.exe не найден по пути:" << pathExeNanoCAD;
        return QString();
    }
    QString versionNanoCAD = "25.1";
    if (versionNanoCAD.isEmpty())
    {
        qWarning() << "Не удалось извлечь версию nanoCAD.";
        return QString();
    }

    QString mainNumberVersionNanoCAD = versionNanoCAD.left(4);

    // Получаем путь к ApplicationData
    QString envAppData = QDir::homePath(); // Для упрощения, можно также использовать getenv("APPDATA")
    QString pathToLogFolderNanoCAD = envAppData + "/Nanosoft/nanoCAD x64 " + mainNumberVersionNanoCAD + "/nnmsstcs";

    return pathToLogFolderNanoCAD;
}



void Widget::onItemClicked(QListWidgetItem* item)
{
}

void Widget::onTryButtonClicked()
{
    QListWidgetItem* currentItem = ui->insightList->currentItem();
}

void Widget::launchModel()
{
    QListWidgetItem* currentItem = ui->insightList->currentItem();
    QString logsForModel = readLogs();
    int currentRow = ui->insightList->currentRow();
    if (currentRow == 0)
    {
        runModelNextCommand(logsForModel);
        currentItem->setText(predictedText);
    }
    else if (currentRow == 1)
    {
        runModelBlockPredicted(logsForModel);
        currentItem->setText(predictedText);
    }
    else if (currentRow == 2)
    {
        runModelMacrosPredicted(logsForModel);
        currentItem->setText(predictedText);
    }
    update();
}

void Widget::launchProcess(QString name, QStringList arguments, QString working_dir)
{
    QProcess* process = new QProcess(this);
    process->setWorkingDirectory(working_dir);
    /*connect(process, &QProcess::readyReadStandardOutput, [=]() {
        QByteArray data = process->readAllStandardOutput();
        QString output(data); qDebug() << output;
    });*/
    process->start(name, arguments);
    if (!process->waitForStarted())
    {
        qDebug("Could not start process");
        return;
    }
    if (!process->waitForFinished())
    {
        qDebug("Could not finish process");
        return;
    }

    QByteArray data = process->readAll();
    predictedText = QString::fromUtf8(data);

}


void Widget::runModelNextCommand(const QString& seed_text)
{
    QStringList arguments;
    arguments << "D:\diploma\project_m\cpp_version\learn_module\predict_next_command.py" << seed_text;
    launchProcess("py", arguments, ".");
}

void Widget::runModelBlockPredicted(const QString& seed_text)
{
    QStringList arguments;
    arguments << "D:\diploma\project_m\cpp_version\learn_module\predict_new_block.py" << seed_text;
    launchProcess("py", arguments, ".");
}



void Widget::runModelMacrosPredicted(const QString& seed_text)
{
    QStringList arguments;
    arguments << "D:\diploma\project_m\cpp_version\learn_module\predict_new_macros.py" << seed_text;
    launchProcess("py", arguments, ".");
}


QString Widget::readLogs()
{
    QString logs = readFileToString(pathToLogs);
    return formatTextToStandard(logs);
}

QString Widget::readFileToString(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Не удалось открыть файл для чтения:" << filePath;
        return QString();
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    return content;
}

QString Widget::formatTextToStandard(const QString& text)
{
    QString doc_replaced = "\n";
    try
    {
        // Поиск всех тегов вида <...>, кроме </...>
        QRegularExpression regex("<[^/].*?>");
        QRegularExpressionMatchIterator i = regex.globalMatch(text);
        QStringList results;
        while (i.hasNext())
        {
            QRegularExpressionMatch match = i.next();
            results << match.captured(0);
        }
        QString data = results.join(" ");

        data.replace('\n', ' ')
            .replace('\r', ' ')
            .replace('“', ' ')
            .replace('”', ' ');
        data.replace("<", "").replace(">", "");
        data = data.toLower();

        // Список подстрок для удаления
        const QStringList toRemove = {
            "exit", "closedocument", "opendocument",
            "about", "vectorizer", "startupvperftest",
            "tipofday", "grip", "ribbon",
            "grip_stretch", "inspector", "newdocument",
            "viewpan", "ncgs_toggle_", "-netload",
            "netload", "toggle3dosnap", "regen",
            "module_nanocad_commandsprediction", "nanocad_commandsprediction"
        };

        for (const QString& substr : toRemove)
            data.remove(substr);
        
        QStringList dataArray = data.split(' ', Qt::SkipEmptyParts);
        doc_replaced = dataArray.join("\n");
    }
    catch (...) { }
    return doc_replaced;
}