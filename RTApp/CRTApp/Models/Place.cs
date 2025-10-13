using System;
using System.ComponentModel.DataAnnotations.Schema;

namespace CRTApp.Models
{
    public class Place
    {
        public int Id { get; set; }
        public Guid Link { get; set; }
        public required string Name { get; set; }
        public decimal Longitude { get; set; }
        public decimal Latitude { get; set; }
        public string GoogleId { get; set; }
        [NotMapped]
        public int Order { get; set; }
        [NotMapped]
        public string Image { get; set; }
    }
}