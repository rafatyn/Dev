#include <iostream>
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>
#include <string>
#include <windows.h>

std::string ExePath() {
	char buffer[MAX_PATH];
	GetModuleFileName(nullptr, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

int main()
{
	Awesomium::WebConfig webConfig;
	std::string path = ExePath() + std::string("\\Log.log");
	webConfig.log_path = Awesomium::WSLit(path.c_str());
	webConfig.log_level = Awesomium::kLogLevel_Normal;

	Awesomium::WebCore* webCore = Awesomium::WebCore::Initialize(webConfig);

	Awesomium::WebView* webView = webCore->CreateWebView(500, 500);

	webView->LoadURL(Awesomium::WebURL(Awesomium::WSLit("http://www.google.com")));

	while (webView->IsLoading())
		webCore->Update();

	Sleep(300);
	webCore->Update();

	Awesomium::BitmapSurface* bitmapSurface = (Awesomium::BitmapSurface*)webView->surface();

	if (bitmapSurface != nullptr) {
		std::string path = ExePath() + std::string("\\result.jpg");
		bitmapSurface->SaveToJPEG(Awesomium::WSLit(path.c_str()));
	}

	std::getchar();

	webView->Destroy();

	Awesomium::WebCore::Shutdown();

	return 0;
}