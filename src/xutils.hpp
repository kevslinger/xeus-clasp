

#ifndef XCLASP_UTILS_HPP
#define XCLASP_UTILS_HPP

#include <vector>

#include "nlohmann/json.hpp"

#include "xeus/xcomm.hpp"


namespace nl = nlohmann;


/*
#if PY_MAJOR_VERSION == 2
    #define XPYT_BUILTINS "__builtin__"
    #define XPYT_EXEC_COMMAND "exec(\"\"\"exec _code_ in _scope_\"\"\")"
#else
    #define XPYT_BUILTINS "builtins"
    #define XPYT_EXEC_COMMAND "exec(_code_, _scope_, _scope_)"
    #endif*/

namespace xclasp
{
  std::string red_text(const std::string& text);
  std::string green_text(const std::string& text);
  std::string blue_text(const std::string& text);

  // py::list zmq_buffers_to_pylist(const std::vector<zmq::message_t>& buffers);
  // std::vector<zmq::message_t> pylist_to_zmq_buffers(const py::list& bufferlist);
  //  py::object cppmessage_to_pymessage(const xeus::xmessage& msg);
  // bool holding_gil();

/*
#define XPYT_HOLDING_GIL(func)           \
    if (holding_gil())                   \
    {                                    \
        func;                            \
    }                                    \
    else                                 \
    {                                    \
        py::gil_scoped_acquire acquire;  \
        func;                            \
    }
 */

  // void exec(const py::object& code, const py::object& scope = py::globals());

  std::string get_tmp_prefix();
  std::string get_tmp_file(const std::string& prefix,
                           //const std::string& session_id),
                           int execution_count,
                           const std::string& extension);
  
}

/*namespace nlohmann
{
  template<>
  struct adl_serializer<py::object>
  {
    static py::object from_json(const json& j);
    static void to_json(json& j, const py::object& obj);
    };
}*/

#endif
