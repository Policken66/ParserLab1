#include <iostream>

#include "ParserLab1.h"
#include "Token.h"
#include <ErrorHandler.h>
#include <Lexer.h>
#include <Parser.h>

ParserLab1::ParserLab1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.plainTextEdit_log->setReadOnly(true);

    connect(ui.action_start, &QAction::triggered, this, &ParserLab1::_action_start_triggered);
}

ParserLab1::~ParserLab1()
{}

void ParserLab1::_action_start_triggered() {
    qDebug() << "=== Parser ===";
    QString test = ui.plainTextEdit_input->toPlainText();
    QString output = "";
    try {
        Lexer lexer(test);
        QVector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        bool success = parser.parse();
        output = "Result: " + QString(success ? "SUCCESS" : "FAILED");
        qDebug() << "Result:" << (success ? "SUCCESS" : "FAILED");
    }
    catch (const ErrorHandler::SyntaxError& e) {
        output = "Error: " + QString(e.what());
        qDebug() << "Error:" << e.what();
    }

    ui.plainTextEdit_log->setPlainText(output);
}
