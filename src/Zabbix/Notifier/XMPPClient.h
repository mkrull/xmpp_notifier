/*
 * XMPPClient.h
 *
 *  Created on: 27.09.2012
 *      Author: mak
 */

#ifndef XMPPCLIENT_H_
#define XMPPCLIENT_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include "Config.h"
#include "Logger.h"

using namespace std;
using namespace boost;

namespace Zabbix { namespace Notifier {

    typedef boost::shared_ptr< asio::io_service > io_svc;
    typedef boost::shared_ptr< asio::io_service::work > io_svc_work;
    typedef boost::shared_ptr< asio::io_service::strand > io_svc_strand;

    class XMPPClient : public gloox::MessageHandler, gloox::ConnectionListener {
        public:
            XMPPClient(boost::shared_ptr<Config> config, boost::shared_ptr<Logger> logger);
            virtual ~XMPPClient();
            void worker();
        private:
            boost::shared_ptr<Config> config;
            boost::shared_ptr<Logger> logger;
            gloox::Client* client;
            virtual void handleMessage(const gloox::Message& stanza, gloox::MessageSession* session = 0);
            virtual void onConnect();
            virtual bool onTLSConnect( const gloox::CertInfo& info );
            virtual void onDisconnect( gloox::ConnectionError e );
            bool check_authorized(string username);
            void connect();
    };

}
}

#endif /* XMPPCLIENT_H_ */
