
#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

#include "xeus/xkernel.hpp"
#include "xeus/xkernel_configuration.hpp"
#include "xeus/xserver.hpp"

#include "xeus-clasp/xinterpreter.hpp"
#include "xdebugger.hpp"

#include "xwidgets/xbutton.hpp"
#include "xwidgets/xnumeral.hpp"

#include "xwidgets/xnumber.hpp"
#include "xwidgets/xslider.hpp"

#include "clasp/clasp.h"


std::string extract_filename(int& argc, const char* argv[])
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


int start_interpreter(const std::string& file_name)
{
    printf("%s:%d:%s  file_name = %s\n", __FILE__, __LINE__, __FUNCTION__, file_name.c_str());
    const char* argv[] = {"xclasp"};
    int argc = 1;
    //    std::string file_name = extract_filename(argc, argv);
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
            std::clog << "Starting xeus-clasp kernel...\n\n"
                      << "If you want to connect to this kernel from another client, just copy"
                      << " and paste the following content inside of a `kernel.json` file. And then run for example:\n\n"
                      << "# jupyter console --existing kernel.json\n\n"
                      << "kernel.json\n```\n{\n"
                      << "    \"transport\": \"" << config.m_transport << "\",\n"
                      << "    \"ip\": \"" << config.m_ip << "\",\n"
                      << "    \"control_port\": " << config.m_control_port << ",\n"
                      << "    \"shell_port\": " << config.m_shell_port << ",\n"
                      << "    \"stdin_port\": " << config.m_stdin_port << ",\n"
                      << "    \"iopub_port\": " << config.m_iopub_port << ",\n"
                      << "    \"hb_port\": " << config.m_hb_port << ",\n"
                      << "    \"signature_scheme\": \"" << config.m_signature_scheme << "\",\n"
                      << "    \"key\": \"" << config.m_key << "\"\n"
                      << "}\n```\n";

            kernel.start();
        }

    return 0;
}


struct Foo {
    int _x;
    int _y;
    int _z;
    Foo() {};
    void setFoo(int x, int y, int z) {
        this->_x = x;
        this->_y = y;
        this->_z = z;
    }
    core::List_sp getFoo() {
        return core::Cons_O::createList(core::make_fixnum(this->_x),
                                        core::make_fixnum(this->_y),
                                        core::make_fixnum(this->_z));
    }
};


namespace xw
{
    
struct DoubleSlider : xslider<double> {
    template <>
    struct xnumber_traits<double>
    {
        using value_type = double;
    };
  
};

};

void startup()
{
    printf("%s:%d Starting up expose with clbind\n", __FILE__, __LINE__ );
    using namespace clbind;
    package("XCLASP") [
                       def("start-interpreter",&start_interpreter)
                       ,
                       class_<Foo>("Foo",no_default_constructor)
                       .         def("setFoo",&Foo::setFoo)
                       .         def("getFoo",&Foo::getFoo)
                       ,
                       class_<xw::xbutton<bool>>("Button",no_default_constructor)
                       ,
                       class_<xw::DoubleSlider>("DoubleSlider",no_default_constructor)
                       ];
}

CLASP_REGISTER_STARTUP(startup);

