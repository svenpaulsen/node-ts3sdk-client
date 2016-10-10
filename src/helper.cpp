/**
 * TeamSpeak 3 SDK Client Addon for Node.js
 *
 * Copyright (c) Sven Paulsen. All rights reserved.
 */

#include "helper.h"

/**
 * Creates a random return code for later use in TeamSpeak 3 SDK functions.
 */
char* Helper::createReturnCode(int length)
{
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char*       random    = NULL;
    
    if(length)
    {
        random = (char*) malloc(sizeof(char)*(length +1));
        
        if(random)
        {
            for (int n = 0; n < length; n++)
            {
                int key   = rand() % (int)(sizeof(charset) -1);
                random[n] = charset[key];
            }
            
            random[length] = '\0';
        }
    }
    
    return random;
}
