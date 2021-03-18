#include  "server.h"
#include "client.h"
std::string fileName;
std::string gurl;


int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        fileName = std::string(argv[1]);
        std::string url("http://127.0.0.1:8000/api/upload");
        gurl = url;
        startClient(url);
        return 0;
    }
    else
    {
        std::cout << "Start to server.........." << std::endl;
        std::string url("http://0.0.0.0:8000");
        startServer(url);
        return 0;
    }

}

