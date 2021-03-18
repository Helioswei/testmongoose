#ifndef CLIENT_H
#define CLIENT_H
#include "basic.h"
extern  std::string fileName;
extern  std::string gurl;

static void clientFn(struct mg_connection* c, int ev, void* ev_data, void* fn_data)
{
    if (ev == MG_EV_CONNECT)
    {
        //upload file
        size_t fileSize = mg_file_size(fileName.c_str());
        char* fileData = mg_file_read(fileName.c_str());
        std::string boundary = NETWORKBOUNDRY;
        char tmp[256];
        snprintf(tmp, sizeof(tmp),
                 "%s\r\n"
                 "Content-Disposition: form-data; name=file; filename=%s\r\n"
                 "Content-Type: %s\r\n"
                 "\r\n",
                 boundary.c_str(), fileName.c_str(), NETWORKAPPLICATION);

        struct mg_str host = mg_url_host(gurl.c_str());
        std::string hostStr = std::string(host.ptr, host.len);
        unsigned long length = static_cast<unsigned long>(fileSize + strlen(tmp) + boundary.length() + 2);

        //send header
        mg_printf(c,
                  "POST %s?name=%s&offset=%d HTTP/1.1\r\n"
                  "Host: %s\r\n"
                  "Content-Length: %d\r\n"
                  "Content-Type: %s; boundary=%s\r\n"
                  "\r\n"
                  , mg_url_uri(gurl.c_str()), fileName.c_str(), fileSize
                  , hostStr.c_str()
                  , length
                  , NETWORKAPPLICATION);
        mg_printf(c, "%s", tmp);
        //send data
        mg_send(c, fileData, fileSize);
        mg_printf(c, "%s--\r\n", boundary.c_str());
        free(fileData);
    }
    else if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message* hm = static_cast<struct mg_http_message*>(ev_data);
        std::string response(hm->message.ptr, hm->message.len);
        std::cout << "response: " << response << std::endl;
        c->is_closing = 1;
        *static_cast<bool*>(fn_data) = true;
    }
    else if (ev == MG_EV_ERROR)
    {
        *static_cast<bool*>(fn_data) = true;
    }
}

void startClient(const std::string& url = "")
{
    struct mg_mgr mgr;
    bool done = false;
    mg_mgr_init(&mgr);
    mg_http_connect(&mgr, url.c_str(), clientFn, &done);

    while (!done) mg_mgr_poll(&mgr, 1000);

    mg_mgr_free(&mgr);
}















#endif //CLIENT_H
