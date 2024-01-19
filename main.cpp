#include <iostream>
using namespace std;
#include <string>

#include "tree.hpp";
#include "Token.hpp";


// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15


double calculate(string inputstr);

int main(){
    string expression = "- * + 5 2 - 7 1 4";
    calculate(expression);
	return 1;
}

double calculate(string inputstr){
    TokenList* tknlist=convertStr_to_TokenList(inputstr); //Convert String to TokenList, return head
    SyntaxTree* syntaxt= parse(tknlist);                   //Convert tknlist to tree, return root
    double calculationResult=syntaxt->pnode->getValue();  //Calculate from tree
    syntaxt->print();                  // Print tree in conventional expression
    cout<<" = "<<calculationResult<<"\n";    // Complete the conventional expression with calculation result
    syntaxt->deleteTree();
}


// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15
// HOURS SPENT>15





