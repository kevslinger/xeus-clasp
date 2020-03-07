#include <string>
#include <iostream>

#include "nlohmann/json.hpp"

#include "xeus/xinterpreter.hpp"

#include "xeus-clasp/xinterpreter.hpp"
#include "xeus-clasp/xeus_clasp_config.hpp"
#include <clasp/clasp.h>

namespace nl=nlohmann;

namespace xclasp
{
  void interpreter::configure_impl()
  {
    /* TODO: Implement me*/
  }

  interpreter::interpreter(int /*argc*/, const char* const* /*argv*/)
  {
    xeus::register_interpreter(this);
    redirect_output();
    redirect_display();
    /* TODO: Implement me*/
  }
  
  interpreter::~interpreter()
  {
  }

  nl::json interpreter::execute_request_impl(int execution_count,
                                             const std::string& code,
                                             bool silent,
                                             bool /*store_history*/,
                                             nl::json /*user_expressions*/,
                                             bool allow_stdin)
  {
      std::clog << __FUNCTION__ << "Trying to execute " << code << "\n";
    core::SimpleBaseString_sp sbs = core::SimpleBaseString_O::make(code);
    core::SimpleBaseString_sp eval = core::SimpleBaseString_O::make("EVALUATE");
    core::SimpleBaseString_sp pkg = core::SimpleBaseString_O::make("XCLASP");
    core::Symbol_sp eval_sym = core::cl__intern(eval,pkg);
    core::StringOutputStream_sp stdout = gc::As<core::StringOutputStream_sp>(core::clasp_make_string_output_stream());
    core::DynamicScopeManager scope1(ext::_sym__PLUS_processStandardOutput_PLUS_,stdout);
    core::StringOutputStream_sp stderr = gc::As<core::StringOutputStream_sp>(core::clasp_make_string_output_stream());
    core::DynamicScopeManager scope2(ext::_sym__PLUS_processErrorOutput_PLUS_,stderr);
    core::T_mv result = core::eval::funcall(eval_sym,sbs);
    // Implement something like xeus-python formatted_docstring(code)
    nl::json kernel_res;
    core::String_sp stdout_str = stdout->getAndReset();
    core::String_sp stderr_str = stderr->getAndReset();
    if (core::cl__length(stdout_str)>0) {
        this->publish_stream("stdout",stdout_str->get_std_string());
    }
    if (core::cl__length(stderr_str)>0) {
        this->publish_stream("stderr",stderr_str->get_std_string());
    }
    kernel_res["status"] = "ok";
    kernel_res["payload"] = nl::json::array();
    kernel_res["payload"][0] = nl::json::object({
                                                 {"data", {
                                                           {"text/plain", _rep_(result)}
                                                     }},
                                                 {"source", "page"},
                                                 {"start", 0}
        });
    kernel_res["user_expressions"] = nl::json::object();
    return kernel_res;
  }

  nl::json interpreter::complete_request_impl(
      const std::string& code,
      int cursor_pos)
  {
    std::clog << "Trying to complete request " << code << "\n";
    /* TODO: Impelement me*/
    return nullptr;
  }

  nl::json interpreter::inspect_request_impl(const std::string& code,
                                             int curosor_pos,
                                             int /*detail_level*/)
  {
    std::clog << "Trying to inspect request " << code << "\n";
    /* TODO: Implement me*/
    return nullptr;
  }

  nl::json interpreter::is_complete_request_impl(const std::string& code)
  {
    std::clog << "Checking if the request is complete: " << code << "\n";
    /* TODO: Impelement me*/
    return nullptr;
  }

  nl::json interpreter::kernel_info_request_impl()
  {
    nl::json result;
    result["implementation"] = "xeus-clasp";
    result["implementation_version"] = XCLASP_VERSION; //TODO: Update xeus-clasp version

    /* The jupyter-console banner for xeus-clasp is the following:
         __   ________ _    _  _____        _____ _                _____ _____  
         \ \ / /  ____| |  | |/ ____|      / ____| |        /\    / ____|  __ \ 
          \ V /| |__  | |  | | (___ ______| |    | |       /  \  | (___ | |__) |
           > < |  __| | |  | |\___ \______| |    | |      / /\ \  \___ \|  ___/ 
          / . \| |____| |__| |____) |     | |____| |____ / ____ \ ____) | |     
         /_/ \_\______|\____/|_____/       \_____|______/_/    \_\_____/|_|     
                                                                        
                                                                       
          C++ Jupyter Kernel for Clasp
        */
    std::string banner = ""
      " __   ________ _    _  _____        _____ _                _____ _____\n"
      " \\ \\ / /  ____| |  | |/ ____|      / ____| |        /\\    / ____|  __ \n" 
      "  \\ V /| |__  | |  | | (___ ______| |    | |       /  \\  | (___ | |__) |\n"
      "   > < |  __| | |  | |\\___ \\______| |    | |      / /\\ \\  \\___ \\|  ___/\n"
      "  / . \\| |____| |__| |____) |     | |____| |____ / ____ \\ ____) | |   \n"  
      " /_/ \\_\\______|\\____/|_____/       \\_____|______/_/    \\_\\_____/|_|  \n"           
      "  C++ Jupyter Kernel for Clasp  \n"
      "  Clasp ";

    banner.append("0.5"); //TODO: Update clasp version
    result["banner"] = banner;

    result["language_info"]["name"] = "common lisp";
    result["language_info"]["version"] = "0.5"; //TODO: Update clasp version
    result["language_info"]["mimetype"] = "text/x-common-lisp";
    result["language_info"]["file_extension"] = ".lisp";
    result["status"] = "ok";
    return result;
  }

  void interpreter::shutdown_request_impl()
  {
  }

  nl::json interpreter::internal_request_impl(const nl::json& content)
  {
    /* TODO: Implement me*/
    return nullptr;
  }

  void interpreter::redirect_output()
  {
    /* TODO: Impelment me*/

  }

  void interpreter::redirect_display()
  {
    /* TODO: Implement me*/
  }
  
  
}
