//
//  InvalidValueException.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 02.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include <sstream>
#include "InvalidValueException.h"

using namespace std;


InvalidValueException::InvalidValueException(){
    message = "Undefined Erro occured";
}

InvalidValueException::InvalidValueException( std::string message, int value ){
    this->message = message;
    this->value = value;
    
}

 string InvalidValueException::getMessage() { 
    
    std::stringstream ss;
        ss <<  message << " Value=" <<value;
  
    return ss.str();
    
    
     };

