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

    bool XMPPClient::onTLSConnect( const gloox::CertInfo& info ){
        // accept all certificates unchecked
        return true;
    }

    void XMPPClient::handleMessage(const gloox::Message& stanza, gloox::MessageSession* session){
        gloox::Message::MessageType type = gloox::Message::MessageType::Chat;
        gloox::Message msg( type , stanza.from(), "hello from zabbix notifier");

        XMPPClient::client->send(msg);
    }

    void XMPPClient::run(){

    }

    void XMPPClient::onDisconnect( gloox::ConnectionError e ){

    }

    void XMPPClient::onConnect(){

    }

    void XMPPClient::worker(){
        logger->debug("started worker");

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

    XMPPClient::XMPPClient(boost::shared_ptr<Config> config, boost::shared_ptr<Logger> logger) {

        XMPPClient::config = config;
        XMPPClient::logger = logger;
        XMPPClient::logger->set_level(XMPPClient::config->get_value("log_level"));

        XMPPClient::client = 0;
    }

    XMPPClient::~XMPPClient() {
    }
}
}
