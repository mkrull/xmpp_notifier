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
#include <gloox/messagehandler.h>

using namespace std;
using namespace boost;

namespace Zabbix { namespace Notifier {

    typedef shared_ptr< asio::io_service > io_svc;
    typedef shared_ptr< asio::io_service::work > io_svc_work;
    typedef shared_ptr< asio::io_service::strand > io_svc_strand;

    class XMPPClient : public gloox::MessageHandler, gloox::ConnectionListener {
        public:
            XMPPClient(shared_ptr<Config> config, shared_ptr<Logger> logger);
            virtual ~XMPPClient();
            void run(io_svc io_service);
        private:
            shared_ptr<Config> config;
            shared_ptr<Logger> logger;
            void worker(io_svc io_service);
            gloox::Client* client;
            virtual void handleMessage(const gloox::Message& stanza, gloox::MessageSession* session = 0);
            virtual void onConnect();
            virtual void onTLSConnect( gloox::CertInfo& info );
            virtual void onDisconnect( gloox::ConnectionError e );
    };

}
}

#endif /* XMPPCLIENT_H_ */
