#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include "library.h"
std::vector<std::string> BUFFER;
void processing()
{
    while (true)
    {
        std::string b = BUFFER;
        BUFFER.clear();
        std::cout << b;
        int res=sum(b);
        if (send(sock, res, sizeof(res), 0) == -1)
        {

            close(sock);
            return -1;
        }
    }
}

void inputstr()
{
    while (true)
    {
        std::string a;
        std::cout << "Введи в меня дядя";
        std::getline(std::cin, a);
        auto result = std::find_if(a.begin(), a.end(), [](char ch)
                                   { return !std::isdigit(ch); });
        if (result != end(a))
        {
            std::cerr << "Строка должна состоять только из цифр";
        }
        else if (a.size() > 64)
        {
            std::cerr << "Строка не должна превышать 64 символа";
        }
        sort_elem(a);
        BUFFER.push_back(a);
    }
}
int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)

    {
        std::cerr << "Ошибка возврата дескриптора гнезда" << std::endl;

        return -1;
    }
    struct sockaddr_in servAddr;
    servAddr.sin_family = inet_addr("127.0.0.1");
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(8080);
    if (bind(sock, (const struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
    {

        std::cerr << "не получилось связать сокет с адресом или портом" << std::endl;
        close(sock);
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
    {
        std::cerr << "не получилось connect" << std::endl;
        close(sock);
        return -1;
    }
    std::thread t1(inputstr);
    std::thread t2();
    t1.join();
    t2.join();
    close(sock);
    return 0;
}