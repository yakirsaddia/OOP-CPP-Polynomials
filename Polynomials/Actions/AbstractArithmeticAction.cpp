/*
 * Polynomials Calculator and Graph Drawing
 * Created By: Haim Adrian and Yakir Saadia
 * Final Project for OOP course at Holon Institute of Technology
 * 2019-2020
 */

#include <ostream>
#include "AbstractArithmeticAction.h"
#include "../Utils/PolynomialUtils.h"

void AbstractArithmeticAction::logArithmeticActionMessage(bool isRedo)
{
	Polynomial leftPoly = PolynomialUtils::buildPolynomialFromList(actionContext.getSelectedPolyIndex());
	Polynomial rightPoly = PolynomialUtils::buildPolynomialFromList(actionContext.getSelectedPolyIndex2());

	std::ostringstream out;
	out << '(' << leftPoly << ')' << ' ' << getActionOperator() << ' ' << '(' << rightPoly << ')';

	std::string str = out.str();
	std::wstring wstr(str.begin(), str.end());

	PolynomialsApplication::getInstance().getMainWindow()->logMessageWithInputText(
		std::wstring(isRedo ? L"Redo of " : L"") + getActionName() + L"Action: " + wstr + L" = ");
}

void AbstractArithmeticAction::innerDoExecute()
{
	try
	{
		// Get new polynomial (result of arithmetic operation)
		Polynomial p = doExecute();
		std::ostringstream out;
		out << p;

		std::string str = out.str();
		std::wstring wstr(str.begin(), str.end());

		CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
		input->SetSel(0, input->GetWindowTextLengthW());
		input->ReplaceSel(wstr.c_str());
	}
	catch (std::invalid_argument & e)
	{
		throw ExecuteActionException(e);
	}
	catch (std::overflow_error & e)
	{
		throw ExecuteActionException(e);
	}
}

void AbstractArithmeticAction::execute(const ActionContext & context)
{
	AbstractInputTextKeeperAction::execute(context);

	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
	keepWholeText(input);

	innerDoExecute();

	logArithmeticActionMessage();
}

void AbstractArithmeticAction::undo()
{
	CEdit * input = PolynomialsApplication::getInstance().getInputTextControl();
	input->SetSel(0, input->GetWindowTextLengthW());
	input->ReplaceSel(text);

	PolynomialsApplication::getInstance().getMainWindow()->logMessage(L"Undo of " + getActionName() + L"Action" + L" completed.");
}

void AbstractArithmeticAction::redo()
{
	innerDoExecute();
	logArithmeticActionMessage(true);
}