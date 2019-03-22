using System;
using System.Data;

namespace FuelXLS2DB
{
    class GasStation
    {
        // Direccion
        public string Provincia;
        public string Municipio;
        public string Localidad;
        public string CodigoPostal;
        public string Direccion;
        public string Margen;
        public string Longitud;
        public string Latitud;
        
        // Precios
        public string Gasolina95;
        public string Gasolina98;
        public string GasoleoA;
        public string GasoleoAPlus;
        public string GasoleoB;
        public string BioEtanol;
        public string Biodiesel;
        public string GNC;
        public string GNL;
        public string GLP;
        
        // Porcentajes
        public string EsterMetilico;
        public string BioAlcohol;
        
        // Info
        public string Rotulo;
        public string TipoVenta;
        public string Rem;
        public string Horario;

        public GasStation(DataRow row)
        {
            // Strings
            Provincia   = row[ 0].ToString().Replace("'", "#");
            Municipio   = row[ 1].ToString().Replace("'", "#");
            Localidad   = row[ 2].ToString().Replace("'", "#");
            Direccion   = row[ 4].ToString().Replace("'", "#");
            Margen      = row[ 5].ToString().Replace("'", "#");
            Rotulo      = row[20].ToString().Replace("'", "#");
            TipoVenta   = row[21].ToString().Replace("'", "#");
            Rem         = row[22].ToString().Replace("'", "#");
            Horario     = row[23].ToString().Replace("'", "#");

            // Numbers
            CodigoPostal    = row[ 3].ToString() == "" ? "NULL" : row[ 3].ToString();
            Longitud        = row[ 6].ToString() == "" ? "NULL" : row[ 6].ToString().Replace(",", ".");
            Latitud         = row[ 7].ToString() == "" ? "NULL" : row[ 7].ToString().Replace(",", ".");
            Gasolina95      = row[ 8].ToString() == "" ? "NULL" : row[ 8].ToString().Replace(",", ".");
            Gasolina98      = row[16].ToString() == "" ? "NULL" : row[16].ToString().Replace(",", ".");
            GasoleoA        = row[ 9].ToString() == "" ? "NULL" : row[ 9].ToString().Replace(",", ".");
            GasoleoAPlus    = row[12].ToString() == "" ? "NULL" : row[12].ToString().Replace(",", ".");
            GasoleoB        = row[10].ToString() == "" ? "NULL" : row[10].ToString().Replace(",", ".");
            BioEtanol       = row[11].ToString() == "" ? "NULL" : row[11].ToString().Replace(",", ".");
            Biodiesel       = row[13].ToString() == "" ? "NULL" : row[13].ToString().Replace(",", ".");
            GNC             = row[17].ToString() == "" ? "NULL" : row[17].ToString().Replace(",", ".");
            GNL             = row[18].ToString() == "" ? "NULL" : row[18].ToString().Replace(",", ".");
            GLP             = row[19].ToString() == "" ? "NULL" : row[19].ToString().Replace(",", ".");
            EsterMetilico   = row[14].ToString() == "" ? "NULL" : row[14].ToString().Replace(",", ".");
            BioAlcohol      = row[15].ToString() == "" ? "NULL" : row[15].ToString().Replace(",", ".");
        }
    }
}
