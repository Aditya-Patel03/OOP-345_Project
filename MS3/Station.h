// Name:Patel Aditya Dharmesh
// Seneca Student ID: 143595205
// Seneca email: adpatel31@myseneca.ca
// Date of completion: 4/10/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <iomanip>
#include <string.h>
using namespace std;

namespace sdds {


	class Station {
		int m_id;
		string m_name;
		string m_desc;
		unsigned int m_serial;
		unsigned int m_current;
		static size_t m_widthField;
		static int id_generator;
	public:
		Station(const string& str);
		const string& getItemName() const;
		unsigned int getNextSerialNumber();
		unsigned int getQuantity() const;
		void updateQuantity();
		void display(std::ostream& os, bool full) const;
	};
}

#endif
