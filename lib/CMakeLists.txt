add_library(mcpib SHARED
  src/detail/FromPythonImpl.cpp
  src/internal/format.cc
  src/Callable.cpp
  src/CallableOverload.cpp
  src/Class.cpp
  src/Module.cpp
  src/PyPtr.cpp
  src/PythonException.cpp
  src/TypeInfo.cpp
  src/TypeRegistration.cpp
  src/TypeRegistry.cpp
  src/WrapperError.cpp
  )
