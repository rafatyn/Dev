using System;

namespace CRTApp.Models
{
    public class UserBookmark
    {
        public int Id { get; set; }
        public int FK_User { get; set; }
        public string Type { get; set; }
        public int? FK_Parent { get; set; }
        public int FK_Record { get; set; }
    }
}