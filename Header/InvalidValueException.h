//
//  InvalidValueException.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 02.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

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