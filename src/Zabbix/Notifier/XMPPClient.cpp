/*
 * XMPPClient.cpp
 *
 *  Created on: 27.09.2012
 *      Author: mak
 */

#include "XMPPClient.h"

using namespace std;
using namespace boost;
using namespace Zabbix::Notifier;

namespace Zabbix { namespace Notifier {

    virtual void handleMessage(const gloox::Message& stanza, gloox::MessageSession* session = 0){
        gloox::Message msg( stanza.m_from(), "hello from zabbix notifier");
        XMPPClient::client->send(msg);
    }

    void XMPPClient::run(io_svc io_service){
        thread_group workers;
        workers.create_thread(bind(&worker, io_service));
    }

    void XMPPClient::worker(io_svc io_service){
        logger->debug("started worker");

        try {
            system::error_code e;
            io_service->run(e);

            if (e){
                logger->err(e.message());
            }
        }
        catch (std::exception& ec){
            logger->err(ec.what());
        }

        string jabber_id = XMPPClient::config->get_value("xmpp_username")
                + "@"
                + XMPPClient::config->get_value("xmpp_server")
                + "/"
                + XMPPClient::config->get_value("xmpp_resource");

        gloox::JID jid(jabber_id);
        XMPPClient::client = new gloox::Client( jid, XMPPClient::config->get_value("xmpp_password"));
        XMPPClient::client->registerMessageHandler(this);
        XMPPClient::client->connect();
    }

    XMPPClient::XMPPClient(shared_ptr<Config> config, shared_ptr<Logger> logger) {
        io_svc io_service( new asio::io_service );
        io_svc_work work( new asio::io_service::work( *io_service) );
        io_svc_strand strand( new asio::io_service::strand( *io_service ) );

        XMPPClient::config = config;
        XMPPClient::logger = logger;
        XMPPClient::logger->set_level(XMPPClient::config->get_value("log_level"));

        XMPPClient::client = 0;
    }

    XMPPClient::~XMPPClient() {
    }
}
}
