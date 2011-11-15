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
    std::string m_message;

public:
    ExceptionGenerale(std::string message) throw();
    virtual ~ExceptionGenerale() throw();

    virtual const char* what() const throw();
};

class ParametreManquant: public ExceptionGenerale {
public:
    ParametreManquant(std::string message) throw();
    virtual ~ParametreManquant() throw();

    virtual const char* what() const throw();
};

#endif /* EXCEPTION_H_ */
