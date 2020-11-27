/* expression_tree.cpp
   CSC 116 - Fall 2017
   
*/

#include <string>
#include <cmath> //For exp(), log(), sin(), cos() and pow()
#include "expression_tree.hpp"

/* Constant */
double TreeNodeConstant::evaluate( double x ){
    // we do not use the x, so we ignore it
    // this stops the compiler from issuing a parameter non-used warning/error
    std::ignore = x;
	return constant_value;


}
TreeNodePtr TreeNodeConstant::differentiate( ){
	//Derivative of a constant is 0

	TreeNodeConstant constant{0};
	TreeNodePtr constantPtr = std::make_shared<TreeNodeConstant>(constant);
	return constantPtr;

}
TreeNodePtr TreeNodeConstant::duplicate(){
	TreeNodePtr duplicate = std::make_shared<TreeNodeConstant>(constant_value);
	return duplicate;
}

/* Literal X */
double TreeNodeX::evaluate( double x ){
	return x;
}
TreeNodePtr TreeNodeX::differentiate( ){
	//Derivative of x is 1
	TreeNodeConstant constant{1};
	TreeNodePtr constantPtr = std::make_shared<TreeNodeConstant>(constant);
	return constantPtr;
}
TreeNodePtr TreeNodeX::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeX>();
	return duplicate;
}

/* Plus operator */
double TreeNodePlus::evaluate( double x ){
	double sum;
	sum = left->evaluate(x) + right->evaluate(x);
	return sum;
}
TreeNodePtr TreeNodePlus::differentiate( ){
	//Derivative of a + b is the sum of the derivatives of each.
	TreeNodePtr derivPtr = std::make_shared<TreeNodePlus> (left->differentiate(), right->differentiate());
	return derivPtr;

}
TreeNodePtr TreeNodePlus::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodePlus>(left, right);
	return duplicate;
}

/* Minus operator */
double TreeNodeMinus::evaluate( double x ){
	double remainder = left->evaluate(x) - right->evaluate(x);
	return remainder;
}
TreeNodePtr TreeNodeMinus::differentiate( ){
	//Derivative of a - b is the difference of the derivatives of each.
	TreeNodePtr derivPtr = std::make_shared<TreeNodeMinus> (left->differentiate(), right->differentiate());
	return derivPtr;

}
TreeNodePtr TreeNodeMinus::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeMinus>(left,right);
	return duplicate;
}

/* Multiplication operator */
double TreeNodeMultiply::evaluate( double x ){
	double product = left->evaluate(x) * right->evaluate(x);
	return product;
}
TreeNodePtr TreeNodeMultiply::differentiate( ){
	//d/dx ( a*b ) = (d/dx a)*b +  a*(d/dx b)
	TreeNodePtr leeft = std::make_shared<TreeNodeMultiply> (left->differentiate(), right); 
	TreeNodePtr riight = std::make_shared<TreeNodeMultiply> (left, right->differentiate());
	TreeNodePtr productRule = std::make_shared<TreeNodePlus> (leeft, riight);
	return productRule;

}
TreeNodePtr TreeNodeMultiply::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeMultiply>(left,right);
	return duplicate;
}

/* Division operator */
double TreeNodeDivide::evaluate( double x ){
	double quotient = left->evaluate(x) / right->evaluate(x);
	return quotient;
}
TreeNodePtr TreeNodeDivide::differentiate( ){
	//d/dx ( a/b ) = ((d/dx a)*b - a*(d/dx b))/b^2

	TreeNodePtr leeft = std::make_shared<TreeNodeMultiply> (left->differentiate(), right);
	TreeNodePtr riight = std::make_shared<TreeNodeMultiply>(left, right->differentiate());
	TreeNodePtr top = std::make_shared<TreeNodeMinus> (leeft, riight);
	TreeNodePtr butt = std::make_shared<TreeNodeConstantPower>(right, 2);
	
	TreeNodePtr quotientRule = std::make_shared<TreeNodeDivide>(top, butt);
	return quotientRule;
}
TreeNodePtr TreeNodeDivide::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeDivide>(left,right);
	return duplicate;
}

