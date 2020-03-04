


#ifndef XCLASP_TRACEBACK_HPP
#define XCLASP_TRACEBACK_HPP

#include <vector>
#include <string>

namespace xclasp
{
  struct xerror
  {
    std::string n_ename;
    std::string m_evalue;
    std::vector<std::string> m_traceback;
  };
  // TODO: implement me
  //xerror extract_error(py::error_already_set& error, const std::vector<std::string>& inputs);
}

#endif
