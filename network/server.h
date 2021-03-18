#ifndef SERVER_H
#define SERVER_H
#include "basic.h"

static void serverFn(struct mg_connection* c, int ev, void* ev_data, void* fn_data)
{
    if (ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message* hm = static_cast<struct mg_http_message*>(ev_data);

        //one function  deal with boundary by myself
        if (mg_http_match_uri(hm, "/api/upload"))
        {
            char* crlf = NETWORKAPPLICATION"\r\n\r\n";
            char* boudary = NETWORKBOUNDRY"--";
            char name[200] = "";
            mg_http_get_var(&hm->query, "name", name, sizeof(name));
            char* crlfRet = strstr(const_cast<char*>(hm->body.ptr), crlf);
            char* boundaryRet = strstr(const_cast<char*>(hm->body.ptr), boudary);

            if (crlfRet != nullptr && boundaryRet != nullptr)
            {
                FILE* fp;

                if ((fp = fopen(name, "wb")) == nullptr)
                {
                    mg_http_reply(c, 400, "", "fopen file %s error", name);
                }
                else
                {

                    size_t len = (boundaryRet != nullptr) ? boundaryRet - crlfRet  - strlen(crlf) : strlen(crlfRet) - strlen(crlf);
                    fwrite(&crlfRet[strlen(crlf)], 1, len, fp);
                    fclose(fp);
                    mg_http_reply(c, 200, "", "");
                }
            }
            else
            {
                if (crlfRet == nullptr)
                {
                    mg_http_reply(c, 500, "", "Can't not find CRLF");
                }
                else if (boundaryRet == nullptr)
                {
                    mg_http_reply(c, 500, "", "Can't not find boundaryRet");
                }
            }

            //other function to use mongoose
            //mg_http_upload(c, hm, ".");
        }
        else
        {
            struct mg_http_serve_opts opts = {.root_dir = "webroot", nullptr};
            mg_http_serve_dir(c, static_cast<struct mg_http_message*>(ev_data), &opts);
        }
    }



}

void startServer(const std::string& url = "")
{
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, url.c_str(), serverFn, nullptr);

    for (;;)mg_mgr_poll(&mgr, 1000);

    mg_mgr_free(&mgr);
}




#endif
