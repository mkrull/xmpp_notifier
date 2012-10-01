/*
 * tests.cpp
 *
 *  Created on: 21.09.2012
 *      Author: mak
 */

#include "../src/Notifier/Config.h"
#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

using namespace std;
using namespace Notifier;

TEST(Basic, ConfigFile){

        Config* config = new Config("t/test.lua");

        string user = config->get_value("user");
        EXPECT_STREQ("xmpp_notifier", user.c_str());

        string group = config->get_value("group");
        EXPECT_STREQ("xmpp_notifier", group.c_str());

        string log_level = config->get_value("log_level");
        EXPECT_STREQ("DEBUG", log_level.c_str());

        string xmpp_username = config->get_value("xmpp_username");
        EXPECT_STREQ("notifier", xmpp_username.c_str());

        string xmpp_password = config->get_value("xmpp_password");
        EXPECT_STREQ("test123", xmpp_password.c_str());

        string xmpp_server = config->get_value("xmpp_server");
        EXPECT_STREQ("localhost", xmpp_server.c_str());

        string xmpp_server_port = config->get_value("xmpp_server_port");
        EXPECT_STREQ("5223", xmpp_server_port.c_str());

        string xmpp_resource = config->get_value("xmpp_resource");
        EXPECT_STREQ("bot_at_work", xmpp_resource.c_str());

        vector<string> authorized_users = config->get_value_list("authorized_users");
        EXPECT_STREQ("user1", (authorized_users[0]).c_str());
        EXPECT_STREQ("user2", (authorized_users[1]).c_str());
        EXPECT_STREQ("user3", (authorized_users[2]).c_str());

        map<string, int> tasks = config->get_value_map("tasks");
        EXPECT_EQ(10, tasks["test"]);
        EXPECT_EQ(3, tasks["more"]);
        EXPECT_EQ(300, tasks["evenmore"]);

        delete config;

}

TEST(Basic, Shared){

        boost::shared_ptr<Config> config( new Config("t/test.lua") );

        string user = config->get_value("user");
        EXPECT_STREQ("xmpp_notifier", user.c_str());

        string group = config->get_value("group");
        EXPECT_STREQ("xmpp_notifier", group.c_str());

        string log_level = config->get_value("log_level");
        EXPECT_STREQ("DEBUG", log_level.c_str());

        string xmpp_username = config->get_value("xmpp_username");
        EXPECT_STREQ("notifier", xmpp_username.c_str());

        string xmpp_password = config->get_value("xmpp_password");
        EXPECT_STREQ("test123", xmpp_password.c_str());

        string xmpp_server = config->get_value("xmpp_server");
        EXPECT_STREQ("localhost", xmpp_server.c_str());

        string xmpp_server_port = config->get_value("xmpp_server_port");
        EXPECT_STREQ("5223", xmpp_server_port.c_str());

        string xmpp_resource = config->get_value("xmpp_resource");
        EXPECT_STREQ("bot_at_work", xmpp_resource.c_str());

        vector<string> authorized_users = config->get_value_list("authorized_users");
        EXPECT_STREQ("user1", (authorized_users[0]).c_str());
        EXPECT_STREQ("user2", (authorized_users[1]).c_str());
        EXPECT_STREQ("user3", (authorized_users[2]).c_str());

        map<string, int> tasks = config->get_value_map("tasks");
        EXPECT_EQ(10, tasks["test"]);
        EXPECT_EQ(3, tasks["more"]);
        EXPECT_EQ(300, tasks["evenmore"]);

}

TEST(Basic, ExternalLogger){

        boost::shared_ptr<Logger> logger( new Logger() );
        boost::shared_ptr<Config> config( new Config(logger, "t/test.lua") );

        string user = config->get_value("user");
        EXPECT_STREQ("xmpp_notifier", user.c_str());

        string group = config->get_value("group");
        EXPECT_STREQ("xmpp_notifier", group.c_str());

        string log_level = config->get_value("log_level");
        EXPECT_STREQ("DEBUG", log_level.c_str());

        string xmpp_username = config->get_value("xmpp_username");
        EXPECT_STREQ("notifier", xmpp_username.c_str());

        string xmpp_password = config->get_value("xmpp_password");
        EXPECT_STREQ("test123", xmpp_password.c_str());

        string xmpp_server = config->get_value("xmpp_server");
        EXPECT_STREQ("localhost", xmpp_server.c_str());

        string xmpp_server_port = config->get_value("xmpp_server_port");
        EXPECT_STREQ("5223", xmpp_server_port.c_str());

        string xmpp_resource = config->get_value("xmpp_resource");
        EXPECT_STREQ("bot_at_work", xmpp_resource.c_str());

        vector<string> authorized_users = config->get_value_list("authorized_users");
        EXPECT_STREQ("user1", (authorized_users[0]).c_str());
        EXPECT_STREQ("user2", (authorized_users[1]).c_str());
        EXPECT_STREQ("user3", (authorized_users[2]).c_str());

        map<string, int> tasks = config->get_value_map("tasks");
        EXPECT_EQ(10, tasks["test"]);
        EXPECT_EQ(3, tasks["more"]);
        EXPECT_EQ(300, tasks["evenmore"]);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}



