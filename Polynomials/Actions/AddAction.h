#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_ADDACTION_H
#define POLYNOMIALS_ADDACTION_H

#include "AbstractArithmeticAction.h"

class AddAction : public AbstractArithmeticAction
{
protected:
	IAction * clone();
	Polynomial doExecute();
	std::wstring getActionName() { return L"Add"; }
	char getActionOperator() { return '+'; }
};

#endif
