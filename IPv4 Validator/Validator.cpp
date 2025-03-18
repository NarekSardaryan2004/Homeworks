#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <sstream>

constexpr size_t TOTAL_IPS = 1UL << 20;

std::string intToIp(u_int32_t ip) {
    return std::to_string((ip >> 24) & 0xFF) + "." +
           std::to_string((ip >> 16) & 0xFF) + "." +
           std::to_string((ip >> 8) & 0xFF) + "." +
           std::to_string(ip & 0xFF);
}

u_int32_t IPToint(const std::string& ip) {
    u_int32_t a, b, c, d;
    char dot;
    std::istringstream iss(ip);
    if (!(iss >> a >> dot >> b >> dot >> c >> dot >> d) || dot != '.') {
        throw std::invalid_argument("Invalid IP format");
    }
    return (a << 24) | (b << 16) | (c << 8) | d;
}

u_int32_t generateRandomIPInt() {
    return rand() % TOTAL_IPS;
}

int main()
{
    srand(time(0));
    std::ofstream file("random_ips.txt");
    
    if (!file) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    // for (int i = 0; i < 10; ++i) {
    //     std::string ip;
    //     std::cout << "write ip: ";
    //     std::cin >> ip;
    //     file << ip << std::endl;
    // }

    for (int i = 0; i < 30000; ++i) {
        u_int32_t ip = generateRandomIPInt();
        file << intToIp(ip) << std::endl;
    }

    file.close();

    std::ifstream inputFile("random_ips.txt");
    if (!inputFile) {
        std::cerr << "Error opening file for reading!" << std::endl;
        return 1;
    }

    std::bitset<TOTAL_IPS> uniqueIPs;
    std::string ip;
    size_t uniqueCount = 0;

    while(getline(inputFile, ip)) {
        u_int32_t ipInt = IPToint(ip) % TOTAL_IPS;
        if (!uniqueIPs.test(ipInt)) {
            uniqueIPs.set(ipInt);
            ++uniqueCount;
        }
    }
    inputFile.close();

    std::cout << "Unique IP addresses count: " << uniqueCount << std::endl;

    return 0;
}
