
#include "HyperInt.h"

#include <iostream>
#include <sstream>


using namespace std;

typedef vector<short>::size_type hyper_size;


/*********************************************************************
 *						CONSTRUCTORS & DESTRUCTOR
 *********************************************************************/

/*
 *	Parameterized constructor taking a long as input if the number fits. Otherwise use the HyperInt(string) constructor.
 */
HyperInt::HyperInt(const long & hi) {
	std::string number;
	std::stringstream strstream;
	strstream << hi;
	strstream >> number;

	//Read string in reverse for optimal performance when doing arithmetic
	for(string::size_type i = number.size()-1; i!=-1; --i){
		char a = number.at(i);
		short b = a-48;//Get number value from ASCII
		VALUE.push_back(b);//Push each digit in vector value (reverse order)
	}
	LENGTH = VALUE.size();//Initialize LENGTH
}

/*
 *	Parameterized constructor taking a string as input if the number is too large to fit in the HyperInt(long) constructor.
 */
HyperInt::HyperInt(const string & s){
	for(string::size_type i = s.size()-1; i!=-1; --i){
		char a = s.at(i);
		short b = a-48; // Conversion from ASCII
		VALUE.push_back(b);
	}
	LENGTH = VALUE.size();
}

/*
 *	Parameterized constructor taking a vector<short> as input. Vector representing the number should be in reversed order:
 *	Example: If the number is 2014 then the vector should be {4 1 0 2}.
 */
HyperInt::HyperInt(const vector<short> & hi, std::vector<short>::size_type len) : 
	VALUE(hi),
	LENGTH(len)
{};

/*
 *	Destructor for the HyperInt type. Leaving default because no pointer members thus no special operations needed.
 */
HyperInt::~HyperInt(){}


/*********************************************************************
 *					ARITHMETIC OPERATIONS (*, +, +=, *=)
 *********************************************************************/

/*
 *	Operator * allowing to perform the following operation:
 *	1. HI1 * HI2
 */
const HyperInt operator*(const HyperInt & lhi, const HyperInt & rhi){

	vector<short> LAYER;
	HyperInt result(0);
	short carry = 0;
	int value = 0;

	if(lhi.LENGTH >= rhi.LENGTH){//Check length for range
		

		for(hyper_size i = 0; i != rhi.LENGTH; i++){//Go through each digit of smaller vector

			for(int k=0; k != i; ++k){//Push 0 in vector for each new layer (don't push first loop, push one 0 after, two 0 next loop...)
					LAYER.push_back(0);
				}

			for(hyper_size j = 0; j != lhi.LENGTH; j++){//Go through each digit of bigger vector
				value = (rhi.VALUE[i]*lhi.VALUE[j]);//Multiply each digit of smaller vector with every digit of bigger vector
				if(value > 9){//There is a carry
					if((value%10 + carry) > 9){//There is another carry from adding value to previous carry
						LAYER.push_back((value%10 + carry)%10);//Push result's last digit (e.g. for 9*9 = 81 we push 1)
						carry = 1;
					}
					else{
						LAYER.push_back(value%10 + carry);//Push result's last digit
						carry = 0;
					}
					carry += value / 10;//add carry of multiplied value (e.g. for 9*9=81, carry is 8)
				}
				else{
					if((value + carry) > 9){//Carry by adding value to previous carry
						LAYER.push_back((value + carry)%10);
						carry = 1;
					}
					else{
						LAYER.push_back(value + carry);
						carry = 0;
					}
				}
			}
			if(carry != 0){//If carry remains, push it
				LAYER.push_back(carry);
				carry = 0;
			}

				HyperInt hy(LAYER, LAYER.size());
				result += hy;//Add the layers

				LAYER.clear();
		}

	}
	else if(rhi.LENGTH > lhi.LENGTH){//Do the same but in opposite order as first if
		
		for(hyper_size i = 0; i != lhi.LENGTH; i++){

			for(int k=0; k != i; ++k){
				LAYER.push_back(0);
			}

			for(hyper_size j = 0; j != rhi.LENGTH; j++){
				value = (lhi.VALUE[i]*rhi.VALUE[j]);
				if(value > 9){
					if((value%10 + carry) > 9){
						LAYER.push_back((value%10 + carry)%10);
						carry = 1;
					}
					else{
						LAYER.push_back(value%10 + carry);
						carry = 0;
					}
					carry += value / 10;
				}
				else{
					if((value + carry) > 9){
						LAYER.push_back((value + carry)%10);
						carry = 1;
					}
					else{
						LAYER.push_back(value + carry);
						carry = 0;
					}
				}
			}
			if(carry != 0){
				LAYER.push_back(carry);
				carry = 0;
			}

			HyperInt hy(LAYER, LAYER.size());
			result += hy;

			LAYER.clear();
		}
	}
		
	return result;
}

