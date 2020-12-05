#include "StandardCalculatorViewModel.h"
#include "StringUtils.h"
#include "ResourceProvider.h"

using namespace CalculatorApp;
using namespace CalculationManager;

void StandardCalculatorViewModel::SetExpressionDisplay(std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens, std::shared_ptr<std::vector<std::shared_ptr<IExpressionCommand>>> const& commands)
{
    m_tokens = tokens;
    m_commands = commands;
    if (!m_isEditingEnabled)
    {
        SetTokens(tokens);
    }

    CalculationExpressionAutomationName = GetCalculatorExpressionAutomationName();

    AreTokensUpdated = true;

    std::cout << "CalculationExpressionAutomationName" << std::endl;
    std::wcout << CalculationExpressionAutomationName << std::endl;
}

void StandardCalculatorViewModel::SetTokens(_Inout_ std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens)
{
    AreTokensUpdated = false;

    const size_t nTokens = tokens->size();

    if (nTokens == 0)
    {
        //m_ExpressionTokens->Clear();
        m_ExpressionTokens.clear();
        return;
    }

    //const auto& localizer = LocalizationSettings::GetInstance();

    const wstring separator = L" ";
    for (unsigned int i = 0; i < nTokens; ++i)
    {
        auto currentToken = (*tokens)[i];

        TokenType type;
        bool isEditable = currentToken.second != -1;
        //localizer.LocalizeDisplayValue(&(currentToken.first));

        if (!isEditable)
        {
            type = currentToken.first == separator ? TokenType::Separator : TokenType::Operator;
        }
        else
        {
            const shared_ptr<IExpressionCommand>& command = m_commands->at(currentToken.second);
            type = command->GetCommandType() == CommandType::OperandCommand ? TokenType::Operand : TokenType::Operator;
        }

        //auto currentTokenString = StringReference(currentToken.first.c_str());
        auto currentTokenString = currentToken.first;
        if (i < m_ExpressionTokens.size())
        {
            auto existingItem = m_ExpressionTokens.at(i);
            if (type == existingItem.Type() && existingItem.Token().compare(currentTokenString) == 0)
            {
                existingItem.setTokenPosition(i);
                existingItem.setIsTokenEditable(isEditable);
                existingItem.setCommandIndex(0);
            }
            else
            {
                auto cur = m_ExpressionTokens.begin();
                for (unsigned int j = 0; j < i; j++, cur++) {}
                DisplayExpressionToken expressionToken = DisplayExpressionToken(currentTokenString, i, isEditable, type);
                m_ExpressionTokens.insert(cur, expressionToken);
            }
        }
        else
        {
            auto expressionToken = DisplayExpressionToken(currentTokenString, i, isEditable, type);
            m_ExpressionTokens.push_back(expressionToken);
        }
    }

    while (m_ExpressionTokens.size() != nTokens)
    {
        m_ExpressionTokens.pop_back();
    }
}

