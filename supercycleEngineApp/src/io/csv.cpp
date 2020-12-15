/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#include <fstream>
#include <sstream>

#include "cmnbase.hpp"
#include "csv.hpp"
#include "dlog.hpp"
#include "dperf.hpp"

namespace io
{

// size_t CSVStrData::_getNumOfLines(std::ifstream& ifs)
// {
//   auto _lnum_ = std::count(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), '\n');
//   ifs.clear();
//   ifs.seekg(0);

//   return _lnum_;
// }

int CSVStrData::init(std::string file)
{
  //guard
  if (cmn::file::exists(file) == false)
    return 1;
  if (file == _file)
    return 1;

  DPERFLOG(dperf::INFO)
  DLOG(dlog::INFO, << " _file " << _file << " file " << file)
  _file = file;

  std::ifstream ifs_;
  ifs_.open(file, std::ifstream::in);
  //size_t _lnum_ = _getNumOfLines(ifs);

  _header.clear();
  (void)std::getline(ifs_, _header);

  _rows.clear();
  //_rows.reserve(_lnum_);
  for (std::string row_; std::getline(ifs_, row_); /**/)
    _rows.push_back(row_);

  ifs_.close();

  return 0;
}

int CSVStrMap::init(std::string file)
{
  DPERFLOG(dperf::INFO)

  if (CSVStrData::init(file) > 0)
    return 1;

  _keys.clear();
  _keys = _vect(_header);

  //_rows.clear();
  //_rows.reserve(_rows.size());
  //for (auto const& it : _rows)
  //  _rows.emplace_back(_vect(it));

  _row_id = 0;
  _cycle_id = 0;

  return 0;
}

std::map<std::string, std::string> CSVStrMap::_readRowMap(const size_t rowid) const
{
  if (_rows.empty() == true)
  {
    DLOG(dlog::ERROR, << " (_rows.empty() == true) rowid " << rowid)
    return {};
  }

  std::vector<std::string> row_ = _vect(_rows[rowid]);

  if (row_.size() != _keys.size())
  {
    DLOG(dlog::ERROR, << " (row_.size() != _keys.size()) rowid " << rowid << " row_.size() " << row_.size() << " _keys.size() " << _keys.size())
    return {};
  }

  std::map<std::string, std::string> rowmap_ = {};

  for (size_t i = 0; i < _keys.size(); i++)
    rowmap_[_keys[i]] = row_[i];

  return rowmap_;
}

void CSVStrMap::_iterator() const
{
  if (_row_id < _rows.size() - 1)
    _row_id++;
  else
  {
    _row_id = 0;
    _cycle_id++;
  }
}

std::map<std::string, std::string> CSVStrMap::getRowMap() const
{
  const size_t row_id_ = _row_id;

  _iterator();

  return _readRowMap(row_id_);
}

std::string CSVStrData::getFileName() const
{
  return _file.substr(_file.find_last_of("/") + 1);
}

size_t CSVStrMap::_clean_and_count(std::string& str) const
{
  //DPERFLOG(dperf::DEBUG3)
  if (str.empty() == true)
    return 0;

  size_t i = 0;
  size_t csv_num_ = 0;
  char str_[str.size() + 1];

  for (char const& c : str)
  {
    switch (c)
    {
    case '\r':
    case '\n': //not necessary as it cannot happen
    case '\"':
    case '\'':
    case ' ':
      break;
    case ',':
      csv_num_++;
    default:
      str_[i] = c;
      i++;
    }
  }
  str_[i] = '\0';
  //assing the filtered string
  str = str_;
  //Compensate the last value
  csv_num_++;
  //return the amount of words
  return csv_num_;
}

std::vector<std::string> CSVStrMap::_vect(const std::string& line) const
{
  //DPERFLOG(dperf::INFO)
  if (line.empty() == true)
    return {};

  std::string line_ = line;

  std::vector<std::string> outv_;
  std::string tmp_;

  size_t wordnum_ = _clean_and_count(line_);

  std::stringstream ss_(line_);

  outv_.reserve(wordnum_);
  while (std::getline(ss_, tmp_, ','))
    outv_.emplace_back(tmp_);

  return outv_;
}

} // namespace io
