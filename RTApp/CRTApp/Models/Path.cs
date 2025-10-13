using System;
using System.ComponentModel.DataAnnotations.Schema;

namespace CRTApp.Models
{
    public class Path
    {
        public int Id { get; set; }
        public Guid Link { get; set; }
        public required string Name { get; set; }
        public string Location { get; set; }
        public int Rating { get; set; }
        public int EstimatedPrice { get; set; }
        public string Currency { get; set; }
        [NotMapped]
        public bool Liked { get; set; }
        [NotMapped]
        public string Image { get; set; }
    }
}