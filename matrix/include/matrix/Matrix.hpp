#pragma once

#include <map>

namespace matrix 
{

template <typename T, T dflt>
class Matrix
{
    friend class MatrixProxy;
    friend class MatrixIterator;

    public:

    class MatrixProxy
    {
        Matrix& _m;
        std::size_t _x = 0;
        std::size_t _y = 0;

        public:

        MatrixProxy(Matrix& m, std::size_t x)
            :_m(m)
            ,_x(x)
        {}

        MatrixProxy operator[](std::size_t y)
        {
            _y = y;
            return *this;
        }

        void operator=(const T& val)
        {
            _m.load(_x, _y) = val;
            _m.save(_x, _y);
        }

        bool operator==(const T& val)
        {
            return _m.load(_x, _y) == val;
        }

        operator T()
        {
            return _m.load(_x, _y);
        }
    };

    MatrixProxy operator[](const std::size_t x)
    {
        return MatrixProxy(*this, x);
    }

    private:

    using y_strg_type = std::map<std::size_t, T>;
    using xy_strg_type = std::map<std::size_t, y_strg_type>;

    xy_strg_type _elems;

    T _acum = dflt;
    std::size_t _size = 0;
    
    bool contains (const std::size_t x, const std::size_t y) const
    {
        if (_elems.count(x) && _elems.at(x).count(y))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    T& load(const std::size_t x, const std::size_t y)
    {
        if (contains(x, y))
        {
            return _elems[x][y];
        }
        else
        {
            return _acum;
        }
    }

    void save(const std::size_t x, const std::size_t y)
    {
        if (!contains(x, y))
        {
            _elems[x][y] = _acum;
            _acum = dflt;
            _size++;
        }
    }

    public:


    std::size_t size() const
    {
        return _size;
    }


    class MatrixIterator
    {
        using xy_it_type = typename xy_strg_type::iterator;
        using y_it_type = typename y_strg_type::iterator;

        xy_it_type _xy_it;
        xy_it_type _xy_it_end;

        y_it_type _y_it;
        y_it_type _y_it_end;

        std::size_t _size = 0;

        public:
        MatrixIterator(xy_it_type xy_it, xy_it_type xy_it_end, y_it_type y_it, y_it_type y_it_end)
            :_xy_it(xy_it)
            ,_xy_it_end(xy_it_end)
            ,_y_it(y_it)
            ,_y_it_end(y_it_end)
        {}

        MatrixIterator& operator++()
        {
            std::advance(_y_it, 1);
            if (_y_it == _y_it_end)
            {
                if (std::next(_xy_it) != _xy_it_end)
                {
                    std::advance(_xy_it, 1);
                    _y_it = _xy_it->second.begin();
                    _y_it_end = _xy_it->second.end();
                }
            }
            return *this;
        }

        bool operator != (const MatrixIterator& it)
        {
            if ((it._xy_it != _xy_it) || (it._y_it != _y_it))
            {
                return true;
            }
            return false;
        }

        T& operator* () const
        {
            return _y_it->second;
        }
    };

    MatrixIterator begin()
    {
        return MatrixIterator(_elems.begin(), _elems.end(),
            _elems.begin()->second.begin(), _elems.begin()->second.end());
    }

    MatrixIterator end()
    {
        auto x_pre_end = std::prev(_elems.end());
        return MatrixIterator(x_pre_end, _elems.end(),
            x_pre_end->second.end(), x_pre_end->second.end());
    }

};


}
