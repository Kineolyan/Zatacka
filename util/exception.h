/*
 * option.h
 *
 *  Created on: 8 nov. 2011
 *      Author: oliv
 */

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <string>
#include <stdexcept>

class ExceptionGenerale: public std::exception {
protected:
    std::string m_prefixe;
    std::string m_message;

public:
    ExceptionGenerale(std::string message, std::string prefixe = "") throw();
    virtual ~ExceptionGenerale() throw();

    virtual const char* what() const throw();
};

class InstanceManquante: public ExceptionGenerale {
public:
    InstanceManquante(std::string message) throw();
    virtual ~InstanceManquante() throw();
};

class TraceImpossible: public ExceptionGenerale {
public:
	TraceImpossible(std::string message) throw();
    virtual ~TraceImpossible() throw();
};

class HorsLimite: public ExceptionGenerale {
public:
	HorsLimite(std::string message) throw();
    virtual ~HorsLimite() throw();
};

#endif /* EXCEPTION_H_ */