/*
 *	Operator + allowing to perform the following operation:
 *	1. HI1+HI2
 */
const HyperInt operator+(const HyperInt & lhi, const HyperInt & rhi){
	short carry = 0;
	int value = 0;
	vector<short> RESULT_VALUES;

	if(lhi.LENGTH >= rhi.LENGTH){//Check for length to avoid going out of range
		for(hyper_size i = 0; i!=lhi.LENGTH; i++){//Go through each digit of biggest vector
			if(i < rhi.LENGTH){//Check not out of range of smallest vector
				value = (lhi.VALUE[i] + rhi.VALUE[i]);//Added value at each index
				if(value > 9){//There is a carry
					short a = value - 10;
					RESULT_VALUES.push_back(a + carry);//Push value - 10 + carry ,  there will never be another carry from adding previous carry since biggest added value is 8<9 (9+9=18)
					carry = 1;
				}
				else{//No carry
					if((value + carry ) == 10){//Check for carry, e.g. if digit is 9 + the carry(1) -> 10
						RESULT_VALUES.push_back(0);
						carry = 1;
					}
					else{
						RESULT_VALUES.push_back(value + carry);
						carry = 0;
					}
				}
			}
			else{
				RESULT_VALUES.push_back(lhi.VALUE[i] + carry);//If length is different, add remaining values of biggest HyperInt
				carry = 0;
			}
			
		}	
		if(carry != 0){//If carry remains, add it 
			RESULT_VALUES.push_back(carry);
			carry = 0;
		}
	}
	
	else if(rhi.LENGTH > lhi.LENGTH){//Do the same but in opposite order as first if
		for(hyper_size i = 0; i!=rhi.LENGTH; i++){
			if(i < lhi.LENGTH){
				value = (lhi.VALUE[i] + rhi.VALUE[i]);
				if(value > 9){
					short a = value - 10;
					RESULT_VALUES.push_back(a + carry);
					carry = 1;
				}
				else{
					if((value + carry ) == 10){
						short a = value - 10;
						RESULT_VALUES.push_back(0);
						carry = 1;
					}
					else{
						RESULT_VALUES.push_back(value + carry);
						carry = 0;
					}
				}
			}
			else{
				RESULT_VALUES.push_back(rhi.VALUE[i] + carry);
				carry = 0;
			}
		}	
				
		if(carry != 0){
			RESULT_VALUES.push_back(carry);
			carry = 0;
		}
	}

	HyperInt result(RESULT_VALUES, RESULT_VALUES.size());

	return result;
}

/*
 *	Operator += allowing to perform the following operation:
 *	1. HI1 += HI2
 */
const HyperInt &  HyperInt::operator+=(const HyperInt & hi){
	(*this) = (*this) + hi;
	LENGTH = VALUE.size(); //Update length
	return (*this);
}

/*
 * Operator *= allowing to perform the following operation:
 *	1. HI1 *= HI2
 */
