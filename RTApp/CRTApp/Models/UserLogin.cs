using System;

namespace CRTApp.Models
{
    public class UserLogin
    {
        public int Id { get; set; }
        public int FK_User { get; set; }
        public required string UserName { get; set; }
        public required string HashedPassword { get; set; }
    }
}