/*
 * Copyright (c) 2014, Jim Bosch
 * All rights reserved.
 *
 * mcpib is distributed under a simple BSD-like license;
 * see the LICENSE file that should be present in the root
 * of the source distribution.
 */
#ifndef MCPIB_ToPythonTraits_hpp_INCLUDED
#define MCPIB_ToPythonTraits_hpp_INCLUDED

#include "mcpib/PyPtr.hpp"
#include "mcpib/TypeInfo.hpp"
#include "mcpib/TypeRegistration.hpp"

#include <memory>

namespace mcpib {

template <typename T>
class ToPythonTraits {
public:

    static TypeInfo getTypeInfo() { return makeTypeInfo<T>(); }

    static PyPtr convert(TypeRegistration const & registration, T v) {
        return registration.getValueToPython().convert(&v);
    }

};

template <typename U>
class ToPythonTraits<U const> {
public:

    static TypeInfo getTypeInfo() { return makeTypeInfo<U>(); }

    static PyPtr convert(TypeRegistration const & registration, U v) {
        return registration.getValueToPython().convert(&v);
    }

};

template <typename U>
class ToPythonTraits<U *> {
public:

    static TypeInfo getTypeInfo() { return makeTypeInfo<U>(); }

    static PyPtr convert(TypeRegistration const & registration, U * v) {
        return registration.getPointerToPython().convert(v);
    }

};

template <typename U>
class ToPythonTraits<U &> {
public:

    static TypeInfo getTypeInfo() { return makeTypeInfo<U>(); }

    static PyPtr convert(TypeRegistration const & registration, U & v) {
        return registration.getRefToPython().convert(&v);
    }

};

template <typename U>
class ToPythonTraits<U const *> {
public:

    static TypeInfo getTypeInfo() { return makeTypeInfo<U>(); }

    static PyPtr convert(TypeRegistration const & registration, U const * v) {
        return registration.getConstPointerToPython().convert(const_cast<U*>(v));
    }

};

template <typename U>
class ToPythonTraits<U const &> {
public:

    static TypeInfo getTypeInfo() { return makeTypeInfo<U>(); }

    static PyPtr convert(TypeRegistration const & registration, U const & v) {
        return registration.getConstRefToPython().convert(const_cast<U*>(&v));
    }

};

template <typename U>
class ToPythonTraits<U &&> {
public:

    static TypeInfo getTypeInfo() { return makeTypeInfo<U>(); }

    static PyPtr convert(TypeRegistration const & registration, U && v) {
        return registration.getValueToPython().convert(std::move(v));
    }

};

template <typename T>
PyPtr TypeRegistration::toPython(T && v) const {
    return ToPythonTraits<T>::convert(*this, std::forward<T>(v));
}

template <typename T>
PyPtr TypeRegistry::toPython(T && v) const {
    return this->_lookupToPython(ToPythonTraits<T>::getTypeInfo())->toPython(std::forward<T>(v));
}

} // namespace mcpib

#endif // !MCPIB_ToPythonTraits_hpp_INCLUDED
