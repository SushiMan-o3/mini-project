#include <iostream>
#include <cstring>

#include <vector>

using namespace std;

// vector with all connections so you can broadcast to them
// ipv4 for socket + set up

#define PORT 8080

void broadcast(){

}

void messageHandler(){

}

int main(){
    // bind ip to port

    // listen for connections (loop) -> accept connection (use a mutex during this to lock up the vector)
    // create a thread and start listening for messages from client -> broad cast to all other clients

    // close connection, clean up maybe?
    return 0;
}