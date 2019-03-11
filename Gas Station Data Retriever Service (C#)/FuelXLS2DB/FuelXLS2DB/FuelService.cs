using ExcelDataReader;
using System;
using System.Data;
using System.IO;
using System.Net;
using System.ServiceProcess;
using System.Threading;
using System.Timers;

namespace FuelXLS2DB
{
    public class Constants 
    {
        public const string ExcelFilePath = @"C:\Users\Ayesa\Downloads\preciosEESS_es.xls";
        public const string ExcelFileUrl = @"http://www.geoportalgasolineras.es/resources/files/preciosEESS_es.xls";        
        public const int RowsPerTransaction = 1500;
    }

    public partial class FuelService : ServiceBase
    {
        public FuelService()
        {
            InitializeComponent();
        }

        protected override void OnStart(string[] args)
        {
            Thread.Sleep(10000);
            System.Timers.Timer Timer = new System.Timers.Timer();
            Timer.Elapsed += GetFuelData;
            Timer.Interval = 3600000;
            Timer.Enabled = true;
            Timer.AutoReset = true;

            GetFuelData(null, null);
        }

        private static void GetFuelData(Object source, ElapsedEventArgs e)
        {
            using (var client = new WebClient())
            {
                client.DownloadFile(Constants.ExcelFileUrl, Constants.ExcelFilePath);
            }

            using (FileStream stream = File.Open(Constants.ExcelFilePath, FileMode.Open, FileAccess.Read))
            {
                using (IExcelDataReader reader = ExcelReaderFactory.CreateReader(stream))
                {
                    DataSet spreadsheet = reader.AsDataSet();
                    DataTable page1 = spreadsheet.Tables[0];

                    DataRowCollection rows = page1.Rows;
                    string date = rows[0][1].ToString();

                    rows.RemoveAt(0); rows.RemoveAt(0); rows.RemoveAt(0); rows.RemoveAt(0);

                    Database.Database db = new Database.Database();
                    ushort count = 0;
                    string accRows = "";

                    foreach (DataRow row in rows)
                    {
                        GasStation gas = new GasStation(row);
                        accRows += db.CreateInsert(DateTime.Parse(date), gas);
                        count++;

                        if (count % Constants.RowsPerTransaction == 0)
                        {
                            db.InsertMultipleRows(accRows);
                            accRows = "";
                            count = 0;
                        }
                    }

                    if (count > 0)
                    {
                        db.InsertMultipleRows(accRows);
                    }

                    db.SetNulls();

                    db.Connection.Close();
                }
            }

            File.Delete(Constants.ExcelFilePath);
        }

        protected override void OnStop()
        {
        }
    }
}
