/*
 * Given an image represented by an NxN matrix, with each pixel being 4 bytes,
 * rotate the image by 90 degrees. In-place.
 */

#include <cstdlib>
#include <cassert>
#include <cstring>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <iterator>

/**
 * Rotate by 90 degrees => each row should become a column.
 *
 * Assume input matrix format is contiguous block,
 * laid out row-by-row.
 *
 * A clockwise rotation has the first row ending as the last column,
 * but otherwise in the same order.
 * Similarly, second row is second-last col, etc.
 *
 * So M(i,j) -> M(j, N-1-i)
 *  where i is row number, j is column number, both in range [0,N).
 */
uint32_t* rotate90(uint32_t* buffer, size_t N)
{
    uint32_t* copy_buffer = (uint32_t*) malloc(sizeof(uint32_t) * N * N);

    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            copy_buffer[j * N + (N-1-i)] = buffer[i * N + j];
        }
    }

    return copy_buffer;
}


void test_copying()
{
    uint32_t inbuf[] = { 1, 2, 3,
                         4, 5, 6,
                         7, 8, 9 };

    uint32_t expected_output[] = { 7, 4, 1,
                                   8, 5, 2,
                                   9, 6, 3 };

    uint32_t *output = rotate90(inbuf, 3);

    assert( memcmp(output, expected_output, 9 * sizeof(uint32_t)) == 0 );
}


// Doing it inplace from here on

class ImageBuffer
{
    private:
        uint32_t* const _underlying;
        size_t const    _N;

    public:
        ImageBuffer(uint32_t* buffer, size_t N)
            : _underlying(buffer)
            , _N(N)
        {}

        uint32_t& operator() (size_t row, size_t col) {
            return _underlying[row * _N + col];
        }

        uint32_t  operator() (size_t row, size_t col) const {
            return _underlying[row * _N + col];
        }

        void rotate90_inplace();

        uint32_t* buffer() { return _underlying; }

        void rotate_pixelgroup_inplace(size_t i, size_t j);
};


inline void
ImageBuffer::rotate_pixelgroup_inplace(size_t i, size_t j)
{
    size_t N = _N;

    std::swap( (*this)(i,j),             (*this)(N-1-j, i) );
    std::swap( (*this)(N-1-j, i),        (*this)(N-1-i, N-1-j) );
    std::swap( (*this)(N-1-i, N-1-j),    (*this)(j, N-1-i) );
}

/**
 * To do it in-place with constant auxiliary space usage,
 * consider that the rotation can be broken down into disjoint
 * 4-pixel sets, which rotate as a length-4 list.
 *
 *   M(i,j) -> M(j, N-1-i)
 *          -> M(N-1-i, N-1-j)
 *          -> M(N-1-j, i)
 *          -> back to M(i,j).
 *
 *  We ensure the whole square is rotated by choosing these 4-groups
 *  to cover border layers from the outside in.
 *
 *  We need (i,j) in range
 *      i <- [0, N/2),
 *      j <- [i, N-i)
 */
inline void
ImageBuffer::rotate90_inplace()
{
    for (size_t i = 0; i < _N/2; ++i) {
        for (size_t j = i; j < _N -1 - i; ++j) {
            this->rotate_pixelgroup_inplace(i, j);
        }
    }
}


uint32_t*
rotate90_inplace(uint32_t* buffer, size_t N)
{
    ImageBuffer buf(buffer, N);
    buf.rotate90_inplace();
    //buf.rotate_pixelgroup_inplace(0,0);
    //buf.rotate_pixelgroup_inplace(0,1);
    return buf.buffer();
}


void test_inplace()
{
    using namespace std;

    uint32_t inbuf[] = { 1, 2, 3,
                         4, 5, 6,
                         7, 8, 9 };

    uint32_t expected_output[] = { 7, 4, 1,
                                   8, 5, 2,
                                   9, 6, 3 };

    uint32_t *output = rotate90_inplace(inbuf, 3);

    std::copy(output,
            output + 3,
            std::ostream_iterator<int>(std::cout, ", ")
            );
    cout << endl;
    std::copy(output + 3,
            output + 6,
            std::ostream_iterator<int>(std::cout, ", ")
            );
    cout << endl;
    std::copy(output + 6,
            output + 9,
            std::ostream_iterator<int>(std::cout, ", ")
            );
    cout << endl;

    assert( memcmp(output, expected_output, 9 * sizeof(uint32_t)) == 0 );
}


int main()
{
    test_copying();
    test_inplace();
}
