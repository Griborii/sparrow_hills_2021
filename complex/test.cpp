#include <iostream>
#include <limits>
#include <sstream>
#include <vector>

using namespace std;

class BigInt {
	public:
		BigInt(){};
		BigInt(vector<int>, bool);
		BigInt(long long b);
	    BigInt(const BigInt& copied);
		BigInt& operator=(const BigInt& copied);
		friend ostream& operator<<(ostream&, BigInt);
	    ~BigInt(){};
		vector<int> operator+(BigInt) const;
		vector<int> operator-(BigInt) const;
		vector<int> operator*(BigInt) const;
	private:
	    bool Znak;
		vector<int> Maks;
};
BigInt::BigInt(long long n) {
    vector<int> Bob(0);
    Znak = (n >= 0);
    while (n > 0) {
        Bob.push_back (n % 10);
        n = n / 10;
    }
    Maks = Bob;
}
BigInt::BigInt(vector<int> v, bool z) {
    Maks = v;
    Znak = z;
}
BigInt::BigInt(const BigInt& copied) {
    Maks = copied.Maks;
}
BigInt& BigInt::operator=(const BigInt& copied) {
    return *this;
}
ostream& operator<<(ostream& Out, BigInt x) {
	for (int i = 0; i < x.Maks.size(); ++i) {
		Out << x.Maks[i];
	}
	return Out;
}
bool Sravnenie(vector<int> b1, vector<int> b2) {
	if (b1.size() > b2.size()) {
		return true;
	}
	if (b1.size() > b2.size()) {
		return true;
	}
	for (int i = b1.size() - 1; i >= 0; --i) {
		if (b1[i] > b2[i]) {
			return true;
		}
		if (b1[i] > b2[i]) {
			return false;
		}
	}
}
vector<int> BigInt::operator+ (BigInt other) const{
    BigInt Answer1 = (*this);
    BigInt Answer = (*this);
    bool b;
    if (Answer1.Znak == other.Znak) {
        for (int i = 0; i < min(Answer1.Maks.size(), other.Maks.size()); ++i) {
            Answer.Maks[i] = (b + Answer1.Maks[i] + other.Maks[i]) % 10;
            b = ((b + Answer1.Maks[i] + other.Maks[i]) >= 10);
        }

        if (Answer1.Maks.size() < other.Maks.size()) {
            for (int i = Answer1.Maks.size(); i < other.Maks.size(); ++i) {
                Answer.Maks.push_back((other.Maks[i] + b) % 10);
                b = (other.Maks[i] + b >= 10);
            }
        }
        if (b == 1) {
                Answer.Maks.push_back(1);
        }
        Answer.Znak = Answer1.Znak;
    }
    else {
		if (Sravnenie(Answer1.Maks, other.Maks)) {
			for (int i = 0; i < other.Maks.size(); ++i) {
	            Answer.Maks[i] = (-b + Answer1.Maks[i] - other.Maks[i] + 10) % 10;
    	        b = ((-b + Answer1.Maks[i] - other.Maks[i]) < 0);
        	}
        	int i = other.size(); 
        	while (b == 1) {
        		Answer.Maks[i] = (-b + Answer1.Maks[i] - other.Maks[i] + 10) % 10;
    	        b = ((-b + Answer1.Maks[i] - other.Maks[i]) < 0);
    	        ++i;
			}
		}
		else {
			for (int i = 0; i < Answer1.Maks.size(); ++i) {
	            Answer.Maks[i] = (-b + other.Maks[i] - Answer1.Maks[i] + 10) % 10;
    	        b = ((-b - Answer1.Maks[i] + other.Maks[i]) < 0);
        	}
        	int i = other.size(); 
        	while (b == 1) {
        		Answer.Maks[i] = (-b + Answer1.Maks[i] - other.Maks[i] + 10) % 10;
    	        b = ((-b + Answer1.Maks[i] - other.Maks[i]) < 0);
    	        ++i;
			}
		}
    }
}
std::string toString(const BigInt& value)
{
    std::stringstream buf;
    buf << value;
    return buf.str();
}

