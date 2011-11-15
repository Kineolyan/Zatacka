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

ParametreManquant::ParametreManquant(string message) throw():
    ExceptionGenerale(message)
{}

ParametreManquant::~ParametreManquant() throw()
{}

const char* ParametreManquant::what() const throw() {
    string explication = "[Parametre manquant] ";
    explication+= m_message;
    return explication.c_str();
}
