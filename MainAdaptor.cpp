#include "MainAdaptor.h"

int IsInError = 0;
int IsEditingEnabled = 0;
int m_KeyPressed = 0;
int IsFToEChecked = 0;
bool IsOperatorCommand = false;
NumbersAndOperatorsEnum m_CurrentAngleType = NumbersAndOperatorsEnum::Degree;
int m_isLastOperationHistoryLoad = 0;
int IsFToEEnabled = 0;

Command ConvertToOperatorsEnum(NumbersAndOperatorsEnum operation)
{
    return static_cast<Command>(operation);
}

bool IsOpnd(Command command)
{
    static constexpr Command opnd[] = { Command::Command0, Command::Command1, Command::Command2, Command::Command3, Command::Command4,  Command::Command5,
                                        Command::Command6, Command::Command7, Command::Command8, Command::Command9, Command::CommandPNT };

    return find(begin(opnd), end(opnd), command) != end(opnd);
}

bool IsRecoverableCommand(Command command)
{
    if (IsOpnd(command))
    {
        return true;
    }

    // Programmer mode, bit flipping
    if (Command::CommandBINEDITSTART <= command && command <= Command::CommandBINEDITEND)
    {
        return true;
    }

    static constexpr Command recoverableCommands[] = { Command::CommandA, Command::CommandB, Command::CommandC,
                                                       Command::CommandD, Command::CommandE, Command::CommandF };

    return find(begin(recoverableCommands), end(recoverableCommands), command) != end(recoverableCommands);
}

void send_command(CalculatorManager& m_standardCalculatorManager, NumbersAndOperatorsEnum numOpEnum)
{
    Command cmdenum = ConvertToOperatorsEnum(numOpEnum);

    if (IsInError)
    {
        m_standardCalculatorManager.SendCommand(Command::CommandCLEAR);

        if (!IsRecoverableCommand(static_cast<Command>(numOpEnum)))
        {
            return;
        }
    }

    if (IsEditingEnabled && numOpEnum != NumbersAndOperatorsEnum::IsScientificMode && numOpEnum != NumbersAndOperatorsEnum::IsStandardMode
        && numOpEnum != NumbersAndOperatorsEnum::IsProgrammerMode && numOpEnum != NumbersAndOperatorsEnum::FToE
        && (numOpEnum != NumbersAndOperatorsEnum::Degree) && (numOpEnum != NumbersAndOperatorsEnum::Radians) && (numOpEnum != NumbersAndOperatorsEnum::Grads))
    {
        if (!m_KeyPressed)
        {
            //SaveEditedCommand(m_selectedExpressionToken->TokenPosition, cmdenum);
        }
    }
    else
    {
        if (numOpEnum == NumbersAndOperatorsEnum::IsStandardMode || numOpEnum == NumbersAndOperatorsEnum::IsScientificMode
            || numOpEnum == NumbersAndOperatorsEnum::IsProgrammerMode)
        {
            IsEditingEnabled = false;
        }
        if (numOpEnum == NumbersAndOperatorsEnum::Memory)
        {
            //OnMemoryButtonPressed();
        }
        else
        {
            if (numOpEnum == NumbersAndOperatorsEnum::Clear || numOpEnum == NumbersAndOperatorsEnum::ClearEntry
                || numOpEnum == NumbersAndOperatorsEnum::IsStandardMode || numOpEnum == NumbersAndOperatorsEnum::IsProgrammerMode)
            {
                // On Clear('C') the F-E button needs to be UnChecked if it in Checked state.
                // Also, the Primary Display Value should not show in exponential format.
                // Hence the check below to ensure parity with Desktop Calculator.
                // Clear the FE mode if the switching to StandardMode, since 'C'/'CE' in StandardMode
                // doesn't honor the FE button.
                if (IsFToEChecked)
                {
                    IsFToEChecked = false;
                }
            }
            if (numOpEnum == NumbersAndOperatorsEnum::Degree || numOpEnum == NumbersAndOperatorsEnum::Radians || numOpEnum == NumbersAndOperatorsEnum::Grads)
            {
                m_CurrentAngleType = numOpEnum;
            }
            if ((cmdenum >= Command::Command0 && cmdenum <= Command::Command9) || (cmdenum == Command::CommandPNT) || (cmdenum == Command::CommandBACK)
                || (cmdenum == Command::CommandEXP))
            {
                IsOperatorCommand = false;
            }
            else
            {
                IsOperatorCommand = true;
            }

            if (m_isLastOperationHistoryLoad
                && ((numOpEnum != NumbersAndOperatorsEnum::Degree) && (numOpEnum != NumbersAndOperatorsEnum::Radians)
                    && (numOpEnum != NumbersAndOperatorsEnum::Grads)))
            {
                IsFToEEnabled = true;
                m_isLastOperationHistoryLoad = false;
            }

            //TraceLogger::GetInstance()->UpdateButtonUsage(numOpEnum, GetCalculatorMode());
            m_standardCalculatorManager.SendCommand(cmdenum);
        }
    }
}