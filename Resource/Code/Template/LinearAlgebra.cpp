#include <cstddef>

namespace LinearAlgebra
{
    template <size_t n>
    class Determinant
    {
        double a[n][n];

    public:
        double *operator[](size_t x) { return a[x]; }
        const double *operator[](size_t x) const { return a[x]; }
        explicit operator double() const
        {
            ;
        }
    };

    template <size_t n, size_t m>
    class Matrix
    {
        double a[n][m];

    public:
        double *operator[](size_t x) { return a[x]; }
        const double *operator[](size_t x) const { return a[x]; }

        Matrix operator+(Matrix b) const
        {
            Matrix c;
            for (size_t i = 0; i < n; ++i)
                for (size_t j = 0; j < m; ++j)
                    c[i][j] = a[i][j] + b[i][j];
            return c;
        }
        Matrix operator-(Matrix b) const
        {
            Matrix c;
            for (size_t i = 0; i < n; ++i)
                for (size_t j = 0; j < m; ++j)
                    c[i][j] = a[i][j] - b[i][j];
            return c;
        }
    };
}