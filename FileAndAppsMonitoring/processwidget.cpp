#include "processwidget.h"

ProcessWidget::ProcessWidget(QTableWidget *wid, QWidget *parent) :
    QWidget(parent),
    widget(wid)
{
    connect(this, SIGNAL(refreshData()), this, SLOT(deleteAllocatedItems()));
    connect(this, SIGNAL(refreshData()), this, SLOT(populateUi()));

}

ProcessWidget::~ProcessWidget(){
    deleteAllocatedItems();
}

void ProcessWidget::populateUi(){

    SystemUtil util;
    QList<Process> processList;
    int returnCode = util.getProcessesList(&processList);

    if(returnCode == ST_SUCCESS){
        qDebug() << "Successfully retrieved process list. . . ";
    }else {
        qDebug() << "Problem retrieving process list . . . . .";
    }

    widget->setRowCount(processList.size());

    QTableWidgetItem *pidItem;
    QTableWidgetItem *pNameItem;
    QTableWidgetItem *pUserItem;
    QTableWidgetItem *pCpuUsageItem;
    QTableWidgetItem *pMemUsageItem;

    for(int i = 0;i < processList.size(); i++ ){

        pidItem       = new QTableWidgetItem(QString::number
                                             (processList.at(i).getProcessId()));
        pNameItem     = new QTableWidgetItem(QString
                                             (processList.at(i).getProcessName()));
        pUserItem     = new QTableWidgetItem(QString
                                             (processList.at(i).getUser()));
        pCpuUsageItem = new QTableWidgetItem(QString("%1 %").
                                             arg(QString::number(processList.at(i).getCpuUsage(),'f',2)));
        pMemUsageItem = new QTableWidgetItem(QString("%1 KiB").
                                             arg(QString::number(processList.at(i).getMemoryUsage(),'f',2)));

        pidItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        pUserItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        pCpuUsageItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        pMemUsageItem->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        widget->setItem(i,0,pidItem);
        widget->setItem(i,1,pNameItem);
        widget->setItem(i,2,pUserItem);
        widget->setItem(i,3,pCpuUsageItem);
        widget->setItem(i,4,pMemUsageItem);
    }
    widget->setCurrentCell(0,0);

}

void ProcessWidget::deleteAllocatedItems(){

    for(int i = 0; i < widget->rowCount(); i++){
        for(int j = 0 ;j < widget->columnCount(); j++){
            widget->setCurrentCell(i, j);
            delete widget->currentItem();
        }
    }

}

void ProcessWidget::refreshTimer(){
    emit refreshData();
}
