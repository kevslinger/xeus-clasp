
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

#include "xeus/xkernel.hpp"
#include "xeus/xkernel_configuration.hpp"
#include "xeus/xserver.hpp"

#include "xeus-clasp/xinterpreter.hpp"
#include "xdebugger.hpp"


std::string extract_filename(int& argc, char* argv[])
{
    std::string res = "";
    for (int i = 0; i < argc; ++i)
    {
        if ((std::string(argv[i]) == "-f") && (i + 1 < argc))
        {
            res = argv[i + 1];
            for (int j = i; j < argc - 2; ++j)
            {
                argv[j] = argv[j + 2];
            }
            argc -= 2;
            break;
        }
    }
    return res;
}


int main(int argc, char* argv[])
{
  
  std::string file_name = extract_filename(argc, argv);
  using interpreter_ptr = std::unique_ptr<xclasp::interpreter>;
  interpreter_ptr interpreter = interpreter_ptr(new xclasp::interpreter(argc, argv));
    
  using history_manager_ptr = std::unique_ptr<xeus::xhistory_manager>;
  history_manager_ptr hist = xeus::make_in_memory_history_manager();
  
  if (!file_name.empty())
  {
    xeus::xconfiguration config = xeus::load_configuration(file_name);

    xeus::xkernel kernel(config,
                         xeus::get_user_name(),
                         std::move(interpreter),
                         std::move(hist),
                         xeus::make_console_logger(xeus::xlogger::msg_type,
                                                   xeus::make_file_logger(xeus::xlogger::content, "xeus.log")),
                         xeus::make_xserver_shell_main,
                         xclasp::make_clasp_debugger);
    std::clog <<
      "Starting xeus-clasp kernel...\n\n"
      "If you want to connect to this kernel from another client, you can use"
      " the " + file_name + " file."
      << std::endl;

    kernel.start();                       
  }
  else
  {
    std::clog << "File name is empty";
    xeus::xkernel kernel(xeus::get_user_name(),
                         std::move(interpreter),
                         std::move(hist),
                         nullptr,
                         xeus::make_xserver_shell_main,
                         xclasp::make_clasp_debugger);
    const auto& config = kernel.get_config();
    std::clog <<
      "Starting xeus-clasp kernel...\n\n"
      "If you want to connect to this kernel from another client, just copy"
      " and paste the following content inside of a `kernel.json` file. And then run for example:\n\n"
      "# jupyter console --existing kernel.json\n\n"
      "kernel.json\n```\n{\n"
      "    \"transport\": \"" + config.m_transport + "\",\n"
      "    \"ip\": \"" + config.m_ip + "\",\n"
      "    \"control_port\": " + config.m_control_port + ",\n"
      "    \"shell_port\": " + config.m_shell_port + ",\n"
      "    \"stdin_port\": " + config.m_stdin_port + ",\n"
      "    \"iopub_port\": " + config.m_iopub_port + ",\n"
      "    \"hb_port\": " + config.m_hb_port + ",\n"
      "    \"signature_scheme\": \"" + config.m_signature_scheme + "\",\n"
      "    \"key\": \"" + config.m_key + "\"\n"
      "}\n```\n";

    kernel.start();
  }

  return 0;
}