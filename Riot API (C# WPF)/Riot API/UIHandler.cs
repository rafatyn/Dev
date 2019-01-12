using CefSharp;
using CefSharp.Wpf;
using System;
using System.Threading.Tasks;

namespace Riot_API
{
    class UIHandler
    {
        static IFrame frame;
        static ChromiumWebBrowser browser;

        public static void LoadBrowser(ChromiumWebBrowser WebBrowser)
        {
            // Initialize variables
            browser = WebBrowser;
            frame = browser.GetMainFrame();

            // Load UI Handler into JS Object
            WebBrowser.JavascriptObjectRepository.Register("UIHandler", new UIHandler(), false, null);
        }

        public static string CheckClassId(string selectorIdClass)
        {
            string script = "";

            // Check if it is an Id or a Class
            if (selectorIdClass.StartsWith("."))
            {
                script += @"document.getElementsByClassName('" + selectorIdClass.Substring(1) + @"')[0];";
            }
            else if (selectorIdClass.StartsWith("#"))
            {
                script += @"document.getElementById('" + selectorIdClass.Substring(1) + @"');";
            }
            else
            {
                script += @"document.getElementById('" + selectorIdClass + @"');";
            }

            return script;
        }

        public static void AddChild(string element, string parent)
        {
            // Check if can execute JS
            if (browser.CanExecuteJavascriptInMainFrame)
            {
                string script = @"(function(){ var parent = ";

                // Check if it is an Id or a Class
                script += CheckClassId(parent);

                // Add behavior
                script += element + @"parent.appendChild(element); })();";

                // Execute script async
                frame.EvaluateScriptAsync(script).ContinueWith(e =>
                {
                    if (e.Exception != null)
                        throw e.Exception;
                });
            }
        }

        public static void GetSelectedOption(string selectorId, Action<Task<JavascriptResponse>> callback)
        {
            // Check if can execute JS
            if (browser.CanExecuteJavascriptInMainFrame)
            {
                string script = @"(function(){ var element = ";

                // Check if it is an Id or a Class
                script += CheckClassId(selectorId);

                // Add behavior
                script += @"return element.options[element.selectedIndex].text; })(); ";

                // Execute script async
                frame.EvaluateScriptAsync(script).ContinueWith(e =>
                {
                    // Call callback function with JS result
                    callback(e);
                });
            }
        }

        public static void SelectorAddOption(string selectorId, string value, string text)
        {
            // Check if can execute JS
            if (browser.CanExecuteJavascriptInMainFrame)
            {
                string script = @"(function(){ var element = ";

                // Check if it is an Id or a Class
                script += CheckClassId(selectorId);

                // Add behavior
                script += @"var option = document.createElement('option');
                            option.text = '" + text + @"';
                            option.value = '" + value + @"';
                            element.appendChild(option); })(); ";

                // Execute script async
                frame.EvaluateScriptAsync(script).ContinueWith(e =>
                {
                    if (e.Exception != null)
                        throw e.Exception;
                });
            }
        }

        public static void SelectOptionByText(string selectorId, string text)
        {
            // Check if can execute JS
            if (browser.CanExecuteJavascriptInMainFrame)
            {
                string script = @"(function(){ var element = ";

                // Check if it is an Id or a Class
                script += CheckClassId(selectorId);

                // Add behavior
                script += @"var children = [].slice.call(element.children);
                            children.forEach(function(item, index) {
                                if(item.text == '" + text + @"')
                                    element.selectedIndex = index;
                            }); 
                            })();";

                // Execute script async
                frame.EvaluateScriptAsync(script).ContinueWith(e =>
                {
                    if (e.Exception != null)
                        throw e.Exception;
                });
            }
        }

        public static void SelectOptionByValue(string selectorId, string value)
        {
            // Check if can execute JS
            if (browser.CanExecuteJavascriptInMainFrame)
            {
                string script = @"(function(){ var element = ";

                // Check if it is an Id or a Class
                script += CheckClassId(selectorId);

                // Add behavior
                script += @"var children = [].slice.call(element.children);
                            children.forEach(function(item, index) {
                                if(item.value == '" + value + @"')
                                    element.selectedIndex = index;
                            }); 
                            })();";

                // Execute script async
                frame.EvaluateScriptAsync(script).ContinueWith(e =>
                {
                    if (e.Exception != null)
                        throw e.Exception;
                });
            }
        }

        public static void SelectOptionByTextAndValue(string selectorId, string value, string text)
        {
            // Check if can execute JS
            if (browser.CanExecuteJavascriptInMainFrame)
            {
                string script = @"(function(){ var element = ";

                // Check if it is an Id or a Class
                script += CheckClassId(selectorId);

                // Add behavior
                script += @"var children = [].slice.call(element.children);
                            children.forEach(function(item, index) {
                                if(item.text == '" + text + @"' && item.value == '" + value + @"')
                                    element.selectedIndex = index;
                            }); 
                            })();";

                // Execute script async
                frame.EvaluateScriptAsync(script).ContinueWith(e =>
                {
                    if (e.Exception != null)
                        throw e.Exception;
                });
            }
        }

        public void SearchSelected(string summonerName)
        {
            Request.SummonerName = summonerName;

            bool response = MainWindow.RequestCurrentGameInfo();

            // Call JS funtion into window to collect all timers and start them DEBUG
            if (response)
            {
                // Check if can execute JS
                if (browser.CanExecuteJavascriptInMainFrame)
                {
                    // Add behavior
                    string script = @"window.configureCanvas();";

                    // Execute script async
                    frame.EvaluateScriptAsync(script).ContinueWith(e =>
                    {
                        if (e.Exception != null)
                            throw e.Exception;
                    });
                }
            }
        }
    }
}
