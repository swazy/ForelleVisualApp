//
//  InvalidSourceException.cpp
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 02.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#include <sstream>
#include "InvalidSourceException.h"

using namespace std;


InvalidSourceException::InvalidSourceException(){
    message = "Undefined Erro occured";
    source = '\0';
}

InvalidSourceException::InvalidSourceException( std::string message, const char source ){
    this->message = message;
    this->source = source;
    
}

string InvalidSourceException::getMessage() { 
    
    std::stringstream ss;
    ss <<  message << " Source=" <<source;
    
    return ss.str();
    
    
};

