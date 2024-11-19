#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Life_after_school_QT.h"

class Life_after_school_QT : public QMainWindow
{
    Q_OBJECT

public:
    Life_after_school_QT(QWidget *parent = nullptr);
    ~Life_after_school_QT();

private:
    Ui::Life_after_school_QTClass ui;
};
