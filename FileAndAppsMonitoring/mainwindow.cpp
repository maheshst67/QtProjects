#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::changeEvent(QEvent* e)
{
    switch (e->type())
    {
    case QEvent::LanguageChange:
        this->ui->retranslateUi(this);
        break;
    case QEvent::WindowStateChange:
    {
        if (this->windowState() & Qt::WindowMinimized)
        {
            QTimer::singleShot(250, this, SLOT(hide()));
        }

        break;
    }
    default:
        break;
    }

    QMainWindow::changeEvent(e);
}

void MainWindow::on_pushButton_clicked()
{
    Path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), ".", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    ui->lineEdit->setText(Path);
    ui->listWidget->clear();
    watcher = new QFileSystemWatcher(this);
    watcher->addPath(Path);

    disconnect(watcher, SIGNAL(directoryChanged(QString)) , this, SLOT(NotifyChanges(QString)));
    QDir dir(Path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for(int i=0;i<list.size();++i)
    {
        ui->listWidget->addItem(list.at(i).fileName());
    }


    connect(watcher, SIGNAL(directoryChanged(QString)) , this, SLOT(NotifyChanges(QString)));
    connect(watcher, SIGNAL(fileChanged(QString)) , this, SLOT(NotifyChanges(QString)));
}

void MainWindow::NotifyChanges(const QString &path)
{
    QStringList oldList, newList;

    for(int i =0;i<ui->listWidget->count();i++)
    {
        QListWidgetItem *item = ui->listWidget->item(i);
        oldList << item->text();
    }
    qSort(oldList);


    QDir dir(Path);
    dir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for(int i=0;i<list.size();++i)
    {
       newList << list.at(i).fileName();
    }
    qSort(newList);

    QSet<QString> intersection;
    if(oldList.count() > newList.count())
    {
        ui->listWidget->clear();
        intersection = oldList.toSet().intersect(newList.toSet());
        foreach (const QString &value, intersection)
        {
            ui->listWidget->addItem(value);
        }
        ui->label_2->setText("File Removed");
    }

    else if(oldList.count() < newList.count())
    {
        intersection = newList.toSet().subtract(oldList.toSet());

        foreach (const QString &value, intersection)
        {
            QListWidgetItem *wi = new QListWidgetItem;
            wi->setText(value);
            wi->setForeground(Qt::blue);

            ui->listWidget->addItem(wi);
        }
        ui->label_2->setText("File Added");
    }

    else
    {
        ui->listWidget->clear();
        intersection = newList.toSet().intersect(oldList.toSet());
        foreach (const QString &value, intersection)
        {
            ui->listWidget->addItem(value);
        }

        intersection = newList.toSet().subtract(oldList.toSet());

        foreach (const QString &value, intersection)
        {
            QListWidgetItem *wi = new QListWidgetItem;
            wi->setText(value);
            wi->setForeground(Qt::blue);

            ui->listWidget->addItem(wi);
        }

        ui->label_2->setText("File Modified");
    }
}



void MainWindow::on_pushButton_2_clicked()
{

    widProcesses = new ProcessWidget(ui->tableWidget);
    widProcesses->populateUi();



    processTimer = new QTimer(this); processTimer->start();
    socketTimer  = new QTimer(this); socketTimer->start();

    processTimer->setInterval(settings.value("timer/process").toInt() * 1000);
    socketTimer->setInterval(settings.value("timer/socket").toInt() * 1000);

    connect(processTimer, SIGNAL(timeout()), widProcesses, SLOT(refreshTimer()));
}





