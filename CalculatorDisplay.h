// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#pragma once

#include "CEngine/ICalcDisplay.h"
#include "StandardCalculatorViewModel.h"
#include "CalculatorDisplayCallBack.h"

namespace CalculatorApp
{
    // Callback interface to be implemented by the CalculatorManager
    class CalculatorDisplay : public ICalcDisplay
    {
    public:
        CalculatorDisplay();
        void SetCallback(CalculatorDisplayCallBack *callback);
        void SetHistoryCallback(/*Platform::WeakReference callbackReference*/);

    private:
        void SetPrimaryDisplay(const std::wstring& displayString, bool isError) override;
        void SetIsInError(bool isError) override;
        void SetExpressionDisplay(
            std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens,
            std::shared_ptr<std::vector<std::shared_ptr<IExpressionCommand>>> const& commands) override;
        void SetMemorizedNumbers(const std::vector<std::wstring>& memorizedNumbers) override;
        void OnHistoryItemAdded(unsigned int addedItemIndex) override;
        void SetParenthesisNumber(unsigned int parenthesisCount) override;
        void OnNoRightParenAdded() override;
        void MaxDigitsReached() override;
        void BinaryOperatorReceived() override;
        void MemoryItemChanged(unsigned int indexOfMemory) override;
        void InputChanged() override;

    private:
        CalculatorDisplayCallBack *m_callback;
        //Platform::WeakReference m_callbackReference;
        //Platform::WeakReference m_historyCallbackReference;
        StandardCalculatorViewModel m_StandardCalculatorViewModel;
    };
}