const HyperInt &  HyperInt::operator*=(const HyperInt & hi){
	(*this) = (*this) * hi;
	LENGTH = VALUE.size();//Update length
	return (*this);
}

/*
 * Operator ^ allowing to perform the following operation:
 *	1. HI1^HI2
 */
const HyperInt HyperInt::operator^ (const HyperInt & hi) const{
	HyperInt result(1);

	double long value = 0;

	//Length of the hyperInt gives number of power of 10 to loop through, e.g. 313 length is 3 and we loop from 0 to 2 : 3*10^0 + 1*10^1 + 3*10^2
	for(long i = 0; i != hi.LENGTH; i++){
		value = pow(10,i) * hi.VALUE[i]; //Here we do digit (e.g. 3) * the power of 10 (e.g. 10^0, 10^1 ...)
		for(short j = 0; j != value; j++){
			result *= (*this);//Multiply HyperInt n times (where n is the value of passed HyperInt)
		}
	}

	return result;
}


/*********************************************************************
 *					POSTINCREMENT & PREINCREMENT (++)
 *********************************************************************/

/*
 *	Operator ++ (Pre Increment) allowing us to perform the following operations:
 *		++HI to increment by 1 the HyperInt object 
 */
HyperInt & HyperInt::operator++(){
	short carry = 1;

	if(VALUE[0] != 9){//Check if last digit is 9 for carry
		VALUE[0] += 1;
		carry = 0;
	}else{
		VALUE[0] = 0;
		for(hyper_size i = 1; i!=LENGTH; i++){//Go through each digit and add carry until carry becomes 0
			if(VALUE[i] + carry == 10){
				VALUE[i] = 0;
				carry = 1;
			}
			else{
				VALUE[i] = VALUE[i] + carry;
				carry = 0;
				break; //Carry is now 0 so other values don't need to be incremented
			}
		}	
	}

	if(carry == 1){//If carry remains, push 1 in vector (e.g. for 999 -> 1000)
		++LENGTH;
		VALUE.push_back(1);
	}
	
	return (*this);
}

/*
 *	Operator ++ (Post Increment) allowing us to perform the following operations:
 *		HI++ to increment by 1 the HyperInt object 
 */
HyperInt HyperInt::operator++(int){
	HyperInt a(VALUE, LENGTH);
	++(*this);
	return a;
}



/*********************************************************************
 *						INSERTERS & EXTRACTORS
 *********************************************************************/

/*
 *	Operator << allowing us to display the value of a HyperInt object. Can be used this way:
 *		cout << HI; (e.g: Would display 1234 if HI has value 1234)
 */
ostream & operator<<(std::ostream & os, const HyperInt & hi){
	//Go in reverse order through VALUE vector to display since an HyperInt is initialized in reverse order
	for (int i = hi.LENGTH-1; i != -1; i--){
		os << hi.VALUE[i];
	}

	return os;
}

/*
 *	Operator >> allowing us to insert the value of a HyperInt object. Can be used this way:
 *		cin >> HI; (e.g: Would display 1234 if HI has value 1234)
 */
istream & operator>>(std::istream & is, HyperInt & hi){
	
	string VALUE;

	is >> VALUE;

	hi = HyperInt(VALUE);

	return is;
}




/*********************************************************************
 *				BOOLEAN OPERATOS (<, <=, >, >=, ==, !=)
 *********************************************************************/

/*
 *	Operator == allowing us to test if two HyperInt objects are equal. Can be used this way:
 *		if(HI1 == HI2) (e.g: Would display true if HI1 has the same value as HI2)
 */
const bool operator== (const HyperInt lhi,const HyperInt rhi){
	if( lhi.LENGTH != rhi.LENGTH )
		return false;
	else {
		for(hyper_size i = 0; i != lhi.LENGTH; ++i){
			if(lhi.VALUE[i] != rhi.VALUE[i])
				return false;
		}
	}
	return true;
}

