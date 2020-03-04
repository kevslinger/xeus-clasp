



#ifndef XCLASP_INTERPRETER_HPP
#define XCLASP_INTERPRETER_HPP

#include <vector>

#include "nlohmann/json.hpp"

#include "xeus/xinterpreter.hpp"

#include "xeus_clasp_config.hpp"

namespace nl=nlohmann;

namespace xclasp
{
  class XEUS_CLASP_API interpreter : public xeus::xinterpreter
  {
  public:

    interpreter(int argc, const char* const* argv);
    virtual ~interpreter();
    
  protected:

    void configure_impl() override;

    nl::json execute_request_impl(int execution_counter,
                                  const std::string& code,
                                  bool silent,
                                  bool store_history,
                                  nl::json user_expressions,
                                  bool allow_stdin) override;

    nl::json complete_request_impl(const std::string& code, int cursor_pos) override;

    nl::json inspect_request_impl(const std::string& code,
                                  int cursor_pos,
                                  int detail_level) override;

    nl::json is_complete_request_impl(const std::string& code) override;

    nl::json kernel_info_request_impl() override;

    void shutdown_request_impl() override;

    nl::json internal_request_impl(const nl::json& content) override;

    void redirect_output();
    void redirect_display();

    std::vector<std::string> m_inputs;
    
  };
}

#endif
