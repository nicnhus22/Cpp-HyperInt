#include "HyperInt.h"

#include <iostream>
#include <string>
#include <regex>
#include <stdlib.h>

using namespace std;

/*
 *	Simple function to split the input operation entered by the user.
 *  If 12^12 then the vector will contain : {'12', '^', '12'} so we can
 *  apply the corresponding operation.
 */
vector<string> inputSplit(const string & INPUT){ 
	vector<string> OPERATION; 

	regex rx("(\\d+)"); 
	smatch match; 
	regex_search(INPUT,match, rx); 

	string OP = INPUT.substr(match.length(),1); 
	string LN = INPUT.substr(match.position(), match.length()); 
	string RN = INPUT.substr(match.length()+1); 

	OPERATION.push_back(LN); 
	OPERATION.push_back(OP); 
	OPERATION.push_back(RN); 
	
	return OPERATION; 
}

/*
 *	Simply display a serie of operations to test all the operators within the HyperInt class.
 */
void displayList(){

	HyperInt hi(313);
	HyperInt li("313");
	HyperInt ci("999");

	cout << endl;
	cout << "First  HyperInt: 313 created as follow: hi(313)"     << endl;
	cout << "Second HyperInt: 313 created as follow: li(\"313\")" << endl;
	cout << "Third  HyperInt: 999 created as follow: ci(\"999\")" << endl << endl;

	cout << "Result of hi+li: " << (hi+li) << endl;
	cout << "Result of hi*li: " << (hi*li) << endl << endl;

	cout << "Performing hi+=li." << endl;
	hi+= li;
	cout << "HyperInt hi after operation: " << (hi) << endl << endl;

	cout << "Performing li*=313." << endl;
	li*=313;
	cout << "HyperInt li after operation: " << (li) << endl << endl;

	cout << "Performing li++." << endl;
	(li++);
	cout << "HyperInt li after operation: " << (li) << endl << endl;

	cout << "Performing ++li." << endl;
	(++li);
	cout << "HyperInt li after operation: " << (li) << endl << endl;

	cout << "Performing ++ci." << endl;
	(++ci);
	cout << "HyperInt ci after operation: " << (ci) << endl << endl;

	cout << "Performing hi=313 and li=313." << endl;
	hi=313; li=313;
	cout << "Performing hi^li: " << (hi^li) << endl << endl;


	if(hi){
		cout << "Performing if(hi): TRUE" << endl;
	}
	else{
		cout << "Performing if(hi): FALSE" << endl;
	}

}

void f()
{
	HyperInt A,B,C;

	cin >> A;//does cin>>A>>B; work?
	cin >> B;
	C = A;
	cout<<"the numbers are: "<<A<<" and "<<B<<endl;
	cout<<"+ : "<< (A+B)  <<endl;
	cout<<"+=: "<< (C+=B) <<endl;
	C = A;
	cout<<"* : "<< (A*B)  <<endl<<"*=: "<< (C*=B) <<endl;
	cout<<"^ : "<< (A^B)  <<endl;
	cout<<"!=: "<< (A!=B) <<endl<<"==: "<< (A==B) <<endl;
	cout<<"< : "<< (A<B)  <<endl<<"> : "<< (A>B)  <<endl;
	
	A = 0;
	B = 1;

	cout<<"bool("<<A<<") is ";
	if(A) cout<<"true";//you can use toBool()
	else  cout<<"false";
	
	cout<<endl<<"bool("<<B<<") is ";
	if(B) cout<<"true";//you can use toBool()
	else  cout<<"false";

	A = HyperInt(1);
	HyperInt D(1);
	B = D;
	cout<<endl<<"values are now: "<<A<<" and "<<B<<endl;
	cout<<"++i: "<<++A<<", and i++: "<<B++<<endl;
	cout<<"FINALLY: "<<A<<" "<<B;
}

int main(){
	
	string			INPUT_OPERATION; // Get the operation from the user
	string			OPERAND;		 // Store the operand to apply right operation
	vector<string>	LO_OP_RO;		 // Put the LeftOperand, Operand and RightOperand in vector to perform operation

	while(true){

		cout << "1. Press 'Q' if you want to quit" << endl
			 << "2. Press 'L' if you want to display the test list" << endl 
			 << "Please enter an operation: ";
		cin  >> INPUT_OPERATION;

		(INPUT_OPERATION == "Q" ? exit(EXIT_SUCCESS) : false);
		(INPUT_OPERATION == "L" ? displayList()      : false);
		
		if(INPUT_OPERATION != "L"){
			LO_OP_RO = inputSplit(INPUT_OPERATION);

			OPERAND = LO_OP_RO[1];
			HyperInt LO(LO_OP_RO[0]);
			HyperInt RO(LO_OP_RO[2]);
			HyperInt RESULT;

			if      (OPERAND == "*") RESULT = LO*RO;
			else if (OPERAND == "+") RESULT = LO+RO;
			else if (OPERAND == "^") RESULT = LO^RO;

			cout << "The result of " << INPUT_OPERATION << " is: "<< RESULT << endl << endl;
		}
	}

	return 0;
}