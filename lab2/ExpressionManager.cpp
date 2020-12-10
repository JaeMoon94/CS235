#include "ExpressionManager.h"

bool ExpressionManager::isBalanced(string expression){
	// cout << "isBalanced: " << expression << " Length of exression: " << expression.length() << endl;

	stack<char> myExpressions;

	cout << expression.at(0) << endl;
	if(expression.at(0) == ')' || expression.at(0) == '}' || expression.at(0) == ']') return false;
	
	for(int i = 0; i < expression.length(); i++)
	{
		if(isBracketsOrParen(expression.at(i)))
		{
			cout << "Saving... " << expression.at(i) << endl;
			myExpressions.push(expression.at(i));
		}
		
		// cout << "Top of the stack: " << myExpressions.top() << endl;

		if(expression.at(i) == ')')
		{
			if(myExpressions.top() == '(') myExpressions.pop();
		}
		else if(expression.at(i) == ']')
		{
			if(myExpressions.top() == '[') myExpressions.pop();
		}
		else if(expression.at(i) == '}' && i != 0)
		{
			if(myExpressions.top()== '{') myExpressions.pop();
		}
	}
	cout << "Stack size: " <<  myExpressions.size() << endl;
	if(myExpressions.empty())
	{ 
		return true;
	}
	else
	{
		return false;
	}
	

}

string ExpressionManager::postfixToInfix(string postfixExpression){
	// cout << "postfixToInfix: " << postfixExpression << endl;

	stringstream sstr(postfixExpression);
	string tempstr;
	string frontstr;
	string newStr;

	stack <string> myStacks;
	// if(isalpha(postfixExpression.at(0))) return "invalid";
	
	while(sstr >> tempstr)
	{
		if(isNum(tempstr))
		{
			myStacks.push(tempstr);
		}
		else
		{
			if(myStacks.empty()) return "invalid";
			if (tempstr == "+")
			{
				if(myStacks.empty()) return "invalid";
				newStr = myStacks.top();
				myStacks.pop();
				if(myStacks.empty()) return "invalid";
				frontstr = myStacks.top();
				myStacks.pop();

				frontstr = "( " + frontstr  + " + " + newStr + " )";
				myStacks.push(frontstr);
			}
			else if(tempstr =="-")
			{
				if(myStacks.empty()) return "invalid";
				newStr = myStacks.top();
				myStacks.pop();
				if(myStacks.empty()) return "invalid";
				frontstr = myStacks.top();
				myStacks.pop();

				frontstr = "( " + frontstr  + " - " + newStr + " )";
				myStacks.push(frontstr);
			}
			else if (tempstr == "*")
			{
				if(myStacks.empty()) return "invalid";
				newStr = myStacks.top();
				myStacks.pop();
				if(myStacks.empty()) return "invalid";
				frontstr = myStacks.top();
				myStacks.pop();

				frontstr = "( " + frontstr  + " * " + newStr + " )";
				myStacks.push(frontstr);
			}
			else if (tempstr == "/")
			{
				if(myStacks.empty()) return "invalid";
				newStr = myStacks.top();
				myStacks.pop();
				if(myStacks.empty()) return "invalid";
				frontstr = myStacks.top();
				myStacks.pop();

				frontstr = "( " + frontstr + " / " + newStr + " )";
				myStacks.push(frontstr);
			}
			else if (tempstr == "%")
			{
				if(myStacks.empty()) return "invalid";
				newStr = myStacks.top();
				myStacks.pop();
				if(myStacks.empty()) return "invalid";
				frontstr = myStacks.top();
				myStacks.pop();

				frontstr = "( " + frontstr + " % " + newStr + " )";
				myStacks.push(frontstr);
			}
						
		}
		
	}
	if(myStacks.size() > 1) return "invalid";
	return myStacks.top();
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
	cout << "postfixEvaluate: " << postfixExpression << endl;

	if(!isdigit(postfixExpression.at(0))) return "invalid";
	stack<int> myNums;
	int currentNum;
	int tempNum;
	stringstream val;
	stringstream sstr(postfixExpression);
	string tempStr;

	while(sstr >> tempStr)
	{
		if(isNum(tempStr))
		{
			myNums.push(stoi(tempStr));
		}
		else
		{
			if(tempStr == "+")
			{
				tempNum = myNums.top();
				myNums.pop();

				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum + tempNum; 
				myNums.push(currentNum);

			}

			else if(tempStr == "-")
			{
				tempNum = myNums.top();
				myNums.pop();

				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum - tempNum; 
				myNums.push(currentNum);
			}
			else if(tempStr == "*")
			{
				
				tempNum = myNums.top();
				myNums.pop();

				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum * tempNum; 
				myNums.push(currentNum);
			}
			else if(tempStr == "/")
			{
				if(tempNum == 0) return "invalid";
				tempNum = myNums.top();
				myNums.pop();

				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum / tempNum; 
				myNums.push(currentNum);

			}
			else if(tempStr == "%")
			{
				tempNum = myNums.top();
				myNums.pop();

				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum % tempNum; 
				myNums.push(currentNum);

			}
			
		}
		
	}

	// cout << myNums.size() << endl;
	


	if(myNums.size() > 1) 
	{
		return "invalid";
	}
	else 
	{
		val << myNums.top();
		return val.str();
	}
}

