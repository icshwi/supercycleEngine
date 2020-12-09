/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#include <fstream>

#include "csv.hpp"
#include "cmnbase.hpp"
#include "dlog.hpp"
#include "dperf.hpp"

namespace io
{

  size_t CSVStrData::_getNumOfLines(std::ifstream &ifs)
  {
    auto _lnum_ = std::count(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>(), '\n');
    ifs.clear();
    ifs.seekg(0);

    return _lnum_;
  }

  int CSVStrData::init(std::string file)
  {
    DPERFTIMERSCOPE(dperf::INFO);
    DLOG(dlog::INFO) << " _file " << _file << " file " << file;

    std::ifstream ifs_;
    if (file == _file)
      return 1;
    else
      _file = file;

    ifs_.open(file, std::ifstream::in);
    //size_t _lnum_ = _getNumOfLines(ifs);

    _header.clear();
    (void)std::getline(ifs_, _header);

    _rows.clear();
    //_rows.reserve(_lnum_);
    for (std::string row; std::getline(ifs_, row); /**/)
      _rows.push_back(row);

    ifs_.close();

    return 0;
  }

  int CSVStrMap::init(std::string file)
  {
    DPERFTIMERSCOPE(dperf::INFO);

    if (_csvstr.init(file) > 0)
      return 1;

    _header.clear();
    _header = cmn::str::csv2vect(_csvstr._header);

    _rows.clear();
    _rows.reserve(_csvstr._rows.size());
    for (auto const &it : _csvstr._rows)
      _rows.emplace_back(cmn::str::csv2vect(it));

    _row_id = 0;
    _cycle_id = 0;

    return 0;
  }

  std::map<std::string, std::string> CSVStrMap::_readRowMap(const size_t rowid)
  {
    const std::vector<std::string> &row_ = _rows[rowid];
    std::map<std::string, std::string> rowmap_;

    for (size_t i = 0; i < _header.size(); i++)
      //if (row_[i].empty() == false)
      rowmap_[_header[i]] = row_[i];

    return rowmap_;
  }

  void CSVStrMap::_iterator()
  {
    if (_row_id < _rows.size() - 1)
      _row_id++;
    else
    {
      _row_id = 0;
      _cycle_id++;
    }
  }

  std::map<std::string, std::string> CSVStrMap::getRowMap()
  {
    const size_t _row_id_ = _row_id;

    _iterator();

    return _readRowMap(_row_id_);
  }

  std::map<std::string, std::string> CSVStrMap::checkRowMapNext()
  {
    return _readRowMap(_row_id);
  }

} // namespace io
