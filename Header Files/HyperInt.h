
#include <iostream>
#include <vector>

#ifndef HYPERINT_H
#define HYPERINT_H

class HyperInt {

	friend const bool operator== (const HyperInt lhi,const HyperInt rhi);
	friend const bool operator!= (const HyperInt lhi,const HyperInt rhi);
	friend const bool operator<  (const HyperInt lhi,const HyperInt rhi);
	friend const bool operator<= (const HyperInt lhi,const HyperInt rhi);
	friend const bool operator>  (const HyperInt lhi,const HyperInt rhi);
	friend const bool operator>= (const HyperInt lhi,const HyperInt rhi);

	friend std::ostream & operator<<(std::ostream & os, const HyperInt & hi);
	friend std::istream & operator>>(std::istream & os, HyperInt & hi);

	friend const HyperInt operator*(const HyperInt & lhi, const HyperInt & rhi);
	friend const HyperInt operator+(const HyperInt & lhi, const HyperInt & rhi);
	
	


	public:
		HyperInt(const long & hi=0);
		HyperInt(const std::string & s);
		HyperInt(const std::vector<short> & hi, std::vector<short>::size_type l = 0);
		~HyperInt();

		const HyperInt    operator^ (const HyperInt & pow) const;
		const HyperInt &  operator+=(const HyperInt & hi);
		const HyperInt &  operator*=(const HyperInt & hi);
			  HyperInt &  operator++();		
			  HyperInt    operator++(int);
						  operator bool() const;	

	private:
		std::vector<short> VALUE;
		std::vector<short>::size_type LENGTH;

};
	
#endif