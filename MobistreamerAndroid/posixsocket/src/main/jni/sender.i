/* File : example.i */
%module sender

%apply (char *STRING, size_t LENGTH) { (char *data, size_t len) }

%{
#include "SenderSocket.h"
%}

/* Let's just grab the original header file here */
%include "SenderSocket.h"
