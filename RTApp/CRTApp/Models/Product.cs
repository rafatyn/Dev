using System;
using System.ComponentModel.DataAnnotations.Schema;

namespace CRTApp.Models
{
    public class Product
    {
        public int Id { get; set; }
        public Guid Link { get; set; }
        public required string Name { get; set; }
        public required string Description { get; set; }
        public float Price { get; set; }
        public int FK_Place { get; set; }
        public int Order { get; set; }
        public decimal Rating { get; set; }
        [NotMapped]
        public bool Liked { get; set; }
        [NotMapped]
        public bool Bookmarked { get; set; }
        [NotMapped]
        public string Image { get; set; }
    }
}