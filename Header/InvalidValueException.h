//
//  InvalidValueException.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 02.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
#ifndef InvalidValueException_H
#define InvalidValueException_H

using namespace std;

class InvalidValueException {
    
private:
    
    string message;
    int value;
    
public:
    InvalidValueException();
    InvalidValueException(string message, int value );
    
    string getMessage();
        
};
#endif