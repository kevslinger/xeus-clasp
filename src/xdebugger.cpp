


#include <string>

#include "nlohmann/json.hpp"

#include "xeus/xinterpreter.hpp"
#include "xeus/xmiddleware.hpp"

#include "xdebugger.hpp"
#include "xutils.hpp"

namespace nl = nlohmann;

namespace xclasp
{
  debugger::debugger(zmq::context_t& context,
                     const xeus::xconfiguration& config,
                     const std::string& user_name,
                     const std::string& session_id)
    : m_is_started(false)
  {
    
  }

  nl::json debugger::process_request_impl(const nl::json& header,
                                          const nl::json& message)
  {
    /* TODO: Implement me!*/
    return nullptr;
  }

  nl::json forward_message(const nl::json& message)
  {
    /* TODO: Implement me!*/
    return nullptr;
  }

  nl::json update_cell_request(const nl::json& message)
  {
    /* TODO: Implement me!*/
    return nullptr;
  }

  void start()
  {
    /* TODO: Implement me! */
  }

  void stop()
  {
    /* TODO: Implement me! */
  }

  
  std::unique_ptr<xeus::xdebugger> make_clasp_debugger(zmq::context_t& context,
                                                       const xeus::xconfiguration& config,
                                                       const std::string& user_name,
                                                       const std::string& session_id)
  {
    /* TODO: Implement me!*/
    //return nullptr;
    return std::unique_ptr<xeus::xdebugger>(new debugger(context, config, user_name, session_id));
  }
  

}