unordered_map<wstring, wstring> GetTokenToReadableNameMap()
{
    // Resources for the engine use numbers as keys. It's inconvenient, but also difficult to
    // change given that the engine heavily relies on perfect ordering of certain elements.
    // To compromise, we'll declare a map from engine resource key to automation name from the
    // standard project resources.
    static vector<pair<wstring, wstring>> s_parenEngineKeyResourceMap = { // Sine permutations
                                                                          make_pair<wstring, wstring>(L"67", L"SineDegrees"),
                                                                          make_pair<wstring, wstring>(L"73", L"SineRadians"),
                                                                          make_pair<wstring, wstring>(L"79", L"SineGradians"),
                                                                          make_pair<wstring, wstring>(L"70", L"InverseSineDegrees"),
                                                                          make_pair<wstring, wstring>(L"76", L"InverseSineRadians"),
                                                                          make_pair<wstring, wstring>(L"82", L"InverseSineGradians"),
                                                                          make_pair<wstring, wstring>(L"25", L"HyperbolicSine"),
                                                                          make_pair<wstring, wstring>(L"85", L"InverseHyperbolicSine"),

                                                                          // Cosine permutations
                                                                          make_pair<wstring, wstring>(L"68", L"CosineDegrees"),
                                                                          make_pair<wstring, wstring>(L"74", L"CosineRadians"),
                                                                          make_pair<wstring, wstring>(L"80", L"CosineGradians"),
                                                                          make_pair<wstring, wstring>(L"71", L"InverseCosineDegrees"),
                                                                          make_pair<wstring, wstring>(L"77", L"InverseCosineRadians"),
                                                                          make_pair<wstring, wstring>(L"83", L"InverseCosineGradians"),
                                                                          make_pair<wstring, wstring>(L"26", L"HyperbolicCosine"),
                                                                          make_pair<wstring, wstring>(L"86", L"InverseHyperbolicCosine"),

                                                                          // Tangent permutations
                                                                          make_pair<wstring, wstring>(L"69", L"TangentDegrees"),
                                                                          make_pair<wstring, wstring>(L"75", L"TangentRadians"),
                                                                          make_pair<wstring, wstring>(L"81", L"TangentGradians"),
                                                                          make_pair<wstring, wstring>(L"72", L"InverseTangentDegrees"),
                                                                          make_pair<wstring, wstring>(L"78", L"InverseTangentRadians"),
                                                                          make_pair<wstring, wstring>(L"84", L"InverseTangentGradians"),
                                                                          make_pair<wstring, wstring>(L"27", L"HyperbolicTangent"),
                                                                          make_pair<wstring, wstring>(L"87", L"InverseHyperbolicTangent"),

                                                                          // Secant permutations
                                                                          make_pair<wstring, wstring>(L"SecDeg", L"SecantDegrees"),
                                                                          make_pair<wstring, wstring>(L"SecRad", L"SecantRadians"),
                                                                          make_pair<wstring, wstring>(L"SecGrad", L"SecantGradians"),
                                                                          make_pair<wstring, wstring>(L"InverseSecDeg", L"InverseSecantDegrees"),
                                                                          make_pair<wstring, wstring>(L"InverseSecRad", L"InverseSecantRadians"),
                                                                          make_pair<wstring, wstring>(L"InverseSecGrad", L"InverseSecantGradians"),
                                                                          make_pair<wstring, wstring>(L"Sech", L"HyperbolicSecant"),
                                                                          make_pair<wstring, wstring>(L"InverseSech", L"InverseHyperbolicSecant"),

                                                                          // Cosecant permutations
                                                                          make_pair<wstring, wstring>(L"CscDeg", L"CosecantDegrees"),
                                                                          make_pair<wstring, wstring>(L"CscRad", L"CosecantRadians"),
                                                                          make_pair<wstring, wstring>(L"CscGrad", L"CosecantGradians"),
                                                                          make_pair<wstring, wstring>(L"InverseCscDeg", L"InverseCosecantDegrees"),
                                                                          make_pair<wstring, wstring>(L"InverseCscRad", L"InverseCosecantRadians"),
                                                                          make_pair<wstring, wstring>(L"InverseCscGrad", L"InverseCosecantGradians"),
                                                                          make_pair<wstring, wstring>(L"Csch", L"HyperbolicCosecant"),
                                                                          make_pair<wstring, wstring>(L"InverseCsch", L"InverseHyperbolicCosecant"),

                                                                          // Cotangent permutations
                                                                          make_pair<wstring, wstring>(L"CotDeg", L"CotangentDegrees"),
                                                                          make_pair<wstring, wstring>(L"CotRad", L"CotangentRadians"),
                                                                          make_pair<wstring, wstring>(L"CotGrad", L"CotangentGradians"),
                                                                          make_pair<wstring, wstring>(L"InverseCotDeg", L"InverseCotangentDegrees"),
                                                                          make_pair<wstring, wstring>(L"InverseCotRad", L"InverseCotangentRadians"),
                                                                          make_pair<wstring, wstring>(L"InverseCotGrad", L"InverseCotangentGradians"),
                                                                          make_pair<wstring, wstring>(L"Coth", L"HyperbolicCotangent"),
                                                                          make_pair<wstring, wstring>(L"InverseCoth", L"InverseHyperbolicCotangent"),

                                                                          // Miscellaneous Scientific functions
                                                                          make_pair<wstring, wstring>(L"94", L"Factorial"),
                                                                          make_pair<wstring, wstring>(L"35", L"DegreeMinuteSecond"),
                                                                          make_pair<wstring, wstring>(L"28", L"NaturalLog"),
                                                                          make_pair<wstring, wstring>(L"91", L"Square"),
                                                                          make_pair<wstring, wstring>(L"CubeRoot", L"CubeRoot"),
                                                                          make_pair<wstring, wstring>(L"Abs", L"AbsoluteValue")
    };

    static vector<pair<wstring, wstring>> s_noParenEngineKeyResourceMap = { // Programmer mode functions
                                                                            make_pair<wstring, wstring>(L"9", L"LeftShift"),
                                                                            make_pair<wstring, wstring>(L"10", L"RightShift"),
                                                                            make_pair<wstring, wstring>(L"LogBaseY", L"Logy"),

                                                                            // Y Root scientific function
                                                                            make_pair<wstring, wstring>(L"16", L"YRoot")
    };

    unordered_map<wstring, wstring> tokenToReadableNameMap{};

     static const wstring openParen = GetCEngineString(s_openParenResourceKey);

    for (const auto& keyPair : s_parenEngineKeyResourceMap)
    {
        wstring engineStr = GetCEngineString(keyPair.first);
        wstring automationName =GetResourceString(keyPair.second);

        tokenToReadableNameMap.emplace(engineStr + openParen, automationName);
    }
    s_parenEngineKeyResourceMap.clear();

    for (const auto& keyPair : s_noParenEngineKeyResourceMap)
    {
        wstring engineStr = GetCEngineString(keyPair.first);
        wstring automationName = GetResourceString(keyPair.second);

        tokenToReadableNameMap.emplace(engineStr, automationName);
    }
    s_noParenEngineKeyResourceMap.clear();

     //Also replace hyphens with "minus"
    wstring minusText = GetResourceString(L"minus");
    tokenToReadableNameMap.emplace(L"-", minusText);

    return tokenToReadableNameMap;
}

wstring GetNarratorReadableToken(wstring rawToken)
{
    static unordered_map<wstring, wstring> s_tokenToReadableNameMap = GetTokenToReadableNameMap();

    auto itr = s_tokenToReadableNameMap.find(rawToken);
    if (itr == s_tokenToReadableNameMap.end())
    {
        return rawToken;
    }
    else
    {
        wstring openParen = GetCEngineString(s_openParenResourceKey);
        return wstring(itr->second.c_str()) + L" " + openParen;
    }
}

wstring StandardCalculatorViewModel::GetCalculatorExpressionAutomationName()
{
    wstring expression = L"";
    for (auto&& token : m_ExpressionTokens)
    {
        expression += GetNarratorReadableToken(token.Token());
    }

    //return GetLocalizedStringFormat(m_expressionAutomationNameFormat, expression);
    return expression;
}