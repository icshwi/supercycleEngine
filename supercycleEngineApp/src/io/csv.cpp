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
                            << " m_file " << m_file << " file " << file;

    std::ifstream ifs;
    if (file == m_file)
      return 1;
    else
      m_file = file;

    ifs.open(file, std::ifstream::in);

    m_header.clear();
    (void)std::getline(ifs, m_header);

    m_rows.clear();
    for (std::string row; std::getline(ifs, row); /**/)
      m_rows.push_back(row);

    ifs.close();

    return 0;
  }

  int CSVStrMap::init(std::string file)
  {
    if (m_csvstr.init(file) > 0)
      return 1;

    m_header.clear();
    m_header = cmn::str::vect(m_csvstr.m_header);

    m_rows.clear();
    for (auto const &it : m_csvstr.m_rows)
      m_rows.push_back(cmn::str::vect(it));

    return 0;
  }

  std::map<std::string, std::string> CSVStrMap::readRowMap(const size_t l_rowid)
  {
    const std::vector<std::string> &l_row = m_rows[l_rowid];
    std::map<std::string, std::string> l_m;

    for (size_t i = 0; i < m_header.size(); i++)
      if (l_row[i].empty() == false)
        l_m[m_header[i]] = l_row[i];

    return l_m;
  }

  std::map<std::string, std::string> CSVStrMap::getRowMap()
  {
    const size_t l_rowid = m_row_id;

    if (m_row_id < m_rows.size() - 1)
      m_row_id++;
    else
      m_row_id = 0;

    return readRowMap(l_rowid);
  }

  std::map<std::string, std::string> CSVStrMap::checkRowMapNext()
  {
    return readRowMap(m_row_id);
  }

} // namespace io
