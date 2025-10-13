using System;

namespace CRTApp.Models.Request
{
    public class CreatePlaceRequest
    {
        public required string Name { get; set; }
        public required decimal Longitude { get; set; }
        public required decimal Latitude { get; set; }
        public required string GoogleId { get; set; }
    }
}