string ExpressionManager::infixToPostfix(string infixExpression){
	cout << "infixToPostfix: " << infixExpression << endl;
	stringstream sstr(infixExpression);
	string tempstr;
	string returnStr = "";
	stack <string> myStack;

	if(isBalanced(infixExpression) == false) return "invalid";
	if(isChar(infixExpression)) return "invalid";
	if(isSpecial(infixExpression)) return "invalid";
	if(!isdigit(infixExpression.at(0)) && infixExpression.at(0) != '(') return "invalid";

	while(sstr >> tempstr)
	{
		if(isNum(tempstr))
		{
			returnStr = returnStr + tempstr + " ";
		}
		
		
		else
		{
			cout << "input: " << tempstr << endl;
			if(setPrecedence(tempstr) == 0)
			{
				myStack.push(tempstr);
				// cout << "TOP OF THE STACK: " << myStack.top() << endl;
			}
			else if(setPrecedence(tempstr) == 1)
			{
				if(myStack.empty() || setPrecedence(myStack.top()) < 1)
				{
					myStack.push(tempstr);
					// cout << "TOP OF THE STACK: " << myStack.top() << endl;
				}

				else{
				while(!myStack.empty() && (setPrecedence(myStack.top()) >= 1))
					{
						returnStr = returnStr + myStack.top() + " ";
						myStack.pop();
						cout << myStack.size() << endl;
						cout << myStack.size() << endl;
					}
					myStack.push(tempstr);
				}
			}
			else if(setPrecedence(tempstr) == 2)
			{
				if(myStack.empty() || setPrecedence(myStack.top()) < 2)
				{
					myStack.push(tempstr);
					// cout << "TOP OF THE STACK: " << myStack.top() << endl;
				}
				else if(setPrecedence(myStack.top()) >= 2)
				{
					returnStr = returnStr + myStack.top() + " ";
					// cout << "TOP OF THE STACK: " << myStack.top() << endl;
					myStack.pop();
					myStack.push(tempstr);
					// cout << "TOP OF THE STACK: " << myStack.top() << endl;
				}
			}

			else if(setPrecedence(tempstr) == 3)
			{
				while(myStack.top() != "(")
				{
					returnStr = returnStr + myStack.top() + " ";
					myStack.pop();
				}
				myStack.pop();
			}

		}
		
	}

	while(!myStack.empty())
	{
		returnStr = returnStr + myStack.top() + " ";
		// cout << myStack.top() + " ";
		myStack.pop();	
	}



	cout << "returnStr: " << returnStr << endl;

	if(postfixValidation(returnStr) == false) return "invalid";

	if(!returnStr.empty()) returnStr.pop_back();

	return returnStr;
}


// # helper functions

bool ExpressionManager::isBracketsOrParen(char c){
	if(c == '(') return true;
	else if(c == '{') return true;
	else if(c == '[') return true;
	else return false;
}



string ExpressionManager:: charToString(char c)
{
	string s(1,c);

	return s;
}

int ExpressionManager:: setPrecedence(string s)
{
	if(s == "(" ) return 0;
	else if(s == "+" || s == "-") return 1;
	else if(s == "*" || s == "/" || s == "%") return 2;
	else if(s == ")") return 3;
}

bool ExpressionManager:: isChar(string s)
{

	for(int i = 0; i < s.size(); i++)
	{
		if(isalpha(s.at(i))) return true;
	}
	return false;
}

bool ExpressionManager:: isSpecial(string s)
{
	for(int i = 0; i < s.size(); i++)
	{
		if(s.at(i) == 36 || s.at(i) == 64)
		{
			return true;
		}
		if(s.at(i) == 46) return true;
	}
	return false;
}

bool ExpressionManager:: isNum(string s)
{
	for(int i = 0; i < s.length(); i++)
	{
		if(isdigit(s.at(i)) == false) return false;
	}
	return true;
}

bool ExpressionManager:: postfixValidation(string s)
{
	if(!isdigit(s.at(0))) return false;
	stack<int> myNums;
	int currentNum;
	int tempNum;
	stringstream val;
	stringstream sstr(s);
	string tempStr;

	while(sstr >> tempStr)
	{
		if(isNum(tempStr))
		{
			myNums.push(stoi(tempStr));
		}
		else
		{
			if(tempStr == "+")
			{
				if(myNums.empty()) return false;
				tempNum = myNums.top();
				myNums.pop();

				if(myNums.empty()) return false;
				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum + tempNum; 
				myNums.push(currentNum);

			}

			else if(tempStr == "-")
			{
				if(myNums.empty()) return false;
				tempNum = myNums.top();
				myNums.pop();

				if(myNums.empty()) return false;
				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum - tempNum; 
				myNums.push(currentNum);
			}
			else if(tempStr == "*")
			{
				if(myNums.empty()) return false;
				tempNum = myNums.top();
				myNums.pop();

				if(myNums.empty()) return false;
				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum * tempNum; 
				myNums.push(currentNum);
			}
			else if(tempStr == "/")
			{
				if(tempNum == 0) return false;

				if(myNums.empty()) return false;
				tempNum = myNums.top();
				myNums.pop();

				if(myNums.empty()) return false;
				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum / tempNum; 
				myNums.push(currentNum);

			}
			else if(tempStr == "%")
			{
				if(myNums.empty()) return false;
				tempNum = myNums.top();
				myNums.pop();

				if(myNums.empty()) return false;
				currentNum = myNums.top();
				myNums.pop();

				currentNum = currentNum % tempNum; 
				myNums.push(currentNum);

			}
			
		}
		
	}

	// cout << myNums.size() << endl;
	
	if(myNums.size() > 1) 
	{
		return false;
	}
	else 
	{
		return true;
	}
}