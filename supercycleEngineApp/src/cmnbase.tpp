
#ifndef CMNBASE_TPP_
#define CMNBASE_TPP_

template <class T>
std::vector<T> map2vec(std::map<T, T> argm, int col)
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

template <class T, class U>
std::vector<std::string> map2vecstr(std::map<T, U> argm, int col)
{
    std::vector<std::string> tmpvs;

    for (auto const &it : argm)
    {
        if (col == 0)
            tmpvs.push_back(cmn::str(it.first));
        else if (col == 1)
            tmpvs.push_back(cmn::str(it.second));
        else
            return std::vector<std::string>();
    }

    return tmpvs;
}

template <class T>
std::string vec2str(std::vector<T> argv)
{
    std::string tmp_str;

    for (auto const &it : argv)
    {
        tmp_str += cmn::str(it);
        tmp_str += " ";
    }

    return tmp_str;
}

template <class T>
std::string mapcol2str(std::map<T, T> argm, int col)
{
    return vec2str<T>(map2vec<T>(argm, col));
}

template <class T, class U>
std::string mapcol2str(std::map<T, U> argm, int col)
{
    if (col == 0)
        return vec2str<std::string>(map2vecstr<T, U>(argm, 0));
    else if (col == 1)
        return vec2str<std::string>(map2vecstr<T, U>(argm, 1));

    return {};
}

template <class T, class U>
std::string map2str(std::map<T, U> argm)
{
    std::string tmps = "";

    for (auto const &it : argm)
    {
        tmps += cmn::str(it.first);
        tmps += " ";
        tmps += cmn::str(it.second);
        tmps += " ";
    }

    return tmps;
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

template <class T>
int vec2p(void *destarr, std::vector<T> srcv)
{
    T *dest = (T *)destarr;

    int i = 0;
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

#endif // CMNBASE_TPP
