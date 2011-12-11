//                -- protocol_traits.hpp --
//
//          Copyright (c) Darren Garvey 2007-2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
////////////////////////////////////////////////////////////////
#ifndef BOOST_CGI_PROTOCOL_TRAITS_HPP_INCLUDED_
#define BOOST_CGI_PROTOCOL_TRAITS_HPP_INCLUDED_

#include <boost/asio/ip/tcp.hpp>
#include <boost/none.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/config.hpp>
///////////////////////////////////////////////////////////
#include "boost/cgi/common/parse_options.hpp"
#include "boost/cgi/common/role_type.hpp"
#include "boost/cgi/common/tags.hpp"
#include "boost/cgi/fcgi/specification.hpp"
#include "boost/cgi/fwd/basic_client_fwd.hpp"
#include "boost/cgi/fwd/basic_connection_fwd.hpp"
#include "boost/cgi/fwd/basic_protocol_service_fwd.hpp"
#include "boost/cgi/fwd/basic_request_fwd.hpp"
#include "boost/cgi/fwd/form_parser_fwd.hpp"
#ifdef BOOST_CGI_ENABLE_SESSIONS
#  include "boost/cgi/fwd/sessions_fwd.hpp"
#endif // BOOST_CGI_ENABLE_SESSIONS

BOOST_CGI_NAMESPACE_BEGIN

  struct empty;

  namespace cgi  {}
  namespace fcgi
  {
  class fcgi_service_impl;
  template<typename Protocol>
  class fcgi_request_service;
  class fcgi_acceptor_service;
  }
  namespace scgi
  {
  class scgi_service_impl;
  class scgi_request_service;
  class scgi_acceptor_service;
  }

  // Forward declarations

  class cgi_service_impl;
  class fcgi_service_impl;

  class fcgi_acceptor_service;
  template<typename Protocol>
  class fcgi_request_acceptor_service;

  class cgi_request_service;
  class fcgi_request_service;

 namespace common {
 
    enum session_opts
    {
      path_session,
      domain_session
    };

    template<typename Protocol>
    struct protocol_traits
    {
    };

    /// Common Traits for CGI.
    template<>
    struct protocol_traits<tags::cgi>
    {
      typedef protocol_traits<tags::cgi>             type;
      typedef tags::cgi                              protocol_type;
      typedef cgi_request_service                    request_service_impl;
      typedef cgi_request_service                    service_type;
      typedef common::basic_protocol_service<
                  protocol_type
              >                                      protocol_service_type;
      typedef basic_request<
                  protocol_type
              >                                      request_type; 
      typedef cgi_service_impl                       service_impl_type;
      typedef basic_connection<
                  tags::async_stdio
              >                                      connection_type;
      typedef basic_client<
                  protocol_type
              >                                      client_type;
      typedef form_parser                            form_parser_type;
      typedef boost::none_t                          header_type;
      typedef char                                   char_type;
      typedef std::basic_string<char_type>           string_type;
      typedef string_type                            buffer_type;
      typedef boost::array<unsigned char, 8>         header_buffer_type;
      typedef boost::asio::const_buffers_1           const_buffers_type;
      typedef boost::asio::mutable_buffers_1         mutable_buffers_type;
      typedef common::role_type                      role_type;
      typedef boost::shared_ptr<request_type>        pointer;
#ifdef BOOST_CGI_ENABLE_SESSIONS
      typedef basic_session<
                std::map<string_type, string_type>
              >                                      session_type;
      typedef boost::uuids::random_generator         uuid_generator_type;
      typedef basic_session_manager<
                protocol_type
              >                                      session_manager_type;
      static const bool auto_start_session = true;
      static const int session_options = path_session;

#endif // BOOST_CGI_ENABLE_SESSIONS
      static const common::parse_options parse_opts = common::parse_all;
    };

    /// Common Traits for FastCGI.
    template<>
    struct protocol_traits<tags::fcgi>
    {
      typedef protocol_traits<tags::fcgi>            type;
      typedef tags::fcgi                             protocol_type;
      typedef fcgi::fcgi_request_service<protocol_type>             request_service_impl;
      typedef fcgi::fcgi_request_service<protocol_type>             service_type;
      typedef basic_protocol_service<
                  protocol_type
              >                                      protocol_service_type;
      typedef basic_request<protocol_type>           request_type; 
      typedef boost::shared_ptr<request_type>        request_ptr;
      typedef fcgi::fcgi_service_impl                service_impl_type;
      typedef fcgi_request_acceptor_service<protocol_type>  acceptor_service;
      typedef fcgi::fcgi_acceptor_service            acceptor_service_impl;
#if defined(BOOST_WINDOWS)
      typedef basic_connection<
                  tags::anonymous_pipe
              >                                      connection_type;
      //typedef anonymous_pipe                         connection_type;
#else
      typedef basic_connection<
                  tags::shareable_tcp_socket
              >                                      connection_type;
#endif // defined(BOOST_WINDOWS)
      typedef boost::asio::ip::tcp                   native_protocol_type;
      typedef boost::asio::socket_acceptor_service<
                  native_protocol_type
              >                                      acceptor_service_type;
      typedef 
          acceptor_service_type::implementation_type acceptor_impl_type;
      typedef acceptor_service_type::native_type     native_type;
      typedef unsigned short                         port_number_type;
      typedef boost::asio::ip::tcp::endpoint         endpoint_type;
      typedef basic_client<protocol_type>            client_type;
      typedef form_parser                            form_parser_type;
      typedef fcgi::spec::header                     header_type;
      typedef fcgi::spec_detail::role_types          role_type;

      typedef char                                   char_type;
      typedef std::basic_string<char_type>           string_type;
      typedef string_type                            buffer_type;
      typedef boost::array<unsigned char, 8>         header_buffer_type;
      typedef boost::asio::const_buffers_1           const_buffers_type;
      typedef boost::asio::mutable_buffers_1         mutable_buffers_type;
      typedef boost::shared_ptr<request_type>        pointer;
#ifdef BOOST_CGI_ENABLE_SESSIONS
      typedef basic_session<
                std::map<string_type, string_type>
              >                                      session_type;
      typedef boost::uuids::random_generator         uuid_generator_type;
      typedef basic_session_manager<
                protocol_type
              >                                      session_manager_type;
      static const bool auto_start_session = true;
      static const int session_options = path_session;
#endif // BOOST_CGI_ENABLE_SESSIONS

      static const parse_options parse_opts = common::parse_none;
    };

 } // namespace common
BOOST_CGI_NAMESPACE_END

#endif // BOOST_CGI_PROTOCOL_TRAITS_HPP_INCLUDED_