void check(int64_t x, int64_t y)
{
    const BigInt bigX = x;
    const BigInt bigY = y;

    if (bigX + bigY != BigInt(x + y))
    {
        std::cout << x << " + " << y << " != " << x + y << " got " << bigX + bigY << '\n';
    }

    if (bigX - bigY != BigInt(x - y))
    {
        std::cout << x << " - " << y << " != " << x - y << " got " << bigX - bigY << '\n';
    }

    if (bigX * bigY != BigInt(x * y))
    {
        std::cout << x << " * " << y << " != " << x * y << " got " << bigX * bigY << '\n';
    }

    if (x != 0 && y != 0)
    {
        if (bigX / bigY != BigInt(x / y))
        {
            std::cout << x << " / " << y << " != " << x / y << " got " << bigX / bigY << '\n';
        }
        if (bigX % bigY != BigInt(x % y))
        {
            std::cout << x << " % " << y << " != " << x % y << " got " << bigX % bigY << '\n';
        }
    }
}

void doCheckEqual(const BigInt& actual, const char* expected, size_t line)
{
    const auto str = toString(actual);
    if (str != expected)
    {
        std::cout << "at line " << line << ": " << str << " != " << expected << '\n';
    }
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

int main()
{
    BigInt x = 3;
    checkEqual(x, "3");
    BigInt y = x;
    checkEqual(y, "3");
    BigInt z;
    checkEqual(z, "0");

    checkEqual(BigInt(-10), "-10");

    checkTrue(x == y);
    checkTrue(y == x);
    checkTrue(x != z);
    checkTrue(z != x);

    z = y;
    checkEqual(z, "3");

    x = 100;
    checkEqual(x, "100");

    checkTrue(!(x < x));
    checkTrue(x < 200);
    checkTrue(BigInt(50) < x);
    checkTrue(BigInt(-500) < x);
    checkTrue(BigInt(-500) < BigInt(-200));

    checkTrue(!(x > x));
    checkTrue(BigInt(200) > x);
    checkTrue(x > BigInt(50));
    checkTrue(x > BigInt(-500));
    checkTrue(BigInt(-200) > BigInt(-500));

    checkTrue(x <= x);
    checkTrue(x <= 200);
    checkTrue(BigInt(50) <= x);
    checkTrue(BigInt(-500) <= x);
    checkTrue(BigInt(-500) <= BigInt(-200));

    checkTrue(x >= x);
    checkTrue(BigInt(200) >= x);
    checkTrue(x >= BigInt(50));
    checkTrue(x >= BigInt(-500));
    checkTrue(BigInt(-200) >= BigInt(-500));
    checkTrue(BigInt(0) == -BigInt(0));

    checkEqual(BigInt(10) + BigInt(10), "20");
    checkEqual(BigInt(-10) + BigInt(10), "0");
    checkEqual(BigInt(10) + BigInt(-10), "0");
    checkEqual(BigInt(-10) + BigInt(-10), "-20");

    checkEqual(BigInt(10) - BigInt(10), "0");
    checkEqual(BigInt(-10) - BigInt(10), "-20");
    checkEqual(BigInt(10) - BigInt(-10), "20");
    checkEqual(BigInt(-10) - BigInt(-10), "0");

    checkEqual(BigInt(0) + BigInt(-1), "-1");
    checkEqual(BigInt(0) - BigInt(1), "-1");

    checkEqual(BigInt(100) - BigInt(100), "0");
    checkEqual(BigInt(99) - BigInt(100), "-1");
    checkEqual(BigInt(10) - BigInt(11), "-1");
    checkEqual(BigInt(20) - BigInt(19), "1");

    for (int i = -21; i <= 21; ++i)
    {
        for (int j = -21; j <= 21; ++j)
        {
            check(i, j);
        }
    }

    const int64_t step = std::numeric_limits<uint32_t>::max() / 99;
    const int64_t lower = std::numeric_limits<int32_t>::min() + step;
    const int64_t upper = std::numeric_limits<int32_t>::max() - step;

    for (int64_t i = lower; i < upper; i += step)
    {
        for (int64_t j = -99; j < 99; ++j)
        {
            check(i, j);
        }
    }

    const BigInt big1 = std::numeric_limits<int64_t>::max();
    checkEqual(big1, "9223372036854775807");

    const BigInt big2 = big1 * big1;
    std::cout << "9223372036854775807 * 9223372036854775807\n";
    checkEqual(big2, "85070591730234615847396907784232501249");

    const BigInt big3 = big2 * big2;
    std::cout << "85070591730234615847396907784232501249 * 85070591730234615847396907784232501249\n";
    checkEqual(big3, "7237005577332262210834635695349653859421902880380109739573089701262786560001");

    std::cout << "done\n";

    return 0;
}
