/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#include "csv.hpp"
#include "dlog.hpp"
#include "cmnbase.hpp"

#include <boost/algorithm/string.hpp>

namespace io
{

    //CSVReader::CSVReader(std::string argfl)
    //{
    //    init(argfl);
    //    dlog::Print(dlog::DEBUG2) << "CSVReader::CSVReader"
    //                        << " filelink " << filelink << " delimeter " << delimeter;
    //}

    CSVReader::~CSVReader()
    {
        dlog::Print(dlog::DEBUG2) << "CSVReader::~CSVReader";
        close();
    }

    void CSVReader::close()
    {
        dlog::Print(dlog::DEBUG2) << "CSVReader::close()";
        if (ifs.is_open())
            ifs.close();
    }

    int CSVReader::init(std::string argfl)
    {
        dlog::Print(dlog::DEBUG2) << "CSVReader::init";

        close();

        if (cmn::isFile(argfl) == false)
            return 1;

        ifs.open(argfl, std::ifstream::in);

        filelink = argfl;
        // Read key row
        key_row = getRow();
        // Reset the row counter
        row_id = 0;

        return 0;
    }

    /*
 * Parses through csv file line by line and returns the data
 * in vector of vector of strings.
 */
    std::vector<std::vector<std::string>>
    CSVReader::getContent()
    {
        //std::ifstream file(fileName);
        std::vector<std::vector<std::string>> dataList;
        std::string line = "";
        // Iterate through each line and split the content using delimeter
        while (getline(ifs, line))
        {
            std::vector<std::string> vec;
            boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
            dataList.push_back(vec);
        }
        // Close the File
        //ifs.close();
        return dataList;
    }

    std::vector<std::string>
    CSVReader::getRow()
    {
        dlog::Print(dlog::DEBUG3) << "CSVReader::getRow()";

        std::string line = "";
        std::vector<std::string> vec;

        row_id++;
        if (!getline(ifs, line))
        {
            dlog::Print(dlog::DEBUG) << "CSVReader::getRow() csv file ended at row_id " << row_id;
            return {}; //vec.empty() check
        }
        boost::algorithm::split(vec, line, boost::is_any_of(delimeter));

        return vec;
    }

    std::map<std::string, std::string>
    CSVReader::getRowMap()
    {
        dlog::Print(dlog::DEBUG3) << "CSVReader::getRowMap()";

        std::map<std::string, std::string> mp;
        std::vector<std::string> row = getRow();

        if (row.empty())
            return {};

        if (row.size() != key_row.size())
        {
            dlog::Print(dlog::ERROR) << "CSVReader::getRowMap() row.size()!=key_row.size() row_id " << row_id;
            return {};
        }

        for (size_t i = 0; i < key_row.size(); ++i)
        {
            mp.insert({key_row[i], row[i]});
        }

        return mp;
    }

} // namespace io
