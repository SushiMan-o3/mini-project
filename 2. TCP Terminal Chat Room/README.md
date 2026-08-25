# TCP Chat Room
## What is TCP Chat Room?
TCP Chat Room is a way for 


### What is a server?


## How it works?


## Why use a TCP Connection over a UDP?
TCP connections (connection based) are priortize reliability, where data arrives in order and missing data is resent. Often times TCP connections are used in chat rooms. 

UDP connections (connection less actually) are often faster and less reliable, as it sends data without guarenteeing it arrives. Often used in video calls. 

UDP have less latency than TCP, and is often best for real time data. 

**Eg.** Video calls (I found this kinda cool)
Video calls, you are essentially sending data to the server and the server is sendind data to you using a UDP connection as fast as they could so that we could minimize the lag. 

User A ── UDP ──> User B
User A <─ UDP ─── User B


## Implementation Notes


## Important Concepts
