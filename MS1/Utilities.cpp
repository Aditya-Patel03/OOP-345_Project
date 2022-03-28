// Name:Patel Aditya Dharmesh
// Seneca Student ID: 143595205
// Seneca email: adpatel31@myseneca.ca
// Date of completion: 3/27/2022
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.#ifndef SDDS_UTILITIES_H
#include <iostream>
#include <string>

#include "Utilities.h"

using namespace std;

namespace sdds
{
    char Utilities::m_delimiter = ' ';

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {
        string result = "";
        size_t init_pos = next_pos;
        next_pos = str.find(m_delimiter, init_pos);
        if (init_pos == next_pos)
        {
            more = false;
            throw "   ERROR: No token.\n";
        }
        else if (next_pos == string::npos)
        {
            result = str.substr(init_pos);
            m_widthField = max(result.length(), m_widthField);
            more = false;
        }
        else
        {
            result = str.substr(init_pos, next_pos - init_pos);
            m_widthField = max(result.length(), m_widthField);
            more = true;
        }
        next_pos++;
        return result;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}