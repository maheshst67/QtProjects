#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QWidget>
#include <QTableWidget>
#include "systemutil.h"

/**
 * Description:
 *
 * This class shows the list of processes running on the system
 */
class ProcessWidget : public QWidget {
    Q_OBJECT

public:
    explicit ProcessWidget(QTableWidget *wid, QWidget *parent = 0);
    ~ProcessWidget();


private:
    QTableWidget  *widget;

signals:
    void refreshData();

public slots:
    void populateUi();
    void deleteAllocatedItems();
    void refreshTimer();

};

#endif // USERINTERFACE_H
