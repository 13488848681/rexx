
#include <utils/headers.h>
#include <common/general.h>
#include <common/storage.h>
#include <common/private_key.h>
#include <common/argument.h>
#include <common/daemon.h>
#include <overlay/peer_manager.h>
#include <ledger/ledger_manager.h>
#include <consensus/consensus_manager.h>
#include <glue/glue_manager.h>
#include <api/web_server.h>
#include <api/websocket_server.h>
#include <api/console.h>
#include <ledger/contract_manager.h>
#include <monitor/monitor_manager.h>
#include "configure.h"

void SaveWSPort();
void RunLoop();
int main(int argc, char *argv[]){

#ifdef WIN32
	_set_output_format(_TWO_DIGIT_EXPONENT);
#else
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	size_t stacksize = 0;
	int ret = pthread_attr_getstacksize(&attr, &stacksize);
	if (ret != 0) {
		printf("get stacksize error!:%d\n", (int)stacksize);
		return -1;
	}

	if (stacksize <= 2 * 1024 * 1024)
	{
		stacksize = 2 * 1024 * 1024;

		pthread_attr_t object_attr;
		pthread_attr_init(&object_attr);
		ret = pthread_attr_setstacksize(&object_attr, stacksize);
		if (ret != 0) {
			printf("set main stacksize error!:%d\n", (int)stacksize);
			return -1;
		}
	}
#endif

	utils::SetExceptionHandle();
	utils::Thread::SetCurrentThreadName("rexx-thread");

	utils::Daemon::InitInstance();
	utils::net::Initialize();
	utils::Timer::InitInstance();
	rexx::Configure::InitInstance();
	rexx::Storage::InitInstance();
	rexx::Global::InitInstance();
	rexx::SlowTimer::InitInstance();
	utils::Logger::InitInstance();
	rexx::Console::InitInstance();
	rexx::PeerManager::InitInstance();
	rexx::LedgerManager::InitInstance();
	rexx::ConsensusManager::InitInstance();
	rexx::GlueManager::InitInstance();
	rexx::WebSocketServer::InitInstance();
	rexx::WebServer::InitInstance();
	rexx::MonitorManager::InitInstance();
	rexx::ContractManager::InitInstance();

	rexx::Argument arg;
	if (arg.Parse(argc, argv)){
		return 1;
	}

	do {
		utils::ObjectExit object_exit;
		rexx::InstallSignal();

		if (arg.console_){
			arg.log_dest_ = utils::LOG_DEST_FILE; //Cancel the std output
			rexx::Console &console = rexx::Console::Instance();
			console.Initialize();
			object_exit.Push(std::bind(&rexx::Console::Exit, &console));
		}

		srand((uint32_t)time(NULL));
		rexx::StatusModule::modules_status_ = new Json::Value;
#ifndef OS_MAC
		utils::Daemon &daemon = utils::Daemon::Instance();
		if (!rexx::g_enable_ || !daemon.Initialize((int32_t)1234))
		{
			LOG_STD_ERRNO("Failed to initialize daemon", STD_ERR_CODE, STD_ERR_DESC);
			break;
		}
		object_exit.Push(std::bind(&utils::Daemon::Exit, &daemon));
#endif

		rexx::Configure &config = rexx::Configure::Instance();
		std::string config_path = rexx::General::CONFIG_FILE;
		if (!utils::File::IsAbsolute(config_path)){
			config_path = utils::String::Format("%s/%s", utils::File::GetBinHome().c_str(), config_path.c_str());
		}

		if (!config.Load(config_path)){
			LOG_STD_ERRNO("Failed to load configuration", STD_ERR_CODE, STD_ERR_DESC);
			break;
		}

		std::string log_path = config.logger_configure_.path_;
		if (!utils::File::IsAbsolute(log_path)){
			log_path = utils::String::Format("%s/%s", utils::File::GetBinHome().c_str(), log_path.c_str());
		}
		const rexx::LoggerConfigure &logger_config = rexx::Configure::Instance().logger_configure_;
		utils::Logger &logger = utils::Logger::Instance();
		logger.SetCapacity(logger_config.time_capacity_, logger_config.size_capacity_);
		logger.SetExpireDays(logger_config.expire_days_);
		if (!rexx::g_enable_ || !logger.Initialize((utils::LogDest)(arg.log_dest_ >= 0 ? arg.log_dest_ : logger_config.dest_),
			(utils::LogLevel)logger_config.level_, log_path, true)){
			LOG_STD_ERR("Failed to initialize logger");
			break;
		}
		object_exit.Push(std::bind(&utils::Logger::Exit, &logger));
		LOG_INFO("Initialized daemon successfully");
		LOG_INFO("Loaded configure successfully");
		LOG_INFO("Initialized logger successfully");

		// end run command
		rexx::Storage &storage = rexx::Storage::Instance();
		LOG_INFO("The path of the database is as follows: keyvalue(%s),account(%s),ledger(%s)", 
			config.db_configure_.keyvalue_db_path_.c_str(),
			config.db_configure_.account_db_path_.c_str(),
			config.db_configure_.ledger_db_path_.c_str());

		if (!rexx::g_enable_ || !storage.Initialize(config.db_configure_, arg.drop_db_)) {
			LOG_ERROR("Failed to initialize database");
			break;
		}
		object_exit.Push(std::bind(&rexx::Storage::Exit, &storage));
		LOG_INFO("Initialized database successfully");

		if (arg.drop_db_) {
			LOG_INFO("Droped database successfully");
			return 1;
		} 
		
		if ( arg.clear_consensus_status_ ){
			rexx::Pbft::ClearStatus();
			LOG_INFO("Cleared consensus status successfully");
			return 1;
		}

		if (arg.clear_peer_addresses_) {
			rexx::KeyValueDb *db = rexx::Storage::Instance().keyvalue_db();
			db->Put(rexx::General::PEERS_TABLE, "");
			LOG_INFO("Cleared peer addresss list successfully");
			return 1;
		} 

		if (arg.create_hardfork_) {
			rexx::LedgerManager &ledgermanger = rexx::LedgerManager::Instance();
			if (!ledgermanger.Initialize()) {
				LOG_ERROR("Failed to initialize legder manger!");
				return -1;
			}
			rexx::LedgerManager::CreateHardforkLedger();
			return 1;
		}

		rexx::Global &global = rexx::Global::Instance();
		if (!rexx::g_enable_ || !global.Initialize()){
			LOG_ERROR_ERRNO("Failed to initialize global variable", STD_ERR_CODE, STD_ERR_DESC);
			break;
		}
		object_exit.Push(std::bind(&rexx::Global::Exit, &global));
		LOG_INFO("Initialized global module successfully");

		//Consensus manager must be initialized before ledger manager and glue manager
		rexx::ConsensusManager &consensus_manager = rexx::ConsensusManager::Instance();
		if (!rexx::g_enable_ || !consensus_manager.Initialize(rexx::Configure::Instance().ledger_configure_.validation_type_)) {
			LOG_ERROR("Failed to initialize consensus manager");
			break;
		}
		object_exit.Push(std::bind(&rexx::ConsensusManager::Exit, &consensus_manager));
		LOG_INFO("Initialized consensus manager successfully");

		rexx::LedgerManager &ledgermanger = rexx::LedgerManager::Instance();
		if (!rexx::g_enable_ || !ledgermanger.Initialize()) {
			LOG_ERROR("Failed to initialize ledger manager");
			break;
		}
		object_exit.Push(std::bind(&rexx::LedgerManager::Exit, &ledgermanger));
		LOG_INFO("Initialized ledger successfully");

		rexx::GlueManager &glue = rexx::GlueManager::Instance();
		if (!rexx::g_enable_ || !glue.Initialize()){
			LOG_ERROR("Failed to initialize glue manager");
			break;
		}
		object_exit.Push(std::bind(&rexx::GlueManager::Exit, &glue));
		LOG_INFO("Initialized glue manager successfully");

		rexx::PeerManager &p2p = rexx::PeerManager::Instance();
		if (!rexx::g_enable_ || !p2p.Initialize(NULL, false)) {
			LOG_ERROR("Failed to initialize peer network");
			break;
		}
		object_exit.Push(std::bind(&rexx::PeerManager::Exit, &p2p));
		LOG_INFO("Initialized peer network successfully");

		rexx::SlowTimer &slow_timer = rexx::SlowTimer::Instance();
		if (!rexx::g_enable_ || !slow_timer.Initialize(1)){
			LOG_ERROR_ERRNO("Failed to initialize slow timer", STD_ERR_CODE, STD_ERR_DESC);
			break;
		}
		object_exit.Push(std::bind(&rexx::SlowTimer::Exit, &slow_timer));
		LOG_INFO("Initialized slow timer with " FMT_SIZE " successfully", utils::System::GetCpuCoreCount());

		rexx::WebSocketServer &ws_server = rexx::WebSocketServer::Instance();
		if (!rexx::g_enable_ || !ws_server.Initialize(rexx::Configure::Instance().wsserver_configure_)) {
			LOG_ERROR("Failed to initialize web server");
			break;
		}
		object_exit.Push(std::bind(&rexx::WebSocketServer::Exit, &ws_server));
		LOG_INFO("Initialized web server successfully");

		rexx::WebServer &web_server = rexx::WebServer::Instance();
		if (!rexx::g_enable_ || !web_server.Initialize(rexx::Configure::Instance().webserver_configure_)) {
			LOG_ERROR("Failed to initialize web server");
			break;
		}
		object_exit.Push(std::bind(&rexx::WebServer::Exit, &web_server));
		LOG_INFO("Initialized web server successfully");

		SaveWSPort();
		
		rexx::MonitorManager &monitor_manager = rexx::MonitorManager::Instance();
		if (!rexx::g_enable_ || !monitor_manager.Initialize()) {
			LOG_ERROR("Failed to initialize monitor manager");
			break;
		}
		object_exit.Push(std::bind(&rexx::MonitorManager::Exit, &monitor_manager));
		LOG_INFO("Initialized monitor manager successfully");

		rexx::ContractManager &contract_manager = rexx::ContractManager::Instance();
		if (!contract_manager.Initialize(argc, argv)){
			LOG_ERROR("Failed to initialize contract manager");
			break;
		}
		object_exit.Push(std::bind(&rexx::ContractManager::Exit, &contract_manager));
		LOG_INFO("Initialized contract manager successfully");

		rexx::g_ready_ = true;

		RunLoop();

		LOG_INFO("Process begins to quit...");
		delete rexx::StatusModule::modules_status_;

	} while (false);

	rexx::ContractManager::ExitInstance();
	rexx::SlowTimer::ExitInstance();
	rexx::GlueManager::ExitInstance();
	rexx::LedgerManager::ExitInstance();
	rexx::PeerManager::ExitInstance();
	rexx::WebSocketServer::ExitInstance();
	rexx::WebServer::ExitInstance();
	rexx::MonitorManager::ExitInstance();
	rexx::Configure::ExitInstance();
	rexx::Global::ExitInstance();
	rexx::Storage::ExitInstance();
	utils::Logger::ExitInstance();
	utils::Daemon::ExitInstance();
	
	if (arg.console_ && !rexx::g_ready_) {
		printf("Initialized failed, please check log for detail\n");
	}
	printf("process exit\n");
}

