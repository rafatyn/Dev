using System;

namespace CRTApp.Models
{
    public class User
    {
        public int Id { get; set; }
        public Guid Link { get; set; }
        public required string Name { get; set; }
    }
}