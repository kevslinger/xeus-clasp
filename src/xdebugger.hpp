

#ifndef XCLASP_DEBUGGER_HPP
#define XCLASP_DEBUGGER_HPP

#include "zmq.hpp"
#include "nlohmann/json.hpp"
#include "xeus/xdebugger.hpp"

#include "xeus-clasp/xeus_clasp_config.hpp"

namespace xclasp
{
  class XEUS_CLASP_API debugger : public xeus::xdebugger
  {
  public:

    debugger(zmq::context_t& context,
             const xeus::xconfiguration& config,
             const std::string& user_name,
             const std::string& session_id);

    virtual ~debugger() = default;

  private:

    virtual nl::json process_request_impl(const nl::json& header,
                                          const nl::json& message);

    nl::json forward_message(const nl::json& message);
    nl::json update_cell_request(const nl::json& message);

    void start();
    void stop();

    /* TODO
      xptvsd_client m_ptvsd_client;
      zmq::socket_t m_ptvsd_socket;
      zmq::socket_t m_ptvsd_header;
    */
    bool m_is_started;
    
  };

  XEUS_CLASP_API
  std::unique_ptr<xeus::xdebugger> make_clasp_debugger(zmq::context_t& context,
                                                          const xeus::xconfiguration& config,
                                                          const std::string& user_name,
                                                          const std::string& session_id);
  
}

#endif
