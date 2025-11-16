#pragma once

#include <QVector>
#include <QString>
#include <QChar>

#include "Token.h"

class Lexer {
public:
	explicit Lexer() 
		: _input(QString()), _position(0), _current_char(QChar()) {}
	explicit Lexer(const QString& input);
	QVector<Token> tokenize();

private:
	void _advance();
	void _skip_whitespace();
	QString _read_identifier();
	QString _read_number();
	QString _read_string();

private:
	QString _input;
	int _position;
	QChar _current_char;
};