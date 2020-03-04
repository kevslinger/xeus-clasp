

#include "nlohmann/json.hpp"

#include "xeus/xcomm.hpp"
#include "xeus/xinterpreter.hpp"



namespace nl=nlohmann;

namespace xclasp
{
  /*********************
   * xcomm declaration *
   ********************/

  class xcomm
  {
  public:

    using cpp_callback_type = std::function<void(const xeus::xmessage&)>;
    using zmq_buffers_type = std::vector<zmq::message_t>;
    /* TODO: Implement me */
  };

  xcomm::xcomm(xeus::xcomm&& comm)
    : m_comm(std::move(comm))
  {
  }

  /************************
   * xcomm implementation *
   ***********************/

  /*xcomm::xcomm(const py::args& /*args, const py::kwargs& kwargs)
        : m_comm(target(kwargs), id(kwargs))
    {
        m_comm.open(
            kwargs.attr("get")("metadata", py::dict()),
            kwargs.attr("get")("data", py::dict()),
            pylist_to_zmq_buffers(kwargs.attr("get")("buffers", py::list()))
        );
        }*/

  
  xcomm::~xcomm()
  { 
  }

  std::string xcomm::comm_id() const
  {
    return m_comm.id();
  }

  bool xcomm::kernel() const
  {
    return true;
  }

  void xcomm::close()
  {
    /* TODO: Implement me */
  }

  void xcomm::send()
  {
    /* TODO: Implement me */
  }

  void xcomm::on_msg()
  {
    /* TODO: Implement me */
  }

  void xcomm::on_close()
  {
    /* TODO: Implement me */
  }

  xeus::xtarget* xcomm::target() const
  {
    /* TODO: Impelemnt me */
  }

  xeus::xguid xcomm::id() const
  {
    /* TODO: Implement me */
  }

  auto xcomm::cpp_callback() const -> cpp_callback_type
  {
    /* TODO: Implement me */
  }

  void register_target(){
    /* TODO: Implement me */
  }

  namespace detail
  {
    struct xmock_object
    {
    };
  }

  struct xmock_kernel
  {
      xmock_kernel() {}
      /* TODO: Implement me */
  };

  /* TODO: Implement get_kernel_module_impl 
    py::module get_kernel_module_impl()
    {
        py::module kernel_module = py::module("kernel");

        py::class_<detail::xmock_object> _Mock(kernel_module, "_Mock");
        py::class_<xcomm>(kernel_module, "Comm")
            .def(py::init<py::args, py::kwargs>())
            .def("close", &xcomm::close)
            .def("send", &xcomm::send)
            .def("on_msg", &xcomm::on_msg)
            .def("on_close", &xcomm::on_close)
            .def_property_readonly("comm_id", &xcomm::comm_id)
            .def_property_readonly("kernel", &xcomm::kernel);
        py::class_<xmock_kernel>(kernel_module, "mock_kernel", py::dynamic_attr())
            .def(py::init<>())
            .def_property_readonly("_parent_header", &xmock_kernel::parent_header);

        kernel_module.def("register_target", &register_target);
        kernel_module.def("register_post_execute", [](py::args, py::kwargs) {});
        kernel_module.def("enable_gui", [](py::args, py::kwargs) {});
        kernel_module.def("showtraceback", [](py::args, py::kwargs) {});

        kernel_module.def("get_ipython", [kernel_module]() {
            py::object kernel = kernel_module.attr("mock_kernel")();
            py::object comm_manager = kernel_module.attr("_Mock");
            comm_manager.attr("register_target") = kernel_module.attr("register_target");
            kernel.attr("comm_manager") = comm_manager;

            py::object xeus_python = kernel_module.attr("_Mock");
            xeus_python.attr("register_post_execute") = kernel_module.attr("register_post_execute");
            xeus_python.attr("enable_gui") = kernel_module.attr("enable_gui");
            xeus_python.attr("showtraceback") = kernel_module.attr("showtraceback");
            xeus_python.attr("kernel") = kernel;
            return xeus_python;
        });

        return kernel_module;
    }

    py::module get_kernel_module()
    {
        static py::module kernel_module = get_kernel_module_impl();
        return kernel_module;
    }
    } */
  
}
