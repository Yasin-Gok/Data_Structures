#include <stdio.h>
#include <string>

using namespace std;

extern string Infix2Postfix(string& s);
extern int EvaluatePostfixExpression(string& s);

int Test1();
int Test2();
int Test3();
int Test4();
int Test5();

int main() {
	int grade = 0;
	
	printf("======================= TEST1 ========================\n");
	grade += Test1();
	printf("------------------------------------------------------\n");
	printf("Final grade: %d\n\n", grade);

	if (grade > 0) {
		grade = 0;
		printf("======================= TEST2 ========================\n");
		grade += Test2();
		printf("------------------------------------------------------\n");
		printf("Final grade: %d\n\n", grade);
		
		grade = 0;
		printf("======================= TEST3 ========================\n");
		grade += Test3();
		printf("------------------------------------------------------\n");
		printf("Final grade: %d\n\n", grade);

		grade = 0;
		printf("======================= TEST4 ========================\n");
		grade += Test4();
		printf("------------------------------------------------------\n");
		printf("Final grade: %d\n\n", grade);

		grade = 0;
		printf("======================= TEST5 ========================\n");
		grade += Test5();
		printf("------------------------------------------------------\n");
		printf("Final grade: %d\n", grade);
	}
	
	// printf("------------------------------------------------------\n");
	// printf("Final grade: %d\n", grade);
	return 0;
}

  /****************************************************
   * Test1
   ****************************************************/
int Test1() {
	// infixExpr: 3500 - ((43*12) + (47/2));    
	// Let the C++ compiler do the evaluation :-)
	int expressionValue = 3500 - ((43 * 12) + (47 / 2));

	// postfix: 3500 43 12 * 47 2 / + -
	string postfixExpr = "3500 43 12 * 47 2 / + -";
	int result = EvaluatePostfixExpression(postfixExpr);
	if (result != expressionValue) return 0;
	
	return result;
} //end-Test1

/****************************************************
 * Test2
 ****************************************************/
int Test2() {
	int expressionValue = 20 + 2 * 3 + (2 * 8 + 5) * 4;

	string infixExpr = "20 + 2 * 3     + (2*8 + 5)* 4";
	string postfixExpr = Infix2Postfix(infixExpr);
	printf("Infix Expr: <%s>\nPostfixExpr: <%s>\n", infixExpr.c_str(), postfixExpr.c_str());

	int result = EvaluatePostfixExpression(postfixExpr);
	if (result != expressionValue) return 0;

	return result;
} //end-Test2

/****************************************************
 * Test3
 ****************************************************/
int Test3() {
	// Let the C++ compiler do the evaluation :-)
	int expressionValue = 20 * 2 + 3 - (2 * 8 + 5) * 4;

	string infixExpr = "20* 2 + 3 - (2*8 + 5)* 4";
	string postfixExpr = Infix2Postfix(infixExpr);
	printf("Infix Expr: <%s>\nPostfixExpr: <%s>\n", infixExpr.c_str(), postfixExpr.c_str());

	int result = EvaluatePostfixExpression(postfixExpr);
	if (result != expressionValue) return 0;

	return result;
} //end-Test3

/****************************************************
 * Test4
 ****************************************************/
int Test4() {
	int expressionValue = 220 - 45 - 10;

	string infixExpr = "220 - 45 - 10";
	string postfixExpr = Infix2Postfix(infixExpr);
	printf("Infix Expr: <%s>\nPostfixExpr: <%s>\n", infixExpr.c_str(), postfixExpr.c_str());

	int result = EvaluatePostfixExpression(postfixExpr);
	if (result != expressionValue) return 0;

	return result;
} //end-Test4

/****************************************************
 * Test5
 ****************************************************/
int Test5() {
	int expressionValue = (((13 + 35) * 22) / 45) - (45 + 34 * (190 - 34)) / 100;

	string infixExpr = "(((13+35)*22)/45) - (45+34*(190-34))/100";
	string postfixExpr = Infix2Postfix(infixExpr);
	printf("Infix Expr: <%s>\nPostfixExpr: <%s>\n", infixExpr.c_str(), postfixExpr.c_str());

	int result = EvaluatePostfixExpression(postfixExpr);
	if (result != expressionValue) return 0;

	return result;
} //end-Test5