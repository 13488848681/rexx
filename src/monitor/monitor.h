
#ifndef MONITOR_H_
#define MONITOR_H_

#include <proto/cpp/monitor.pb.h>
#include <proto/cpp/overlay.pb.h>
#include <common/network.h>

namespace rexx {
	typedef std::shared_ptr<protocol::WsMessage> WsMessagePointer;

	class Monitor : public rexx::Connection {
	private:

		bool state_changed_;              /* state changed */
		int64_t active_time_;             /* the active time of monitor */
		std::string session_id_;          /* session id */
		std::string peer_node_address_;   /* peer node address */
		
		std::string rexx_version_;        /* rexx version */
		int64_t monitor_version_;         /* monitor version */
		int64_t rexx_ledger_version_;     /* rexx ledger version */
		std::string rexx_node_address_;   /* rexx node address */

	public:
		Monitor(rexx::server *server_h, rexx::client *client_h, rexx::tls_server *tls_server_h, rexx::tls_client *tls_client_h,
			rexx::connection_hdl con, const std::string &uri, int64_t id);

		void SetSessionId(const std::string &session_id);
		void SetActiveTime(int64_t current_time);
		bool IsActive() const;
		int64_t GetActiveTime() const;

		utils::InetAddress GetRemoteAddress() const;
		std::string GetPeerNodeAddress() const;

		bool SendHello(int32_t listen_port, const std::string &node_address, std::error_code &ec);
		void SetRexxInfo(const protocol::ChainStatus &hello);
	};
}

#endif