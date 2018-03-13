#include <iostream>
#include "Utils.h"
#include "AwesomiumApp/app.h"


#ifdef _WIN32
int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE, wchar_t*,
	int nCmdShow) {
#else
int main() {
#endif

	Awesomium::WebConfig webConfig;
	std::string path = Utils::ExePath() + std::string("\\Log.log");
	webConfig.log_path = Awesomium::WSLit(path.c_str());
	webConfig.log_level = Awesomium::kLogLevel_Verbose;

	Awesomium::WebCore* webCore = Awesomium::WebCore::Initialize(webConfig);

	AwesomiumApp app;
	app.Run();
	
	return 0;
}