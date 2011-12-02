//
//  InvalidSourceException.h
//  ForelleVisualApp
//
//  Created by Patrick Fürst on 02.12.11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

using namespace std;

class InvalidSourceException {
    
private:
    
    string message;
    char source;
    
public:
    InvalidSourceException();
    InvalidSourceException(string message, const char source );
    
    string getMessage();
    
};