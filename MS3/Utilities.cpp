// Name:Patel Aditya Dharmesh
// Seneca Student ID: 143595205
// Seneca email: adpatel31@myseneca.ca
// Date of completion: 4/10/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Utilities.h"

namespace sdds {

	char Utilities::m_delimiter = ' ';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		size_t indexDelimiter = (str.find(getDelimiter(), next_pos));
		std::string extracted = str.substr(next_pos, indexDelimiter - next_pos);

		if (indexDelimiter == next_pos) {
			more = false;
			throw "No token between delimiters!";
		}

		next_pos = indexDelimiter + 1;
		setFieldWidth(std::max(m_widthField, extracted.size()));
		more = indexDelimiter != std::string::npos;

		return extracted;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}
