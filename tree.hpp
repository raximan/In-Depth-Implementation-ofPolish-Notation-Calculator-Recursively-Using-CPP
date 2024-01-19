#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

#include "Token.hpp"
class Node {
public:
    Node(Token*& token, Node* right = nullptr, Node* left = nullptr):Left(left),Right(right) {tokenval=token->tokenvalue;}
    virtual double getValue() const = 0;
    string tokenval;
    Node* Right;
    Node* Left;
    ~Node() {
    // TO DELETE NODE AND ALL THE CHILD NODES
    // WORKS FOR THIS CODE AND MUST BE CHANGED IN CASES WHERE CHILD NODES SHOULD BE PROTECTED
    delete Left;
    delete Right;
    }
};

// FULL DEFINITION OF CLASS

class OperatorNode : public Node {
    public:
        OperatorNode( Token* token, Node* left = nullptr, Node* right = nullptr): Node(token, left, right) {
        	string tokenvalu=token->tokenvalue;
        	if(tokenvalu=="+"){
                Operation=ADDITION;
            } else if(tokenvalu=="-"){
                Operation=SUBTRACTION;
            } else if(tokenvalu=="*"){
                Operation=MULTIPLICATION;
            } else if(tokenvalu=="/"){
                Operation=DIVISION;
            }else{
                std::cout<<"UKNOWN OPERAND!!!!";
            }
        }
        double getValue() const override {
            double leftValue = Left->getValue();
            double rightValue = Right->getValue();

            switch (Operation) {
            case ADDITION:
                return leftValue + rightValue;
            case SUBTRACTION:
                return leftValue - rightValue;
            case MULTIPLICATION:
                return leftValue * rightValue;
            case DIVISION:
                return leftValue / rightValue;
            }

            return 0.0; // Default case, though it should not happen if input is valid
        }
        OpType Operation;

        ~OperatorNode() {
            // TO DELETE NODE AND ALL THE CHILD NODES
            // WORKS FOR THIS CODE AND MUST BE CHANGED IN CASES WHERE CHILD NODES SHOULD BE PROTECTED
            delete Left;
            delete Right;
        }
};
// NumberNode class
class NumberNode : public Node {
    private:
        double value;
    public:
        NumberNode(Token*& token, Node* left = nullptr, Node* right = nullptr): Node(token, left, right) {
        string tokenvalu=token->tokenvalue;
        value=std::stof(tokenvalu);
        }
        double getValue() const  {
            return value;
        }
        ~NumberNode() {
        cout<<"Destructing Operator Node, Value: "<<value<<"\n";
        // TO DELETE NODE AND ALL THE CHILD NODES
        // WORKS FOR THIS CODE AND MUST BE CHANGED IN CASES WHERE CHILD NODES SHOULD BE PROTECTED
        delete Left;
        delete Right;
        }
};

class SyntaxTree{
    public:
        SyntaxTree(Node*& usyntaxNode):pnode(usyntaxNode){}
        Node* pnode;
        void print();
        void printHelper(Node* head, string* result);// For More smooth Implementation of 'print' without extra variables
        void deleteTree(){
            //WHERE DELETING TREE IS EXPLICILY SEEKED
            delete pnode;}
        ~SyntaxTree(){
            delete pnode;
        }

    };
// TOKENLIST TRACKER IS USED TO KEEP TRACK OF THE 'POINTER' OF TOKENS AND CHANGE THEM WHEN NECESSARY
Node* parseHelper(TokenList** TokenListTracker,Node*curr);
SyntaxTree* parse(TokenList* tknlist);

// CONVEYING TOKENS TO THE NODES RECURSIVELY BY THEIR TYPE
Node* parseHelper(TokenList** TokenListTracker,Node*curr){
    if((*TokenListTracker)->data->type==NUMBER){
        Node* NumNode=new NumberNode((*TokenListTracker)->data);
        *TokenListTracker=(*TokenListTracker)->next;
        return NumNode;
    }
    else if((*TokenListTracker)->data->type==OPERATOR){

        Node* OpNode=new OperatorNode((*TokenListTracker)->data);
        *TokenListTracker=(*TokenListTracker)->next;
        OpNode->Left=parseHelper(TokenListTracker,OpNode->Left);
        OpNode->Right=parseHelper(TokenListTracker,OpNode->Right);
        return OpNode;
    }
}

void SyntaxTree::printHelper(Node* head, string* result) {
    if (head == nullptr) {
        return;
    }

    // PUT PARANTHESIS FOR + AND - FOR BETTER LOOKING
    if (head->tokenval == "+" || head->tokenval == "-") {
        *result += "(";
    }

    //CHECK NODE IS NUMBER
    if (head->Left != nullptr) {
        printHelper(head->Left, result);
    }

    *result += head->tokenval;

    //CHECK NODE IS NUMBER
    if (head->Right != nullptr) {
        printHelper(head->Right, result);
    }

    if (head->tokenval == "+" || head->tokenval == "-") {
        *result += ")";
    }
}

void SyntaxTree::print(){
    string result="";
    printHelper(pnode,&result);
    // Check if the first character is '(' and the last character is ')'
    if (result.length() >= 2 && result.front() == '(' && result.back() == ')') {
        // Remove the first and last character
        result = result.substr(1, result.length() - 2);
    }

    // Print the modified result
    cout << result;
}

// CONVERT TOKENLIST TO SYNTAXTREE
SyntaxTree* parse(TokenList* tknlist){
	SyntaxTree* head;
	Node* nodeHead;
	Node* nodeCurrent;
	TokenList** currentTokenList;
	if(tknlist!=nullptr){
        if(tknlist->data->type==OPERATOR){
            nodeHead=new OperatorNode(tknlist->data);
            head=new SyntaxTree(nodeHead);
        }
        else if(tknlist->data->type==NUMBER){
            nodeHead=new NumberNode(tknlist->data);
            head=new SyntaxTree(nodeHead);
        }
        nodeCurrent=nodeHead;
        currentTokenList= &tknlist;
    }
    nodeCurrent->Left=parseHelper(&((*currentTokenList)->next),nodeCurrent->Left);
    nodeCurrent->Right=parseHelper(&((*currentTokenList)->next),nodeCurrent->Right);
    return head;
}



#endif // TREE_HPP_INCLUDED
