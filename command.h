#ifndef __COMMAND_CLASS__
#define __COMMAND_CLASS__

#include "composite.h"

class Command {
	protected:
		Base* root;
	
	public:
		Command() { };
		Command(Base* abc) : root(abc) {};
		double execute() {
			return root->evaluate();
		};
		Base* get_root() {
			return root;
		};
};

class OpCommand : public Command {
	//OpCommand Code Here
	public:
		OpCommand() : Command(new Op()) {};
		OpCommand(int abc) : Command(new Op((double)abc)) {};
};

class AddCommand : public Command {
	//AddCommand Code Here
	public:
		AddCommand() : Command(new Add()) {};
		AddCommand(Command* abc, int xyz) : Command(new Add(abc->get_root(), new Op((double)xyz))) {};
};

class SubCommand : public Command {
	//SubCommand Code Here
	public:
		SubCommand() : Command(new Sub()) {};
		SubCommand(Command* abc, int xyz) : Command(new Sub(abc->get_root(), new Op((double)xyz))) {};
};

class MultCommand : public Command {
	//MultCommand Code Here
	public:
		MultCommand() : Command(new Mult()) {};
		MultCommand(Command* abc, int xyz) : Command(new Mult(abc->get_root(), new Op((double)xyz))) {};
};

class SqrCommand : public Command {
	//SqrCommand Code Here
	public:
		SqrCommand() : Command(new Sqr()) {};
		SqrCommand(Command* abc) : Command(new Sqr(abc->get_root())) {};
};

#endif //__COMMAND_CLASS__
