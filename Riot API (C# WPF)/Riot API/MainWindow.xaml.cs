using CefSharp;
using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Reflection;
using System.Text;
using System.Windows;
using System.Windows.Input;

namespace Riot_API
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            // Enable Wcf to allow Register JS Objects
            CefSharpSettings.WcfEnabled = true;
            CefSharpSettings.WcfTimeout = TimeSpan.Zero;
        }

        public static bool RequestCurrentGameInfo()
        {
            CurrentGame currentGameWindow;
            try
            {
                currentGameWindow = new CurrentGame();
                return true;
            }
            catch (WebException exeption)
            {
                MessageBox.Show(exeption.Message + '\n' + Request.LastError, exeption.Status.ToString(), MessageBoxButton.OK, MessageBoxImage.Warning, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
                return false;
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            // Load HTML file in the UI
            LoadHTML("App.html");

            // Set KeyBoard focus to Browser
            Keyboard.Focus(Browser);

            // Assign method to the event
            Browser.FrameLoadEnd += FrameLoaded;

            // Assign custom right click menu
            Browser.MenuHandler = new CustomMenuHandler();
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            Console.WriteLine("Number of request done: {0}", Request.NumberRequest);

            Browser.Dispose();
            Cef.Shutdown();

            try
            {
                Process[] proc = Process.GetProcessesByName("CefSharp.BrowserSubprocess");
                foreach(Process process in proc)
                {
                    process.Kill();
                }
            }
            catch(Exception exeption)
            {
                MessageBox.Show(exeption.Message, "", MessageBoxButton.OK, MessageBoxImage.Error, MessageBoxResult.OK, MessageBoxOptions.DefaultDesktopOnly);
            }
        }

        private void FrameLoaded(object sender, FrameLoadEndEventArgs e)
        {
            // Load HTML UI Handler with the browser
            UIHandler.LoadBrowser(Browser);

            // Add option to the region select
            foreach (string region in Request.RegionNames)
            {
                UIHandler.SelectorAddOption(".region-selector", "", region);
            }

            // Preselect EUW option
            UIHandler.SelectOptionByText(".region-selector", "EUW");

            // Ask for the selected option
            UIHandler.GetSelectedOption(".region-selector", (x) =>
            {
                // Check if exist
                for (int i = 0; i < Request.RegionNames.Length; i++)
                {
                    // If exist load the requested region API url
                    if (Request.RegionNames[i] == x.Result.Result.ToString())
                    {
                        //Request.SelectedRegion = Request.RegionServer[i];
                        Request.SelectedRegionServer = Request.RegionServer[i];
                        Request.SelectedRegionName = Request.RegionNames[i];
                        break;
                    }
                }

                // Init Request Handler
                Request.Init();
            });
        }

        private void LoadHTML(string url)
        {
            // Get file directory to take it as root
            string fileDir = NormalizeToAssemblyPath(url
                .Substring(0, url.LastIndexOf('/') == -1 ?
                (url.LastIndexOf('\\') == -1 ? 0 : url.LastIndexOf('\\')) : url.LastIndexOf('/')));

            // Get html file from assembly
            url = "WebResources." + NormalizeToAssemblyPath(url);
            string html = GetAssemblyFileUTF8(url);

            // Get referenced css into html from assembly
            while (html.Contains("<link type=\"text/css\" rel=\"stylesheet\""))
            {
                // Find out the position of the css reference
                int beginCssLink = html.IndexOf("<link type=\"text/css\" rel=\"stylesheet\"");
                int endCssLink = html.IndexOf("/>", beginCssLink) + 2;
                int beginCssUrl = html.IndexOf("href", beginCssLink) + 6;

                // Get css file from assembly
                string cssUrl = html.Substring(beginCssUrl, html.IndexOf("\"", beginCssUrl) - beginCssUrl);
                cssUrl = "WebResources." + fileDir + NormalizeToAssemblyPath(cssUrl);

                string css = GetAssemblyFileUTF8(cssUrl);

                // Remove css reference
                html = html.Substring(0, beginCssLink - 1) + html.Substring(endCssLink + 1, html.Length - endCssLink - 1);

                // Add css to html
                html = html.Insert(html.IndexOf(@"</head>"), string.Format(@"<style type=""text/css"">{0}</style>", css.Substring(0, css.Length - 1)));
            }

            while (html.Contains("<script src=\""))
            {
                // Find out the position of the js reference
                int beginJsLink = html.IndexOf("<script src=\"");
                int endJsLink = html.IndexOf("/>", beginJsLink) + 2;
                int beginJsUrl = html.IndexOf("src", beginJsLink) + 5;

                // Get js file from assembly
                string jsUrl = html.Substring(beginJsUrl, html.IndexOf("\"", beginJsUrl) - beginJsUrl);
                jsUrl = "WebResources." + fileDir + NormalizeToAssemblyPath(jsUrl);

                string js = GetAssemblyFileUTF8(jsUrl);

                // Remove js reference
                html = html.Substring(0, beginJsLink - 1) + html.Substring(endJsLink + 1, html.Length - endJsLink - 1);

                // Add js to html
                html = html.Insert(html.IndexOf(@"</body>"), string.Format(@"<script>{0}</script>", js.Substring(0, js.Length - 1)));
            }

            // Encode the html file
            string base64EncodedHtml = Convert.ToBase64String(Encoding.UTF8.GetBytes(html));

            // Load the HTML once the BrowserInitializedEvent is fired
            Browser.IsBrowserInitializedChanged += (sender, e) =>
            {
                Browser.Load("data:text/html;base64," + base64EncodedHtml);
            };
        }

        private string NormalizeToAssemblyPath(string path)
        {
            return path.Replace('/', '.').Replace('\\', '.');
        }

        private string GetAssemblyFileUTF8(string path)
        {
            // Get assembly file
            Assembly assembly = Assembly.GetExecutingAssembly();
            Stream textStream = assembly.GetManifestResourceStream("Riot_API." + path);
            byte[] htmlBuffer = new byte[textStream.Length + 1];
            long bytesReaded = 0;

            // Load the file into a stream
            while (bytesReaded < textStream.Length)
            {
                if (textStream.Length >= Int32.MaxValue)
                {
                    textStream.Read(htmlBuffer, 0, Int32.MaxValue);
                    bytesReaded += Int32.MaxValue;
                }
                else
                {
                    textStream.Read(htmlBuffer, 0, (int)(textStream.Length - bytesReaded));
                    bytesReaded += (int)(textStream.Length - bytesReaded);
                }
            }

            // Convert the stream to UFT8 string
            return System.Text.Encoding.UTF8.GetString(htmlBuffer);
        }
    }
}
