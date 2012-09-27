-- basic architecture
--
--                   --------------- --------------
--  XMPP Server <--> | XMPP Client | | API Client | <--> Zabbix API
--                   --------------- --------------
--                communicates        queries zabbix api
--                with authorized     runs actions (scripts)
--                XMPP clients
--
-- connections to XMPP servers and the daemon require ssl

-- available configuration options including data type
-- and defaults (if any)
--
-- mandatory
--     xmpp_username : string
--         xmmp client name to use for the XMPP Client to connect
--     xmpp_password : string
--         xmpp password to beforementioned account
--     authorized_users : table<string>
--         list of xmpp_users authorized to send commands to the notifier
--         client
-- optional:
--     user : string : "zabbix_notifier"
--         system username the notifier XMPP Client runs as
--     group : string : "zabbix_notifier"
--         group the XMPP Client drops permission to
--     zabbix_api_server : string : "localhost:80"
--         host:port string the API Client listens for connections
--     log_level : string : "INFO"
--         loglevel of the logger. valid values:
--         "EMERG", "ALERT", "CRIT", "ERR", "WARNING",
--         "NOTICE", "INFO", "DEBUG"
--     xmpp_server : string : "localhost:5223"
--         xmpp server the XMPP Client will connect to
--     xmpp_resource : string : "bot_at_work"
--         resource to connect with

xmpp_username = "zabbix"
xmpp_password = "test123"
log_level = "DEBUG"

authorized_users = {
	"user1",
	"user2",
	"user3"
}
