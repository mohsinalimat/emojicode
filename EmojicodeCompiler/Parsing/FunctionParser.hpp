//
//  FunctionParser.hpp
//  EmojicodeCompiler
//
//  Created by Theo Weidmann on 28/07/2017.
//  Copyright © 2017 Theo Weidmann. All rights reserved.
//

#ifndef FunctionParser_hpp
#define FunctionParser_hpp

#include <utility>

#include "../AST/ASTExpr.hpp"
#include "../AST/ASTStatements.hpp"
#include "../Lex/TokenStream.hpp"
#include "../Parsing/OperatorHelper.hpp"
#include "../Types/TypeContext.hpp"
#include "AbstractParser.hpp"

namespace EmojicodeCompiler {

class ASTNode;

class FunctionParser : AbstractParser {
public:
    FunctionParser(Package *pkg, TokenStream &stream, TypeContext context) : AbstractParser(pkg, stream), typeContext_(std::move(context)) {}
    std::shared_ptr<ASTBlock> parse();
private:
    TypeContext typeContext_;
    std::shared_ptr<ASTBlock> fnode_ = std::make_shared<ASTBlock>(SourcePosition(0, 0, ""));
    std::shared_ptr<ASTStatement> parseStatement();
    ASTBlock parseBlock();
    std::shared_ptr<ASTExpr> parseCondition();
    std::shared_ptr<ASTExpr> parseExprTokens(const Token &token, int precendence);
    std::shared_ptr<ASTExpr> parseExprLeft(const Token &token, int precedence);

    std::shared_ptr<ASTExpr> parseExprIdentifier(const Token &token);
    ASTArguments parseArguments(const SourcePosition &position);
    std::shared_ptr<ASTTypeExpr> parseTypeExpr(const SourcePosition &p);

    std::shared_ptr<ASTExpr> parseExpr(int precedence) {
        return parseExprTokens(stream_.consumeToken(), precedence);
    }

    template <typename T>
    std::shared_ptr<T> parseUnaryPrefix(const Token &token) {
        return std::make_shared<T>(parseExpr(kPrefixPrecedence), token.position());
    }

    template <typename T>
    std::shared_ptr<T> parseListingLiteral(Emojis end, const Token &token) {
        auto node = std::make_shared<T>(token.position());
        while (stream_.nextTokenIsEverythingBut(end)) {
            node->addValue(parseExpr(0));
        }
        stream_.consumeToken();
        return node;
    }

    int peakOperatorPrecedence();
};

}  // namespace EmojicodeCompiler

#endif /* FunctionParser_hpp */
