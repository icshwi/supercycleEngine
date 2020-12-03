/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#include "csvvec.hpp"

#include <fstream>

namespace io
{

  int CSV2Vec::init(std::string file)
  {
    std::ifstream ifs;
    ifs.open(file, std::ifstream::in);

    (void)std::getline(ifs, m_header);

    for (std::string row; std::getline(ifs, row); /**/)
      m_rows.push_back(row);

    ifs.close();

    return 0;
  }

  std::string CSV2Vec::getRow()
  {
    size_t rowid = m_rows_end;

    if (m_rows.size() - 1 > m_rows_end)
      m_rows_end++;
    else
      m_rows_end = 0;

    return m_rows[rowid];
  }

  std::string CSV2Vec::checkRowNext()
  {
    return m_rows[m_rows_end];
  }

  CSV2Vec &CSV2Vec::instance()
  {
    static CSV2Vec s_csv2vec;
    return s_csv2vec;
  }

} // namespace io
