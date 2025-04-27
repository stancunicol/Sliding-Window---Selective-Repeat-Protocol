# Sliding Window - Selective Protocol
This project implements a simple simulation of the Selective Repeat protocol, a type of sliding window protocol used for reliable data transmission over networks.

# Project Overview
The application simulates how a sender transmits a series of packages to a receiver using the Selective Repeat protocol. It models concepts such as:

Sending and resending packages based on timeout.

Acknowledging received packages.

Sliding the transmission window dynamically as acknowledgments are received.

It uses random generation of transmission times and simulates possible retransmissions due to timeouts.

# Components
Package: Represents a data packet with an ID, acknowledgment status (ack), and a time value representing the simulated sending time.

Sender: Manages the sending of packages, maintaining a sliding window and handling retransmissions when necessary.

Receiver: Collects correctly received packages and maintains the reception buffer.

# Features
Randomized transmission time for each package.

Simulation of timeouts: if a package is not acknowledged within a specific time, it is resent.

Dynamic window movement once consecutive packages are acknowledged.

Visualization of the sending window, sent packages, and received packages.

Adjustable window size based on the number of packages.

# How it Works
Input: The user specifies the number of packages to send.

Window Size: Randomly generated based on the number of packages.

Sending Process:

Each package is assigned a random sending time.

Packages within the current window are sent.

Acknowledgments are simulated based on whether the sending time is less than the timeout threshold.

On timeout, packages are resent with a new random time.

Completion: The simulation ends once all packages are acknowledged.

# Technologies Used
C++ Standard Library (vector, iostream, random, thread, chrono, unordered_set)

C++17 standard features.

# Example

![image](https://github.com/user-attachments/assets/1858ee46-bc32-4f68-95b6-9968cedfb3ed)

![image](https://github.com/user-attachments/assets/9e6cc5bc-a311-4f6e-bb72-dd9305d0f946)

![image](https://github.com/user-attachments/assets/ee912579-3629-4b3c-916f-511c8aa2ca3d)
