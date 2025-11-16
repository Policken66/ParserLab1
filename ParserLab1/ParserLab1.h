#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ParserLab1.h"

class ParserLab1 : public QMainWindow
{
    Q_OBJECT

public:
    ParserLab1(QWidget *parent = nullptr);
    ~ParserLab1();

private slots:
    void _action_start_triggered();

private:
    Ui::ParserLab1Class ui;
};

