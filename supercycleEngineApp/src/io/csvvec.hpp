/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-12-03
 */

#pragma once

#include <string>
#include <vector>

namespace io
{

  class CSV2Vec
  {
  public:
    CSV2Vec(){};
    int init(std::string file);
    std::string getRow();
    std::string checkRowNext();
    static CSV2Vec &instance();

  private:
    size_t m_rows_end;
    std::vector<std::string> m_rows;
    std::string m_header;
  };

} // namespace io
