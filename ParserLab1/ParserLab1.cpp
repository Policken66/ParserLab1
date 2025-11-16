#include <iostream>

#include "ParserLab1.h"
#include "Token.h"

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
    QVector<Token> test_tokens = {
        Token(TokenType::COUT, "cout", 0),
        Token(TokenType::OPERATOR, "<<", 5),
        Token(TokenType::STRING, "Hello world", 8),
        Token(TokenType::OPERATOR, "<<", 21),
        Token(TokenType::IDENTIFIER, "x", 24),
        Token(TokenType::SEMICOLON, ";", 25)
    };

    qDebug() << "Тестовые токены:";
    for (const auto& token : test_tokens) {
        TokenUtils::print_token(token);
    }
    qDebug() << "Токены напечатаны!";
}