void RunLoop(){
	int64_t check_module_interval = 5 * utils::MICRO_UNITS_PER_SEC;
	int64_t last_check_module = 0;
	while (rexx::g_enable_){
		int64_t current_time = utils::Timestamp::HighResolution();

		for (auto item : rexx::TimerNotify::notifys_){
			item->TimerWrapper(utils::Timestamp::HighResolution());
			if (item->IsExpire(utils::MICRO_UNITS_PER_SEC)){
				LOG_WARN("The execution time(" FMT_I64 " us) for the timer(%s) is expired after 1s elapses", item->GetLastExecuteTime(), item->GetTimerName().c_str());
			}
		}

		utils::Timer::Instance().OnTimer(current_time);
		utils::Logger::Instance().CheckExpiredLog();

		if (current_time - last_check_module > check_module_interval){
			utils::WriteLockGuard guard(rexx::StatusModule::status_lock_);
			rexx::StatusModule::GetModulesStatus(*rexx::StatusModule::modules_status_);
			last_check_module = current_time;
		}

		utils::Sleep(1);
	}
}

void SaveWSPort(){    
    std::string tmp_file = utils::File::GetTempDirectory() +"/rexx_listen_port";
	Json::Value json_port = Json::Value(Json::objectValue);
	json_port["webserver_port"] = rexx::WebServer::Instance().GetListenPort();
	json_port["wsserver_port"] = rexx::WebSocketServer::Instance().GetListenPort();
	utils::File file;
	if (file.Open(tmp_file, utils::File::FILE_M_WRITE | utils::File::FILE_M_TEXT))
	{
		std::string line = json_port.toFastString();
		file.Write(line.c_str(), 1, line.length());
		file.Close();
	}
}