/* Constant power operator (the exponent will always be a fixed value) */
double TreeNodeConstantPower::evaluate( double x ){
	double power = left->evaluate(x);
	//std::cout<<"Exp("<<exponent<<")";
	for(int i=1; i < exponent; ++i){
		power =power * left->evaluate(x);
	}
	return power;

}
TreeNodePtr TreeNodeConstantPower::differentiate( ){
	//d/dx ( a^c ) = c*(d/dx a)*(a)^(c-1)
	TreeNodePtr draggdown = std::make_shared<TreeNodeConstant>(exponent);
	TreeNodePtr expn = std::make_shared<TreeNodeConstantPower>(left, (exponent-1));
	TreeNodePtr deriv = std::make_shared<TreeNodeMultiply>(left->differentiate(), expn);
	TreeNodePtr cons = std::make_shared<TreeNodeMultiply>(draggdown, deriv);
	return cons;  //cons is the final iteration when the constant c is multiplied in.

}
TreeNodePtr TreeNodeConstantPower::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeConstantPower>(left,exponent);
	return duplicate;
}

/* exp function */
double TreeNodeExpFunction::evaluate( double x ){
	double eulResult = exp(argument->evaluate(x));
	return eulResult;
}
TreeNodePtr TreeNodeExpFunction::differentiate( ){
	//d/dx ( e^f(x) ) = (e^f(x))*f'(x)
	TreeNodePtr ogfunct = std::make_shared<TreeNodeExpFunction>(argument);
	TreeNodePtr eulerDeriv = std::make_shared<TreeNodeMultiply>(ogfunct, argument->differentiate());
	return eulerDeriv;
}
TreeNodePtr TreeNodeExpFunction::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeExpFunction>(argument);
	return duplicate;
}

/* log function */
double TreeNodeLogFunction::evaluate( double x ){
	double logResult = log(argument->evaluate(x));
	return logResult;
}
TreeNodePtr TreeNodeLogFunction::differentiate( ){
	//d/dx ( log( f(x) ) ) = (1/f(x))*f'(x) = f'(x)/f(x)
	TreeNodePtr logDeriv = std::make_shared<TreeNodeDivide>(argument->differentiate(), argument);
	return logDeriv;

}
TreeNodePtr TreeNodeLogFunction::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeLogFunction>(argument);
	return duplicate;
}

/* sin function */
double TreeNodeSinFunction::evaluate( double x ){
	double sinResult = sin(argument->evaluate(x));
	return sinResult;
}
TreeNodePtr TreeNodeSinFunction::differentiate( ){
	//d/dx ( sin(f(x)) ) = cos(f(x))*f'(x)
	TreeNodePtr cosTerm = std::make_shared<TreeNodeCosFunction>(argument);
	TreeNodePtr cosDeriv = std::make_shared<TreeNodeMultiply>(cosTerm, argument->differentiate());
	return cosDeriv;
}
TreeNodePtr TreeNodeSinFunction::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeSinFunction>(argument);
	return duplicate;
}

/* cos function */
double TreeNodeCosFunction::evaluate( double x ){
	double cosResult = sin(argument->evaluate(x));
	return cosResult;
}
TreeNodePtr TreeNodeCosFunction::differentiate( ){
	//d/dx ( cos(f(x)) ) = -1*sin(f(x))*f'(x)
	TreeNodePtr negOne = std::make_shared<TreeNodeConstant>(-1);
	TreeNodePtr sinTerm = std::make_shared<TreeNodeSinFunction>(argument);
	TreeNodePtr negify = std::make_shared<TreeNodeMultiply>(negOne, sinTerm);
	TreeNodePtr sinDeriv = std::make_shared<TreeNodeMultiply>(negify, argument->differentiate());
	return sinDeriv;
}
TreeNodePtr TreeNodeCosFunction::duplicate( ){
	TreeNodePtr duplicate = std::make_shared<TreeNodeCosFunction>(argument);
	return duplicate;
}




