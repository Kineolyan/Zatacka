#include "exception.h"

using namespace std;

ExceptionGenerale::ExceptionGenerale(string message) throw():
    m_message(message)
{}

ExceptionGenerale::~ExceptionGenerale() throw()
{}

const char* ExceptionGenerale::what() const throw() {
    return m_message.c_str();
}

InstanceManquante::InstanceManquante(string message) throw():
    ExceptionGenerale(message)
{}

InstanceManquante::~InstanceManquante() throw()
{}

const char* InstanceManquante::what() const throw() {
    string explication = "[Instance manquante] ";
    explication+= m_message;
    return explication.c_str();
}

TraceImpossible::TraceImpossible(string message) throw():
    ExceptionGenerale(message)
{}

TraceImpossible::~TraceImpossible() throw()
{}

const char* TraceImpossible::what() const throw() {
    string explication = "[Trace impossible] ";
    explication+= m_message;
    return explication.c_str();
}
