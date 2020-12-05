#pragma once
//class MainAdaptor
//{
//};
#include <iterator>
#include <map>
#include "ResourceProvider.h"
#include "CalculatorManager.h"
#include "CalculatorButtonUser.h"
#include "CalculatorDisplay.h"
#include "EngineResourceProvider.h"
#include "CalculatorResource.h"

using namespace std;
using std::cout;

using namespace CalculationManager;
using namespace CalculatorApp;



void send_command(CalculatorManager& m_standardCalculatorManager, NumbersAndOperatorsEnum numOpEnum);
