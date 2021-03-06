/*
 * Copyright (c) 2014, Jim Bosch
 * All rights reserved.
 *
 * mcpib is distributed under a simple BSD-like license;
 * see the LICENSE file that should be present in the root
 * of the source distribution.
 */

#include "mcpib/WrapperError.hpp"
#include "mcpib/internal/initializers.hpp"

namespace mcpib {

namespace {

static PyObject * WrapperError = nullptr;
static PyObject * UnknownCppException = nullptr;
static PyObject * SignatureError = nullptr;
static PyObject * FromPythonError = nullptr;
static PyObject * AmbiguousOverloadError = nullptr;
static PyObject * ToPythonError = nullptr;

void addException(
    PyPtr const & module, PyObject * & type,
    char const * name, char const * doc,
    PyObject * base=nullptr
) {
    type = PyErr_NewExceptionWithDoc(
        const_cast<char*>(name),
        const_cast<char*>(doc),
        base,
        nullptr  // dict
    );
    Py_INCREF(type);
    PyModule_AddObject(module.get(), name + 6, type);
}

} // anonymous

namespace internal {

void declareWrapperErrors(PyPtr const & module) {
    addException(module, WrapperError, "mcpib.WrapperError",
                 "Base class for all exceptions raised by mcpib wrapper code.");
    addException(module, UnknownCppException, "mcpib.UnknownCppException",
                 "Exception raised in Python when an unrecognized C++ exception is caught in C++.",
                 WrapperError);
    addException(module, SignatureError, "mcpib.SignatureError",
                 "Base class for exceptions raised when Python arguments do not match a C++ signature",
                 PyPtr::steal(PyTuple_Pack(2, WrapperError, PyExc_TypeError)).get());
    addException(module, FromPythonError, "mcpib.FromPythonError",
                 "Exception raised when a Python object cannot be converted to the required C++ type",
                 SignatureError);
    addException(module, AmbiguousOverloadError, "mcpib.AmbiguousOverloadError",
                 "Exception raised when there is no single C++ overload that best matches the Python types",
                 SignatureError);
    addException(module, ToPythonError, "mcpib.ToPythonError",
                 "Exception raised when a C++ object cannot be converted to Python",
                 PyPtr::steal(PyTuple_Pack(2, WrapperError, PyExc_TypeError)).get());
}

} // namespace internal

PythonException raiseWrapperError(std::string message) {
    return PythonException::raise(PyPtr::borrow(WrapperError), std::move(message));
}

PythonException raiseUnknownCppException(std::string message) {
    return PythonException::raise(PyPtr::borrow(UnknownCppException), std::move(message));
}

PythonException raiseSignatureError(std::string message) {
    return PythonException::raise(PyPtr::borrow(SignatureError), std::move(message));
}

PythonException raiseFromPythonError(std::string message) {
    return PythonException::raise(PyPtr::borrow(FromPythonError), std::move(message));
}

PythonException raiseAmbiguousOverloadError(std::string message) {
    return PythonException::raise(PyPtr::borrow(AmbiguousOverloadError), std::move(message));
}

PythonException raiseToPythonError(std::string message) {
    return PythonException::raise(PyPtr::borrow(ToPythonError), std::move(message));
}

} // namespace mcpib
