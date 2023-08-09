#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <thread>
#include <chrono>

#include "globals.hpp"

#include "download.hpp"
#include "patcher.hpp"

int main(int argc, char* argv[]) {
	puts("����֮ǰ��������ɴ�����VPN���������ȣ������á�");
	std::string wantsNextPatch;
	if (Downloader::needsUpdate()) {
		puts("��Ҫ���£��밴 Enter �����ظ���");
		waitforinput();
		Downloader::UpdateInstaller();
		//return 1; /* doeesnt reach */
	}
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "disablemanifest") == 0) {
			Globals::usesNoManifests = true;
			break;
		}
	}
	puts("����׼������...");
	Downloader::PrepareDownload();
	puts("����׼����ϣ�");
	Patcher::CleanPatchFiles();
	puts("��ʼ����...");
	Downloader::DownloadCS2();
	puts("������ϣ�");
	puts("Starting Patches...");
	Patcher::PatchClient();

	puts("�Ƿ�Ҫ��װ�ƶ�������������bhop/surf��������װ�˲������Ի�ø��õ��ƶ�Ч����");
	puts("�ڼ����ϰ���Y����ʾ���ǡ��򰴡�N����ʾ����");
	std::cin >> wantsNextPatch;
	for (char& c : wantsNextPatch) { /* make the anwser lowercase */
		c = std::tolower(c);
	}
	if (wantsNextPatch.find("y") != std::string::npos) {
		Patcher::PatchServer();
		puts("�ƶ�������װ��ɣ�");
	}

	puts("�Ƿ�װ����oof.lv����Ϸģ�飿�����https://github.com/CS2-OOF-LV/CS2-Client��");
	puts("�ڼ����ϰ���Y����ʾ���ǡ��򰴡�N����ʾ����");
	std::cin >> wantsNextPatch;
	for (char& c : wantsNextPatch) { /* make the anwser lowercase */
		c = std::tolower(c);
	}
	if (wantsNextPatch.find("y") != std::string::npos) {
	puts("��ʼ���ؿͻ��� Mod ����...");
	puts("�������Ҫһ��ʱ��...");
	Downloader::DownloadMods();
	puts("����ɿͻ���ģ�鲹�����أ�");
	}

	puts("�����������ļ�...");
	if (!Globals::usesNoManifests) {
		std::filesystem::remove_all("manifestFiles");
	}
	puts("������ϣ�");
	puts("����һ�����Դ2���桪��Դ����������");
	puts("������ϣ�����Enter���ر����س���");
	waitforinput();
	return 0;
}
