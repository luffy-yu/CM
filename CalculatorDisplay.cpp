// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

// This class provides the concrete implementation for the ICalcDisplay interface
// that is declared in the Calculation Manager Library.
#include "pch.h"
#include "CalculatorDisplay.h"
//#include "StandardCalculatorViewModel.h"
#include "StringUtils.h"
//#include "BridgeCalculatorDisplay.h"

using namespace CalculatorApp;
using namespace CalculationManager;
//using namespace Platform;
using namespace std;

CalculatorDisplay::CalculatorDisplay()
{
}

void CalculatorDisplay::SetCallback(CalculatorDisplayCallBack *callback)
{
    cout << "SetCallBack" << endl;
    m_callback = callback;
}

//void CalculatorDisplay::SetHistoryCallback(Platform::WeakReference callbackReference)
//{
//    m_historyCallbackReference = callbackReference;
//}

void CalculatorDisplay::SetPrimaryDisplay(const wstring& displayStringValue, bool isError)
{
    //if (m_callbackReference)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->SetPrimaryDisplay(StringReference(displayStringValue.c_str()), isError);
    //    }
    //}
    //TODO
    std::cout << "SetPrimaryDisplay" << std::endl;
    std::wcout << displayStringValue << std::endl;
    //std::cout << ws2s(displayStringValue) << std::endl;
    
    if(m_callback)
    {
        m_callback->SetPrimaryDisplay(displayStringValue, isError);
    }
}

void CalculatorDisplay::SetParenthesisNumber(unsigned int parenthesisCount)
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->SetParenthesisCount(parenthesisCount);
    //    }
    //}
    std::cout << "SetParenthesisNumber" << std::endl;
}

void CalculatorDisplay::OnNoRightParenAdded()
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->OnNoRightParenAdded();
    //    }
    //}
    std::cout << "OnNoRightParenAdded" << std::endl;
}

void CalculatorDisplay::SetIsInError(bool isError)
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->IsInError = isError;
    //    }
    //}
    std::cout << "SetIsInError:" << isError << std::endl;
}

void CalculatorDisplay::SetExpressionDisplay(
    std::shared_ptr<std::vector<std::pair<std::wstring, int>>> const& tokens,
    std::shared_ptr<std::vector<std::shared_ptr<IExpressionCommand>>> const& commands)
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->SetExpressionDisplay(tokens, commands);
    //    }
    //}
//    std::cout << "SetExpressionDisplay" << std::endl;
    m_StandardCalculatorViewModel.SetExpressionDisplay(tokens, commands);
}

void CalculatorDisplay::SetMemorizedNumbers(const vector<std::wstring>& newMemorizedNumbers)
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->SetMemorizedNumbers(newMemorizedNumbers);
    //    }
    //}
    std::cout << "SetMemorizedNumbers" << std::endl;
}

void CalculatorDisplay::OnHistoryItemAdded(unsigned int addedItemIndex)
{
    //if (m_historyCallbackReference != nullptr)
    //{
    //    if (auto historyVM = m_historyCallbackReference.Resolve<ViewModel::HistoryViewModel>())
    //    {
    //        historyVM->OnHistoryItemAdded(addedItemIndex);
    //    }
    //}
    std::cout << "OnHistoryItemAdded" << std::endl;
}

void CalculatorDisplay::MaxDigitsReached()
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->OnMaxDigitsReached();
    //    }
    //}
    std::cout << "MaxDigitsReached" << std::endl;
}

void CalculatorDisplay::BinaryOperatorReceived()
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->OnBinaryOperatorReceived();
    //    }
    //}
    std::cout << "BinaryOperatorReceived" << std::endl;
}

void CalculatorDisplay::MemoryItemChanged(unsigned int indexOfMemory)
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->OnMemoryItemChanged(indexOfMemory);
    //    }
    //}
    std::cout << "MemoryItemChanged" << std::endl;
}

void CalculatorDisplay::InputChanged()
{
    //if (m_callbackReference != nullptr)
    //{
    //    if (auto calcVM = m_callbackReference.Resolve<ViewModel::StandardCalculatorViewModel>())
    //    {
    //        calcVM->OnInputChanged();
    //    }
    //}
    std::cout << "InputChanged" << std::endl;
}
