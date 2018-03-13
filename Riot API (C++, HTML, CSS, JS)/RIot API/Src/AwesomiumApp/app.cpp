#include "app.h"

using namespace Awesomium;

AwesomiumApp::AwesomiumApp():
app_(Application::Create()), view_(0), method_dispatcher_(new MethodDispatcher()) 
{
	app_->set_listener(this);
}

AwesomiumApp::~AwesomiumApp() {
	if (view_)
		app_->DestroyView(view_);
	if (app_)
		delete app_;
}

void AwesomiumApp::Run() {
	app_->Run();
}

// Inherited from Application::Listener
void AwesomiumApp::OnLoaded() {
	view_ = View::Create(500, 300);
	// < Set up your View here. >
	BindMethods(view_->web_view());

	std::string path = Utils::ExePath() + std::string("\\WebResources\\App.html");
	WebURL url(WSLit(path.c_str()));
	view_->web_view()->LoadURL(url);
}
  
void AwesomiumApp::BindMethods(WebView* web_view) {
	// Create a global js object named 'app'
	JSValue result = web_view->CreateGlobalJavascriptObject(WSLit("app"));
	if (result.IsObject()) {
		// Bind our custom method to it.
		JSObject& app_object = result.ToObject();
		method_dispatcher_->Bind(app_object,
			WSLit("sayHello"),
			JSDelegate(this, &AwesomiumApp::OnSayHello));
	}

	// Bind our method dispatcher to the WebView
	web_view->set_js_method_handler(method_dispatcher_);
}

void AwesomiumApp::OnSayHello(WebView* caller, const JSArray& args) {
	app_->ShowMessage("Hello!");
}