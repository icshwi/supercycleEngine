#ifndef CSV_HPP
#define CSV_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <map>


namespace io
{

/*
 * A class to read data from a csv file.
 */
class CSVReader
{
private:
    std::string filelink;
    std::string delimeter=",";
    std::ifstream ifs;
    std::vector<std::string> key_row;
    std::uint64_t row_id;
    std::vector<std::vector<std::string> > getContent();
    std::vector<std::string> getRow();
public:
    CSVReader(std::string);
    CSVReader(){;};
    // CSVReader(){};
    ~CSVReader();
    void init(std::string);
    void close();
    std::vector<std::string> getKeys(){return key_row;};
    std::string getFileLink(){return filelink;};
    std::uint64_t getRowId(){return row_id;};
    std::map<std::string,std::string> getRowMap();
};

/*
void csv_test(std::string file_path="examples/example.csv");
void csv_test1(std::string file_path="examples/example.csv");
void csv_test2(std::string file_path="../reftabs/supercycles/example01.csv");
*/
//void csv_test(std::string file_path="../reftabs/supercycles/example01.csv");


} //namespace

#endif // SSCSV_HPP
