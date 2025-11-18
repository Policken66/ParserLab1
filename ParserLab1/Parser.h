#pragma once
#include <Token.h>
#include <QVector>
#include <QString>

class Parser {
public:
	explicit Parser(const QVector<Token>& tokens);
	bool parse();

private:
	// Вспомогательные методы
	void _advance();
	void _eat(TokenType expected_type);


	// Методы для правил грамматики
	void _parse_S();
	void _parse_Output();
	void _parse_List();
	void _parse_Item();

private:
	QVector<Token> _tokens;
	int _current_token_index;
	Token _current_token;
};