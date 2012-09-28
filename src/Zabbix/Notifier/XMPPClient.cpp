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

    //
    // needed virtual methods
    //
    void XMPPClient::onConnect(){
        logger->info("Connecting");
    }

    bool XMPPClient::onTLSConnect( const gloox::CertInfo& info ){
        logger->info("Connecting with TLS");

        // TODO debug info on certificate

        // accept all certificates unchecked
        return true;
    }

    void XMPPClient::onDisconnect( gloox::ConnectionError e ){
        if (e != gloox::ConnectionError::ConnNoError){

            // TODO handle error and reconnect by error type
            logger->err("Disconnected with error");

            // reconnect
            XMPPClient::connect();
        }
        else {
            logger->notice("Disconnected");
        }
    }

    void XMPPClient::handleMessage(const gloox::Message& stanza, gloox::MessageSession* session){

        // handle if sender is authorized
        if (XMPPClient::check_authorized(stanza.from().bare())){
            logger->debug("Authorized user: " + stanza.from().bare());

            // TODO actually do something usefull

            // notify notify_users
            vector<string> users = XMPPClient::config->get_value_list("notify_users");
            if (!users.empty()){
                for (vector<string>::iterator it = users.begin(); it != users.end(); it++){
                    logger->debug("Notifying jid: " + *it);
                    gloox::Message::MessageType type = gloox::Message::MessageType::Chat;
                    gloox::JID jid(*it);
                    gloox::Message msg( type , jid, "hello from zabbix notifier");

                    XMPPClient::client->send(msg);
                }
            }
            else {
                logger->notice("Notify_users is empty, no notifications sent");
            }
        }
        else {
            logger->notice("Unauthorized user: " + stanza.from().bare());
        }
    }

    //
    // helpers
    //
    bool XMPPClient::check_authorized(string username){
        logger->debug("Checking authorization of " + username);

        vector<string> users = XMPPClient::config->get_value_list("authorized_users");

        // check against usernames in authorized_users without and with xmpp_server suffix
        for (vector<string>::iterator it = users.begin(); it != users.end(); it++){
            logger->debug("Checking against: " + *it);
            if (username.compare(*it) == 0)
                return true;

            logger->debug("Checking against: " + *it + "@" + XMPPClient::config->get_value("xmpp_server"));
            if (username.compare(*it + "@" + XMPPClient::config->get_value("xmpp_server")) == true)
                return true;
        }

        return false;
    }

    //
    // run parts
    //
    void XMPPClient::worker(){
        logger->debug("started worker");

        XMPPClient::connect();

        logger->debug("finished worker");
    }

    void XMPPClient::connect(){
        string jabber_id = XMPPClient::config->get_value("xmpp_username")
                + "@"
                + XMPPClient::config->get_value("xmpp_server")
                + "/"
                + XMPPClient::config->get_value("xmpp_resource");

        gloox::JID jid(jabber_id);
        XMPPClient::client = new gloox::Client( jid, XMPPClient::config->get_value("xmpp_password"));
        XMPPClient::client->registerMessageHandler(this);
        XMPPClient::client->registerConnectionListener(this);
        XMPPClient::client->connect();
    }

    // setup config and logging
    XMPPClient::XMPPClient(boost::shared_ptr<Config> config, boost::shared_ptr<Logger> logger) {

        XMPPClient::config = config;
        XMPPClient::logger = logger;
        XMPPClient::logger->set_level(XMPPClient::config->get_value("log_level"));

        XMPPClient::client = 0;
    }

    // destroy all
    XMPPClient::~XMPPClient() {
        // wait to log messages
        sleep(3);
        delete XMPPClient::client;
    }
}
}
