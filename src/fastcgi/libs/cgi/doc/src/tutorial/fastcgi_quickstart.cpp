//              -- fastcgi_quickstart.cpp --
//
//            Copyright (c) Darren Garvey 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////

//[fastcgi_quickstart

#include <iostream> // for std::cerr
#include <string>
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
/*<
A catch-all header is available which includes all of the headers you should
need for FastCGI.

For the sake of clarity we alias the `boost::fcgi` namespace rather than
dumping all of the library names with a `using namespace`. This way, you can
see what comes from the library.
>*/
#include <boost/cgi/fcgi.hpp>
namespace fcgi = boost::fcgi;

/*<
The following code is taken straight from the calc3 example in
[@http://boost.org/libs/spirit Boost.Spirit]. The only difference is to
use `float`s rather than `int`s.
>*/
namespace client
{
    namespace qi = boost::spirit::qi;
    namespace ascii = boost::spirit::ascii;

    ///////////////////////////////////////////////////////////////////////////
    //  Our calculator grammar
    ///////////////////////////////////////////////////////////////////////////
    template <typename Iterator>
    struct calculator : qi::grammar<Iterator, float(), ascii::space_type>
    {
        calculator() : calculator::base_type(expression)
        {
            using qi::_val;
            using qi::_1;
            using qi::float_;

            expression =
                term                            [_val = _1]
                >> *(   ('+' >> term            [_val += _1])
                    |   ('-' >> term            [_val -= _1])
                    )
                ;

            term =
                factor                          [_val = _1]
                >> *(   ('*' >> factor          [_val *= _1])
                    |   ('/' >> factor          [_val /= _1])
                    )
                ;

            factor =
                float_                          [_val = _1]
                |   '(' >> expression           [_val = _1] >> ')'
                |   ('-' >> factor              [_val = -_1])
                |   ('+' >> factor              [_val = _1])
                ;
        }

        qi::rule<Iterator, float(), ascii::space_type> expression, term, factor;
    };
} // namespace client

/*<
The first thing to do is write a handler function which takes a request and a
response and does all request-specific work. Later, we will look at writing
the code that calls this function.
>*/
int handle_request(fcgi::request& req)
{
/*<
A FastCGI request is not loaded or parsed by default. 
>*/
  req.load(fcgi::parse_all);
/*<
Now that the request has been loaded, we can access all of the request data.
The request data is available using `std::map<>`-like public members of a
`fcgi::request`.[footnote
The data is stored internally in a single `fusion::vector<>`
]

A FastCGI request has several types of variables available. These are listed
in the table below, assuming that `req` is an instance of `fcgi::request`:

[table
  [[Source] [Variable] [Description]]
  [
    [Environment] [`req.env`] [The environment of a FastCGI request contains
    most of the information you will need to handle a request. There is a basic
    set of common environment variables that you can expect to be set by most
    HTTP servers around. A list of them is available on the __TODO__ (link)
    variables page.]
  ]
  [
    [GET] [`req.get`] [The variables passed in the query string of an HTTP GET
    request. The `get_data` map is multivalued and mimics a `std::multimap<>`.]
  ]
  [
    [POST] [`req.post`] [The HTTP POST data that is sent in an HTTP request's
    body. For file uploads, only the filename is stored in this map. As with
    `get`, the `post_data` map is multivalued and mimics a `std::multimap<>`.]
  ]
  [
    [Cookies] [`req.cookies`] [Cookies are sent in the HTTP_COOKIE environment
    variable. These can store limited amounts session information on the
    client's machine, such as database session ids or tracking information. As
    with `get`, the `cookie_data` map is multivalued and mimics a
    `std::multimap<>`.]
  ]
  [
    [File Uploads] [`req.uploads`] [File uploads, sent in an HTTP POST where
    the body is MIME-encoded as multipart/form-data. Uploaded files are read
    onto the server's file system. The value of an upload variable is the path
    of the file. The `upload_data` map is also multivalued.]
  ]
  [
    [Form] [`req.form`] [The form variables are either the GET variables or
    the POST variables, depending on the request method of the request.]
  ]
]
>*/

  fcgi::response resp;/*<
The `response` class provides a streaming interface for writing replies. You
can write to the request object directly, but for now we're going to use the
`response`, which works well for most situations.

As you can see, the `response` is decoupled from the rest of the library. The
advantages of using it over any other custom container are separate handling
of the response body and headers, and a [funcref
boost::cgi::common::response::send send()] function which wraps the whole
response and writes it out to the client who instigated the request.

Writing to a `response` is buffered. If an error occurs, you can `clear()` the
response and send an error message instead. Buffered writing may not always
suit your use-case (eg. returning large files), but when memory is not at a
real premium, buffering the response is highly preferable.

Not only does buffering help with network latency issues, but being able to
cancel the response and send another at any time is almost essential when
an error can crop up at any time. A `cgi::response` is not tied to a
request, so the same response can be reused across multiple requests.[footnote
Not with plain CGI though, of course.]

When sending a response that is large relative to the amount of memory
available to the system, you may need to write unbuffered.
>*/

  if (req.form.count("expression"))
  {
    resp<< "<fieldset><legend>Result</legend><pre>";
        
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef client::calculator<iterator_type> calculator;

    calculator calc; // Our grammar

    std::string str ( req.form["expression"] );
    float result;
    if (!str.empty())
    {
        std::string::const_iterator iter = str.begin();
        std::string::const_iterator end = str.end();
        bool r = phrase_parse(iter, end, calc, space, result);

        if (r && iter == end)
        {
            resp << "-------------------------\n";
            resp << "Parsing succeeded\n";
            resp << "result = " << result << '\n';
            resp << "-------------------------\n";
        }
        else
        {
            std::string rest(iter, end);
            resp << "-------------------------\n";
            resp << "Parsing failed\n";
            resp << "stopped at: \": " << rest << "\"\n";
            resp << "-------------------------\n";
        }
    }
    else
    {
      resp<< "No expression found.";
    }
    resp<< "</pre></fieldset>";
  }
  resp<< "<form method='post' id=''>"
      << "  Expression: <input type='text' name='expression' value='"
      <<   req.form["expression"] << "'><br />"
      << "  <input type='submit' value='Calculate!'>"
      << "</form>"
      << fcgi::content_type("text/html");
/*<
Finally, send the response back and close the request.
>*/
  return fcgi::commit(req, resp);
}

/*<
We now have a request handler in all of it's contrived glory.

The program's `main` function needs to parse the request, call the request
handler defined above, and finally send the response.
>*/
int main(int, char**)
{
  fcgi::service service; /*<
A Service handles asynchronous operations and some of the protocol-specific
bits.
>*/
  fcgi::acceptor acceptor(service); /*<
An `Acceptor` handles accepting requests and little else.
>*/
  int status;
  
/*<
Keep accepting requests until the handler returns an error.
>*/
  do {
/*<
The function `boost::fcgi::acceptor::accept` has a few overloads. The one used
here takes a function or function object with the signature:
``
boost::function<int (boost::fcgi::request&)>
``
ie. A function that takes a reference to a `request` and returns an `int`.
The returned `int` should be non-zero if the request was handled with
an error.
>*/
    status = acceptor.accept(&handle_request);
    if (status)
        std::cerr
            << "Request handled with error. Exit code: "
            << status << std::endl;
  } while (!status);
  return status;
}

//]
