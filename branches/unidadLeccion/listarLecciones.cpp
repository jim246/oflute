#include <iostream>
#include <boost/filesystem.hpp>

using namespace std;

int main(int argc, char *argv[])
{
    boost::filesystem::path rutaDirectorio("lecciones");

    boost::filesystem::directory_iterator inicial(rutaDirectorio), final;

    
    for( ; inicial != final ; ++ inicial){
	cout << inicial -> path() << endl;
    } //*/

    return 0;
}

