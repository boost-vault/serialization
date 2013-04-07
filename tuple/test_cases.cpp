
#include <map>
#include <fstream>

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/map.hpp>

#include "tuple.hpp"

using namespace std;
using namespace boost;


// Test cases for serializing tuples using boost::serialize library.

typedef tuple< int, int > TwoTuple_Key;
typedef tuple< int, int, int > ThreeTuple_Key;
typedef tuple< int, int, int, int > FourTuple_Key;
typedef tuple< int, int, int, int, int > FiveTuple_Key;
typedef tuple< int, int, int, int, int, int > SixTuple_Key;
typedef tuple< int, int, int, int, int, int, int > SevenTuple_Key;
typedef tuple< int, int, int, int, int, int, int, int > EigthTuple_Key;
typedef tuple< int, int, int, int, int, int, int, int, int > NineTuple_Key;
typedef tuple< int, int, int, int, int, int, int, int, int, int > TenTuple_Key;

typedef map< TwoTuple_Key  , int > TwoMap;
typedef map< ThreeTuple_Key, int > ThreeMap;
typedef map< FourTuple_Key , int > FourMap;
typedef map< FiveTuple_Key , int > FiveMap;
typedef map< SixTuple_Key  , int > SixMap;
typedef map< SevenTuple_Key, int > SevenMap;
typedef map< EigthTuple_Key, int > EigthMap;
typedef map< NineTuple_Key , int > NineMap;
typedef map< TenTuple_Key  , int > TenMap;


int main()
{
   TwoMap   twoMap;
   ThreeMap threeMap;
   FourMap  fourMap;
   FiveMap  fiveMap;
   SixMap   sixMap;
   SevenMap sevenMap;
   EigthMap eigthMap;
   NineMap  nineMap;
   TenMap   tenMap;

   const TwoMap&   cTwoMap   = twoMap;
   const ThreeMap& cThreeMap = threeMap;
   const FourMap&  cFourMap  = fourMap;
   const FiveMap&  cFiveMap  = fiveMap;
   const SixMap&   cSixMap   = sixMap;
   const SevenMap& cSevenMap = sevenMap;
   const EigthMap& cEightMap = eigthMap;
   const NineMap&  cNineMap  = nineMap;
   const TenMap&   cTenMap   = tenMap;

   ofstream ofs( "test.txt" );
   boost::archive::text_oarchive oa( ofs );

   oa & twoMap;
   oa & threeMap;
   oa & fourMap;
   oa & fiveMap;
   oa & sixMap;
   oa & sevenMap;
   oa & eigthMap;
   oa & nineMap;
   oa & tenMap;

   return 0;
}