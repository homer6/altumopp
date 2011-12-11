
#define BOOST_TEST_MAIN blah
#include <boost/test/unit_test.hpp>
//#include <boost/test/included/prg_exec_monitor.hpp>
#include <boost/throw_exception.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace std;

int foo() { throw std::logic_error("You can't use foo()."); }

int bar() { BOOST_THROW_EXCEPTION( std::logic_error("You can't use bar().") ); }

template<typename T>
T as(string val, T const& t = T()) {
  return boost::lexical_cast<T>(val);
}

//int cpp_main(int argc, char** argv)
BOOST_AUTO_TEST_CASE( asoduh )
{
  cout<< "Hello, test." << endl;
  cout<< as<float>("3.1415962") << endl;
  BOOST_CHECK_EQUAL( as<float>("3.1415962"), 3.1415962 );
  BOOST_CHECK_EQUAL( boost::lexical_cast<float>("3.1415962"), 3.1415962 );
  //bar();
  //foo();
  cin.get();
}