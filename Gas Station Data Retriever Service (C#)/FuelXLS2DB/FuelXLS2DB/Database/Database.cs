using System.Data.SQLite;
using System;

namespace FuelXLS2DB.Database
{
    class Database
    {
        public SQLiteConnection Connection { get; private set; }
        public SQLiteCommand Command { get; private set; }

        public Database(bool reset = false)
        {
            Connection = new SQLiteConnection(@"Data Source=C:\Users\Ayesa\Downloads\database.sqlite;Version=3;");
            Connection.Open();

            if (reset)
                ResetDatabase();

            Command = Connection.CreateCommand();
            Command.CommandText = @"CREATE TABLE IF NOT EXISTS FuelHistory (
                                        Fecha               DATETIME,
                                        Provincia           VARCHAR(255),
                                        Municipio           VARCHAR(255),
                                        Localidad           VARCHAR(255),
                                        CodigoPostal        INT,
                                        Direccion           VARCHAR(255),
                                        Margen              VARCHAR(1),
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
                                        Rotulo              VARCHAR(255),
                                        TipoVenta           VARCHAR(1),
                                        Rem                 VARCHAR(2),
                                        Horario             VARCHAR(255))";
            Command.ExecuteNonQuery();
        }

        private void ResetDatabase()
        {
            Command = Connection.CreateCommand();
            Command.CommandText = @"DROP TABLE FuelHistory";
            Command.ExecuteNonQuery();
        }

        public string CreateInsert(DateTime date, GasStation gas)
        {
            return string.Format(@"INSERT INTO FuelHistory VALUES ('{0}','{1}','{2}','{3}','{4}','{5}','{6}','{7}',
                                    '{8}','{9}','{10}','{11}','{12}','{13}','{14}','{15}','{16}','{17}','{18}',
                                    '{19}','{20}','{21}','{22}','{23}','{24}');",
                                    date, gas.Provincia, gas.Municipio, gas.Localidad, gas.CodigoPostal,
                                    gas.Direccion, gas.Margen, gas.Longitud, gas.Latitud, gas.Gasolina95,
                                    gas.Gasolina98, gas.GasoleoA, gas.GasoleoAPlus, gas.GasoleoB, gas.BioEtanol,
                                    gas.Biodiesel, gas.GNC, gas.GNL, gas.GLP, gas.EsterMetilico, gas.BioAlcohol,
                                    gas.Rotulo, gas.TipoVenta, gas.Rem, gas.Horario);
        }

        public void InsertMultipleRows(string rows)
        {
            using(Command = Connection.CreateCommand()){
                using (SQLiteTransaction trans = Connection.BeginTransaction())
                {
                    Command.CommandText = rows;
                    Command.ExecuteNonQuery();

                    trans.Commit();
                }
            }
        }

        public void SetNulls()
        {
            using (Command = Connection.CreateCommand())
            {
                using (SQLiteTransaction trans = Connection.BeginTransaction())
                {
                    Command.CommandText = @"UPDATE FuelHistory SET Longitud = NULL WHERE Longitud = -1;
                                            UPDATE FuelHistory SET Latitud = NULL WHERE Latitud = -1;
                                            UPDATE FuelHistory SET Gasolina95 = NULL WHERE Gasolina95 = -1;
                                            UPDATE FuelHistory SET Gasolina98 = NULL WHERE Gasolina98 = -1;
                                            UPDATE FuelHistory SET GasoleoA = NULL WHERE GasoleoA = -1;
                                            UPDATE FuelHistory SET GasoleoAPlus = NULL WHERE GasoleoAPlus = -1;
                                            UPDATE FuelHistory SET GasoleoB = NULL WHERE GasoleoB = -1;
                                            UPDATE FuelHistory SET BioEtanol = NULL WHERE BioEtanol = -1;
                                            UPDATE FuelHistory SET Biodiesel = NULL WHERE Biodiesel = -1;
                                            UPDATE FuelHistory SET GNC = NULL WHERE GNC = -1;
                                            UPDATE FuelHistory SET GNL = NULL WHERE GNL = -1;
                                            UPDATE FuelHistory SET GLP = NULL WHERE GLP = -1;
                                            UPDATE FuelHistory SET EsterMetilico = NULL WHERE EsterMetilico = -1;
                                            UPDATE FuelHistory SET BioAlcohol = NULL WHERE BioAlcohol = -1;";
                    Command.ExecuteNonQuery();

                    trans.Commit();
                }
            }
        }
    }
}