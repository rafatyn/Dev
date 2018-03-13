#include "application.h"
#include "view.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include "method_dispatcher.h"
#include "../Utils.h"
#ifdef _WIN32
#include <Windows.h>
#endif

using namespace Awesomium;

class AwesomiumApp : public Application::Listener {
  Application* app_;
  View* view_;
  MethodDispatcher* method_dispatcher_;
 public:
	 AwesomiumApp();

	 virtual ~AwesomiumApp();

	 void Run();

  // Inherited from Application::Listener
	 virtual void OnLoaded();
  
	 void BindMethods(WebView* web_view);

  // Inherited from Application::Listener
	virtual void OnUpdate() {}

  // Inherited from Application::Listener
	virtual void OnShutdown() {}

	void OnSayHello(WebView* caller, const JSArray& args);
};