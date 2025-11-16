#include "Token.h"

QString TokenUtils::tokenType_to_string(TokenType type) {
	switch (type) {
		case TokenType::COUT: return "COUT";
		case TokenType::OPERATOR: return "OPERATOR";
		case TokenType::IDENTIFIER: return "IDENTIFIER";
		case TokenType::STRING: return "STRING";
		case TokenType::NUMBER: return "NUMBER";
		case TokenType::SEMICOLON: return "SEMICOLON";
		case TokenType::END: return "END";
		default: return "UNKNOWN";
	}
}

void TokenUtils::print_token(const Token& token) {
	qDebug() << "Token(" << TokenUtils::tokenType_to_string(token.type)
		<< ", \"" << token.value << "\", pos: "
		<< token.position << ")";
}

QString TokenUtils::token_to_string(const Token& token) {
	return QString("Token(%1, \"%2\", pos: %3)\n")
		.arg(TokenUtils::tokenType_to_string(token.type))
		.arg(token.value)
		.arg(token.position);
}