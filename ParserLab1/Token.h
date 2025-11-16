#pragma once

#include <QString>
#include <QDebug>

enum class TokenType {
	COUT,		// ключевое слово cout
	OPERATOR,	// оператор <<
	IDENTIFIER, // идентификатор (перменные, endl)
	STRING,		// строковый литерал
	NUMBER,		// числовой литерал
	SEMICOLON,	// точка с запятой
	END			// конец входных данных
};

class Token {
public:
	TokenType type;
	QString value;
	int position;

	explicit Token() : type(TokenType::END), value(""), position(0) {}

	Token(TokenType type, const QString& value, int position)
		: type(type), value(value), position(position) {}
};

namespace TokenUtils {
	QString tokenType_to_string(TokenType type);
	void print_token(const Token& token);
	QString token_to_string(const Token& token);
}