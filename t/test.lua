-- basic architecture
--
--                   --------------- ------------
--  XMPP Server <--> | XMPP Client | | Action() | <--> Scripts
--                   --------------- ------------
--

-- available configuration options including data type
-- and defaults (if any)
--
-- mandatory
--     xmpp_username : string
--         xmmp client name to use for the XMPP Client to connect
--     xmpp_password : string
--         xmpp password to beforementioned account
-- optional:
--     user : string : "xmpp_notifier"
--         system username the notifier XMPP Client runs as
--     group : string : "xmpp_notifier"
--         group the XMPP Client drops permission to
--     log_level : string : "INFO"
--         loglevel of the logger. valid values:
--         "EMERG", "ALERT", "CRIT", "ERR", "WARNING",
--         "NOTICE", "INFO", "DEBUG"
--     script_dir : string : "script"
--     xmpp_server : string : "localhost:5223"
--         xmpp server the XMPP Client will connect to
--     xmpp_resource : string : "bot_at_work"
--         resource to connect with
--     authorized_users : table<string> : empty
--         list of xmpp_users authorized to send commands to the notifier
--         client
--     notify_users : table<string> : empty
--         list of xmpp_users that get messages from the notifier
--         client

xmpp_username = "notifier"
xmpp_password = "test123"
log_level = "DEBUG"

authorized_users = {
	"user1",
	"user2",
	"user3"
}
