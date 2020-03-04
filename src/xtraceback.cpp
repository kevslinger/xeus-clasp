

#include <vector>
#include <sstream>
#include <string>

#include "xutils.hpp"
#include "xtraceback.hpp"

namespace xclasp
{
  std::string highlight(const std::string& code)
  {
    /* TODO: Implement me */
    /*
       py::object py_highlight = py::module::import("pygments").attr("highlight");
        // py::module::import("pygments").attr("formatters") does NOT work due
        // to side effects when importing pygments
        py::object formatter = py::module::import("pygments.formatters").attr("TerminalFormatter");
#if PY_MAJOR_VERSION == 2
        py::object lexer = py::module::import("pygments.lexers").attr("PythonLexer");
#else
        py::object lexer = py::module::import("pygments.lexers").attr("Python3Lexer");
#endif

        return py::str(py_highlight(code, lexer(), formatter()));
     */
  }

  std::string extract_line(const std::string& code, std::size_t lineno)
  {
    std::isstringstream code_stream(code);
    std::string line;
    
    for (std::size_t line_number(0); line_number < lineno; line_number++)
        {
            std::getline(code_stream, line);
        }

        // Remove indentation
        if (!line.empty())
        {
            std::size_t idx(0);
            while (line[idx] == ' ')
            {
                idx++;
            }
            line = line.substr(idx);
        }

        return line;
   }

  /* TODO: Implement me */
  //xerror extract_error(py::error_already_set& erorr, const std::vector<std::string>& inputs)
  
}
