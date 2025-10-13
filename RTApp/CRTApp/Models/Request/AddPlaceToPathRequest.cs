using System;

namespace CRTApp.Models.Request
{
    public class AddPlaceToPathRequest
    {
        public required int PathId { get; set; }
        public required int PlaceId { get; set; }
        public required int Order { get; set; }
    }
}