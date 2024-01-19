#ifndef TOKEN_HPP_INCLUDED
#define TOKEN_HPP_INCLUDED

//TOKEN TYPES
enum TokenType {
    OPERATOR,
    NUMBER,
    UNKNOWN
};

//OPERATION TOKEN TYPES
enum OpType{
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
};


class Token{
	public:
		Token(string utoken);
		TokenType type;
		string tokenvalue; //Store the token as a string for less complex transition to Node Class
    private:
        bool isValidNumber(const string& str) {
            bool decimalPoint = false;
            size_t startIndex = 0;

            // Handle negative numbers
            if (!str.empty() && str[0] == '-') {
                startIndex = 1;
                if (str.size() == 1) return false; // String contains only '-'
            }

            // Check each character
            for (size_t i = startIndex; i < str.size(); i++) {
                if (str[i] == '.') {
                    if (decimalPoint) return false; // More than one decimal point
                    decimalPoint = true;
                } else if (!isdigit(str[i])) {
                    return false; // Not a digit
                }
            }
            return true;
        }


};

class OperatorToken: public Token{
	public:
		OperatorToken(string uoptoken);
		OpType opToken;
        ~OperatorToken() {
        cout<<"Destructing Operator Token\n";
        }

};

class NumberToken: public Token{
	public:
		NumberToken(string unumtoken);
		double numvalue;
        ~NumberToken() {
        cout<<"Destructing Number Token\n";
        }
};

class TokenList{
    public:
		// constructor
        TokenList(Token *& item, TokenList* ptrnext=nullptr) : data(item), next(ptrnext) {}
            	// the data is public
        TokenList* next;
        Token* data;

        // list modification methods
        void InsertAfter(TokenList *p);
        TokenList *DeleteAfter(void);

        // set the next node, but be careful, the original next node would be lost
        void SetNext(TokenList *p);
        void printTokenList(TokenList* head);
        ~TokenList() {
        delete data;
        }

};
TokenList* convertStr_to_TokenList(string str);

Token::Token(string utoken){
	tokenvalue=utoken;
	//CHECK IF INPUT IS A  VALID TOKEN
    if ( isValidNumber(utoken) ) { // CHECK FOR NEGATIVE CHARACTERS
        type = NUMBER;
    } else if (utoken == "+" || utoken == "-" || utoken == "*" ||utoken == "/") {
        type = OPERATOR;
    } else {
        cout<<"Invalýd Character "<<utoken<<"\n";
        type = UNKNOWN;
    }
}

OperatorToken::OperatorToken(string uoptoken):Token(uoptoken){
	//CHECK TYPE OF OPERATOR
	if(uoptoken=="+"){
		opToken=ADDITION;
	} else if(uoptoken=="-"){
		opToken=SUBTRACTION;
	} else if(uoptoken=="*"){
		opToken=MULTIPLICATION;
	} else if(uoptoken=="/"){
		opToken=DIVISION;
	}else{
		std::cout<<"UKNOWN OPERAND!!!! : '"<<uoptoken<<"'";// Handle edge case
	}
}

NumberToken::NumberToken(string unumtoken):Token(unumtoken){
	numvalue=std::stof(unumtoken); // Convert string input to double
}

void TokenList::InsertAfter(TokenList *p)
{
	if (p != NULL)
    {
        // p points to successor of the current node,
        // and current node points to p.
        p->next = next; //notice access to private part of member of same class
        next = p; //also note correct sequence of operation
    }
    else
        next = NULL;
}

void TokenList:: printTokenList(TokenList* head) {
    TokenList* current = head;

    while (current) {
        std::cout << current->data->tokenvalue << " ";
        current=current->next;
    }
    std::cout << std::endl;
}

TokenList* convertStr_to_TokenList(string str){

	std::string token;
	TokenList* head = nullptr;
    TokenList* current = nullptr;
	for(int i = 0; i<str.length(); i++) {

        // PASS SPACES
        while (i < str.length() && str[i] == ' ') {
            ++i;
        }

        // EXTRACT TOKEN
        while (i < str.length() && str[i] != ' ') {
            token += str[i];
            ++i;
        }

		Token* tkn=new Token(token);//First declare token
		Token* listToken;
		//CHECK TYPE THAN CREATE CHILD CLASS TOKEN
		if(tkn->type==OPERATOR){
            listToken=new OperatorToken(tkn->tokenvalue);
            delete tkn;
        }
		else if(tkn->type==NUMBER){
            listToken=new NumberToken(tkn->tokenvalue);
            delete tkn;
		}
        TokenList* newNode = new TokenList(listToken);
        //ADD TOKEN TO TOKENLIST
        if (!head) {
            // If the list is empty, set the new node as the head
            head = newNode;
            current = newNode;
        } else {
            // Otherwise, add the new node to the end of the list
            current->InsertAfter(newNode) ;
            current = newNode;
        }

        // RESET TOKEN STRING FOR NEXT ITERATION
        token = "";
   }
    return head;
}




#endif // TOKEN_HPP_INCLUDED
