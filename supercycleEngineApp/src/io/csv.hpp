/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef CSV_HPP_
#define CSV_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>

#include <epicsTypes.h>

namespace io
{

/*
 * A class to read data from a csv file.
 */
class CSVReader
{
private:
    std::string filelink;
    std::string delimeter = ",";
    std::ifstream ifs;
    std::vector<std::string> key_row;
    epicsUInt64 row_id;
    std::vector<std::vector<std::string>> getContent();
    std::vector<std::string> getRow();

public:
    //CSVReader(std::string);
    CSVReader(){};
    // CSVReader(){};
    ~CSVReader();
    int init(std::string);
    void close();
    std::vector<std::string> getKeys() { return key_row; };
    std::string getFileLink() { return filelink; };
    epicsUInt64 getRowId() { return row_id; };
    std::map<std::string, std::string> getRowMap();
};

/*
void csv_test(std::string file_path="examples/example.csv");
void csv_test1(std::string file_path="examples/example.csv");
void csv_test2(std::string file_path="../reftabs/supercycles/example01.csv");
*/
//void csv_test(std::string file_path="../reftabs/supercycles/example01.csv");

} // namespace io

#endif // SSCSV_HPP
