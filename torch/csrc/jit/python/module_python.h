#pragma once
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <torch/csrc/jit/api/module.h>
#include <torch/csrc/utils/pybind.h>

namespace py = pybind11;

namespace torch {
namespace jit {

inline c10::optional<Module> as_module(py::handle obj) {
  if (py::isinstance(
          obj, py::module::import("torch.jit").attr("ScriptModule"))) {
    return py::cast<Module>(obj.attr("_c"));
  }
  return c10::nullopt;
}

inline c10::optional<Object> as_object(py::handle obj) {
  if (py::isinstance(obj, py::module::import("torch").attr("ScriptObject"))) {
    return py::cast<Object>(obj);
  }

  if (py::isinstance(
          obj, py::module::import("torch.jit").attr("RecursiveScriptClass"))) {
    return py::cast<Object>(obj.attr("_c"));
  }
  return c10::nullopt;
}

} // namespace jit
} // namespace torch
