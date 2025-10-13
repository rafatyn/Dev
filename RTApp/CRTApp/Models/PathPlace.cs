using System;

namespace CRTApp.Models
{
    public class PathPlace
    {
        public int Id { get; set; }
        public int FK_Path { get; set; }
        public int FK_Place { get; set; }
        public int Order { get; set; }
    }
}