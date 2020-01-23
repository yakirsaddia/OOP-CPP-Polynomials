#pragma once
#pragma warning( disable : 4290 ) // Disables the noexcept warning, so we can define specific exception

#ifndef POLYNOMIALS_OPENACTION_H
#define POLYNOMIALS_OPENACTION_H

#include "IAction.h"
#include "ActionContext.h"

class OpenAction : public IAction
{
private:
	ActionContext actionContext;

protected:
	IAction * clone();

public:
	void execute(const ActionContext & context) throw(ExecuteActionException);
};

#endif