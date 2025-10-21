#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ParserLab1.h"

class ParserLab1 : public QMainWindow
{
    Q_OBJECT

public:
    ParserLab1(QWidget *parent = nullptr);
    ~ParserLab1();

private:
    Ui::ParserLab1Class ui;
};

