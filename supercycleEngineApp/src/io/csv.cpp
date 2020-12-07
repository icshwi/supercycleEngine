/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#include "csv.hpp"
#include "cmnbase.hpp"
#include "dlog.hpp"

#include <fstream>

namespace io
{

  int CSVStrData::init(std::string file)
  {
    dlog::Print(dlog::INFO) << "CSVStrData::init "
                            << " _file " << _file << " file " << file;

    std::ifstream ifs;
    if (file == _file)
      return 1;
    else
      _file = file;

    ifs.open(file, std::ifstream::in);

    _header.clear();
    (void)std::getline(ifs, _header);

    _rows.clear();
    for (std::string row; std::getline(ifs, row); /**/)
      _rows.push_back(row);

    ifs.close();

    return 0;
  }

  int CSVStrMap::init(std::string file)
  {
    if (_csvstr.init(file) > 0)
      return 1;

    _header.clear();
    _header = cmn::str::vect(_csvstr._header);

    _rows.clear();
    for (auto const &it : _csvstr._rows)
      _rows.push_back(cmn::str::vect(it));

    return 0;
  }

  std::map<std::string, std::string> CSVStrMap::readRowMap(const size_t rowid)
  {
    const std::vector<std::string> &_row_ = _rows[rowid];
    std::map<std::string, std::string> _m_;

    for (size_t i = 0; i < _header.size(); i++)
      if (_row_[i].empty() == false)
        _m_[_header[i]] = _row_[i];

    return _m_;
  }

  void CSVStrMap::_iterator()
  {
    if (_row_id < _rows.size() - 1)
      _row_id++;
    else
      _row_id = 0;
  }

  std::map<std::string, std::string> CSVStrMap::getRowMap()
  {
    const size_t _row_id_ = _row_id;

    _iterator();

    return readRowMap(_row_id_);
  }

  std::map<std::string, std::string> CSVStrMap::checkRowMapNext()
  {
    return readRowMap(_row_id);
  }

} // namespace io
