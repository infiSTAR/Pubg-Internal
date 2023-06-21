#pragma once
#include "common/download.h"
#include "common/json.hpp"

struct tUserInfo {
	bool bExist = false;
	unsigned rankPoint = 0;
	float AvgDmg = 0.0f;
	float AvgKills = 0.0f;
	float AvgKda = 0.0f;

	tUserInfo() {}
	tUserInfo(json::JSON& rankedStats, std::string Key) {
		if (!rankedStats.hasKey(Key))
			return;
		auto& RankStats = rankedStats[Key];
		verify(RankStats.hasKey("currentRankPoint"e));
		verify(RankStats.hasKey("roundsPlayed"e));
		verify(RankStats.hasKey("damageDealt"e));
		verify(RankStats.hasKey("kda"e));
		verify(RankStats.hasKey("kills"e));

		auto& CurrentRankPoint = RankStats["currentRankPoint"e];
		auto& RoundsPlayed = RankStats["roundsPlayed"e];
		auto& DamageDealt = RankStats["damageDealt"e];
		auto& Kda = RankStats["kda"e];
		auto& Kills = RankStats["kills"e];

		bExist = true;
		rankPoint = CurrentRankPoint.ToInt();

		const int TotalRounds = RoundsPlayed.ToInt();
		if (!TotalRounds)
			return;

		const float TotalDamage = DamageDealt.ToInt() ? (float)DamageDealt.ToInt() : DamageDealt.ToFloat();//1757.85 126302
		const float TotalKda = Kda.ToFloat() ? (float)Kda.ToFloat() : (float)Kda.ToInt();
		const float TotalKills = (float)Kills.ToInt();
		AvgDmg = TotalDamage / TotalRounds;
		AvgKills = TotalKills / TotalRounds;
		AvgKda = TotalKda;
	}
};

class CUserInfo {
private:
	Download download;

	constexpr static unsigned RankSeason = 18;
	constexpr static float InvalidateTime = 60.0f * 60.0f;	//1hour
	constexpr static size_t MaxSyncLimit = 1;

	constexpr static float RetrySyncTime = 1.0f;
	constexpr static float ResetWaitTime = 5.0f;

	enum class Status {
		Reset,
		NeedSync,
		StartInfo,
		WaitSync,
		WaitInfo,
		StartSync,
		Done,
	};

	struct User {
		Status Code = Status::StartInfo;
		float WaitUntil = 0.0f;
		float SyncTime = -FLT_MAX;
	};

	std::map<std::string, User> UserList;

public:
	std::map<unsigned, tUserInfo> InfoSteamSolo;
	std::map<unsigned, tUserInfo> InfoSteamDuo;
	std::map<unsigned, tUserInfo> InfoSteamSquad;
	std::map<unsigned, tUserInfo> InfoSteamSquadFPP;
	std::map<unsigned, tUserInfo> InfoEmpty;

	void Invalidate(std::string UserName) {
		if (UserName.empty())
			return;

		if (UserList.contains(UserName)) {
			switch (UserList[UserName].Code) {
			case Status::WaitSync:
			case Status::WaitInfo:
				return;
			}
		}

		UserList[UserName].Code = Status::StartSync ;
	}

	void AddUser(std::string UserName) {
		if (UserName.empty())
			return;

		if (UserList.contains(UserName)) {
			auto& User = UserList[UserName];
			if (User.Code == Status::Done && GetTimeSeconds() > User.SyncTime + InvalidateTime) {
				UserList[UserName].Code = Status::NeedSync;
			}
			return;
		}

		UserList[UserName].Code = Status::StartInfo ;
	}

	void UpdateInfoFromJson(std::string UserName, std::string JsonString) {
		if (UserName.empty())
			return;

		auto Parsed = json::JSON::Load(JsonString);
		if (!Parsed.hasKey("rankedStats"e))
			return;

		auto& RankedStats = Parsed["rankedStats"e];
		const unsigned NameHash = CompileTime::StrHash(UserName);

		InfoSteamSolo[NameHash] = { RankedStats, "solo"e };
		InfoSteamDuo[NameHash] = { RankedStats, "duo"e };
		InfoSteamSquad[NameHash] = { RankedStats, "squad"e };
		InfoSteamSquadFPP[NameHash] = { RankedStats, "squad-fpp"e };


		return;
	}

