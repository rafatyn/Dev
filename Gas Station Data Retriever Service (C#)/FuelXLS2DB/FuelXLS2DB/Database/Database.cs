using System.Data.SqlServerCe;
using System;
using System.IO;

namespace FuelXLS2DB.Database
{
    class Database
    {
        public SqlCeConnection Connection { get; private set; }
        public SqlCeCommand Command { get; private set; }

        public Database(bool reset = false)
        {
            if (!File.Exists(@"C:\Trabajo\Personal\FuelXLS2DB\GSDB.sdf")) {
                SqlCeEngine engine = new SqlCeEngine(@"Data Source=C:\Trabajo\Personal\FuelXLS2DB\GSDB.sdf;LCID=1110;Max Database Size=4091;");
                engine.CreateDatabase();
            }
            Connection = new SqlCeConnection(@"Data Source=C:\Trabajo\Personal\FuelXLS2DB\GSDB.sdf;LCID=1110;Max Database Size=4091;");
            Connection.Open();

            if (reset)
                ResetDatabase();

            Command = Connection.CreateCommand();
            Command.CommandText = @"SELECT * FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_NAME = 'FuelHistory'";
            SqlCeDataReader reader = Command.ExecuteReader();

            int count = 0;
            while (reader.Read()) { count++; }
            if (count < 1)
            {
                Command = Connection.CreateCommand();
                Command.CommandText = @"CREATE TABLE FuelHistory (
                                            Fecha               DATETIME,
                                            Provincia           NVARCHAR(255),
                                            Municipio           NVARCHAR(255),
                                            Localidad           NVARCHAR(255),
                                            CodigoPostal        INT,
                                            Direccion           NVARCHAR(255),
                                            Margen              NVARCHAR(1),
                                            Longitud            FLOAT,
                                            Latitud             FLOAT,
                                            Gasolina95          FLOAT,
                                            Gasolina98          FLOAT,
                                            GasoleoA            FLOAT,
                                            GasoleoAPlus        FLOAT,
                                            GasoleoB            FLOAT,
                                            BioEtanol           FLOAT,
                                            Biodiesel           FLOAT,
                                            GNC                 FLOAT,
                                            GNL                 FLOAT,
                                            GLP                 FLOAT,
                                            EsterMetilico       FLOAT,
                                            BioAlcohol          FLOAT,
                                            Rotulo              NVARCHAR(255),
                                            TipoVenta           NVARCHAR(1),
                                            Rem                 NVARCHAR(2),
                                            Horario             NVARCHAR(255))";
                Command.ExecuteNonQuery();
            }
        }

        private void ResetDatabase()
        {
            Command = Connection.CreateCommand();
            Command.CommandText = @"DROP TABLE FuelHistory";
            Command.ExecuteNonQuery();
        }

        public string CreateInsert(DateTime date, GasStation gas)
        {
            return string.Format(@" INSERT INTO FuelHistory VALUES ('{0}','{1}','{2}','{3}',{4},'{5}','{6}',{7},
                                    {8},{9},{10},{11},{12},{13},{14},{15},{16},{17},{18},
                                    {19},{20},'{21}','{22}','{23}','{24}');",
                                    date.ToString("MM/dd/yyyy HH:mm:ss"), gas.Provincia, gas.Municipio, gas.Localidad, 
                                    gas.CodigoPostal, gas.Direccion, gas.Margen, gas.Longitud, gas.Latitud, gas.Gasolina95,
                                    gas.Gasolina98, gas.GasoleoA, gas.GasoleoAPlus, gas.GasoleoB, gas.BioEtanol,
                                    gas.Biodiesel, gas.GNC, gas.GNL, gas.GLP, gas.EsterMetilico, gas.BioAlcohol,
                                    gas.Rotulo, gas.TipoVenta, gas.Rem, gas.Horario);
        }

        public void InsertMultipleRows(string[] rows)
        {
            using (Command = Connection.CreateCommand())
            {
                using (SqlCeTransaction trans = Connection.BeginTransaction())
                {
                    foreach (string row in rows)
                    {
                        if (row != null)
                        {
                            Command.CommandText = row;
                            Command.ExecuteNonQuery();
                        }
                    }

                    trans.Commit();
                }
            }
        }

        public void SetNulls()
        {
            using (Command = Connection.CreateCommand())
            {
                using (SqlCeTransaction trans = Connection.BeginTransaction())
                {
                    Command.CommandText = @"UPDATE FuelHistory SET Longitud = NULL WHERE Longitud = -1;";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET Latitud = NULL WHERE Latitud = -1;";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET Gasolina95 = NULL WHERE Gasolina95 = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET Gasolina98 = NULL WHERE Gasolina98 = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET GasoleoA = NULL WHERE GasoleoA = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET GasoleoAPlus = NULL WHERE GasoleoAPlus = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET GasoleoB = NULL WHERE GasoleoB = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET BioEtanol = NULL WHERE BioEtanol = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET Biodiesel = NULL WHERE Biodiesel = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET GNC = NULL WHERE GNC = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET GNL = NULL WHERE GNL = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET GLP = NULL WHERE GLP = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET EsterMetilico = NULL WHERE EsterMetilico = -1; ";
                    Command.ExecuteNonQuery();
                    Command.CommandText = @"UPDATE FuelHistory SET BioAlcohol = NULL WHERE BioAlcohol = -1; ";
                    Command.ExecuteNonQuery();

                    trans.Commit();
                }
            }
        }
    }
}