/*
 *	Operator != allowing us to test if two HyperInt objects are not equal. Can be used this way:
 *		if(HI1 != HI2) (e.g: Would display true if HI1 doesnt have the same value as HI2)
 */
const bool operator!= (const HyperInt lhi,const HyperInt rhi){
	if( lhi.LENGTH != rhi.LENGTH )
		return true;
	else {
		for(hyper_size i = 0; i != lhi.LENGTH; ++i){
			if(lhi.VALUE[i] != rhi.VALUE[i])
				return true;
		}
	}
	return false;
}

/*
 *	Operator < allowing us to test if an HyperInt object is less than other one. Can be used this way:
 *		if(HI1 < HI2) (e.g: Would display true if HI1 is smaller than HI2)
 */
const bool operator<  (const HyperInt lhi,const HyperInt rhi){
	if(lhi.LENGTH < rhi.LENGTH)
		return true;
	else if (lhi.LENGTH > rhi.LENGTH)
		return false;
	else{
		for (int i = lhi.LENGTH-1; i != -1; i--){ 
			if(lhi.VALUE[i] < rhi.VALUE[i])
				return true;
		}
	}
	return false;
}

/*
 *	Operator <= allowing us to test if an HyperInt object is less than or equal to other one. Can be used this way:
 *		if(HI1 <= HI2) (e.g: Would display true if HI1 is smaller or equal than HI2)
 */
const bool operator<= (const HyperInt lhi,const HyperInt rhi){
	if(lhi.LENGTH < rhi.LENGTH)
		return true;
	else if (lhi.LENGTH > rhi.LENGTH)
		return false;
	else{
		for (int i = lhi.LENGTH-1; i != -1; i--){ 
			if(lhi.VALUE[i] < rhi.VALUE[i])
				return true;
			else if(lhi.VALUE[i] > rhi.VALUE[i])
				return false;
		}
	}
	// Reaches here if nad only if they're equal.
	return true;
}

/*
 *	Operator > allowing us to test if an HyperInt object is more than other one. Can be used this way:
 *		if(HI1 > HI2) (e.g: Would display true if HI1 is greater than HI2)
 */
const bool operator>  (const HyperInt lhi,const HyperInt rhi){
	if(lhi.LENGTH > rhi.LENGTH)
		return true;
	else if (lhi.LENGTH < rhi.LENGTH)
		return false;
	else{ // They have the same length
		for (int i = lhi.LENGTH-1; i != -1; i--){ 
			if(lhi.VALUE[i] > rhi.VALUE[i])
				return true;
		}
	}
	return false;
}

/*
 *	Operator >= allowing us to test if an HyperInt object is more than or equal to an other one. Can be used this way:
 *		if(HI1 >= HI2) (e.g: Would display true if HI1 is greater than or equal HI2)
 */
const bool operator>= (const HyperInt lhi,const HyperInt rhi){
	if(lhi.LENGTH > rhi.LENGTH)
		return true;
	else if (lhi.LENGTH < rhi.LENGTH)
		return false;
	else{ // They have the same length
		for (int i = lhi.LENGTH-1; i != -1; i--){ 
			if(lhi.VALUE[i] > rhi.VALUE[i])
				return (lhi.VALUE[i] > rhi.VALUE[i]);
			else if(lhi.VALUE[i] < rhi.VALUE[i])
				return false;
		}
	}
	// Reaches only if they're equal
	return true;
}

/*
 * Converts HyperInt to bool (0 is false, else true)
 * Should be explicit but this version of VS does not allow explicit for bool operator
 */
HyperInt::operator bool() const{
	if(LENGTH == 0)//If HyperInt was initalized with empty string
		return false;
	bool b = ((*this).LENGTH == 1) && ((*this).VALUE[0] == 0); //If length is 1 (only one digit) and this digit is 0-> False, else True
    return !b;
}
