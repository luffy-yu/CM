#pragma once
#include <iostream>
#include <vector>
#include "pch.h"
#include "Command.h"
#include "ExpressionCommandInterface.h"
#include "StringUtils.h"

using std::string;
using std::vector;
using std::wstring;
using std::shared_ptr;
using std::unordered_map;
using namespace std;
using CalculationManager::CommandType;

static constexpr auto s_openParenResourceKey = L"48";

namespace CalculatorApp {
    enum class TokenType
    {
        Operator,
        Operand,
        Separator
    };

    class DisplayExpressionToken {

    private:
        wstring m_Token;
        int m_TokenPosition;
        bool m_IsTokenEditable;
        TokenType m_Type;
        wstring m_OriginalToken;
        bool m_InEditMode;
        int m_CommandIndex;
    public:
        DisplayExpressionToken(wstring token, int tokenPosition, bool fEditable, TokenType type) : m_Token(token)
            , m_TokenPosition(tokenPosition)
            , m_IsTokenEditable(fEditable)
            , m_Type(type)
            , m_OriginalToken(token)
            , m_InEditMode(false)
            , m_CommandIndex(0) {};

        wstring Token() const
        {
            return m_Token;
        };
        TokenType Type() const
        {
            return m_Type;
        };
        void setTokenPosition(int v)
        {
            m_TokenPosition = v;
        };
        void setIsTokenEditable(bool v)
        {
            m_IsTokenEditable = v;
        };
        void setCommandIndex(int v)
        {
            m_CommandIndex = v;
        };
    };

class StandardCalculatorViewModel
{
private:
    std::shared_ptr<std::vector<std::pair<std::wstring, int>>> m_tokens;
    std::shared_ptr<std::vector<std::shared_ptr<IExpressionCommand>>> m_commands;
    bool m_isEditingEnabled;
    wstring CalculationExpressionAutomationName;
    bool AreTokensUpdated;
    vector<DisplayExpressionToken> m_ExpressionTokens;
public:
    StandardCalculatorViewModel() {};
    void SetExpressionDisplay(
        _Inout_ std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens,
        _Inout_ std::shared_ptr<std::vector<std::shared_ptr<IExpressionCommand>>> const& commands);
    void SetTokens(_Inout_ std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens);
    wstring GetCalculatorExpressionAutomationName();
};

};

