/*
 * If an element of a matrix is zero, set everything on that row/col to zero.
 */

#include <stdint.h>
#include <cstddef>
#include <set>

/** Hackily stealing this class from Ex6,
 * without bothering to set up a multi-file compilation process.
 *
 * Change it to make it actually own its buffer, as it should.
 */
class ImageBuffer
{
    private:
        uint32_t* const _underlying;
        size_t const    _N;

    public:
        ImageBuffer(size_t N)
            : _underlying(new uint32_t[N*N])
            , _N(N)
        {}

        virtual ~ImageBuffer()
        {
            delete _underlying;
        }

        uint32_t& operator() (size_t row, size_t col) {
            return _underlying[row * _N + col];
        }

        uint32_t  operator() (size_t row, size_t col) const {
            return _underlying[row * _N + col];
        }

        uint32_t* buffer() { return _underlying; }

        size_t    width() const { return _N; }
};


void propagate_zeroes(ImageBuffer& buf)
{
    using std::set;

    set<size_t> zero_rows, zero_cols;

    size_t N = buf.width();
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            if ( buf(i,j) == 0 ) {
                zero_rows.insert(i);
                zero_cols.insert(j);
            }
        }
    }

    for (set<size_t>::iterator it = zero_rows.begin(),
                            end = zero_rows.end();
                it != end;
                ++it)
    {
        for (size_t k = 0; k < N; ++k) {
            buf(*it, k) = 0;
        }
    }

    for (set<size_t>::iterator it = zero_cols.begin(),
                            end = zero_cols.end();
                it != end;
                ++it)
    {
        for (size_t k = 0; k < N; ++k) {
            buf(k, *it) = 0;
        }
    }
}
