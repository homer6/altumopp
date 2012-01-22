#include <boost/date_time/posix_time/posix_time.hpp>
#include <fstream>
#include <fastcgi++/request.hpp>
#include <fastcgi++/manager.hpp>

void error_log(const char* msg)
{
   using namespace std;
   using namespace boost;
   static ofstream error;
   if(!error.is_open())
   {
      error.open("/tmp/errlog", ios_base::out | ios_base::app);
      error.imbue(locale(error.getloc(), new posix_time::time_facet()));
   }

   error << '[' << posix_time::second_clock::local_time() << "] " << msg << endl;
}

class HelloWorld: public Fastcgipp::Request<wchar_t>
{
   bool response()
   {
      wchar_t russian[]={ 0x041f, 0x0440, 0x0438, 0x0432, 0x0435, 0x0442, 0x0020, 0x043c, 0x0438, 0x0440, 0x0000 };
      wchar_t chinese[]={ 0x4e16, 0x754c, 0x60a8, 0x597d, 0x0000 };
      wchar_t greek[]={ 0x0393, 0x03b5, 0x03b9, 0x03b1, 0x0020, 0x03c3, 0x03b1, 0x03c2, 0x0020, 0x03ba, 0x03cc, 0x03c3, 0x03bc, 0x03bf, 0x0000 };
      wchar_t japanese[]={ 0x4eca, 0x65e5, 0x306f, 0x4e16, 0x754c, 0x0000 };
      wchar_t runic[]={ 0x16ba, 0x16d6, 0x16da, 0x16df, 0x0020, 0x16b9, 0x16df, 0x16c9, 0x16da, 0x16de, 0x0000 };

      out << "Content-Type: text/html; charset=utf-8\r\n\r\n";

      out << "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' />";
      out << "<title>fastcgi++: Hello World in UTF-8</title></head><body>";
      out << "English: Hello World<br />";
      out << "Russian: " << russian << "<br />";
      out << "Greek: " << greek << "<br />";
      out << "Chinese: " << chinese << "<br />";
      out << "Japanese: " << japanese << "<br />";
      out << "Runic English?: " << runic << "<br />";
      out << "</body></html>";

      err << "Hello apache error log";

      return true;
   }
};

int main()
{

   try
   {
      Fastcgipp::Manager<HelloWorld> fcgi;
//      fcgi.handler();
   }
   catch(std::exception& e)
   {
      error_log(e.what());
   }

}
