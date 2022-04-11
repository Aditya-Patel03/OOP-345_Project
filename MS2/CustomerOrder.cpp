// Name:Patel Aditya Dharmesh
// Seneca Student ID: 143595205
// Seneca email: adpatel31@myseneca.ca
// Date of completion: 4/10/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.#ifndef SDDS_UTILITIES_H
#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"

using namespace std;

namespace sdds {
	size_t CustomerOrder::m_widthField = 0;


	CustomerOrder::CustomerOrder() {
		m_name = "";
		m_product = "";
		m_cntItem = 0;
		m_lstItem = nullptr;
	}

	CustomerOrder::CustomerOrder(const std::string& str):CustomerOrder() {
		Utilities utility;
		size_t next_pos = 0;
		bool more = true;

		const char* Whitespaces = " \t\n\r\f\v";
		try {
			m_name = utility.extractToken(str, next_pos, more);
			m_name.erase(0, m_name.find_first_not_of(Whitespaces));
			m_name.erase(m_name.find_last_not_of(Whitespaces) + 1);

			m_product = utility.extractToken(str, next_pos, more);
			m_product.erase(0, m_product.find_first_not_of(Whitespaces));
			m_product.erase(m_product.find_last_not_of(Whitespaces) + 1);
			m_cntItem = 0;

			size_t start_pos = next_pos;
			while (more) {
				utility.extractToken(str, next_pos, more);
				m_cntItem++;
			}
			m_lstItem = new Item * [m_cntItem];
			more = true;

			for (size_t i = 0; i < m_cntItem; i++) {
				m_lstItem[i] = new Item(utility.extractToken(str, start_pos, more));
				m_lstItem[i]->m_itemName.erase(0, m_lstItem[i]->m_itemName.find_first_not_of(Whitespaces));
				m_lstItem[i]->m_itemName.erase(m_lstItem[i]->m_itemName.find_last_not_of(Whitespaces) + 1);
			}
			if (utility.getFieldWidth() > m_widthField)
				m_widthField = utility.getFieldWidth();
		}
		catch (std::string& msg) {
			cout << msg;
		}
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& moveFrom) noexcept:CustomerOrder() {
		*this = std::move(moveFrom);
	}

	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& rightOperand) noexcept {
		if (this != &rightOperand) {
			if (m_lstItem) {
				for (size_t i = 0; i < m_cntItem; i++) {
					delete m_lstItem[i];
				}
				delete[] m_lstItem;
			}
				m_lstItem = rightOperand.m_lstItem;
				m_name = rightOperand.m_name;
				m_product = rightOperand.m_product;
				m_cntItem = rightOperand.m_cntItem;
				rightOperand.m_lstItem = nullptr;
				rightOperand.m_name = "";
				rightOperand.m_product = "";
				rightOperand.m_cntItem = 0;

		
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder() {
		if (m_lstItem) {
			for (size_t i = 0; i < m_cntItem; i++) {
				delete m_lstItem[i];
			}
		}
		delete[] m_lstItem;
		m_lstItem = nullptr;
	}

	bool CustomerOrder::isOrderFilled() const {
		return std::all_of(m_lstItem, m_lstItem + m_cntItem, [](const Item* item) {
			return item->m_isFilled;
			});

	}

	bool CustomerOrder::isItemFilled(const std::string& itemName) const {
		return std::all_of(m_lstItem, (m_lstItem + m_cntItem), [&itemName](Item* item) {
			if (item->m_itemName == itemName)
				return item->m_isFilled;
			return true;
			});
	}

	void CustomerOrder::fillItem(Station& station, std::ostream& os) {

		std::string temp{}, temp2{};

		for (size_t i = 0; i < m_cntItem; i++) {

			if (m_lstItem[i]->m_itemName == station.getItemName() && m_lstItem[i]->m_isFilled == false) {
				if (station.getQuantity() > 0) {
					station.updateQuantity();
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstItem[i]->m_isFilled = true;

					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					break;
				}
				else
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;

			}
		}
	}

	void CustomerOrder::display(std::ostream& os) const 
	{
			os << m_name << " - " << m_product << std::endl;
	for (unsigned int z = 0; z < m_cntItem; z++)
	{ 
		os << "[" << setw(WIDTH_CODE) << setfill('0') << right << m_lstItem[z]->m_serialNumber << "] "
				<< setfill(' ') << setw(m_widthField) << left << m_lstItem[z]->m_itemName << " - ";
		if (m_lstItem[z]->m_isFilled){
		os << "FILLED" << std::endl;
		}
		else
		{
			os << "TO BE FILLED" << std::endl;
		}
		}

	}

}