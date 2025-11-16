#include <iostream>

#include "ParserLab1.h"
#include "Token.h"
#include <ErrorHandler.h>
#include <Lexer.h>

ParserLab1::ParserLab1(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    ui.plainTextEdit_log->setReadOnly(true);

    connect(ui.action_start, &QAction::triggered, this, &ParserLab1::_action_start_triggered);
}

ParserLab1::~ParserLab1()
{}


QString test_Lexer(const QString& test_name, const QString& input);

void ParserLab1::_action_start_triggered() {
    qDebug() << "=== a Lexer ===";
    QString test = ui.plainTextEdit_input->toPlainText();
    // Test cases
    QString result = test_Lexer("Test", test);
    ui.plainTextEdit_log->setPlainText(result);
}

QString test_Lexer(const QString& test_name, const QString& input) {
    QString result;

    try {
        Lexer lexer(input);
        QVector<Token> tokens = lexer.tokenize();

        for (const auto& token : tokens) {
            TokenUtils::print_token(token);
            result += TokenUtils::token_to_string(token);
        }
        result += "Succes!";
    }
    catch (const ErrorHandler::SyntaxError& e) {
        result += "Error: ";
        result += e.what();
        result += "\n";
    }

    return result;
}