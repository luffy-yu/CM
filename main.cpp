#include <iostream>
#include "MainAdaptor.h"

void test()
{
	CalculatorDisplay m_calculatorDisplay;
	EngineResourceProvider m_resourceProvider;
	CalculatorManager m_standardCalculatorManager(&m_calculatorDisplay, &m_resourceProvider);
    //m_calculatorDisplay.SetCallback(calculatorViewModel);
    send_command(m_standardCalculatorManager, NumbersAndOperatorsEnum::IsStandardMode);
    send_command(m_standardCalculatorManager, NumbersAndOperatorsEnum::Two);
    send_command(m_standardCalculatorManager, NumbersAndOperatorsEnum::Add);
    send_command(m_standardCalculatorManager, NumbersAndOperatorsEnum::Three);
    send_command(m_standardCalculatorManager, NumbersAndOperatorsEnum::Four);
    send_command(m_standardCalculatorManager, NumbersAndOperatorsEnum::Five);
    send_command(m_standardCalculatorManager, NumbersAndOperatorsEnum::Equals);
}


int main(int argc, char* argv[])
{
	cout << "hello\n";
	test();
    int i = 0;
    cin >> i;
	return 0;
}