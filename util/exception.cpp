#include "exception.h"

using namespace std;

ExceptionGenerale::ExceptionGenerale(string message, string prefixe) throw():
    m_prefixe(prefixe), m_message(message)
{}

ExceptionGenerale::~ExceptionGenerale() throw()
{}

const char* ExceptionGenerale::what() const throw() {
    string message = "[";
    message+= m_prefixe + "] " + m_message;
    return message.c_str();
}

InstanceManquante::InstanceManquante(string message) throw():
    ExceptionGenerale(message, "Instance manquante")
{}

InstanceManquante::~InstanceManquante() throw()
{}

TraceImpossible::TraceImpossible(string message) throw():
    ExceptionGenerale(message, "Trace impossible")
{}

TraceImpossible::~TraceImpossible() throw()
{}

HorsLimite::HorsLimite(string message) throw():
    ExceptionGenerale(message, "Hors limite")
{}

HorsLimite::~HorsLimite() throw()
{}
