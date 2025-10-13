using System;

namespace CRTApp.Models
{
    public class UserSession
    {
        public Guid Id { get; set; }
        public int FK_User { get; set; }
        public DateTime ValidUntil { get; set; }
    }
}