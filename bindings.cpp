#define OPPAI_IMPLEMENTATION
#include <pybind11/pybind11.h>
#include "oppai.c"

#include <sstream>

namespace py = pybind11;

class OppaiWrapper
{
public:
    ezpp_t ez;

    OppaiWrapper() {}

    OppaiWrapper* enter() {
        ez = ezpp_new();

        return this;
    }

    void exit(const py::object &type, const py::object &value, const py::object &traceback) {
        ezpp_free(ez);
    }

    void configure(int mode, float acc, int mods, int combo, int nmiss)
    {
        if (!ez) {
            throw py::value_error("OppaiWrapper not initialized");
        }

        // clobber so these orders matter
        ezpp_set_mode(ez, mode);
        ezpp_set_accuracy_percent(ez, acc);
        ezpp_set_mods(ez, mods);
        ezpp_set_combo(ez, combo);
        ezpp_set_nmiss(ez, nmiss);
    }

    void calculate(char* map_path)
    {
        ezpp(ez, map_path);
    }

    void calculate_data(std::string map_data)
    {
        ezpp_data(ez, map_data.c_str(), map_data.size());
    }

    float get_pp() {
        return ezpp_pp(ez);
    }

    float get_sr() {
        return ezpp_stars(ez);
    }
};

PYBIND11_MODULE(oppai, handle)
{
    handle.doc() = "Python wrapper around oppai-ng";

    py::class_<OppaiWrapper>(handle, "OppaiWrapper")
        .def(py::init<>())
        .def("__enter__", &OppaiWrapper::enter)
        .def("__exit__", &OppaiWrapper::exit)
        .def("configure", &OppaiWrapper::configure, py::arg("mode"), py::arg("acc"), py::arg("mods"), py::arg("combo"), py::arg("nmiss"))
        .def("calculate", &OppaiWrapper::calculate)
        .def("calculate_data", &OppaiWrapper::calculate_data)
        .def("get_pp", &OppaiWrapper::get_pp)
        .def("get_sr", &OppaiWrapper::get_sr);
}
