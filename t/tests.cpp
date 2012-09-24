/*
 * tests.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include "../src/Notifier/Config.h"
#include <gtest/gtest.h>

using namespace std;
using namespace Zabbix::Notifier;

TEST(Basic, ConfigFile){

        Config config = Config::Instance("t/test.lua");

        string user = config.get_value("user");
        EXPECT_STREQ("zabbix_notifier", user.c_str());

        string group = config.get_value("group");
        EXPECT_STREQ("zabbix_notifier", group.c_str());

        string listen = config.get_value("listen");
        EXPECT_STREQ("localhost:4242", listen.c_str());

        string log_level = config.get_value("log_level");
        EXPECT_STREQ("debug", log_level.c_str());

        string xmpp_username = config.get_value("xmpp_username");
        EXPECT_STREQ("zabbix", xmpp_username.c_str());

        string xmpp_password = config.get_value("xmpp_password");
        EXPECT_STREQ("test123", xmpp_password.c_str());

        string xmpp_server = config.get_value("xmpp_server");
        EXPECT_STREQ("localhost", xmpp_server.c_str());

        vector<string> authorized_users = config.get_value_list("authorized_users");
        EXPECT_STREQ("user1", (authorized_users[0]).c_str());
        EXPECT_STREQ("user2", (authorized_users[1]).c_str());
        EXPECT_STREQ("user3", (authorized_users[2]).c_str());

}

TEST(Basic, SingletonConfig){

        Config config = Config::Instance();

        string user = config.get_value("user");
        EXPECT_STREQ("zabbix_notifier", user.c_str());

        string group = config.get_value("group");
        EXPECT_STREQ("zabbix_notifier", group.c_str());

        string listen = config.get_value("listen");
        EXPECT_STREQ("localhost:4242", listen.c_str());

        string log_level = config.get_value("log_level");
        EXPECT_STREQ("debug", log_level.c_str());

        string xmpp_username = config.get_value("xmpp_username");
        EXPECT_STREQ("zabbix", xmpp_username.c_str());

        string xmpp_password = config.get_value("xmpp_password");
        EXPECT_STREQ("test123", xmpp_password.c_str());

        string xmpp_server = config.get_value("xmpp_server");
        EXPECT_STREQ("localhost", xmpp_server.c_str());

        vector<string> authorized_users = config.get_value_list("authorized_users");
        EXPECT_STREQ("user1", (authorized_users[0]).c_str());
        EXPECT_STREQ("user2", (authorized_users[1]).c_str());
        EXPECT_STREQ("user3", (authorized_users[2]).c_str());

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}



