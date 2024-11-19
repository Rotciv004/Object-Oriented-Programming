#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lifeafterschool.h"

class Lifeafterschool : public QMainWindow
{
    Q_OBJECT

public:
    Lifeafterschool(QWidget *parent = nullptr);
    ~Lifeafterschool();

private:
    Ui::LifeafterschoolClass ui;
};
