#include <cstdio>
#include <cctype>
#define fre(s) freopen(s ".in", "r", stdin), freopen(s ".out", "w", stdout)

namespace nstd
{
    class istream
    {
        static const int BUFFER_SIZE = 1 << 16;
        char buffer[BUFFER_SIZE];
        char *ptr, *end;

        void readBuffer()
        {
            ptr = buffer;
            end = buffer + fread(buffer, 1, BUFFER_SIZE, stdin);
        }

    public:
        istream() : ptr(buffer), end(buffer)
        {
            readBuffer();
        }

        char getChar()
        {
            if (ptr >= end)
            {
                readBuffer();
                if (ptr >= end)
                    return EOF;
            }
            return *ptr++;
        }

        template <typename T>
        istream &operator>>(T &x)
        {
            x = 0;
            char c;
            bool neg = false;

            do
            {
                c = getChar();
            } while (isspace(c));

            if (c == '-')
            {
                neg = true;
                c = getChar();
            }

            while (isdigit(c))
            {
                x = x * 10 + (c - '0');
                c = getChar();
            }

            if (neg)
                x = -x;
            return *this;
        }

        istream &operator>>(double &x)
        {
            x = 0.0;
            char c;
            bool neg = false;
            double fraction = 1.0;

            do
            {
                c = getChar();
            } while (isspace(c));

            if (c == '-')
            {
                neg = true;
                c = getChar();
            }

            while (isdigit(c))
            {
                x = x * 10.0 + (c - '0');
                c = getChar();
            }

            if (c == '.')
            {
                c = getChar();
                while (isdigit(c))
                {
                    fraction *= 0.1;
                    x += (c - '0') * fraction;
                    c = getChar();
                }
            }

            if (neg)
                x = -x;
            return *this;
        }
    };
    istream cin;
}