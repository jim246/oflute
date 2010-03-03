#include <iostream>
#include <iomanip>

#include "boost/timer.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    boost::timer myTimer;
    double p;
    for (p = 0; p < 900000; ++p)
    {
	cout <<'\r' << p << flush;
    }
    cout << setprecision(20) << myTimer . elapsed() << endl;
    return 0;
}