	std::vector<std::string> GetSyncUserList() const {
		std::vector<std::string> Result;

		for (auto& i : UserList) {
			auto& UserName = i.first;
			auto& Code = i.second.Code;
			if (Code == Status::WaitSync || Code == Status::StartSync)
				Result.push_back(UserName);
		}

		return Result;
	}

	size_t GetSyncUserNumber() const { return GetSyncUserList().size(); }

	void Update() {
		float TimeSeconds = GetTimeSeconds();
		download.Update();

		for (auto& Elem : UserList) {
			std::string UserName = Elem.first;
			auto& User = Elem.second;

			if (TimeSeconds < User.WaitUntil)
				continue;

			const std::string SyncUrl = (std::string)"https://pubg.dakgg.io/api/v1/rpc/player-sync/steam/"e  + UserName;
			const std::string InfoUrl = (std::string)"https://pubg.dakgg.io/api/v1/players/steam/"e + UserName +
				(std::string)"/seasons/division.bro.official.pc-2018-"e + std::to_string(RankSeason);
			switch (User.Code) {
			case Status::Reset:
			{
				User = { Status::StartInfo, TimeSeconds + ResetWaitTime };
				break;
			}
			case Status::NeedSync:
			{
				User.Code = GetSyncUserNumber() < MaxSyncLimit ? Status::StartSync : Status::Done;
				break;
			}
			case Status::StartSync:
			{
				download.Add(SyncUrl);
				User.Code = Status::WaitSync;
				break;
			}
			case Status::StartInfo:
			{
				download.Add(InfoUrl);
				User.Code = Status::WaitInfo;
				break;
			}
			case Status::WaitSync:
			{
				switch (download.GetStatus(SyncUrl)) {
				case DownloadStatus::WaitOpenUrl:
				case DownloadStatus::WaitRead:
					break;
				case DownloadStatus::Done:
				{
					std::vector<uint8_t> JsonData = download.GetData(SyncUrl);
					download.RemoveData(SyncUrl);
					std::string JsonString(JsonData.begin(), JsonData.end());
					auto Parsed = json::JSON::Load(JsonString);

					if (Parsed.hasKey("accountId"e)) {
						User.SyncTime = TimeSeconds;
						User.Code = Status::StartInfo;
					}
					else if (Parsed.hasKey("retryAfter"e)) {
						User.WaitUntil = TimeSeconds + RetrySyncTime;
						User.Code = Status::StartSync;
					}
					else if (Parsed.hasKey("error"e)) {
						const bool IsBusy = Parsed["error"e].ToString() == (std::string)"busy"e;
						User.WaitUntil = TimeSeconds + RetrySyncTime;
						User.Code = IsBusy ? Status::StartSync : Status::Reset;
					}

					break;
				}
				case DownloadStatus::Failed:
					User.Code = Status::Reset;
					break;
				default:
					error(UserName.c_str());
					break;
				}
				break;
			}
			case Status::WaitInfo:
			{
				switch (download.GetStatus(InfoUrl)) {
				case DownloadStatus::WaitOpenUrl:
				case DownloadStatus::WaitRead:
					break;
				case DownloadStatus::Done:
				{
					std::vector<uint8_t> JsonData = download.GetData(InfoUrl);
					download.RemoveData(InfoUrl);
					std::string JsonString(JsonData.begin(), JsonData.end());
					UpdateInfoFromJson(UserName, JsonString);
					User.Code = Status::Done;
					break;
				}
				case DownloadStatus::Failed:
					User.Code = Status::Reset;
					break;
				default:
					error(UserName.c_str());
					break;
				}
				break;
			}
			case Status::Done:
				break;
			}
			
		}
		
	}
};