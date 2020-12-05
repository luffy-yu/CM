// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "../ExpressionCommandInterface.h"

// Callback interface to be implemented by the clients of CCalcEngine if they require equation history
class IHistoryDisplay
{
public:
    virtual ~IHistoryDisplay(){};
    virtual unsigned int AddToHistory(
        std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens,
        std::shared_ptr<std::vector<std::shared_ptr<IExpressionCommand>>> const& commands,
        std::wstring_view result) = 0;
};
