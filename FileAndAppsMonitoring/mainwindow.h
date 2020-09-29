#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QDir>
#include <QFileInfo>
#include <QFileDialog>
#include <QFileSystemWatcher>
#include <QDebug>

#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QSettings>
#include "processwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeEvent(QEvent* e);


private slots:
    void on_pushButton_clicked();

    void NotifyChanges(const QString &path);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    QFileSystemWatcher *watcher;
    QString Path;

    ProcessWidget      *widProcesses;
    QTimer             *processTimer;
    QTimer             *socketTimer;
    QSettings           settings;


protected:
};
#endif // MAINWINDOW_H
