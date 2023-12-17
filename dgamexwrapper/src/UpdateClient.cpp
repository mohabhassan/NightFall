#include "UpdateClient.h"
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>
#include "nlohmann/json.hpp"
#include "CustomCvar.h"
#include "nf_misc.h"
#include <filesystem>
namespace fs = std::filesystem;

using json = nlohmann::json;

constexpr char updateURL[] = "http://nightfall.mohaa.net/api/version_info";



static size_t write_callback_string(string &respStr, char* ptr, size_t size, size_t nmemb)
{
	respStr.append(ptr, size*nmemb);
	return size * nmemb;
}

string UpdateClient::RequestUpdateInfo()
{
	gi->Printf(PATCH_NAME " Update Client: Checking for updates...\n");
	string respStr;//empty string
	long httpCode = -1;
	try
	{
		curlpp::Easy request;

		request.setOpt(new curlpp::options::Url(updateURL));
		request.setOpt(new curlpp::options::Verbose(false));



		//fail on error
		request.setOpt(new curlpp::options::FailOnError(true));

		//follow redirs
		request.setOpt(new curlpp::options::FollowLocation(true));

		//no progress func
		request.setOpt(new curlpp::options::NoProgress(true));

		//dont verify peer
		//verify peer requires ca cert bundle, shipped with exe. not needed.
		//not used anyways, we're not linking libcurl/pp to wolfssl
		//request.setOpt(new curlpp::options::SslVerifyPeer(false));
		
		//specifiy ca bundle location
		fs::path ca_path = fs::current_path() / MAIN_PATH / NF_LIBCURL_CABUNDLENAME;
		request.setOpt(new curlpp::options::CaInfo(ca_path.string()));

		//set timeout to 5 seconds (includes connection phase)
		request.setOpt(new curlpp::options::Timeout(5L));

		//set connection phase timeoute to 5 seconds
		request.setOpt(new curlpp::options::ConnectTimeout(5L));


		using namespace std::placeholders;

		//register write callback to get full response
		request.setOpt(new curlpp::options::WriteFunction(std::bind(&write_callback_string, std::ref(respStr), _1, _2, _3)));

		// perform request
		request.perform();

		//check http code:
		httpCode = curlpp::infos::ResponseCode::get(request);

	}
	catch (const std::exception&e)
	{
		//gi->Printf(PATCH_NAME " api client exception occured: %s\n", e.what());
		gi->Printf(PATCH_NAME " Update Client: Failed to check for updates: %s\n", e.what());
		return "";
	}
	if (httpCode != 200)
	{
		gi->Printf(PATCH_NAME " Update Client: Unexpected response code: %ld\n", httpCode);
		return "";
	}
	return respStr;

}

static size_t write_callback_file(FILE *stream, char* ptr, size_t size, size_t nmemb)
{
	size_t written = fwrite(ptr, size, nmemb, stream);
	return written;
}

