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
  std::string getFilePath() const { return _file; };
  std::string getFileName() const;
  virtual int init(std::string file);

protected:
  std::string _header = {};
  std::vector<std::string> _rows = {};

private:
  //friend class CSVStrMap;
  std::string _file = {};
  //size_t _getNumOfLines(std::ifstream& ifs);
};

class CSVStrMap : public CSVStrData
{
public:
  CSVStrMap(){};
  int init(std::string file) override;
  std::map<std::string, std::string> getRowMap() const;
  size_t getRowId() const { return _row_id; };
  size_t getCycleId() const { return _cycle_id; };

private:
  std::map<std::string, std::string> _readRowMap(const size_t rowid) const;
  mutable size_t _row_id = 0, _cycle_id = 0;
  void _iterator() const;
  size_t _clean_and_count(std::string&) const;
  std::vector<std::string> _vect(const std::string&) const;
  std::vector<std::string> _keys = {};
};

} // namespace io
