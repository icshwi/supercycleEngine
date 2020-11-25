/**
 * @SPDX-License-Identifier LGPL-2.1-only
 * @author Jerzy Jamroz (jerzy.jamroz@ess.eu)
 * @date 2020-03-20
 */

#ifndef CMNBASE_TPP_
#define CMNBASE_TPP_

namespace cmn
{

  template <typename T>
  std::vector<T> map1d2vec(std::map<T, T> argm, int col)
  {
    std::vector<T> v_tmp;

    for (auto const &it : argm)
    {
      if (col == 0)
        v_tmp.push_back(it.first);
      else if (col == 1)
        v_tmp.push_back(it.second);
      else
        return std::vector<T>();
    }

    return v_tmp;
  }

  template <typename T, typename U>
  std::vector<std::string> map2vecstr(std::map<T, U> argm, int col)
  {
    std::vector<std::string> tmpvs;

    for (auto const &it : argm)
    {
      if (col == 0)
        tmpvs.push_back(cmn::str::convert(it.first));
      else if (col == 1)
        tmpvs.push_back(cmn::str::convert(it.second));
      else
        return std::vector<std::string>();
    }

    return tmpvs;
  }

  template <typename T>
  std::string vec2str(std::vector<T> argv)
  {
    std::string tmp_str;

    for (auto const &it : argv)
    {
      tmp_str += cmn::str::convert(it);
      tmp_str += " ";
    }

    return tmp_str;
  }

  template <typename T>
  std::string map1d2str(std::map<T, T> argm, int col)
  {
    return vec2str<T>(map1d2vec<T>(argm, col));
  }

  template <typename T, typename U>
  std::string mapcol2str(std::map<T, U> argm, int col)
  {
    if (col == 0)
      return vec2str<std::string>(map2vecstr<T, U>(argm, 0));
    else if (col == 1)
      return vec2str<std::string>(map2vecstr<T, U>(argm, 1));

    return {};
  }

  template <typename T, typename U>
  std::string map2str(std::map<T, U> argm)
  {
    std::string tmps = "";

    for (auto const &it : argm)
    {
      tmps += cmn::str::convert(it.first);
      tmps += " ";
      tmps += cmn::str::convert(it.second);
      tmps += " ";
    }

    return tmps;
  }

  template <typename T>
  std::vector<T> map2d2vec(std::map<T, T> argm)
  {
    std::vector<T> tmpsv = {};

    for (auto const &it : argm)
    {
      tmpsv.push_back(it.first);
      tmpsv.push_back(it.second);
    }

    return tmpsv;
  }

  template <typename A, typename B>
  std::pair<B, A> flip_pair(const std::pair<A, B> &p)
  {
    return std::pair<B, A>(p.second, p.first);
  }

  template <typename A, typename B>
  std::map<B, A> flip_map(const std::map<A, B> &argm)
  {
    std::map<B, A> dst;
    std::transform(argm.begin(), argm.end(), std::inserter(dst, dst.begin()), flip_pair<A, B>);
    return dst;
  }

  template <typename T>
  size_t vec2p(void *destarr, std::vector<T> srcv)
  {
    T *dest = (T *)destarr;

    size_t i = 0;
    if (srcv.empty() == false)
    {
      for (auto const &it : srcv)
      {
        dest[i] = it;
        i++;
      }
    }
    return i;
  }

} // namespace cmn

//Global
template <typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> argv)
{
  stream << cmn::vec2str<T>(argv);
  return stream;
}

template <typename T, typename U>
std::ostream &operator<<(std::ostream &stream, const std::map<T, U> argm)
{
  stream << cmn::map2str<T, U>(argm);
  return stream;
}

#endif // CMNBASE_TPP
