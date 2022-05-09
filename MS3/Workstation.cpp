// Name:Patel Aditya Dharmesh
// Seneca Student ID: 143595205
// Seneca email: adpatel31@myseneca.ca
// Date of completion: 4/10/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include "Workstation.h"

namespace sdds {
	std::deque<CustomerOrder>g_pending{};
	std::deque<CustomerOrder>g_completed{};
	std::deque<CustomerOrder>g_incomplete{};

	Workstation::Workstation(const std::string& str):Station(str) {
	}

	void Workstation::fill(std::ostream& os) {
		if (!m_orders.empty())
			m_orders.front().fillItem(*this, os);

	}

	bool Workstation::attemptToMoveOrder() {
		bool isMoved = false;
		if (!m_orders.empty()) {
			if (m_orders.front().isItemFilled(getItemName())) {
				if (!m_pNextStation) {
					if (m_orders.front().isOrderFilled())
						g_completed.push_back(std::move(m_orders.front()));
					else
						g_incomplete.push_back(std::move(m_orders.front()));
				}
				else {
					*m_pNextStation += std::move(m_orders.front());
				}
				m_orders.pop_front();
				isMoved = true;
			}
			else if (!getQuantity()) {
				if (!m_pNextStation)
					g_incomplete.push_back(std::move(m_orders.front()));
				else
					*m_pNextStation += std::move(m_orders.front());
				m_orders.pop_front();
				isMoved = true;
			}
		}
		return isMoved;
	}
	
	void Workstation::setNextStation(Workstation* station) {
		if (m_pNextStation != nullptr)
			delete m_pNextStation;

		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation() const {
		return m_pNextStation;
	}
	
	void Workstation::display(std::ostream& os) const {
		if (m_pNextStation) {
			os << getItemName() << " --> " << m_pNextStation->getItemName() << endl;
		}
		else {
			os << getItemName() << " --> End of Line" << endl;
		}
	}
	
	Workstation& Workstation::operator+=(CustomerOrder&& newOrder) {
		m_orders.push_back(std::move(newOrder));
		
		return *this;
	}

}