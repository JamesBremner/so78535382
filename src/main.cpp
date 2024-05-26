#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cStarterGUI.h"

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          lb(wex::maker::make<wex::label>(fm))
    {
        lb.move(50, 50, 100, 30);
        lb.text("Hello World");

        show();
        run();
    }

private:
    wex::label &lb;
};


class cLine
{
    public:
    int myID;
    std::vector<int> vStops;

    cLine( int nLine )
    : myID( nLine )
    {}
    void addStop( int sid )
    {
        vStops.push_back( sid );
    }
    bool isConnected( const cLine& other);
};
class cTimeTable
{
    public:
    std::vector< cLine > vLines;

    int addLine( int nline );
    void readfile();
    void findConnections();
};

    int cTimeTable::addLine( int nline )
    {
        int index = -1;
        for( auto& l : vLines )
        {
            index++;
            if( l.myID == nline )
            {
                return index;
            }
        }
        vLines.emplace_back( nline);
        return vLines.size() - 1;
    }
void cTimeTable::readfile()
{
    std::ifstream ifs("../dat/bus_timetable.csv");
    std::string line;
    getline(ifs, line);
    while (getline(ifs, line))
    {
        std::vector<std::string> vtoken;
        std::stringstream sst(line);
        std::string a;
        while (getline(sst, a, ','))
            vtoken.push_back(a);

        int lid = addLine(atoi(vtoken[5].c_str()));
        vLines[lid].addStop(atoi(vtoken[21].c_str()) );
    }
}

 bool cLine::isConnected( const cLine& other)
 {
    for( int ms : vStops )
        for( int os : vStops )
            if( ms == os ) {
                std::cout << "Line " << myID << " connects to " <<other.myID << " at stop " << ms << "\n";
                return true;
            }
    return false;
 }

void cTimeTable::findConnections()
{
    for( auto it = vLines.begin(); it < vLines.end(); it++ )
        for( auto it2 = it+1; it2 < vLines.end(); it2++ )
            it->isConnected( *it2 );
}

main()
{
    cTimeTable TT;
    TT.readfile();
    TT.findConnections();
    cGUI theGUI;
    return 0;
}
