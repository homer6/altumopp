//                      -- main.hpp --
//
//          Copyright (c) Darren Garvey 2007-2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
//
// [fcgi_charts
//

#include <iostream>
#include <boost/cgi/fcgi.hpp>
#include <boost/cgi/utility/stencil.hpp>
#include <chartdir.h>

using namespace boost::fcgi;

/*
int handle_request(request& req)
{
  req.load(parse_all);
  
  // Construct a response that uses Google cTemplate. Also sets the root
  // directory where the stencils are found.
  stencil resp("stencils/");

  //// Test 1.

  // This is a minimal response. The content_type(...) may go before or after
  // the response text.
  // The content of the response - which is everything streamed to it - is
  // added to a {{content}} field in the stencil.
  resp<< content_type("text/html")
      << "Hello there, universe!";
      
  //// Test 2.

  // Set some fields.
  resp.set("script_name", req.script_name()); // Populates {{script_name}}.
  resp.set("some_string", req.get["string"]); // Populates {{some_string}}.
  // set() supports any type that Boost.Lexical_cast does.
  resp.set("short_bits", 8 * sizeof(short)); // Populates {{short_bits}}.
  if (req.get.count("short"))
  {
    // Almost any type is supported by as<>
    // (ie. any type supported by Boost.Lexical_cast.).
    short some_short = req.get.as<short>("short", -1);
    resp.set("some_short", some_short);
  }
  
  //// Test 3.
  
  // Show a section, conditionally.
  
  // Use the "show" GET variable, or default to the string "show" if not set.
  request::string_type show = req.get.pick("show", "show");
  resp.set("show", show == "show" ? "hide" : "show");
  if (show == "show")
    resp.show("some_section"); // Shows {{#some_section}}...{{/some_section}}.
  
  //// Test 4.
  
  int num = req.get.as("count", 0);
  if (num < 0) num = 0;
  resp.set("show_less", num ? num - 1 : 0);
  resp.set("show_more", num + 1);
  stencil::section sec("section_with_variable");
  for (int i(0); i < num; ++i)
  {
    // We can show a section and set one field in it in one go.
    resp.set("some_section_variable", i + 1, sec);
  }
  
  //// Test 5.

  resp.add(stencil::section("embedded")).set("test", "passed");
  
  stencil::dictionary dict = resp.add("embedded");
  dict.add("subsection") // returns a new sub-dictionary.
      .set("test", "passed again")
      .set("other", "(another field)");
  dict.set("test", "passed yet again", stencil::section("subsection"));

  //// Test 6.

  // Include another stencil into this one at marker {{>include}}.
  resp.include(
      stencil::section(
          "include",
          "stencil.include.html"
        )
    );
  
  // Short-cut for stencil includes.
  resp.include("include", "stencil.include.html");
  
  resp<< cookie("name", "value");

  /// End Tests.
  
  // Expand the response using the specified template.
  // cTemplate has a cache internally, which we can choose to
  // ignore.
  resp.expand("stencil.html", stencil::reload);

  // Send the response and close the request.
  return commit(req, resp);
}
*/

using namespace std;

int main()
{
try {

  cout<< "Hello, world" << endl;
  
  // The data for the bar chart
  double data[] = {85, 156, 179.5, 211, 123};

  // The labels for the bar chart
  const char *labels[] = {"Mon", "Tue", "Wed", "Thu", "Fri"};

  // Create a XYChart object of size 250 x 250 pixels
  boost::scoped_ptr<XYChart> c (new XYChart(250, 250));

  // Set the plotarea at (30, 20) and of size 200 x 200 pixels
  c->setPlotArea(30, 20, 200, 200);

  // Add a bar chart layer using the given data
  c->addBarLayer(DoubleArray(data, sizeof(data)/sizeof(data[0])));

  // Set the labels on the x axis.
  c->xAxis()->setLabels(StringArray(labels, sizeof(labels)/sizeof(labels[0])));

  // Output the chart
  c->makeChart("simplebar.png");

  cerr<< "Press enter to close console window..." << endl;
  cin.get();
  return 0;
  
} catch(std::exception& e) {
  cerr<< "Error: " << e.what() << endl;
} catch(...) {
  using namespace std;
  cerr<< "Unexpected exception." << endl;
}
  // Control only reaches here if an exception has been caught.
  using namespace std;
  cerr<< "Press enter to close console window..." << endl;
  cin.get();
  return 1;
}
//]