//FIXME: this is nasty, but update logic is not really frustrating
bool UpdateClient::UpdateFile(string fileRelPath, string fileURL, string fileMD5)
{
	gi->Printf(PATCH_NAME " Update Client: Checking file: %s\n", fileRelPath.c_str());
	bool fileExists = true;
	try
	{
		fs::path p = fs::current_path() / fileRelPath;
		fs::path np = fs::current_path() / (fileRelPath+".back");


		if (fileExists = fs::exists(p))
		{
			char calculatedMd5[MD5_STR_SIZE] = { 0 };
			if (md5File(fileRelPath.c_str(), calculatedMd5))
			{

				if (_stricmp(fileMD5.c_str(), calculatedMd5) != 0)
				{
					gi->Printf(PATCH_NAME " Update Client: File %s needs to be updated, proceeding...\n", fileRelPath.c_str());
				}
				else
				{
					gi->Printf(PATCH_NAME " Update Client: File %s is up to date, ignoring...\n", fileRelPath.c_str());
					return true;
				}
			}
			else
			{
				gi->Printf(PATCH_NAME " Update Client: Failed to check file %s for updates\n", fileRelPath.c_str());
				return false;
			}
			fs::rename(p, np);
		}
	}
	catch (const std::exception& e)
	{
		gi->Printf(PATCH_NAME " Update Client: Failed to rename file: %s to %s.back : error: %s\n", fileRelPath.c_str(), fileRelPath.c_str(), e.what());
		return false;
	}

	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, fileRelPath.c_str(), "wb");
	if (err != 0)
	{
		gi->Printf(PATCH_NAME " Update Client: Failed to open file: %s for downloading error code: %i , aborting...\n", fileRelPath.c_str(), err);
	
		if (fileExists)
		{
			gi->Printf(PATCH_NAME " Update Client: Recovering file: %s \n", fileRelPath.c_str());

			try
			{
				fs::path np = fs::current_path() / fileRelPath;
				fs::path p = fs::current_path() / (fileRelPath + ".back");
				fs::rename(p, np);
			}
			catch (const std::exception& e)
			{
				gi->Printf(PATCH_NAME " Update Client: Failed to recover file: %s.back back to %s : error: %s\n", fileRelPath.c_str(), fileRelPath.c_str(), e.what());
			}
		}
		return false;
	}

	gi->Printf(PATCH_NAME " Update Client: Downloading file: %s from %s\n", fileRelPath.c_str(), fileURL.c_str());

	long httpCode = -1;
	try
	{
		curlpp::Easy request;

		request.setOpt(new curlpp::options::Url(fileURL));
		request.setOpt(new curlpp::options::Verbose(false));



		//fail on error
		request.setOpt(new curlpp::options::FailOnError(true));

		//follow redirs
		request.setOpt(new curlpp::options::FollowLocation(true));

		//no progress func
		request.setOpt(new curlpp::options::NoProgress(true));

		//dont verify peer
		//verify peer requires ca cert bundle, shipped with exe. not needed.
		//not used anyways, we're not linking libcurl/pp to wolfssl
		//request.setOpt(new curlpp::options::SslVerifyPeer(false));
		
		//specifiy ca bundle location
		fs::path ca_path = fs::current_path() / MAIN_PATH / NF_LIBCURL_CABUNDLENAME;
		request.setOpt(new curlpp::options::CaInfo(ca_path.string()));

		//set timeout to 10 minutes (includes connection phase)
		request.setOpt(new curlpp::options::Timeout(600L));

		//set connection phase timeoute to 10 minutes
		request.setOpt(new curlpp::options::ConnectTimeout(599L));


		using namespace std::placeholders;

		//register write callback to get full response
		request.setOpt(new curlpp::options::WriteFunction(std::bind(&write_callback_file, std::ref(fp), _1, _2, _3)));

		// perform request
		request.perform();

		//check http code:
		httpCode = curlpp::infos::ResponseCode::get(request);

	}
	catch (const std::exception&e)
	{
		fclose(fp);
		//gi->Printf(PATCH_NAME " api client exception occured: %s\n", e.what());
		gi->Printf(PATCH_NAME " Update Client: Failed to download file: %s , error: %s\n", fileRelPath.c_str(), e.what());
		if (fileExists)
		{
			gi->Printf(PATCH_NAME " Update Client: Recovering file: %s \n", fileRelPath.c_str());

			try
			{
				fs::path np = fs::current_path() / fileRelPath;
				fs::path p = fs::current_path() / (fileRelPath + ".back");
				fs::rename(p, np);
			}
			catch (const std::exception& e)
			{
				gi->Printf(PATCH_NAME " Update Client: Failed to recover file: %s.back back to %s : error: %s\n", fileRelPath.c_str(), fileRelPath.c_str(), e.what());
			}
		}
		return false;
	}
	fclose(fp);
	if (fileExists)
	{
		try
		{
			fs::path np = fs::current_path() / (fileRelPath + ".back");
			fs::remove(np);
		}
		catch (const std::exception& e)
		{
			gi->Printf(PATCH_NAME " Update Client: Failed to delete file: %s.back : error: %s , ignoring....\n", fileRelPath.c_str(), fileRelPath.c_str(), e.what());
			return false;
		}
	}

	gi->Printf(PATCH_NAME " Update Client: Updated file %s successfully\n", fileRelPath.c_str());
	return true;
}

UpdateClient::UpdateClient()
{
}


UpdateClient::~UpdateClient()
{
}

void UpdateClient::CheckForUpdate()
{

	string respStr = RequestUpdateInfo();
	if (!respStr.empty())
	{
		json j;
		try
		{
			j = json::parse(respStr);
		}
		catch (json::parse_error& e)
		{
			gi->Printf(PATCH_NAME " Update Client: json::parse failed!\n");
			return;
		}
		if (j["version"] == PATCH_VERSION)
		{
			gi->Printf(PATCH_NAME " Update Client: same version, skipping update.\n");
			return;
		}

		json dir_info;
		if (gameInfo.IsSH())
		{
			CustomCvar shortversion("shortversion", "2.15", CVAR_ROM);
			dir_info = j["sh"][shortversion.GetStringValue()];
		}
		else if (gameInfo.IsBT())
		{
			CustomCvar shortversion("shortversion", "2.30", CVAR_ROM);
			dir_info = j["bt"][shortversion.GetStringValue()];
		}
		else if (gameInfo.IsAA())
		{
			CustomCvar shortversion("shortversion", "1.11", CVAR_ROM);
			dir_info = j["aa"][shortversion.GetStringValue()];
		}
		else//let's use AA for now
		{
			CustomCvar shortversion("shortversion", "1.11", CVAR_ROM);
			dir_info = j["aa"][shortversion.GetStringValue()];
		}


		bool allgood = true;
		// range-based for
		for (auto& element : dir_info)
		{
			string relPath = element["relPath"];
			auto files = element["files"];

			for (auto& file : files) 
			{
				string fileName = file["name"];
				string fileRelPath = relPath + fileName;
				string fileMd5 = file["md5"];
				string fileURL = file["url"];
				allgood = UpdateFile(fileRelPath.c_str(), fileURL.c_str(), fileMd5);
			}
		}
		if (allgood)
		{
			gi->Printf(PATCH_NAME " Update Client: Successfully update from version %s to version %s\n", PATCH_VERSION, string(j["version"]).c_str());
		}
		else
		{
			gi->Printf(PATCH_NAME " Update Client: Update attempt failed.\n");
		}
	}

}
