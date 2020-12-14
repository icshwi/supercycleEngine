/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#pragma once

#include <map>
#include <string>
#include <vector>

namespace io
{

class CSVStrData
{
public:
  CSVStrData(){};
  std::string getFile() const { return _file; };

private:
  friend class CSVStrMap;
  int init(std::string file);
  std::vector<std::string> _rows;
  std::string _header;
  std::string _file;
  size_t _getNumOfLines(std::ifstream& ifs);
};

class CSVStrMap
{
public:
  CSVStrMap(){};
  int init(std::string file);
  std::map<std::string, std::string> getRowMap() const;
  std::map<std::string, std::string> checkRowMapNext() const;
  size_t getRowId() const { return _row_id; };
  size_t getCycleId() const { return _cycle_id; };
  std::string getFilePath() const { return _csvstr._file; };
  std::string getFileName() const;

private:
  std::map<std::string, std::string> _readRowMap(const size_t l_rowid) const;
  CSVStrData _csvstr;
  mutable size_t _row_id = 0, _cycle_id = 0;
  void _iterator() const;
  size_t _clean_and_count(std::string& str);
  std::vector<std::string> _vect(std::string line);
  std::vector<std::vector<std::string>> _rows;
  std::vector<std::string> _header;
};

} // namespace io
