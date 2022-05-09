// Name:Patel Aditya Dharmesh
// Seneca Student ID: 143595205
// Seneca email: adpatel31@myseneca.ca
// Date of completion: 4/10/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Utilities.h"
#include "Station.h"
#include <string>

namespace sdds {

	size_t Station::m_widthField = 0;
	int Station::id_generator = 1;

	Station::Station(const std::string& str) {

		Utilities util;

		bool check = true;
		size_t n_pos = 0;
		m_id = id_generator;
		const char* Whitespaces = " \t\n\r\f\v";
		string tempVar;

		try {
			m_name = util.extractToken(str, n_pos, check);
			m_name.erase(0, m_name.find_first_not_of(Whitespaces));
			m_name.erase(m_name.find_last_not_of(Whitespaces) + 1);
			string tempS = util.extractToken(str, n_pos, check);
			tempS.erase(0, tempS.find_first_not_of(Whitespaces));
			tempS.erase(tempS.find_last_not_of(Whitespaces)+1);
			m_serial = stoi(tempS);

			string tempC = util.extractToken(str, n_pos, check);
			tempC.erase(0, tempC.find_first_not_of(Whitespaces));
			tempC.erase(tempC.find_last_not_of(Whitespaces) + 1);
			m_current = stoi(tempC);

			m_widthField = max(util.getFieldWidth(), m_widthField);

			m_desc = util.extractToken(str, n_pos, check);
			m_desc.erase(0, m_desc.find_first_not_of(Whitespaces));
			m_desc.erase(m_desc.find_last_not_of(Whitespaces) + 1);

		}
		catch (std::string& mstr) {
			cout << mstr;
		}

		id_generator++;
	}

	const std::string& Station::getItemName() const {
		return m_name;
	}

	unsigned int Station::getNextSerialNumber() {
		return m_serial++;
	}

	unsigned int Station::getQuantity() const {
		return m_current;
	}

	void Station::updateQuantity() {
		if (0 > --m_current)
			m_current = 0;
	}

	void Station::display(std::ostream& os, bool full) const {

		os << right << setw(3) << setfill('0') << m_id << " | ";
		os << left << setw(m_widthField) << setfill(' ') << m_name << right;
		os << " | " << setw(6) << setfill('0') << m_serial << " | " << left;

		if (full) {

			os << right << setw(4) << setfill(' ') << m_current << " | ";
			os << left << m_desc << endl;
		}
		if (!full)
			os << endl;
	}
}
