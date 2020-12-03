/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#pragma once

#include <string>
#include <vector>
#include <map>

namespace io
{

  class CSVStrData
  {
  public:
    CSVStrData(){};

  private:
    friend class CSVStrMap;
    int init(std::string file);
    std::vector<std::string> m_rows;
    std::string m_header;
    std::string m_file;
  };

  class CSVStrMap
  {
  public:
    CSVStrMap(){};
    int init(std::string file);
    std::map<std::string, std::string> getRowMap();
    std::map<std::string, std::string> checkRowMapNext();
    size_t getRowId() { return m_row_id; };
    std::string getFile() { return m_csvstr.m_file; };

  private:
    CSVStrData m_csvstr;
    size_t m_row_id;
    std::vector<std::vector<std::string>> m_rows;
    std::vector<std::string> m_header;
  };

} // namespace io
