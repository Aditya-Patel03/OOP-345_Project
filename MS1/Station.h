// Name:Patel Aditya Dharmesh
// Seneca Student ID: 143595205
// Seneca email: adpatel31@myseneca.ca
// Date of completion: 3/27/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.#ifndef SDDS_UTILITIES_H

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <iostream>

using namespace std;

namespace sdds
{
    class Station
    {
        int s_id{ 0 };
        string s_itemname{ "" };
        string s_description{ "" };
        size_t s_serialno{ 0u };
        size_t s_stkitems{ 0u };

        static size_t m_widthField;
        static size_t id_generator;

    public:
        Station(const string& s);
        const string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(ostream& os, bool full) const;
    };
}
#endif // !SDDS_STATION_H